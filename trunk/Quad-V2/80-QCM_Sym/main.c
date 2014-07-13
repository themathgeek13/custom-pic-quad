#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "MCM\MCM.h"
#include "RC\RCSym.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "UART\UART_TX.h"
#include "DCM\DCM.h"
#include "IMU\IMU.h"
#include "QCM\QCM.h"
#include "DEF\DEF.h"

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
// <editor-fold defaultstate="collapsed" desc="Telemetry reporting definitions">
// Telemetry reporting definitions
//==================================================
// Uncomment the following define if you would like
// to report GYRO values
//---------------------------------------------------
//#define _TMReport_GYRO_
//---------------------------------------------------
// Uncomment the following define if you would like
// Gyro values to be rotated to Earth before reporting
// Requires that _TMReport_GYRO_ is defined
//---------------------------------------------------
//#define _TMReport_GYRO_Rotated
//---------------------------------------------------
// Configuration verification
//---------------------------------------------------
#ifdef _TMReport_GYRO_Rotated
	#ifndef _TMReport_GYRO_
		#error _TMReport_GYRO_Rotated requires _TMReport_GYRO_
	#endif
#endif
//==================================================
// Uncomment the following define if you would like
// to report ACC values
//---------------------------------------------------
//#define _TMReport_ACC_
//==================================================
// Uncomment the following define if you would like
// to report native RC values
//---------------------------------------------------
//#define _TMReport_NativeRC_
//==================================================
// Uncomment the following define if you would like
// to report PID controller results
//---------------------------------------------------
#define _TMReport_PID_
//---------------------------------------------------
// Uncomment the following define if you would like
// to report details of PID components of Motor Control
// Requires that _TMReport_PID_ is defined
//---------------------------------------------------
//#define _TMReport_PID_Details
//---------------------------------------------------
// Configuration verification
//---------------------------------------------------
#ifdef _TMReport_PID_Details
	#ifndef _TMReport_PID_
		#error _TMReport_PID_Details requires _TMReport_PID_
	#endif
#endif
//==================================================
// </editor-fold>
//***************************************************
// <editor-fold defaultstate="collapsed" desc="Telemetry data structure">
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
	#ifdef	_TMReport_GYRO_
	//-----------------------------------------------
	// Orientation Data change rate (gyro rate)
	// potentially brought to Earth Frame
	//-----------------------------------------------
	Vector	Gyro;
	#endif
	//-----------------------------------------------
	#ifdef	_TMReport_ACC_
	//-----------------------------------------------
	// Acellerometer Data
	//-----------------------------------------------
	Vector	Acc;
	#endif
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
	#ifdef	_TMReport_NativeRC_
	//-----------------------------------------------
	// Native (before processing) Control Data
	//-----------------------------------------------
	float	RCN_Throttle;
	float	RCN_Roll;
	float	RCN_Pitch;
	float	RCN_Yaw;
	#endif
	//-----------------------------------------------
	#ifdef __MXB_Use__
	//-----------------------------------------------
	// Altitude
	//-----------------------------------------------
	MXBData	MXB;
	#endif
	//-----------------------------------------------

	#ifdef _TMReport_PID_
	//-----------------------------------------------
	// QCM Control Data
	//-----------------------------------------------
	#ifdef _TMReport_PID_Details
	float	DRProp;
	float	DRDiff;
	float	DRInt;
	#endif
	float	DRTot;
	//-------------
	#ifdef _TMReport_PID_Details
	float	DPProp;
	float	DPDiff;
	float	DPInt;
	#endif
	float	DPTot;
	//-------------
	#ifdef _TMReport_PID_Details
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
// </editor-fold>
//=====================================================

int main(void)
	{
	// <editor-fold defaultstate="collapsed" desc="Initialization of HW components/modules">
	//*******************************************************************
	// Initialization of HW components/modules
	//===================================================================
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	BLIAsyncMorse("S", 1);	// dit-dit-dit
	MCMInitT(2.5, 2500);	// Initialize Motor Control for PPM with setting
							// Throttle to HIGH for delay interval to let ESC
							// capture Throttle range
	BLIAsyncMorse("O", 1);	// dah-dah-dah
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
	// <editor-fold defaultstate="collapsed" desc="Initializing IMU">
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
	//*******************************************************************
	BLIAsyncMorse(	"I", 1);	// dit - dit
	//==================================================================
	#ifdef __MXB_Use__
	//--------------------------------------------------------------
	// Initialize MaxBotix range finder
	//--------------------------------------------------------------
	if ( 0 == MXBInit(3, &TM.MXB) )
		BLIDeadStop("ES", 2);
	#endif
	//==================================================================
	// Initialize motion sensor - rotation rate baseline established at
	// this time - QUAD should be motionless!!!
	//------------------------------------------------------------------
	if ( MPUInit(0, 3 ) )	// Initialize motion Sensor
		// 1 kHz/(0+1) = 1000 Hz (1ms)
		// DLPF=3 => Bandwidth 44 Hz (delay: 4.9 msec)
		BLIDeadStop("EA", 2);
	//------------------------------------------------------------------
	BLIAsyncStop();
	//==================================================================
	// </editor-fold>

	//==================================================================
	BLISignalON();
	TMRDelay(2000); 	// Wait for extra 2 sec - to let ESC arm...
	// (finish the song :) )
	BLISignalOFF();
	//===================================================================
	// </editor-fold>

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

	ulong		Alarm		= 0;
	
	#ifdef __CB_To_Model_Front__
		// RC native input rotated to adjust CB orientation to model front
		RCData	RC_CB_To_Model_Front;
		// Control board front does not coincide with the model front
		Matrix	CB_To_Model;
		// Build rotation matrix to adjust for orientation discrepancy
		MatrixYawRotation(__CB_To_Model_Front__, &CB_To_Model);
	#else
		// If CB orientation coincides with the fron of the model
		// we will use Native RC input as base for RC input to
		// Quadrocopter control module
		#define RC_CB_To_Model_Front  RCNative
	#endif


Re_Start:
	//==================================================================
	// Wait for the Receiver ARMing: Control should go Down and then Up
	//------------------------------------------------------------------
	BLIAsyncMorse(	"O", 1);	// doh - doh - doh
	RCSymArm();

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
	RC.Control	= 1;
	//-------------------------------------------------------------------
	
	//*******************************************************************
	// Quadrocopter Control Loop
	//-------------------------------------------------------------------
	BLISignalON();
	while (1)
		{
		// Sets the "frquency" of Control Loop
		Alarm = TMRSetAlarm(10);	// Set Alarm 10 msec in the future
		//============================================================
		// Read commands from receiver - non-blocking call!
		// (we will get out of this call even if connection to the
		// receiver is lost!)
		//============================================================
		// <editor-fold defaultstate="collapsed" desc="Process Receiver feed">
		if ( RCSymRead(&RCNative) )
			{
			//------------------------------------------------------------
			// Normalize Roll and Pitch control input from RC Receiver to
			// +/- 0.35 rad (~20 degrees) and Yaw control input to
			// +/- 3.00 rad (~172 degrees)
			//------------------------------------------------------------
			RCNative.Roll 	= 0.35 * RCNative.Roll;
			RCNative.Pitch	= 0.35 * RCNative.Pitch;
			RCNative.Yaw	= 3.00 * RCNative.Yaw;
			#ifdef __CB_To_Model_Front__
				{
				// Control board front does not coincide with the model front
				Vector	RCInput;
				Vector	RCRotated;
				VectorSet(RCNative.Roll, RCNative.Pitch, RCNative.Yaw, &RCInput);
				MatrixTimesVector(&CB_To_Model, &RCInput, &RCRotated);
				RC_CB_To_Model_Front.Roll		= RCRotated.X;
				RC_CB_To_Model_Front.Pitch		= RCRotated.Y;
				RC_CB_To_Model_Front.Yaw		= RCRotated.Z;
				}
			#endif
			}
		//============================================================
		// Smooth RC data 
		//------------------------------------------------------------
		// Roll, Pitch, and Yaw are smoothed with the IIR(8)
		//------------------------------------------------------------
		RC.Roll		= (RC.Roll	* 7.0	+ RC_CB_To_Model_Front.Roll	) * 0.125;	// 1/8 = 0.125
		RC.Pitch	= (RC.Pitch	* 7.0 	+ RC_CB_To_Model_Front.Pitch) * 0.125;
		RC.Yaw		= (RC.Yaw	* 7.0	+ RC_CB_To_Model_Front.Yaw	) * 0.125;
		//------------------------------------------------------------
		// Throttle is smoothed with the IIR(4) and adjusted to
		// account for actual battery voltage. This is done to
		// improve "hovering" when throttle stick is not moving.
		//------------------------------------------------------------
		// Adjust Native (from RC) throttle to a value corresponding
		float BatAdjTh	= RCNative.Throttle	* BatNomV / ADCGetBatteryVoltage();
		//-----------------------------------------
		RC.Throttle	= (RC.Throttle * 3	+ BatAdjTh) * 0.25;		// 1/4 = 0.25
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
		// Read current orientation and sensor data from the IMU
		// (non-blocking call)
		//============================================================
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
		// dangerously tilted (> 60 degrees) while
		// RC Throttle is low - to protect props 
		//----------------------------------------
		if (IMU.Incl <= 0.5 && RC.Throttle <= 0.40)
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
		#ifdef  _TMReport_GYRO_
			#ifdef	_TMReport_GYRO_Rotated
			//------------------------------------------------------
			// We rotate Gyro vector using "partial" DCM built using
			// only Roll and Pitch angles as the actual Yaw does not
			// affect Angualr Velocity by axis
			//------------------------------------------------------
			Matrix		NoYawDCM;
			// Generate partial rotation matrix
			MatrixEulerRotation(IMU.Roll, IMU.Pitch, 0.0, &NoYawDCM);
			// Rotate Gyro vector
			MatrixTimesVector(&NoYawDCM, &IMU.GyroRate, &TM.Gyro);
			#else
			// Just report native Gyro data
			VectorCopy(&IMU.GyroRate, &TM.Gyro);
			#endif
		#endif
		//----------------------
		#ifdef  _TMReport_ACC_
		// Just report native Gyro data
		VectorCopy(&IMU.Gravity, &TM.Acc);
		#endif
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
		#ifdef _TMReport_NativeRC_
		TM.RCN_Throttle	= RCNative.Throttle;
		TM.RCN_Roll		= RCNative.Roll;
		TM.RCN_Pitch	= RCNative.Pitch;
		TM.RCN_Yaw		= RCNative.Yaw;
		#endif
		//----------------------
		#ifdef __MXB_Use__
		MXBRead(&TM.MXB);
		#endif
		//----------------------
		#ifdef _TMReport_PID_
		#ifdef _TMReport_PID_Details
		TM.DRProp		= QSD.DeltaRollProp;
		TM.DRDiff		= QSD.DeltaRollDiff;
		TM.DRInt		= QSD.DeltaRollInt;
		#endif
		TM.DRTot		= QSD.DeltaRoll;
		//-------------
		#ifdef _TMReport_PID_Details
		TM.DPProp		= QSD.DeltaPitchProp;
		TM.DPDiff		= QSD.DeltaPitchDiff;
		TM.DPInt		= QSD.DeltaPitchInt;
		#endif
		TM.DPTot		= QSD.DeltaPitch;
		//-------------
		#ifdef _TMReport_PID_Details
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
		// Insert controlled "delay" to slow down the Control Loop
		TMRWaitAlarm(Alarm);
		}
	//*******************************************************************
	return 1;
	}






