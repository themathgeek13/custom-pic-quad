#include "MPU\MPU_Local.h"

//==================================================================
// Variables shared (across MPU modules) - set in MPUInit
//==================================================================
byte		_MPU_IL		= 0; 	// MPU (INT1) interrupt level
uint		_MPU_Init	= 0;	// Init flag
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="MPU_CB - MPU Library control block">
//==================================================================
#ifdef Use_MPU1
	MPU_CB			MPU1_CB;
#endif
#ifdef Use_MPU2
	MPU_CB			MPU2_CB;
#endif
//------------------------------------------------------------------
// </editor-fold>
//==================================================================


//=============================================================
// Synchronous READ (internal)
//-------------------------------------------------------------
uint	_MPURead(	MPU_CB*	pCB,
					byte 	Register,
					byte*	Buffer,
					uint  	BufLen	)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//-----------------------
	if (pCB->_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...
	//*********************************************************
	uint	RC		= MPU_OK;
	uint	Count	= 0;
	//---------------------------------------------------------
RetryNACK:
	RC = I2CSyncRead(pCB->_MPU_IDCx, pCB->_MPU_Addr, Register, Buffer, BufLen);
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
uint	_MPUWrite(	MPU_CB*	 pCB,
					byte	 Register,
					byte*	 Buffer,
					uint	 BufLen )
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//-----------------------
	if (pCB->_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...
	//*********************************************************
	uint	RC		= MPU_OK;
	uint	Count	= 0;
	//---------------------------------------------------------
RetryNACK:
	RC = I2CSyncWrite(pCB->_MPU_IDCx, pCB->_MPU_Addr, Register, Buffer, BufLen);
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
uint	_MPUReadRawData(MPU_CB*	pCB, _MPURawData* pData)
	{
	int		RC		= 0;
	byte	Status	= 0;
	ulong	Alarm;
	//-----------------------------------------
	// Structure facilitating data "Unpack"
	//-----------------------------------------
	union
		{
		int		VInt;
		byte	VByte[2];
		}	U;
	//-----------------------------------
	if ( (RC = _MPURead(pCB, MPU6050_INT_STATUS, &Status, 1)) )
		return RC;							// Error...
	//-----------------------------------
	Alarm = TMRSetAlarm(50);	// Expecting to get samplewithin 50 msec
	//-----------------------------------
	while ( (Status & 0x01) != 0x01 )
		{
		TMRDelayTicks(1);  // Short delay...
		if ( (RC = _MPURead(pCB, MPU6050_INT_STATUS, &Status, 1)) )
			return RC;						// Error...
		if (TMRCheckAlarm(Alarm))
			return MPU_TMOUT;
		}

	//-----------------------------------------
	// MPU has a measurement!
	//-----------------------------------------
	byte	Data[14];
	// Read measurement
	if ( (RC = _MPURead(pCB, MPU6050_DATA_START, Data, 14) ) )
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
uint	_MPUCalibrateSync(MPU_CB*	pCB)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//-----------------------
	if (pCB->_MPU_Async)
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
	pCB->_MPU_Gyro_XOffset		= 0;
	pCB->_MPU_Gyro_YOffset		= 0;
	pCB->_MPU_Gyro_ZOffset		= 0;
	//---------------------------------------------------------
	// To collect averages we would like to "watch" MPU for at
	// least 2 seconds; number of samples will be variable
	// depending on the value of RateDiv
	//---------------------------------------------------------
	do
		{
		if ( (RC = _MPUReadRawData(pCB, &RawData)) )
			return RC;							// Error...
		//------------------
		GX += RawData.GX;
		GY += RawData.GY;
		GZ += RawData.GZ;
		T  += RawData.Temp;
		//------------------
		SampleCount++;
		}
	while ( !TMRCheckAlarm(Alarm) );
	//---------------------------------------
	// Gyro offset is calculated in LSB units
	//---------------------------------------
	pCB->_MPU_Gyro_XOffset	= (float)GX/(float)SampleCount;
	pCB->_MPU_Gyro_YOffset	= (float)GY/(float)SampleCount;
	pCB->_MPU_Gyro_ZOffset	= (float)GZ/(float)SampleCount;
	//---------------------------------------
	// Base temperature converted to degrees C
	//---------------------------------------
	pCB->_MPU_Gyro_BaseTemp	= ((float)T/(float)SampleCount - pCB->_MPU_Temp_OffsetTo0)
						  * pCB->_MPU_Temp_Sensitivity;
	//*********************************************************
	return MPU_OK;
	}


