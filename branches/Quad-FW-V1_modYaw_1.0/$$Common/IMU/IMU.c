#include "IMU\IMULocal.h"


//************************************************************
uint	IMUGetUpdate(DCMData* IMUResult)
	{
	//---------------------------
	MPUSample	MPUReading;
	//=======================================================
	return IMUGetUpdateWithSamples(&MPUReading, IMUResult);
	}
//************************************************************

//************************************************************
uint	IMUGetUpdateWhenReady(DCMData* IMUResult)
	{
	//---------------------------
	MPUSample	MPUReading;
	//=======================================================
	if (0 == _IMUInit)
		IMUInit();
	//=======================================================
	// Take MPU (Gyro/Acc) sample
	//=======================================================
	MPUAsyncReadWhenReady(&MPUReading);
	//=======================================================
	// Perform rotation step...
	//=======================================================
	DCMPerformStep(	&MPUReading.G, &MPUReading.A, 
					IMUResult);
	//-------------------------------------------------------
	return IMU_OK;
	}
//************************************************************


//************************************************************
uint	IMUGetUpdateWithSamples(MPUSample*	MPUReading,
								DCMData* 	IMUResult	)
	{
	if (0 == _IMUInit)
		IMUInit();
	//=======================================================
	// Take MPU (Gyro/Acc) sample
	//=======================================================
	if (MPU_OK != MPUAsyncReadIfReady(MPUReading))
		return IMU_STLMPU;
	//=======================================================
	// Perform rotation step...
	//=======================================================
	DCMPerformStep(	&MPUReading->G, &MPUReading->A, 
					IMUResult);
	//-------------------------------------------------------
	return IMU_OK;
	}
//************************************************************



