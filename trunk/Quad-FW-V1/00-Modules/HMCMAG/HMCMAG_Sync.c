#include "HMCMAG\HMCMAG_Local.h"
//*******************************************************
#ifdef __MAG_Use__
//*******************************************************

//=============================================================
// Synchronous READ SAMPLE API (visible externally)
//-------------------------------------------------------------
uint		HMCReadSample(HMCSample* pSample)
	{
	uint			RC		= 0;
	_HMCRawData		RawData;
	//-----------------------------------------
	// Read HMC measurement!
	//-----------------------------------------
	if ( (RC = _HMCReadRawData(&RawData)) )	
		return RC;							// Error...
	//-----------------------------------------------
	// Timestamp and Count
	//-----------------------------------------------
	pSample->TS 	= TMRGetTS();
	pSample->Count	= ++_HMC_Count;
	//-----------------------------------------------
	// Magnetic field - adjusted for sensitivity
	// and Hard Iron
	//-----------------------------------------------
	VectorSet	(
				RawData.MX * _HMC_Sensitivity - _HMC_HardIron.X,
				RawData.MY * _HMC_Sensitivity - _HMC_HardIron.Y,
				RawData.MZ * _HMC_Sensitivity - _HMC_HardIron.Z,
				&pSample->M
				);
	//-----------------------------------------------
	// Adjustment for Soft Iron - Multiplication of 
	// soft iron adjustment matrix by magnetic vector
	// written by resulting vector components. 
	//-----------------------------------------------
	float MX	= VectorDotProduct(&_HMC_SoftIron_X, &pSample->M);
	float MY	= VectorDotProduct(&_HMC_SoftIron_Y, &pSample->M);
	float MZ	= VectorDotProduct(&_HMC_SoftIron_Z, &pSample->M);
	VectorSet	(MX, MY, MZ, &pSample->M);
	//-----------------------------------------------
	return	HMC_OK;
	}
//=============================================================


//-----------------------------------------------------
// Synchronous READ (internal)
//-----------------------------------------------------
uint	_HMCRead(	byte 	Register, 
					byte*	Buffer,
					uint  	BufLen	)
	{
	if (!_HMC_Init)
		return HMC_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	uint	RC		= I2C_OK;
	uint	Count	= 0;
	//---------------------------------------------------------
RetryNACK:
	RC = I2CSyncRead(_HMC_Addr, Register, Buffer, BufLen);
	switch (RC)
		{
		case I2C_OK:
			return I2C_OK;

		case I2C_NACK:
			Count++;
			if (Count < I2C_NACKRetry)
				goto RetryNACK;

		default:
			return	RC;			
		}
	}


//-----------------------------------------------------
// Synchronous WRITE (internal)
//-----------------------------------------------------
uint	_HMCWrite(	byte	 Register, 
					byte*	 Buffer,
					uint	 BufLen )
	{
	if (!_HMC_Init)
		return HMC_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	uint	RC		= I2C_OK;
	uint	Count	= 0;
	//---------------------------------------------------------
RetryNACK:
	RC = I2CSyncWrite(_HMC_Addr, Register, Buffer, BufLen);
	switch (RC)
		{
		case I2C_OK:
			return I2C_OK;

		case I2C_NACK:
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
uint	_HMCReadRawData(_pHMCRawData pData)
	{
	uint	RC		= 0;
	byte	Status	= 0;
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
	if ( (RC = HMCReadStatus(&Status)) )	
		return RC;							// Error...
	if ( (Status & 0x01) != 0x01 )	
		{
		uint	i;
		for (i = 0; i < 1250; i++);  // ~250 us Short delay...
		goto Retry;
		}

	//-----------------------------------------------
	// HMC has a measurement!
	//-----------------------------------------------
	// Please NOTE:
	// the six bytes returned represent values of X,
	// Z, and Y registers. As we use the right-handed
	// coordinate system with axis Z pointing down and
	// considering the orientation of the sensor on
	// the board, we make the following adjustments:
	//	Xres = -X;
	//	Zres = -Z;
	//	Yres =  Y;
	//-----------------------------------------------
	byte	Data[6];
	// Read measurement
	if ( (RC = _HMCRead(0x03, Data, 6) ) )	
		return RC;							// Error...
	//-----------------------------------------------
	// Magnetometer
	//-----------------------------------------------
	U.VByte[1]	= Data[0];
	U.VByte[0]	= Data[1];
	if (U.VInt < -2048)
		return HMC_OWFL;
	pData->MX = -U.VInt;		//	Xres = -X;
	//-----------------------------------------------
	U.VByte[1]	= Data[2];
	U.VByte[0]	= Data[3];
	if (U.VInt < -2048)
		return HMC_OWFL;
	pData->MZ = -U.VInt;		//	Zres = -Z;
	//-----------------------------------------------
	U.VByte[1]	= Data[4];
	U.VByte[0]	= Data[5];
	if (U.VInt < -2048)
		return HMC_OWFL;
	pData->MY = U.VInt;			//	Yres =  Y;
	//-----------------------------------------------
	return	HMC_OK;
	}
//=============================================================


//***************************************************************
#endif /* __MAG_Use__ */


