#include "MPU\MPU_Local.h"

//=============================================================
// Byte-wise Synchronous Get/Put functions
//=============================================================
uint	MPUGetByte(uint MPUx, byte Address, byte* Value)
	{
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	return _MPURead(pCB, Address, Value, 1);
	}
//-----------------------------------------------------
uint	MPUSetByte(uint MPUx, byte Address, byte  Value)
	{
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	byte Temp = Value;
	return _MPUWrite(pCB, Address, &Temp, 1);
	}
//=============================================================

//=============================================================
// Synchronous READ RAW SAMPLE API (visible externally)
//-------------------------------------------------------------
// Rotation and acceleration data is passed to the caller
// "as-is" except for conversion to floating point. No
// adjustment for sensitivity, ZERO point offset, or temperatu-
// re compensation is performed on the data.
// The temperature data, however, is converted to actual tem-
// perature in degrees Celsius as it is based upon the coeffi-
// cients from the datasheet.
//-------------------------------------------------------------
uint		MPUReadRawSample(uint MPUx, MPUData* pSample)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (pCB->_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...
	//*********************************************************
	uint			RC		= 0;
	_MPURawData		RawData;
	//-----------------------------------------
	// Read MPU measurement!
	//-----------------------------------------
	if ( (RC = _MPUReadRawData(pCB, &RawData)) )
		return RC;							// Error...
	//-----------------------------------------------
	// Sample Timestamp
	//-----------------------------------------------
	pSample->TS 	= TMRGetTS();
	//-----------------------------------------------
	// Temperature (C)
	//-----------------------------------------------
	pSample->Temp = (RawData.Temp - pCB->_MPU_Temp_OffsetTo0) * pCB->_MPU_Temp_Sensitivity;
	//-----------------------------------------------
	// Acceleration (G)
	//-----------------------------------------------
	VectorSet	( (float)RawData.AX, (float)RawData.AY, (float)RawData.AZ, &pSample->A );
	//-----------------------------------------------
	// Gyroscopes (Rad/sec)
	//-----------------------------------------------
	VectorSet	( (float)RawData.GX, (float)RawData.GY, (float)RawData.GZ, &pSample->G );
	//-----------------------------------------------
	return	MPU_OK;
	}
//=============================================================

//=============================================================
// Synchronous READ SAMPLE API (visible externally)
//-------------------------------------------------------------
uint		MPUReadSample(uint MPUx, MPUData* pSample)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (pCB->_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...
	//*********************************************************
	uint			RC		= 0;
	_MPURawData		RawData;
	float			TDev;
	//-----------------------------------------
	// Read MPU measurement!
	//-----------------------------------------
	if ( (RC = _MPUReadRawData(pCB, &RawData)) )
		return RC;							// Error...
	//-----------------------------------------------
	// Sample Timestamp
	//-----------------------------------------------
	pSample->TS 	= TMRGetTS();
	//-----------------------------------------------
	// Temperature (C) (will be used in subsequent
	// temperature compensation calculation)
	//-----------------------------------------------
	pSample->Temp = (RawData.Temp - pCB->_MPU_Temp_OffsetTo0) * pCB->_MPU_Temp_Sensitivity;
	//-----------------------------------------------
	// Acceleration (G)
	//-----------------------------------------------
	TDev	= pSample->Temp - pCB->_MPU_Accl_BaseTemp;
	//-----------------------------------------------
	VectorSet	(
				((float)RawData.AX - (pCB->_MPU_Accl_XOffset + pCB->_MPU_Accl_XSlope*TDev)) * pCB->_MPU_Accl_Sensitivity,
				((float)RawData.AY - (pCB->_MPU_Accl_YOffset + pCB->_MPU_Accl_YSlope*TDev)) * pCB->_MPU_Accl_Sensitivity,
				((float)RawData.AZ - (pCB->_MPU_Accl_ZOffset + pCB->_MPU_Accl_ZSlope*TDev)) * pCB->_MPU_Accl_Sensitivity,
				&pSample->A
				);
	//-----------------------------------------------
	// Gyroscopes (Rad/sec)
	//-----------------------------------------------
	TDev	= pSample->Temp - pCB->_MPU_Gyro_BaseTemp;
	//-----------------------------------------------
	VectorSet	(
				((float)RawData.GX - (pCB->_MPU_Gyro_XOffset + pCB->_MPU_Gyro_XSlope*TDev)) * pCB->_MPU_Gyro_Sensitivity,
				((float)RawData.GY - (pCB->_MPU_Gyro_YOffset + pCB->_MPU_Gyro_YSlope*TDev)) * pCB->_MPU_Gyro_Sensitivity,
				((float)RawData.GZ - (pCB->_MPU_Gyro_ZOffset + pCB->_MPU_Gyro_ZSlope*TDev)) * pCB->_MPU_Gyro_Sensitivity,
				&pSample->G
				);
	//-----------------------------------------------
	return	MPU_OK;
	}
//=============================================================


