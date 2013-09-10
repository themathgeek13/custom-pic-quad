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

//***************************************************
// Telemetry data exchange format
//***************************************************
//{
struct
	{
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
	// Orientation Data change rate (true derivative)
	//-----------------------------------------------
	float	RollDer;			
	float	PitchDer;			
	float	YawDer;			
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
	float	DRTot;
	//-------------
	float	DPProp;
	float	DPDiff;
	float	DPInt;
	float	DPTot;
	//-------------
	float	DYProp;
	float	DYDiff;
	float	DYInt;
	float	DYTot;
	//-----------------------------------------------
	// Motor Control Data
	//-----------------------------------------------
	float	Throttle;		// Common throttle setting
	//-----------------------------------------------
	float	Voltage;		// Battery Voltage	
	//----------------------
	} TM;		// Telemetry data structure
//}
//=====================================================

int main(void)
	{
	//*******************************************************************
	// Initialization of HW components/modules
	//===================================================================
	//{
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
	//}
	//===================================================================

	//*******************************************************************
	// Quadrocopter control variables
	//-------------------------------------------------------------------
	ulong		StartTS		= 0;
	ulong		StepTS;

	RCData		RCNative;		// Control input from Receiver
	RCData		RC;				// Smoothed control input used in all
								// control calculations
	
	DCMData		IMU;			// Orientation data from DCM
	
	MCMData		MC;				// Motor control Variables

	//==================================================================
	// Wait for the Receiver ARMing: Throttle should go up and then down
	//------------------------------------------------------------------
	BLIAsyncMorse(	"R", 1);
	RCArm();	
	//==================================================================
	// Initialize motion sensor - rotation rate baseline established at
	// this time - QUAD should be motionless!!!
	//------------------------------------------------------------------
	BLIAsyncMorse(	"I", 1);
	if (MPUInit(0, 3))	// Initialize motion Sensor
						// 1 kHz/(0+1) = 1000 Hz (1ms)
						// DLPF=3 => Bandwidth 44 Hz (delay: 4.9 msec)
		BLIDeadStop("EA", 2);
	//==================================================================

Re_Start:
	//==================================================================
	BLIAsyncMorse("O", 1);			// dit-dit-dit
	RCReadWhenReady(&RCNative);		// Get reading from receiver
	while 	(
				0 == RCNative.Control 
			|| 
				RCNative.Throttle > 0.1
			)
		{
		RCReadWhenReady(&RCNative);	// Get next reading from receiver
		}
	//==================================================================
	BLIAsyncMorse("S", 1);			// dah-dah-dah
	MPUAsyncStop();
	if (MPUCalibrate() != MPU_OK)	
		// Gyro Calibration filed
		BLIDeadStop("EA", 2);
	BLIAsyncStop();
	//==================================================================
	// Start IMU and wait until orientation estimate stabilizes
	//------------------------------------------------------------------
	BLIAsyncMorse(	"I", 1);
	IMUInit();
	//==================================================================
	QCMReset();			// Initialize (reset) QCM variables
	//==================================================================
	BLIAsyncStop();
	//==================================================================

	//******************************************************************
	// Control variables used to smooth RC receiver data
	//------------------------------------------------------------------
	// Reset Smothed RC data 
	//-------------------------------------------------------------------
	RC.Roll		= 0.0;
	RC.Pitch	= 0.0;
	RC.Yaw		= 0.0;
	//------------------------
	RC.Throttle	= 0.0;
	//------------------------
	RC.Control	= RCNative.Control;
	//-------------------------------------------------------------------
	
	//*******************************************************************
	// Quadrocopter Control Loop
	//-------------------------------------------------------------------
	BLISignalON();
	while (1)
		{
		//============================================================
		// Read commands from receiver - non-blocking call!
		// (we will get out of this call even if connection to the
		// receiver is lost!)
		//============================================================
		//{
		if (RCRead(&RCNative))
			{
			//------------------------------------------------------------
			// Normalize Roll, Pitch, and Yaw control
			// settings from RC Receiver 		
			//------------------------------------------------------------
			RCSetLNRate(&RCNative);	// Apply linear rate
//			RCSetSQRate(&RCNative);	// Apply Quadratic rate
			}
		//============================================================
		// Smooth RC data 
		//------------------------------------------------------------
		// Roll and pitch are smoothed with the IIR(32)
		//------------------------------------------------------------
		RC.Roll		= (RC.Roll		* 31.0	+ RCNative.Roll		) * 0.03125;	// 1/32 = 0.03125
		RC.Pitch	= (RC.Pitch		* 31.0 	+ RCNative.Pitch	) * 0.03125;
		//------------------------------------------------------------
		// Yaw is smoothed with the IIR(8) (it is further smoothed
		// through integration in the QCM Step routine)
		//------------------------------------------------------------
		RC.Yaw		= (RC.Yaw		* 7 	+ RCNative.Yaw		) * 0.12500;	// 1/8 = 0.125
		//------------------------------------------------------------
		// Throttle is smoothed with the IIR(4) 
		//------------------------------------------------------------
		RC.Throttle	= (RC.Throttle	* 3		+ RCNative.Throttle	) * 0.25000;	// 1/4 = 0.25
		//-----------------------------------------
		RC.Control	= RCNative.Control;
		//}
		//============================================================


		//============================================================
		// Implement Motor Cut-Off if RC Control is LOW
		//============================================================
		//{
		if (0 == RC.Control)
			{
			// Yes, Control is reliably low!
			//--------------------------------------------
			// Override motor control
			//--------------------------------------------
			MC.F = MC.B = MC.L = MC.R = 0;
			MCMSet(&MC);
			//--------------------------------------------
			// Reset Timing series
			StartTS = 0;
			//--------------------------------------------
			// Flight terminated, post EOF to Data Logger
			//--------------------------------------------
			TMRDelay(10);	// Wait for pipe to clear
			UARTPostIfReady( NULL, 0);
			// ... and again - to be sure!
			TMRDelay(10);	// Wait for pipe to clear
			UARTPostIfReady( NULL, 0);
			//----------------------------------
			goto Re_Start;
			}
		//}
		//============================================================

		//============================================================
		// Obtain and process battery charge status
		//============================================================
		float BatteryCharge	= QCMBatteryMgmt();	
		if (BatteryCharge < 0.35 /* < 35% */ )
			{
			float MaxLevel = 2.0 * BatteryCharge;
			if (RC.Throttle > MaxLevel)
				RC.Throttle = MaxLevel;
			}
		//============================================================

		//============================================================
		// Read current orientation from the IMU
		// with sensors' measurements
		// (non-blocking call)
		//============================================================
		TMRDelay(9);
		//-----------------------------------------
		if (IMU_OK == IMUGetUpdate(&IMU))
			{
			// Calculate motor control based
			// upon IMU data
			QCMPerformStep(&RC, &IMU, &MC);
			}
		else
			{
			// IMU Failed to provide update -
			// set Motor Control to native throttle
			MC.F = MC.B = MC.L = MC.R = RC.Throttle;
			}
		//============================================================

		//*****************************************
		// Implement Motor Cut-Off if model is
		// dangerously tilted (> 70 degrees) while
		// RC Throttle is low - to protect props 
		//----------------------------------------
		if (IMU.Incl <= 0.342 && RC.Throttle <= 0.4)
			{
			// Override motor control
			MC.F = MC.B = MC.L = MC.R = 0;
			}
		//----------------------------------------

		//*****************************************
		// Update motor control
		//*****************************************
		MCMSet(&MC);
		//-----------------------------------------
		
		//===========================================================
		// Load and post telemetry data (non-blocking call)
		//-----------------------------------------------------------
		//{
		StepTS =  TMRGetTS();
		//-----------------------------------------
		if (0 == StartTS)
			// Time stamp of cycle start!
			StartTS =  StepTS;
		//-----------------------------------------
		TM.TS			= StepTS - StartTS;
		//----------------------
		TM.Roll			= IMU.Roll;
		TM.Pitch		= IMU.Pitch;
		TM.Yaw			= IMU.Yaw;
		TM.Inclination	= IMU.Incl;
		//----------------------
		TM.RollDer		= QSD.RollDer;
		TM.PitchDer		= QSD.PitchDer;
		TM.YawDer		= QSD.YawDer;
		//----------------------
		TM.RC_Throttle	= RC.Throttle;
		TM.RC_Roll		= RC.Roll;
		TM.RC_Pitch		= RC.Pitch;
		TM.RC_Yaw		= RC.Yaw;
		//----------------------
		TM.DRProp		= QSD.DeltaRollProp;
		TM.DRDiff		= QSD.DeltaRollDiff;
		TM.DRInt		= QSD.DeltaRollInt;
		TM.DRTot		= QSD.DeltaRoll;
		//-------------
		TM.DPProp		= QSD.DeltaPitchProp;
		TM.DPDiff		= QSD.DeltaPitchDiff;
		TM.DPInt		= QSD.DeltaPitchInt;
		TM.DPTot		= QSD.DeltaPitch;
		//-------------
		TM.DYProp		= QSD.DeltaYawProp;
		TM.DYDiff		= QSD.DeltaYawDiff;
		TM.DYInt		= QSD.DeltaYawInt;
		TM.DYTot		= QSD.DeltaYaw;
		//----------------------
		TM.Throttle		= QSD.Throttle;				// Real Throttle
		//----------------------
		TM.Voltage 		= QSD.Voltage;

		//}
		//===========================================================
		UARTPostIfReady( (unsigned char *) &TM, sizeof(TM)	);
		//===========================================================

		}
	//*******************************************************************
	return 1;
	}






