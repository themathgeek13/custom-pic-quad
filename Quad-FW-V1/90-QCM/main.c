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
#include "UART\UART_TX.h"
#include "DCM\DCM.h"
#include "IMU\IMU.h"
#include "QCM\QCM.h"

#include "QCM\QCMStepData.h"		// Needed for Telemetry data

//---------------------------------
// Header for optional HW components
//---------------------------------
#ifdef __MAG_Use__
	#include "HMCMAG\HMCMAG.h"
#endif
#ifdef __MXB_Use__
	#include "MXB\MXB.h"
#endif
//---------------------------------

//***************************************************
// Telemetry data exchange format
//***************************************************
// Uncomment the following define if you would like
// to report PID controller results
//---------------------------------------------------
//#define _PID_
//---------------------------------------------------
// Uncomment the following define if you would like
// to report details of PID components of Motor Control
// Requires that _PID_ is defined
//---------------------------------------------------
//#define _PID_Details
//---------------------------------------------------
// Configuration verification
//---------------------------------------------------
#ifdef _PID_Details
	#ifndef _PID_
		#error _PID_Details requires _PID_
	#endif
#endif
//***************************************************
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
	//-----------------
	float	Azimuth;
	//-----------------------------------------------
	// Orientation Data change rate (gyro rate
	// brought to Earth Frame)
	//-----------------------------------------------
	Vector	Omega;
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

	#ifdef __MXB_Use__
	//-----------------------------------------------
	// Altitude and vertical Speed
	//-----------------------------------------------
	MXBData	MXB;
	#endif

	#ifdef _PID_
	//-----------------------------------------------
	// QCM Control Data
	//-----------------------------------------------
	#ifdef _PID_Details
		float	DRProp;
		float	DRDiff;
		float	DRInt;
	#endif
	float	DRTot;
	//-------------
	#ifdef _PID_Details
		float	DPProp;
		float	DPDiff;
		float	DPInt;
	#endif
	float	DPTot;
	//-------------
	#ifdef _PID_Details
		float	DYProp;
		float	DYDiff;
		float	DYInt;
	#endif
	float	DYTot;
	#endif
	//-----------------------------------------------
	// Motor Control Data
	//-----------------------------------------------
	float	Throttle;		// Common throttle setting
	//-----------------------------------------------
	float	Voltage;		// Battery Voltage	
	//----------------------
	} TM;		// Telemetry data structure
//=====================================================

int main(void)
	{
	//*******************************************************************
	// Initialization of HW components/modules
	//===================================================================
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

	float		BatNomV		= ADCGetBatteryNomVoltage();

	//==================================================================
	// Wait for the Receiver ARMing: Throttle should go up and then down
	//------------------------------------------------------------------
	BLIAsyncMorse(	"O", 1);	// doh - doh - doh 
	RCArm();	
	//==================================================================
	// Initialize sensors...
	//------------------------------------------------------------------
	BLIAsyncMorse(	"I", 1);	// dit - dit
	//==================================================================
	#ifdef __MAG_Use__
		//--------------------------------------------------------------
		// Initialize Magnetometer
		//--------------------------------------------------------------
		if (HMCInit(6, 1, 0))	// Initialize magnetic Sensor
								// ODR  = 6 (max, 75 Hz),
								// Gain = 2 (1.3 Gs)
								// DLPF = 0 (no averaging)
			BLIDeadStop("EM", 2);
	#endif
	//==================================================================
	#ifdef __MXB_Use__
		//--------------------------------------------------------------
		// Initialize MaxBotix range finder
		//--------------------------------------------------------------
		if (0 == MXBInit(3, &TM.MXB))
			BLIDeadStop("ES", 2);
	#endif
	//==================================================================
	// Initialize motion sensor - rotation rate baseline established at
	// this time - QUAD should be motionless!!!
	//------------------------------------------------------------------
	if (MPUInit(0, 3))	// Initialize motion Sensor
						// 1 kHz/(0+1) = 1000 Hz (1ms)
						// DLPF=3 => Bandwidth 44 Hz (delay: 4.9 msec)
		BLIDeadStop("EA", 2);
	//------------------------------------------------------------------
	BLIAsyncStop();
	//==================================================================

Re_Start:
	//==================================================================
	BLIAsyncMorse("O", 1);			// doh - doh - doh 
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
	BLIAsyncMorse("T", 1);			// doh
	MPUAsyncStop();
	if (MPUCalibrate() != MPU_OK)	
		// Gyro Calibration filed
		BLIDeadStop("EA", 2);
	BLIAsyncStop();
	//==================================================================
	// Start IMU and wait until orientation estimate stabilizes
	//------------------------------------------------------------------
	BLIAsyncMorse(	"E", 1);		// dit
	IMUInit();
	//------------------------------------------------------------------
	QCMReset();			// Initialize (reset) QCM variables
	//------------------------------------------------------------------
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
		// <editor-fold defaultstate="collapsed" desc="Process Receiver feed">
		if ( RCRead(&RCNative) )
			{
			//------------------------------------------------------------
			// Normalize Roll and Pitch control input from RC Receiver to
			// +/- 0.35 rad (~20 degrees) and Yaw control input to
			// +/- 3.00 rad (~172 degrees)
			//------------------------------------------------------------
			RCNative.Roll 	= 0.35 * RCNative.Roll;
			RCNative.Pitch	= 0.35 * RCNative.Pitch;
			RCNative.Yaw	= 3.00 * RCNative.Yaw;
			}
		//============================================================
		// Smooth RC data 
		//------------------------------------------------------------
		// Roll, Pitch, and Yaw are smoothed with the IIR(32)
		//------------------------------------------------------------
		RC.Roll		= (RC.Roll	* 31.0	+ RCNative.Roll	) * 0.03125;	// 1/32 = 0.03125
		RC.Pitch	= (RC.Pitch	* 31.0 	+ RCNative.Pitch) * 0.03125;
		RC.Yaw		= (RC.Yaw	* 31.0	+ RCNative.Yaw	) * 0.03125;	
		//------------------------------------------------------------
		// Throttle is smoothed with the IIR(4) and adjusted to
		// account for actual battery voltage. This is done to
		// improve "hovering" when throttle stick is not moving.
		//------------------------------------------------------------
		// Adjust Native (from RC) throttle to a value corresponding
		float BatAdjTh	= RCNative.Throttle	* BatNomV / ADCGetBatteryVoltage();
		//-----------------------------------------
		RC.Throttle	= (RC.Throttle * 3	+ BatAdjTh) * 0.25000;	// 1/4 = 0.25
		//-----------------------------------------
		RC.Control	= RCNative.Control;
		// </editor-fold>
		//============================================================

		//============================================================
		// Implement Motor Cut-Off if RC Control is LOW
		//============================================================
		// <editor-fold defaultstate="collapsed" desc="Process RC Control">
		if ( 0 == RC.Control )
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
		// </editor-fold>
		//============================================================

		//============================================================
		// Obtain and process battery charge status
		//============================================================
		// <editor-fold defaultstate="collapsed" desc="Process Battery level">
		float BatteryCharge	= QCMBatteryMgmt();	
		if (BatteryCharge < 0.35)	// BC < 35%
			{
			float MaxLevel = 2.0 * BatteryCharge;
			if (RC.Throttle > MaxLevel)
				RC.Throttle = MaxLevel;
			}
		// </editor-fold>
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
		if (IMU.Incl <= 0.342 && RC.Throttle <= 0.40)
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
		// <editor-fold defaultstate="collapsed" desc="Populating Telemetry">
		StepTS =  TMRGetTS(); 
		//-----------------------------------------
		if ( 0 == StartTS )
			// Time stamp of cycle start!
			StartTS =  StepTS;
		//-----------------------------------------
		TM.TS			= StepTS - StartTS;
		//----------------------
		TM.Roll			= IMU.Roll;
		TM.Pitch		= IMU.Pitch;
		TM.Yaw			= IMU.Yaw;
		TM.Inclination	= IMU.Incl;
		TM.Azimuth		= IMU.Azimuth;
		//----------------------
		// <editor-fold defaultstate="collapsed" desc="Rotate Gyro Vector">
		//------------------------------------------------------
		// We rotate Gyro vector using "partial" DCM built using
		// only Roll and Pitch angles as the actual Yaw does not
		// affect Angualr Velocity by axis
		//------------------------------------------------------
		Matrix		NoYawDCM;
		// Generate partial rotation matrix
		MatrixEulerRotation(IMU.Roll, IMU.Pitch, 0.0, &NoYawDCM);
		// Rotate Gyro vector
		MatrixTimesVector(&NoYawDCM, &IMU.GyroRate, &TM.Omega);
		// </editor-fold>
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
		#ifdef __MXB_Use__
		MXBRead(&TM.MXB);
		#endif
		//----------------------
		#ifdef _PID_
		#ifdef _PID_Details
		TM.DRProp		= QSD.DeltaRollProp;
		TM.DRDiff		= QSD.DeltaRollDiff;
		TM.DRInt		= QSD.DeltaRollInt;
		#endif
		TM.DRTot		= QSD.DeltaRoll;
		//-------------
		#ifdef _PID_Details
		TM.DPProp		= QSD.DeltaPitchProp;
		TM.DPDiff		= QSD.DeltaPitchDiff;
		TM.DPInt		= QSD.DeltaPitchInt;
		#endif
		TM.DPTot		= QSD.DeltaPitch;
		//-------------
		#ifdef _PID_Details
		TM.DYProp		= QSD.DeltaYawProp;
		TM.DYDiff		= QSD.DeltaYawDiff;
		TM.DYInt		= QSD.DeltaYawInt;
		#endif
		TM.DYTot		= QSD.DeltaYaw;
		#endif
		//----------------------
		TM.Throttle		= QSD.Throttle;				// Real Throttle
		//----------------------
		TM.Voltage 		= QSD.Voltage;
		// </editor-fold>
		//===========================================================
		UARTPostIfReady( (unsigned char *) &TM, sizeof(TM)	);
		//===========================================================

		}
	//*******************************************************************
	return 1;
	}






