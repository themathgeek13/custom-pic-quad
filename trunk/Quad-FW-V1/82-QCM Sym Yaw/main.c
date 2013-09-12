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
	//----------------------
	float	RCYaw;			// Parameter input from RC
	//----------------------
	float	MParam;			// Measured parameter
	float	SetPoint;	// Set Point - based on input from RC
	float	Error;			// Error
	//----------------------
	float	Omega;			// Rotational Speed
	//----------------------
	float	Prop;			// Proportional component
	float	Diff;			// Differential component
	float	Int;			// Integral component
	float	MB;				// Motor Balance component
	//----------------------
	float	Total;			// Total Throttle adjustment
	//----------------------
	float	ErrSum;			// Accumulated error sum
	//----------------------
	float	Throttle;		// Common throttle setting
	//----------------------
	float	MCFront;		// 
	float	MCBack;			// 
	float	MCLeft;			// 
	float	MCRight;		// 
	//----------------------
	float	Power;			// Effective voltage applied to motors (common)
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
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
						// BaudRate =  1	=>   2400 bps
						// BaudRate =  2	=>   4800 bps
						// ...
						// BaudRate = 48	=> 115200 bps
						// BaudRate = 99	=> 250000 bps - special case
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
	QCMInit();		// Reset Step calculation variables
	//==================================================================


	//*******************************************************************
	// Simulation variables
	//-------------------------------------------------------------------
	uint		SC			= 0;	// Step counter - for soft motor start

	ulong		StartTS;

	RCData		RC;				// Control input from Receiver
	DCMData		IMU;			// Orientation data from DCM
	MCMData		MC;				// Motor control Variables

	//*******************************************************************
	// Simulation Main Loop
	//-------------------------------------------------------------------
	RCSymReset();	// Re-set simulation sequence
	//---------------------------------------------
	StartTS =  TMRGetTS();
	//---------------------------------------------
	while (1)
		{
		//=========================================
		// Read commands from receiver - blocking call!
		// (we will get out of this call even if con-
		// nection to the receiver is lost!)
		//-----------------------------------------
		RCSymReadWhenReady(&RC);
		//-----------------------------------------
		// Implement Motor Cut-Off if RC Control is LOW
		if (0 == RC.Control)
			{
			MC.F = MC.B = MC.L = MC.R = 0;
			MCMSet(&MC);
			//----------------------------------
			SC			= 0;	// Reset motor "soft start"
			//----------------------------------
			// Re-Start cycle
			//----------------------------------
			goto Re_Arm;		// Wait for next reading
			}
		//-----------------------------------------
		// Normalize Roll and Pitch control settings
		// from RC Receiver to about +/- 0.5 rad
		// ( about +/- 30 degrees of declination)
		//-----------------------------------------
		RC.Roll		*= 0.625;
		RC.Pitch 	*= 0.625;
		//-----------------------------------------
		// Implement motor "soft start"
		//-----------------------------------------

		RC.Yaw = 0.0;

/*
		SC++;
		if (SC < 25)
			RC.Throttle = 0.12;
		else
			{
			if (SC < 325)
				RC.Throttle = 0.3;
			// Test run override
			else
				RC.Throttle = 0.8;
			}
	
		if (SC > 625)
			SC = 25;
*/

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
		TM.RCYaw		= RC.Yaw;
		TM.MParam		= IMU.Yaw;
		TM.SetPoint		= QSD.RCYawInt;			// NOTE: Set point for Yaw achieved
												//		 through integration of Yaw input
		TM.Error		= QSD.YawError;
		TM.Omega		= QSD.YawPVDer;							
		//----------------------
		TM.Prop			= QSD.DeltaYawProp;		// Prop(.)
		TM.Diff			= QSD.DeltaYawDiff;		// Diff(.)
		TM.Int			= QSD.DeltaYawInt;		// Int(.)
		TM.MB			= QSD.DeltaYawMB;		// MB(.)
		//----------------------
		TM.Total		= QSD.DeltaYaw;			// Tot(.)
		//----------------------
		TM.ErrSum		= QSD.YawErrorSum;		// Err. Sum
		//----------------------
		TM.Throttle		= QSD.Throttle;				// throttle
		//----------------------
		TM.MCFront		= MC.F;						// Motor control
		TM.MCBack		= MC.B;						// Motor control
		TM.MCLeft		= MC.L;						// Motor control
		TM.MCRight		= MC.R;						// Motor control
		//----------------------
		TM.Power		= QSD.Power;
		TM.Battery 		= QSD.Voltage;
		//===========================================================
		UARTPostIfReady( (unsigned char *) &TM, sizeof(TM)	);

		}
	//*******************************************************************
	return 1;
	}






