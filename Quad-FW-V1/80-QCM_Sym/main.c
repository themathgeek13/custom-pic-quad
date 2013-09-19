#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "MCM\MCM.h"
#include "RC\RC.h"
#include "RC\RCSym.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "UART\UART.h"
#include "DCM\DCM.h"
#include "IMU\IMU.h"

#include "QCM\QCM.h"
#include "QCM\QCMStepData.h"

#include "DBG\DBG.h"

struct
	{
	// Telemetry data exchange format
	//-----------------------------------------------
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
	float	SetPoint;		// Set Point - from RC
	float	Error;			// Error
	//----------------------
	float	Omega;			// Rotational Speed
	//----------------------
	float	Prop;			// Proportional component
	float	Diff;			// Differential component
	float	Int;			// Integral component
	//----------------------
	float	Total;			// Total Throttle adjustment
	//----------------------
	float	ErrSum;			// Accumulated error sum
	//----------------------
	float	RCThrottle;		// Common throttle setting from RC
	float	MCThrottle;		// Common throttle setting - after correction
	//----------------------
	float	MCLeft;			// 
	float	MCRight;		// 
	//----------------------
	float	Battery;		// Battery Voltage	
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
	UARTInitTX(6, 350);	// Initialize UART1 for TX on IPL=6 at: 
						// BaudRate =  1	=> 	   2,400 bps
						// BaudRate =  2	=>     4,800 bps
						// ...
						// BaudRate = 48	=> 	 115,200 bps	- ZigBEE
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
	// Wait for the Receiver ARMing for Simulation run:
	// Ch5 goes to "0" and then back to "1"
	//------------------------------------------------------------------
Re_Arm:
	BLIAsyncMorse("R", 1);	// dot-doh-dot
	RCSymArm();	
	BLIAsyncStop();
	//==================================================================
	// Initialize motion sensor - rotation rate baseline established at
	// this time - QUAD should be motionless!!!
	// NOTE: Happens only on the FIRST call, all subsequent: just NOP
	//------------------------------------------------------------------
	BLIAsyncMorse(	"E", 1);
	//------------------------------------------------------------------
	if (MPUInit(0, 3))	// Initialize MPU - 1 kHz/(1) (1000 Hz, 1ms)
						// DLPF = 3 => Bandwidth 44 Hz (delay: 4.9 msec)
	
		BLIDeadStop("EA", 2);
	//------------------------------------------------------------------
	// Start IMU and wait until orientation estimate stabilizes
	//------------------------------------------------------------------
	IMUInit();
	//------------------------------------------------------------------
	BLIAsyncStop();
	//==================================================================
	QCMReset();		// Reset Step calculation variables
	//==================================================================


	//*******************************************************************
	// Simulation variables
	//-------------------------------------------------------------------
	ulong		StartTS;

	RCData		RC;				// Control input from Receiver
	DCMData		IMU;			// Orientation data from DCM
	MCMData		MC;				// Motor control Variables

	//*******************************************************************
	// Simulation Main Loop
	//-------------------------------------------------------------------
	RCSymReset();	// Re-set simulation sequence
	RC.Control	= 1;
	RC.Pitch	= 0;
	RC.Roll		= 0;
	RC.Yaw		= 0;
	RC.Throttle	= 0;
	//---------------------------------------------
	StartTS 	= TMRGetTS();
	//---------------------------------------------
	while (1)
		{
		//=========================================
		// Read commands from receiver - non-blocking
		// call!
		// (we will get out of this call even if con-
		// nection to the receiver is lost!)
		//-----------------------------------------
		if (RCSymRead(&RC))
			{
			//-----------------------------------------
			// New control sample obtained from Receiver
			//-----------------------------------------
			// As we are testing just Roll here, we may
			// nullify other control parameters
			//-----------------------------------------
			RC.Pitch = 0.0;
			RC.Yaw	 = 0.0;
			//-----------------------------------------
			// Normalize Roll, Pitch, and Yaw control
			// settings from RC Receiver 		
			//-----------------------------------------
			RCSetSymRate(&RC);	// Apply simulator rate
//			RCSetLNRate(&RC);	// Apply linear rate
//			RCSetSQRate(&RC);	// Apply Quadratic rate
			}
		//=========================================

		//=========================================
		// Implement Motor Cut-Off if RC Control is LOW
		//-----------------------------------------
		if (0 == RC.Control)
			{
			MC.F = MC.B = MC.L = MC.R = 0;
			MCMSet(&MC);
			//----------------------------------
			// Test terminated, post EOF to Logger
			UARTPostWhenReady( NULL, 0);
			//----------------------------------
			// Re-Start cycle
			//----------------------------------
			goto Re_Arm;		// Wait for next reading
			}
		//=========================================


		//=========================================
		// Limit throttle to "flying" conditions
		//=========================================
		if (RC.Throttle < 0.5)
			RC.Throttle = 0.5;
		//-----------------------------------------
		if (RC.Throttle > 0.6)
			RC.Throttle = 0.6;
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

		//=========================================
		// Read current orientation from the IMU
		// with sensors' measurements
		// (non-blocking call)
		//=========================================
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
		
//		MC.F	= 0.0;
//		MC.B	= 0.0;
//
//		MC.L	= 0.0;
//		MC.R	= 0.0;

		//*****************************************
		// Update motor control
		//*****************************************
		MCMSet(&MC);
		//-----------------------------------------

		//===========================================================
		// Finalize load and post telemetry data
		// (non-blocking call)
		//-----------------------------------------------------------
		TM.TS			= TMRGetTS() - StartTS;
		//----------------------
		TM.Roll			= IMU.Roll;
		TM.Pitch		= IMU.Pitch;
		TM.Yaw			= IMU.Yaw;
		TM.Inclination	= IMU.Incl;					
		//----------------------
		TM.SetPoint		= RC.Roll;
		TM.Error		= QSD.RollError;
		TM.Omega		= QSD.RollDer;							
		//----------------------
		TM.Prop			= QSD.DeltaRollProp;		// Prop(.)
		TM.Diff			= QSD.DeltaRollDiff;		// Diff(.)
		TM.Int			= QSD.DeltaRollInt;			// Int(.)
		//----------------------
		TM.Total		= QSD.DeltaRoll;			// Tot(.)
		//----------------------
		TM.ErrSum		= QSD.RollErrorSum;			// Err. Sum
		//----------------------
		TM.RCThrottle	= RC.Throttle;				// throttle
		TM.MCThrottle	= QSD.Throttle;				// throttle
		//----------------------
		TM.MCLeft		= MC.L;						// Motor control
		TM.MCRight		= MC.R;						// Motor control
		//----------------------
		TM.Battery 		= QSD.Voltage;
		//===========================================================
		UARTPostIfReady( (unsigned char *) &TM, sizeof(TM)	);

		}
	//*******************************************************************
	return 1;
	}






