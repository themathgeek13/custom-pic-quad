#include "IMU/IMULocal.h"


//************************************************************
uint	IMUGetUpdateWhenReady(DCMData* IMUResult)
	{
	//---------------------------
	MPUData	MPUReading;
	//=======================================================
	if (0 == _IMUReady)
		return IMU_NOTRDY;
	//=======================================================
	// Take MPU (Gyro/Acc) sample
	//=======================================================
	MPUAsyncReadWhenReady(&MPUReading);
	//=======================================================
	// Perform rotation step...
	//=======================================================
	DCMPerformStep(	MPUReading.TS, &MPUReading.G, &MPUReading.A,
					IMUResult);
	//-------------------------------------------------------
	return IMU_OK;
	}
//************************************************************

//************************************************************
uint	IMUGetUpdate(DCMData* IMUResult)
	{
	//---------------------------
	MPUData	MPUReading;
	//=======================================================
	if (0 == _IMUReady)
		return IMU_NOTRDY;
	//=======================================================
	// Take MPU (Gyro/Acc) sample
	//=======================================================
	if (MPU_OK != MPUAsyncReadIfReady(&MPUReading))
		return IMU_STLMPU;
	//=======================================================
	// Perform rotation step...
	//=======================================================
	DCMPerformStep(	MPUReading.TS, &MPUReading.G, &MPUReading.A,
					IMUResult);
	//-------------------------------------------------------
	return IMU_OK;
	}
//************************************************************



