#include "MPU6050\MPU6050_Local.h"


//-----------------------------------------------------
// Management functions (synchronous interface)
//-----------------------------------------------------
uint	MPUReadID(	byte*	 mpuID)
	{
	return 	_MPURead(0x75, mpuID, 1);
	}
//-----------------------------------------------------
uint	MPUGetDLPF(	byte*	 mpuDLPF)
	{
	return 	_MPURead(0x1A, mpuDLPF, 1);
	}
//-----------------------------------------------------
uint	MPUGetINT(byte*	 mpuINT)
	{
	return 	_MPURead(0x3A, mpuINT, 1);
	}
//-----------------------------------------------------
uint	MPUGetPWRM1(byte*	 mpuPWRM1)
	{
	return 	_MPURead(0x6B, mpuPWRM1, 1);
	}
//-----------------------------------------------------
