#include "MPU\MPU_Local.h"


//-----------------------------------------------------
// Management functions (synchronous interface)
//-----------------------------------------------------
uint	MPUReadID(uint MPUx, byte*	 mpuID)
	{
	return 	MPUGetByte(MPUx, MPU6050_WHO_AM_I, mpuID);
	}
//-----------------------------------------------------
uint	MPUGetDLPF(uint MPUx, byte*	 mpuDLPF)
	{
	return 	MPUGetByte(MPUx, MPU6050_CONFIG, mpuDLPF);
	}
//-----------------------------------------------------
uint	MPUGetINT(uint MPUx, byte*	 mpuINT)
	{
	return 	MPUGetByte(MPUx,MPU6050_INT_STATUS, mpuINT);
	}
//-----------------------------------------------------
uint	MPUGetPWRM1(uint MPUx, byte*	 mpuPWRM1)
	{
	return 	MPUGetByte(MPUx,MPU6050_PWR_MGMT_1, mpuPWRM1);
	}
//-----------------------------------------------------
