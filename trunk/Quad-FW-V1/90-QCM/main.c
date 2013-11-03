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
//=======================================================================

//***************************************************
// Telemetry ....
//***************************************************
// <editor-fold defaultstate="collapsed" desc="Telemetry reporting definitions">
// Telemetry reporting definitions
//==================================================

// <editor-fold defaultstate="collapsed" desc="Gyro Reporting">
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
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Acc Reporting">
//==================================================
// Uncomment the following define if you would like
// to report ACC values
//---------------------------------------------------
//#define _TMReport_ACC_
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Reporting RCFeed">
//==================================================
// Uncomment the following define if you would like
// to report native RC values
//---------------------------------------------------
#define _TMReport_RCFeed_
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Reporting RCSmthd">
//==================================================
// Uncomment the following define if you would like
// to report smothed RC values
//---------------------------------------------------
#define _TMReport_RCSmthd_
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="PID Reporting">
//==================================================
// Uncomment the following define if you would like
// to report PID controller results
//---------------------------------------------------
//#define _TMReport_PID_
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
// </editor-fold>

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
	#ifdef	_TMReport_RCSmthd_
	//-----------------------------------------------
	// Native (before processing) Control Data
	//-----------------------------------------------
	float	RCS_Throttle;
	float	RCS_Roll;
	float	RCS_Pitch;
	float	RCS_Yaw;
	#endif
	//-----------------------------------------------
	#ifdef	_TMReport_RCFeed_
	//-----------------------------------------------
	// Native (with minimal processing) Control Data
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
//=======================================================================

// <editor-fold defaultstate="collapsed" desc="MODE Flags">
//=======================================================================
// MODE flags - in subsequent releases will be controlled by DIP
// switches, but for now controlled by setting values in code :(
//-----------------------------------------------------------------------
// If the front of the Model need to be adjusted with regards to the front
// of the Control board please un-comment the following define.
// This MODE is typically used to change pattern from "+" configuration to
// "X" configuration
BOOL	MODE_CB_to_MF		= TRUE;
//-----------------------------------------------------------------------
// In "Course Lock" mode the "forward" direction is always coincide with
// the "forward" direction captured when the model was "ARMed". To enable
// this mode please uncomment the following line
BOOL	MODE_Course_Lock	= TRUE;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="RC feed normalization routine">
//----------------------------------------------------------------
// Depending on the logic on the control algorithm, raw RC feed
// need to be "normalized" to bring parameters into the required
// range.
//----------------------------------------------------------------
static inline void NormalizeRCFeed(RCData* F)
	{
	//------------------------------------------------------------
	// Normalize Roll and Pitch control input from RC Receiver to
	// +/- 0.35 rad (~20 degrees) and Yaw control input to
	// +/- 3.00 rad (~172 degrees)
	//------------------------------------------------------------
	F->Roll 	*= 0.35;
	F->Pitch	*= 0.35;
	F->Yaw		*= 3.00;
	}
// </editor-fold>


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
	BLISignalON();
	TMRDelay(2000); 	// Wait for extra 2 sec - to let ESC arm...
	// (finish the song :) )
	BLISignalOFF(); // </editor-fold>
	//===================================================================

	//*******************************************************************
	// Quadrocopter control variables
	//-------------------------------------------------------------------
	// <editor-fold defaultstate="collapsed" desc="Timing control variables">
	ulong		StartTS		= 0;	// Flight start time
	ulong		StepTS;				// Control Loop step start time
	ulong		Alarm		= 0;	// "alarm" variable used to set
									// the duration of the Control Loop
	// </editor-fold>

	// <editor-fold defaultstate="collapsed" desc="Variable required to process RC Feed ">
	//-------------------------------------------------------------------
	RCData		RCFeed;			// Control input from Receiver adjusted
								// by control rates. It may also be
								// corrected (if necessary) to account
								// for "+" or "X" configuration as
								// specified by MODE_CB_to_MF flag
	//---------------------------------------
	RCData		RCSmthd;		// Smoothed control input used in all
								// subsequent control calculations
								//---------------------------------------
	RCData		RCFinal;		// Smoothed RC input adjusted for the
								// Yaw angle to provide "Course Lock" (if
								// required). Final RC input provided to
								// Quarocopter Control Module
	//-------------------------------------------------------------------
	// We need battery Nominal voltage to adjust RC Throttle as battery
	// charge depletes.
	float		BatNomV		= ADCGetBatteryNomVoltage ();
	//-------------------------------------------------------------------
	Matrix		Mtr_CB_To_MF;	// Rotation matrix used to adjust Control
								// Board orientation to Model front
								//---------------------------------------
	Matrix		Mtr_CrsLck;		// Rotation matrix used to adjust RC input
								// to account for current Yaw to implement
								// "Course Lock"
								//---------------------------------------
	if (MODE_CB_to_MF)
		// Initialize Rotation Matrix for pre-set angle
		MatrixYawRotation(__CB_To_MF_Angle__, &Mtr_CB_To_MF);
	else
		// Reset Rotation matrix to Identity
		MatrixSetIdentity(&Mtr_CB_To_MF);
	//-------------------------------------------------------------------
	// </editor-fold>
	
	DCMData		IMU;				// Orientation data from DCM
	MCMData		MC;					// Motor control Variables
	//-------------------------------------------------------------------
	


	// <editor-fold defaultstate="collapsed" desc="ARMing RC and initializing IMU">
	//==================================================================
	// Wait for the Receiver ARMing: Throttle should go up and then down
	//------------------------------------------------------------------
	BLIAsyncMorse(	"O", 1);	// doh - doh - doh
	RCArm();
	//==================================================================
	// Initialize sensors... Performed after ARMing to ensure that model
	// is stable
	//------------------------------------------------------------------
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
	if ( MPUInit(0, 3) )	// Initialize motion Sensor
		// 1 kHz/(0+1) = 1000 Hz (1ms)
		// DLPF=3 => Bandwidth 44 Hz (delay: 4.9 msec)
		BLIDeadStop("EA", 2);
	//------------------------------------------------------------------
	BLIAsyncStop();
	//==================================================================
	// </editor-fold>

Re_Start:
	//==================================================================
	// <editor-fold defaultstate="collapsed" desc="Intialize Re-Start">
	//------------------------------------------------------------------
	StartTS		= 0;					// Reset timing of control Loop
	//------------------------------------------------------------------
	BLIAsyncMorse ("O", 1);				// doh - doh - doh
	RCReadWhenReady (&RCFeed);			// Get reading from receiver
	//------------------------------------------------------------------
	// Safety check:  CONTROL should be UP and THROTTLE - LOW
	//------------------------------------------------------------------
	while 	(
			0 == RCFeed.Control
			||
			RCFeed.Throttle > 0.1
			)
		{
		RCReadWhenReady (&RCFeed);		// Get next reading from receiver
		}
	//------------------------------------------------------------------
	// Normalize last read RC values as they will represent the first
	// input into the control algorithm, so should be adjusted accordingly
	//------------------------------------------------------------------
	NormalizeRCFeed(&RCFeed);
	//------------------------------------------------------------------
	// Reset Smothed RC data (initialize filter)
	//------------------------------------------------------------------
	RCDataReset(&RCSmthd);
	//==================================================================
	BLIAsyncMorse ("T", 1);			// doh
	MPUAsyncStop ();
	if (MPUCalibrate () != MPU_OK)
	  // Gyro Calibration filed
	  BLIDeadStop ("EA", 2);
	BLIAsyncStop ();
	//==================================================================
	// Start IMU and wait until orientation estimate stabilizes
	//------------------------------------------------------------------
	BLIAsyncMorse (	"E", 1);		// dit
	IMUInit ();
	// Force update of DCMData as inside the control Loop this
	// call is non-blocking!
	if (IMU_OK != IMUGetUpdateWhenReady (&IMU))
	  // Failure...
	  BLIDeadStop ("A", 1);
	//------------------------------------------------------------------
	QCMReset ();			// Initialize (reset) QCM variables
	//------------------------------------------------------------------
	BLIAsyncStop ();
	// </editor-fold>
	//==================================================================

	//*******************************************************************
	// Quadrocopter Control Loop
	//-------------------------------------------------------------------
	BLISignalON();
	while (1)
		{
		//============================================================
		// Timing of control Loop
		//============================================================
		// <editor-fold defaultstate="collapsed" desc="Control Loop timing management">
		// Sets the "frquency" of Control Loop
		Alarm = TMRSetAlarm (10);	// Set Alarm 10 msec in the future
		//------------------------------------------------------------
		StepTS =  TMRGetTS ();		// Capture TS of this step
		if ( 0 == StartTS )			// First iteration of Control?
		  StartTS =  StepTS;		// Yes, capture timestamp
		// </editor-fold>
		//============================================================

		//============================================================
		// Read commands from receiver - non-blocking call!
		// (we will get out of this call even if connection to the
		// receiver is lost!)
		// At the end processed Receiver data is stored in RCSmthd
		//============================================================
		// <editor-fold defaultstate="collapsed" desc="Process Receiver feed">
		if ( RCRead(&RCFeed) )
			{
			//------------------------------------------------------------
			// Every NEW sample need to be "normalized"
			//------------------------------------------------------------
			NormalizeRCFeed(&RCFeed);
			//------------------------------------------------------------
			// Adjust orientation from "+" to "X" if needed
			//------------------------------------------------------------
			if (MODE_CB_to_MF)
				{
				// Control board front does not coincide with the model front
				Vector	RCInput;
				Vector	RCRotated;
				VectorSet(RCFeed.Roll, RCFeed.Pitch, RCFeed.Yaw, &RCInput);
				MatrixTimesVector(&Mtr_CB_To_MF, &RCInput, &RCRotated);
				RCFeed.Roll		= RCRotated.X;
				RCFeed.Pitch	= RCRotated.Y;
				RCFeed.Yaw		= RCRotated.Z;
				}
			}
		//============================================================
		// Smooth RC data 
		//------------------------------------------------------------
		// Roll, Pitch, and Yaw are smoothed with the IIR(8)
		//------------------------------------------------------------
		RCSmthd.Roll	= (RCSmthd.Roll	* 7.0	+ RCFeed.Roll ) * 0.125;	// 1/8 = 0.125
		RCSmthd.Pitch	= (RCSmthd.Pitch* 7.0 	+ RCFeed.Pitch) * 0.125;
		RCSmthd.Yaw		= (RCSmthd.Yaw	* 7.0	+ RCFeed.Yaw  ) * 0.125;
		//------------------------------------------------------------
		// Throttle is smoothed with the IIR(4) and adjusted to
		// account for actual battery voltage. This is done to
		// improve "hovering" when throttle stick is not moving.
		//------------------------------------------------------------
		// Adjust Native (from RC) throttle to a value corresponding
		float BatV		= ADCGetBatteryVoltage();
		float BatAdjTh	= RCFeed.Throttle;
		if (BatV > 2.0)		// Sanity check :)
			BatAdjTh	= BatAdjTh	* BatNomV / BatV;
		//-----------------------------------------
		RCSmthd.Throttle	= (RCSmthd.Throttle * 3	+ BatAdjTh) * 0.25;		// 1/4 = 0.25
		//-----------------------------------------
		RCSmthd.Control		= RCFeed.Control;
		// </editor-fold>
		//============================================================

		//============================================================
		// Implement Motor Cut-Off if RC Control is LOW
		//============================================================
		// <editor-fold defaultstate="collapsed" desc="Process RC Control">
		if ( 0 == RCSmthd.Control )
			{
			// Yes, Control is reliably low!
			//--------------------------------------------
			// Override motor control
			//--------------------------------------------
			MC.F = MC.B = MC.L = MC.R = 0;
			MCMSet(&MC);
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
			if (RCSmthd.Throttle > MaxLevel)
				RCSmthd.Throttle = MaxLevel;
			}
		// </editor-fold>
		//============================================================

		//============================================================
		// Read current orientation from the IMU  with sensors' raw
		// measurements (non-blocking call) and, if necessary, perform
		// adjustment to RCSmthd to obtain RCFinal
		//============================================================
		// <editor-fold defaultstate="collapsed" desc="Process IMU data and generate Motor Control">
		// First, unconditionally promote RCSmthd to RCFinal
		RCDataCopy(&RCSmthd, &RCFinal);
		//------------------------------------------------------------
		if (IMU_OK == IMUGetUpdate(&IMU))
			{
			if (MODE_Course_Lock)
				{
				// We need to rotate RC input to adjust for current Yaw
				// to implement "Course Lock" - RC Roll and Pitch commands
				// are interpreted as being applied to the original (pre-
				// takeoff) orientation of the model
				//-------------------------------------------------------
				Vector	RCInput;
				Vector	RCRotated;
				// Build rotation matrix to adjust for orientation discrepancy
				MatrixYawRotation(-IMU.Yaw, &Mtr_CrsLck);
				// Load RC input into RCInput vector
				VectorSet(RCSmthd.Roll, RCSmthd.Pitch, RCSmthd.Yaw, &RCInput);
				// Rotate RCInput vector
				MatrixTimesVector(&Mtr_CrsLck, &RCInput, &RCRotated);
				// Save rotated values
				RCFinal.Roll		= RCRotated.X;
				RCFinal.Pitch		= RCRotated.Y;
				RCFinal.Yaw			= RCRotated.Z;
				}
			// Calculate motor control based
			// upon IMU data
			QCMPerformStep(&RCFinal, &IMU, &MC);
			}
		else
			{
			// IMU Failed to provide update -
			// set Motor Control to RC throttle
			MC.F = MC.B = MC.L = MC.R = RCFinal.Throttle;
			}
		// </editor-fold>
		//============================================================

		//************************************************************
		// Implement Motor Cut-Off to protect props if model is
		// dangerously tilted (> 60 degrees) while RC Throttle is low
		//------------------------------------------------------------
		if (IMU.Incl <= 0.5 && RCFinal.Throttle <= 0.40)
			{
			// Override motor control
			MC.F = MC.B = MC.L = MC.R = 0.0;
			}
		//------------------------------------------------------------

		//************************************************************
		// Update motor control
		//************************************************************
		MCMSet(&MC);
		//------------------------------------------------------------
		
		//===========================================================
		// Load and post telemetry data (non-blocking call)
		//-----------------------------------------------------------
		// <editor-fold defaultstate="collapsed" desc="Populating Telemetry">
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
			Vector		Earth;	// One of the Earth axis in Body frame
			Vector		Cross;	// Temporary vector to hold the cross
								// product
			//------------------------------------------------------
			// Calculate Roll and Pitch rates
			//------------------------------------------------------
			// Retrieve Earth Z-axis and calculate cross-product of
			// Z-axis with Gyro vector
			VectorCrossProduct(DCMEarthZ(&Earth), &IMU.GyroRate, &Cross);
			TM.Gyro.X = Cross.X;
			TM.Gyro.Y = Cross.Y;
			//------------------------------------------------------
			// Calculate Yaw rate
			//------------------------------------------------------
			// Retrieve Earth X-axis and calculate cross-product of
			// X-axis with Gyro vector
			VectorCrossProduct(DCMEarthX(&Earth), &IMU.GyroRate, &Cross);
			TM.Gyro.Z = Cross.Z;
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
		TM.RC_Throttle	= RCFinal.Throttle;
		TM.RC_Roll		= RCFinal.Roll;
		TM.RC_Pitch		= RCFinal.Pitch;
		TM.RC_Yaw		= RCFinal.Yaw;
		//----------------------
		#ifdef _TMReport_RCSmthd_
		TM.RCS_Throttle	= RCSmthd.Throttle;
		TM.RCS_Roll		= RCSmthd.Roll;
		TM.RCS_Pitch	= RCSmthd.Pitch;
		TM.RCS_Yaw		= RCSmthd.Yaw;
		#endif
		//----------------------
		#ifdef _TMReport_RCFeed_
		TM.RCN_Throttle	= RCFeed.Throttle;
		TM.RCN_Roll		= RCFeed.Roll;
		TM.RCN_Pitch	= RCFeed.Pitch;
		TM.RCN_Yaw		= RCFeed.Yaw;
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
		TM.Voltage 		= ADCGetBatteryVoltage();
		// </editor-fold>
		//===========================================================
		UARTPostIfReady( (unsigned char *) &TM, sizeof(TM)	);
		//===========================================================
		// Insert controlled "delay" to slow down the Control Loop
		// to pre-set frequency
		TMRWaitAlarm(Alarm);
		//===========================================================
		}
	//*******************************************************************
	return 1;
	}






