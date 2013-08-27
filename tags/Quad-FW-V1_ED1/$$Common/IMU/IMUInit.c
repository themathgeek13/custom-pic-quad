#include "IMU\IMULocal.h"

//************************************************************
volatile uint	_IMUInit 		= 0;	// IMU initializtion flag
//************************************************************

//************************************************************
ulong	IMUInit()
	{
	_IMUInit 		= 0;
	//*******************************************************
	BLIAsyncMorse("W", 1);
	//*******************************************************
	if (MPUAsyncStart())
		BLIDeadStop("A", 1);
	//*******************************************************
	MPUSample	MPUReading;
	DCMData		IMUResult;
	//*******************************************************
	// Clear accumulated sensor readings
	//-------------------------------------------------------
	if (MPUAsyncReadWhenReady(&MPUReading)) 
		BLIDeadStop("A", 1);
	//*******************************************************
	// Reset DCM algorithm
	//-------------------------------------------------------
	DCMReset();
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
	_IMUInit = 1;
	//*******************************************************
	BLIAsyncStop();
	//*******************************************************
	return StCount;
	}
//************************************************************

