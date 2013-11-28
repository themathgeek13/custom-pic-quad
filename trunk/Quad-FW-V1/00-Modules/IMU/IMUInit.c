#include "IMU\IMULocal.h"

//************************************************************
volatile uint	_IMUInit 		= 0;	// IMU initializtion flag
//************************************************************

//************************************************************
ulong	IMUInit()
	{
	_IMUInit 		= 0;
	//*******************************************************
	// Reset DCM algorithm
	//-------------------------------------------------------
	DCMReset();
	//*******************************************************
	BLIAsyncMorse("W", 1);
	//*******************************************************
	MPUSample	MPUReading;
	DCMData		IMUResult;
	//-------------------------------------------------------
	HMCSample	HMCReading;
	if (HMCAsyncStart())
		BLIDeadStop("M", 1);
	// Clear accumulated sensor readings
	if (HMCAsyncReadWhenReady(&HMCReading))
		BLIDeadStop("M", 1);
	//-------------------------------------------------------
	if (MPUAsyncStart())
		BLIDeadStop("A", 1);
	// Clear accumulated sensor readings
	if (MPUAsyncReadWhenReady(&MPUReading)) 
		BLIDeadStop("A", 1);
	//*******************************************************
	// Update DCM until it is synchronized with current
	// orientation vector
	//-------------------------------------------------------
	uint		IsReady	= 0;
	ulong		StCount	= 0;
	//--------------------------
	while (0 == IsReady)
		{
		if (MPUAsyncReadWhenReady(&MPUReading)) 
			BLIDeadStop("A", 1);
		//----------------------------
		IsReady = DCMPerformStep(	 MPUReading.TS,
									&MPUReading.G,
									&MPUReading.A, 
									&IMUResult);
		//----------------------------
		StCount++;
		}
	//*******************************************************
	if (HMC_OK == HMCAsyncReadWhenReady(&HMCReading))
		DCMSetAzimuth(&HMCReading.M);
	//----------------------------------------------
	// Stop magnetometer as it is not used in flight
	//----------------------------------------------
	HMCAsyncStop();
	//*******************************************************
	_IMUInit = 1;
	//*******************************************************
	BLIAsyncStop();
	//*******************************************************
	return StCount;
	}
//************************************************************

