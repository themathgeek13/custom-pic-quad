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
#include "QCM\QCM.h"
#include "IMU\IMU.h"

struct
	{
	// Telemetry data exchange format
	//-----------------------------------------------
	ulong	TS;				// Timestamp (ticks)
	//----------------------
	DCMData	IMUResult;		// Orientation data from DCM
	//----------------------
	Vector	Acc;			// Accelleration vector
	//----------------------
	float	Throttle;		// Common throttle setting
	float	Power;			// Throttle adjusted by battery level
	float	Voltage;		// Battery status		
	//----------------------
	} TMVibro;


int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	BLIAsyncMorse("S", 1);	// dot-dot-dot
	MCMInitT(2.0, 2500);	// Initialize Motor Control for PPM with setting
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
	BLIAsyncMorse(	"R", 1);
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
	QCMStepReset();		// Reset Step calculation variables
	//==================================================================

	//*******************************************************************
	// Vibro Test Main Loop
	//-------------------------------------------------------------------
	ulong		StartTS;

	RCData		RCSample;
	MPUSample	MPUReading;
	MCMData		MCData;
	
	//*******************************************************************
	// Vibro Test Main Loop
	//-------------------------------------------------------------------
	RCSymReset();	// Re-set simulation sequence
	//---------------------------------------------
	StartTS =  TMRGetTS();
	//---------------------------------------------
	while (1)
		{
		//-----------------------------------------
		// Read commands from receiver - blocking call!
		// (we will get out of this call even if con-
		// nection to the receiver is lost!)
		//-----------------------------------------
		RCSymReadWhenReady(&RCSample);
		//-----------------------------------------
		if (0 == RCSample.Control)
			{
			// Implement Motor Cut-Off
			MCData.F = MCData.B = MCData.L = MCData.R = 0;
			MCMSet(&MCData);
			//----------------------------------
			// Re-Start cycle
			//----------------------------------
			goto Re_Arm;		// Wait for next reading
			}

		//-----------------------------------------
		// Read current orientation from the IMU
		// with sensors' measurements
		// (non-blocking call)
		//-----------------------------------------
		IMUGetUpdateWithSamples(&MPUReading,
								&TMVibro.IMUResult	);
		//=========================================

		//*****************************************
		// Calculate motor control
		//*****************************************
		QCMPerformStep(&RCSample, &TMVibro.IMUResult, &MCData);

		//*****************************************
		// Update motor control
		//*****************************************
		MCMSet(&MCData);

		//=========================================
		// Finalize load and post telemetry data
		// (non-blocking call) - once per new sample
		// from RC Receiver
		//-----------------------------------------
		TMVibro.TS			= TMRGetTS() - StartTS;
		//----------------------------------
		VectorCopy(&MPUReading.A, &TMVibro.Acc);
		//----------------------------------
		TMVibro.Throttle	= RCSample.Throttle;
		TMVibro.Voltage 	= ADCGetBatteryVoltage();
		TMVibro.Power		= RCSample.Throttle * TMVibro.Voltage;
		//-----------------------------------------
		UARTPostIfReady( (byte*) &TMVibro, sizeof(TMVibro)	);

		}
	//*******************************************************************
	return 1;
	}


	/* Very good */
//	if (MPUInit(2, 3))	// Initialize MPU - 1 kHz/(2+1) (333 Hz, 3ms)	
//						// DLPF = 3 => Bandwidth 44 Hz (delay: 4.9 msec)

	/* Rather good - WITH NO Filtering!!!*/
	// Stability is fine, but ACC jumps rather crazy
//	if (MPUInit(7, 0))	// Initialize MPU - 1 kHz/ (1000 Hz, 1ms)
//						// DLPF = 0 => Bandwidth 256 Hz, Delay 0.98 msec

	/*  - Minimal Filtering!!!*/
	// Stability is fine, but ACC jumps rather crazy
//	if (MPUInit(0, 1))	// Initialize MPU - 1 kHz/(1) (1000 Hz, 1ms)
//						// DLPF = 1 => Bandwidth 184 Hz (delay: 2.0 msec)
	

