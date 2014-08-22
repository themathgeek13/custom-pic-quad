#include "IMU/IMULocal.h"

//************************************************************
volatile uint	_IMUReady 		= 0;	// IMU initializtion flag
//************************************************************
// Reference to an "internal" MPU6050 function to adjust Acc
// Zx base using calculated attitude in the assumption that
// the model is motionless
//------------------------------------------------------------
uint	MPUAsyncAdjustAccZBase(float AccZBase);

//************************************************************
uint	IMUReset()
	{
	_IMUReady 		= 0;
	//*******************************************************
	BLIAsyncMorse("W", 1);
	//*******************************************************
	MPUData		MPUReading;
	DCMData		IMUResult;
	//-------------------------------------------------------
	HMCSample	HMCReading;
	//*******************************************************
	// Start HMC module so that it may accumulate multiple
	// samples for averaging while DCM stabilizes
	//-------------------------------------------------------
	if (HMCAsyncStart())
		BLIDeadStop("M", 1);
	// Clear accumulated sensor readings
	if (HMCAsyncReadWhenReady(&HMCReading))
		BLIDeadStop("M", 1);
	
	//*******************************************************
	// Reset DCM algorithm
	//-------------------------------------------------------
	DCMReset();
	//*******************************************************
	uint		IsReady	= 0;
	ulong		StCount	= 0;
	ulong		Alarm	= 0;
	//-------------------------------------------------------
	// Start MPU6050 and calibrate Gyro offset
	//-------------------------------------------------------
	if (MPUAsyncStart())
		// Async start failed...
		BLIDeadStop("A", 1);
	if (MPUCalibrate () != MPU_OK)
		// Gyro Calibration failed
		BLIDeadStop ("CA", 2);

	//*******************************************************
	// Read first sample orientation vector
	//-------------------------------------------------------
	if (MPUAsyncReadWhenReady(&MPUReading)) 
		BLIDeadStop("A", 1);
	//-------------------------------------------------------
	// Update DCM until it is synchronized with current
	// orientation vector
	//-------------------------------------------------------
	// Set Alarm for 10 msec so we read an average of
	// about 10 MPU6050 samples for each DCM step
	Alarm = TMRSetAlarm(10);
	//-------------------------------------------------------
	while (0 == IsReady)
		{
		TMRWaitAlarm(Alarm);
		//--------------------------------------
		// Read average of MPU6050 samples
		//--------------------------------------
		if (MPUAsyncReadWhenReady(&MPUReading)) 
			BLIDeadStop("A", 1);
		//--------------------------------------
		Alarm = TMRSetAlarm(10);	// Set Alarm for next measurement
		//--------------------------------------
		IsReady = DCMPerformStep(	 MPUReading.TS,
									&MPUReading.G,
									&MPUReading.A, 
									&IMUResult);
		//----------------------------
		StCount++;
		}
	//*******************************************************
	// Attitude calculation stabilized; now we may adjust
	// Acc Zx base...
	//*******************************************************
	if (MPU_OK != MPUAsyncAdjustAccZBase(IMUResult.Incl)) 
		BLIDeadStop("A", 1);
	//*******************************************************
	// Now that we are done with the attitude calculation we
	// may finalize calculation of true Azimuth from the
	// magnetometer.
	//*******************************************************
	if (HMC_OK == HMCAsyncReadWhenReady(&HMCReading))
		DCMSetAzimuth(&HMCReading.M);
	//----------------------------------------------
	// Stop magnetometer as it is not used in flight
	//----------------------------------------------
	HMCAsyncStop();
	//*******************************************************
	_IMUReady = 1;
	//*******************************************************
	BLIAsyncStop();
	//*******************************************************
	return StCount;
	}
//************************************************************

