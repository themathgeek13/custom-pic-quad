#include "MPU\MPU_Local.h"


//-----------------------------------------------------
// Byte-wise Get/Put functions
//-----------------------------------------------------
uint	MPUGetByte(byte Address, byte* Value)
	{
	return _MPURead(Address, Value, 1);
	}
//-----------------------------------------------------
uint	MPUSetByte(byte Address, byte  Value)
	{
	byte Temp = Value;
	return _MPUWrite(Address, &Temp, 1);
	}
//-----------------------------------------------------
// Management functions (synchronous interface)
//-----------------------------------------------------
uint	MPUReadID(	byte*	 mpuID)
	{
	return 	MPUGetByte(MPU6050_WHO_AM_I, mpuID);
	}
//-----------------------------------------------------
uint	MPUGetDLPF(	byte*	 mpuDLPF)
	{
	return 	MPUGetByte(MPU6050_CONFIG, mpuDLPF);
	}
//-----------------------------------------------------
uint	MPUGetINT(byte*	 mpuINT)
	{
	return 	MPUGetByte(MPU6050_INT_STATUS, mpuINT);
	}
//-----------------------------------------------------
uint	MPUGetPWRM1(byte*	 mpuPWRM1)
	{
	return 	MPUGetByte(MPU6050_PWR_MGMT_1, mpuPWRM1);
	}
//-----------------------------------------------------
