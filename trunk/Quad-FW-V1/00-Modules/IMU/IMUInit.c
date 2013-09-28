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
	#ifdef __MAG_Use__
	HMCSample	HMCReading;
	if (HMCAsyncStart())
		BLIDeadStop("M", 1);
	// Clear accumulated sensor readings
	if (HMCAsyncReadWhenReady(&HMCReading))
		BLIDeadStop("M", 1);
	#endif
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
		IsReady = DCMPerformStep(	&MPUReading.G, 
									&MPUReading.A, 
									&IMUResult);
		//----------------------------
		StCount++;
		}
	//*******************************************************
	#ifdef __MAG_Use__
	if (HMC_OK == HMCAsyncReadWhenReady(&HMCReading))
		DCMSetAzimuth(&HMCReading.M);
	//----------------------------------------------
	// Stop magnetometer as it is not used in flight
	//----------------------------------------------
	HMCAsyncStop();
	#endif
	//*******************************************************
	_IMUInit = 1;
	//*******************************************************
	BLIAsyncStop();
	//*******************************************************
	return StCount;
	}
//************************************************************

