#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "MCM\MCM.h"
#include "RC\RC.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "UART\UART.h"
#include "DCM\DCM.h"
#include "IMU\IMU.h"

#include "QCM\QCM.h"
#include "QCM\QCMStepData.h"		// Needed for Telemetry data

struct
	{
	//***********************************************
	// Telemetry data exchange format
	//***********************************************
	ulong	TS;				// Timestamp (ticks)
	//-----------------------------------------------
	// Orientation Data
	//-----------------------------------------------
	float	Roll;			
	float	Pitch;			
	float	Yaw;			
	//-----------------		
	float	Inclination;			
	//-----------------------------------------------
	// Orientation Data change rate
	//-----------------------------------------------
	float	RollRate;			
	float	PitchRate;			
	float	YawRate;			
	//-----------------------------------------------
	// Control Data
	//-----------------------------------------------
	float	RC_Throttle;
	float	RC_Roll;
	float	RC_Pitch;
	float	RC_Yaw;
	//-----------------------------------------------
	// RC Yaw integral (target Yaw)
	//-----------------------------------------------
	float	RC_Yaw_Int;		// RC Yaw integral
	//-----------------------------------------------
	// QCM Control Data
	//-----------------------------------------------
	float	DRProp;
	float	DRDiff;
	float	DRInt;
	//-------------
	float	DPProp;
	float	DPDiff;
	float	DPInt;
	//-------------
	float	DYProp;
	float	DYDiff;
	//-----------------------------------------------
	// Motor Control Data
	//-----------------------------------------------
	float	Throttle;		// Common throttle setting
	//-----------------------------------------------
	float	MC_Front;		
	float	MC_Back;
	float	MC_Left;		
	float	MC_Right;
	//-----------------------------------------------
	float	Voltage;		// Battery Voltage	
	//----------------------
	} TM;		// Telemetry data structure
//=====================================================


int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	BLIAsyncMorse("S", 1);	// dot-dot-dot
	MCMInitT(2.5, 2500);	// Initialize Motor Control for PPM with setting
							// Throttle to HIGH for delay interval to let ESC
							// capture Throttle range
	BLIAsyncStop();
	//--------------------------
	ADCInit(3);			// Initialize ADC to control battery
	//--------------------------
	RCInit(4);			// Initialize Receiver interface with Priority=4
	//--------------------------
	I2CInit(5, 1);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	UARTInitTX(6, 350);	// Initialize UART1 for TX on IPL=6 at 
						// BaudRate =   48	=>   115,200 bps	- ZigBEE
						//--------------------------------------
						// BaudRate =  100	=>   250,000 bps
						// BaudRate =  200	=>   500,000 bps
						// BaudRate =  250	=>   625,000 bps
						// BaudRate =  350	=>   833,333 bps	- SD Logger
						// BaudRate =  500	=> 1,250,000 bps
						// BaudRate = 1000	=> 2,500,000 bps
	//*******************************************************************
	BLISignalON();
	TMRDelay(2000); 	// Wait for extra 2 sec - to let ESC arm...
						// (finish the song :) )
	BLISignalOFF();
	//==================================================================
	// Wait for the Receiver ARMing: Throttle should go up and then down
	//------------------------------------------------------------------
	BLIAsyncMorse(	"R", 1);
	RCArm();	
	BLIAsyncStop();
	//==================================================================
	// Initialize motion sensor - rotation rate baseline established at
	// this time - QUAD should be motionless!!!
	//------------------------------------------------------------------
	if (MPUInit(0, 3))	// Initialize motion Sensor
						// 1 kHz/(0+1) = 1000 Hz (1ms)
						// DLPF=3 => Bandwidth 44 Hz (delay: 4.9 msec)
		BLIDeadStop("EA", 2);
	//==================================================================
	// Start IMU and wait until orientation estimate stabilizes
	//------------------------------------------------------------------
	BLIAsyncMorse(	"I", 1);	// dot-dot
	IMUInit();
	BLIAsyncStop();
	//------------------------------------------------------------------
	QCMReset();			// Initialize (reset) QCM integral variables
	//==================================================================


	//*******************************************************************
	// Quadrocopter control variables
	//-------------------------------------------------------------------
	ulong		StartTS		= 0;
	ulong		StepTS;

	uint		IsCutOff	= 0;

	RCData		RC;				// Control input from Receiver
	DCMData		IMU;			// Orientation data from DCM
	MCMData		MC;				// Motor control Variables

	//*******************************************************************
	// Quadrocopter Control Loop
	//-------------------------------------------------------------------
	while (1)
		{
		BLISignalON();
		//=========================================
		// Read commands from receiver - blocking call!
		// (we will get out of this call even if con-
		// nection to the receiver is lost!)
		//-----------------------------------------
		RCReadWhenReady(&RC);
		//-----------------------------------------
		// Normalize Roll, Pitch, and Yaw control
		// settings from RC Receiver 		
		//-----------------------------------------
		RCSetLNRate(&RC);	// Apply linear rate
//		RCSetSQRate(&RC);	// Apply Quadratic rate
		//=========================================

		//=========================================
		// Read current orientation from the IMU
		// with sensors' measurements
		// (non-blocking call)
		//-----------------------------------------
		IMUGetUpdate(&IMU	);
		//=========================================

		//=========================================
		// Obtain and process battery charge status
		//-----------------------------------------
		float BatteryCharge	= QCMBatteryMgmt();	
		if (BatteryCharge < 0.3 /* < 30% */ )
			{
			float MaxLevel = 2.0 * BatteryCharge;
			if (RC.Throttle > MaxLevel)
				RC.Throttle = MaxLevel;
			}
		//=========================================

		//*****************************************
		// Calculate motor control
		//*****************************************
		QCMPerformStep(&RC, &IMU, &MC);

		//*****************************************
		// Implement Motor Cut-Off if RC Control is LOW
		//----------------------------------------
		if (0 == RC.Control)
			{
			// Override motor control
			MC.F = MC.B = MC.L = MC.R = 0;
			// Reset Timing series
			StartTS = 0;
			//----------------------------------
			if (0 == IsCutOff)
				{
				IsCutOff = -1;
				BLIAsyncMorse("O", 1);	// doh-doh-doh
				}
			}
		else
			{
			if (IsCutOff)
				{
				IsCutOff = 0;
				BLIAsyncStop();
				}
			}

		//*****************************************
		// Implement Motor Cut-Off if model is
		// dangerously tilted (> 70 degrees)while
		// RC Throttle is low to protect props 
		//----------------------------------------
		if (IMU.Incl <= 0.342 && RC.Throttle <= 0.4)
			{
			// Override motor control
			MC.F = MC.B = MC.L = MC.R = 0;
			}
		//------------------------------------------------------------

		//*****************************************
		// Update motor control
		//*****************************************
		MCMSet(&MC);
		//-----------------------------------------

		if (0 == RC.Control)
			{
			// Flight terminated, post EOF to Logger
			UARTPostIfReady( NULL, 0);
			}
		else
			{
			//=========================================
			// Finalize load and post telemetry data
			// (non-blocking call)
			//-----------------------------------------
			StepTS =  TMRGetTS();
			//-----------------------------------------
			if (0 == StartTS)
				// Time stamp of cycle start!
				StartTS =  StepTS;
	
			//===========================================================
			// Store telemetry
			//-----------------------------------------------------------
			//{
			TM.TS			= StepTS - StartTS;
			//----------------------
			TM.Roll			= IMU.Roll;
			TM.Pitch		= IMU.Pitch;
			TM.Yaw			= IMU.Yaw;
			TM.Inclination	= IMU.Incl;					
			//----------------------
			TM.RollRate		= IMU.RotationRateBF.X;
			TM.PitchRate	= IMU.RotationRateBF.Y;
			TM.YawRate		= IMU.RotationRateBF.Z;
			//----------------------
			TM.RC_Throttle	= RC.Throttle;
			TM.RC_Roll		= RC.Roll;
			TM.RC_Pitch		= RC.Pitch;
			TM.RC_Yaw		= RC.Yaw;
			//----------------------
			TM.RC_Yaw_Int	= QSD.RCYawInt;
			//----------------------
			TM.DRProp		= QSD.DeltaRollProp;
			TM.DRDiff		= IMU.RotationRateEF.X;		// QSD.DeltaRollDiff;
			TM.DRInt		= QSD.DeltaRollInt;
			//-------------
			TM.DPProp		= QSD.DeltaPitchProp;
			TM.DPDiff		= IMU.RotationRateEF.Y;		// QSD.DeltaPitchDiff;
			TM.DPInt		= QSD.DeltaPitchInt;
			//-------------
			TM.DYProp		= QSD.DeltaYawProp;
			TM.DYDiff		= IMU.RotationRateEF.Z;		// QSD.DeltaYawDiff;
			//----------------------
			//----------------------
			TM.Throttle		= QSD.Throttle;				// Real Throttle
			TM.MC_Front		= MC.F;
			TM.MC_Back		= MC.B;
			TM.MC_Left		= MC.L;						
			TM.MC_Right		= MC.R;						
			//----------------------
			TM.Voltage 		= QSD.Voltage;
			//}
			//===========================================================
			UARTPostIfReady( (unsigned char *) &TM, sizeof(TM)	);
			}
		}
	//*******************************************************************
	return 1;
	}






