#include "MPU6050/MPU6050_Local.h"

//=============================================================
// Synchronous READ SAMPLE API (visible externally)
//-------------------------------------------------------------
uint		MPUReadSample(MPUData* pSample)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//-----------------------
	if (_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...
	//*********************************************************
	uint			RC		= 0;
	_MPURawData		RawData;
	float			TDev;
	//-----------------------------------------
	// Read MPU measurement!
	//-----------------------------------------
	if ( (RC = _MPUReadRawData(&RawData)) )	
		return RC;							// Error...
	//-----------------------------------------------
	// Timestamp and Count
	//-----------------------------------------------
	pSample->TS 	= TMRGetTS();
	pSample->Count	= ++_MPU_Count;
	//-----------------------------------------------
	// Temperature (C) (will be used in subsequent
	// temperature compensation calculation)
	//-----------------------------------------------
	pSample->Temp = (RawData.Temp - _MPU_Temp_OffsetTo0) * _MPU_Temp_Sensitivity;
	//-----------------------------------------------
	// Acceleration (G)
	//-----------------------------------------------
	TDev	= pSample->Temp - _MPU_Accl_BaseTemp;
	//-----------------------------------------------
	VectorSet	(
				((float)RawData.AX - (_MPU_Accl_XOffset + _MPU_Accl_XSlope*TDev)) * _MPU_Accl_Sensitivity,
				((float)RawData.AY - (_MPU_Accl_YOffset + _MPU_Accl_YSlope*TDev)) * _MPU_Accl_Sensitivity,
				((float)RawData.AZ - (_MPU_Accl_ZOffset + _MPU_Accl_ZSlope*TDev)) * _MPU_Accl_Sensitivity,
				&pSample->A
				);
	//-----------------------------------------------
	// Gyroscopes (Rad/sec)
	//-----------------------------------------------
	TDev	= pSample->Temp - _MPU_Gyro_BaseTemp;
	//-----------------------------------------------
	VectorSet	(
				((float)RawData.GX - (_MPU_Gyro_XOffset + _MPU_Gyro_XSlope*TDev)) * _MPU_Gyro_Sensitivity,
				((float)RawData.GY - (_MPU_Gyro_YOffset + _MPU_Gyro_YSlope*TDev)) * _MPU_Gyro_Sensitivity,
				((float)RawData.GZ - (_MPU_Gyro_ZOffset + _MPU_Gyro_ZSlope*TDev)) * _MPU_Gyro_Sensitivity,
				&pSample->G
				);
	//-----------------------------------------------
	return	MPU_OK;
	}
//=============================================================


//=============================================================
// Synchronous READ (internal)
//-------------------------------------------------------------
uint	_MPURead(	byte 	Register, 
					byte*	Buffer,
					uint  	BufLen	)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//-----------------------
	if (_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...
	//*********************************************************
	uint	RC		= MPU_OK;
	uint	Count	= 0;
	//---------------------------------------------------------
RetryNACK:
	RC = I2CSyncRead(_MPU_Addr, Register, Buffer, BufLen);
	switch (RC)
		{
		case I2CRC_OK:
			return MPU_OK;

		case I2CRC_NACK:
			Count++;
			if (Count < I2C_NACKRetry)
				goto RetryNACK;

		default:
			return	RC;			
		}
	}
//=============================================================

//=============================================================
// Synchronous WRITE (internal)
//-------------------------------------------------------------
uint	_MPUWrite(	byte	 Register, 
					byte*	 Buffer,
					uint	 BufLen )
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//-----------------------
	if (_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...
	//*********************************************************
	uint	RC		= MPU_OK;
	uint	Count	= 0;
	//---------------------------------------------------------
RetryNACK:
	RC = I2CSyncWrite(_MPU_Addr, Register, Buffer, BufLen);
	switch (RC)
		{
		case I2CRC_OK:
			return MPU_OK;

		case I2CRC_NACK:
			Count++;
			if (Count < I2C_NACKRetry)
				goto RetryNACK;

		default:
			return	RC;			
		}
	}
//=============================================================

//=============================================================
// Synchronous READ of the raw sensor data
//-------------------------------------------------------------
uint	_MPUReadRawData(_pMPURawData pData)
	{
	int		RC		= 0;
	byte	Status	= 0;
	int		i;
	//-----------------------------------------
	// "Unpack" data
	//-----------------------------------------
	union
		{
		int		VInt;
		byte	VByte[2];
		}	U;
	//-----------------------------------

Retry:	// Wait for RDY signal
	if ( (RC = MPUGetINT(&Status)) )	
		return RC;							// Error...
	if ( (Status & 0x01) != 0x01 )	
		{
		for (i = 0; i < 1000; i++);  // Short delay...
		goto Retry;
		}

	//-----------------------------------------
	// MPU has a measurement!
	//-----------------------------------------
	byte	Data[14];
	// Read measurement
	if ( (RC = _MPURead(0x3B, Data, 14) ) )	
		return RC;							// Error...
	//===============================================
	// Due to orientation of the sensor on the board
	// in reference to orientation of the board in
	// the vehicle, direction of the axis need to change
	// to align right-handed coordinate system with
	// the vehicle
	//===============================================
	// Accelerometer:
	//-----------------------------------------------
	// 	Yveh	= -Xa
	//-----------------------------------------------
	U.VByte[1]	= Data[0];
	U.VByte[0]	= Data[1];
	pData->AY 	= -U.VInt;
	//-----------------------------------------------
	// 	Xveh	= -Ya
	//-----------------------------------------------
	U.VByte[1]	= Data[2];
	U.VByte[0]	= Data[3];
	pData->AX 	= -U.VInt;
	//-----------------------------------------------
	// 	Zveh = -Za
	//-----------------------------------------------
	U.VByte[1]	= Data[4];
	U.VByte[0]	= Data[5];
	pData->AZ 	= -U.VInt;
	//-----------------------------------------------
	// Temperature
	//-----------------------------------------------
	U.VByte[1]	= Data[6];
	U.VByte[0]	= Data[7];
	pData->Temp = U.VInt;
	//-----------------------------------------------
	// Gyroscopes
	//-----------------------------------------------
	// 	Yveh	= -Xa
	//-----------------------------------------------
	U.VByte[1]	= Data[8];
	U.VByte[0]	= Data[9];
	pData->GY 	= -U.VInt;
	//-----------------------------------------------
	// 	Xveh	= -Ya
	//-----------------------------------------------
	U.VByte[1]	= Data[10];
	U.VByte[0]	= Data[11];
	pData->GX 	= -U.VInt;
	//-----------------------------------------------
	//	Zveh	= -Za
	//-----------------------------------------------
	U.VByte[1]	= Data[12];
	U.VByte[0]	= Data[13];
	pData->GZ 	= -U.VInt;
	//-----------------------------------------------
	return	MPU_OK;
	}
//=============================================================

//=============================================================
uint	_MPUCalibrateSync()
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//-----------------------
	if (_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...

	//=========================================================
	// Local Variables
	//---------------------------------------------------------
	ulong Alarm	= TMRSetAlarm(2000);	// Set Alarm time 2 sec
										// into the future.
	//---------------------------------------------------------
	_MPURawData		RawData;
	//------------------------
	long			GX			= 0;
	long			GY			= 0;
	long			GZ			= 0;
	long			T			= 0;
	//------------------------
	long			SampleCount	= 0;
	//------------------------
	uint			RC			= MPU_OK;	// Pre-set to Success
	//=========================================================

	//=========================================================
	// Reset  Gyro offsets...
	//---------------------------------------------------------
	_MPU_Gyro_XOffset		= 0;
	_MPU_Gyro_YOffset		= 0;
	_MPU_Gyro_ZOffset		= 0;
	//---------------------------------------------------------
	// To collect averages we would like to "watch" MPU for at
	// least 2 seconds; number of samples will be variable
	// depending on the value of RateDiv
	//---------------------------------------------------------
	do
		{
		if ( (RC = _MPUReadRawData(&RawData)) )
			return RC;							// Error...
		//------------------
		GX += RawData.GX;
		GY += RawData.GY;
		GZ += RawData.GZ;
		T  += RawData.Temp;
		//------------------
		SampleCount++;
		}
	while ( FALSE == TMRTestAlarm(Alarm) );
	//---------------------------------------
	// Gyro offset is calculated in LSB units
	//---------------------------------------
	_MPU_Gyro_XOffset	= (float)GX/(float)SampleCount;
	_MPU_Gyro_YOffset	= (float)GY/(float)SampleCount;
	_MPU_Gyro_ZOffset	= (float)GZ/(float)SampleCount;
	//---------------------------------------
	// Base temperature converted to degrees C
	//---------------------------------------
	_MPU_Gyro_BaseTemp	= ((float)T/(float)SampleCount - _MPU_Temp_OffsetTo0)
						  * _MPU_Temp_Sensitivity;
	//*********************************************************
	return MPU_OK;
	}



