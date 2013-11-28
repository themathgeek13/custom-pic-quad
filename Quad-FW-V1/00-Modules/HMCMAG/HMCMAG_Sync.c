#include "I2C\I2C_Profile.h"
#include "HMCMAG\HMCMAG_Local.h"
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
	uint	RC		= HMC_OK;
	uint	Count	= 0;
	//---------------------------------------------------------
RetryNACK:
	RC = I2CSyncRead(_HMC_Addr, Register, Buffer, BufLen);
	switch (RC)
		{
		case I2CRC_OK:
			return I2CRC_OK;

		case I2CRC_NACK:
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
	uint	RC		= HMC_OK;
	uint	Count	= 0;
	//---------------------------------------------------------
RetryNACK:
	RC = I2CSyncWrite(_HMC_Addr, Register, Buffer, BufLen);
	switch (RC)
		{
		case I2CRC_OK:
			return HMC_OK;

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
		struct
			{
			byte	LSB;
			byte	MSB;
			};
		}	U;
	//-----------------------------------

Retry:	// Wait for RDY signal
	if ( (RC = HMCReadStatus(&Status)) )	
		return RC;							// Error...
	if ( (Status & 0x01) != 0x01 )	
		{
		TMRDelayTicks(2);	  // ~250 us Short delay...
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
	U.MSB	= Data[0];
	U.LSB	= Data[1];
	if (U.VInt < -2048)
		return HMC_OWFL;
	pData->MX = -U.VInt;		//	Xres = -X;
	//-----------------------------------------------
	U.MSB	= Data[2];
	U.LSB	= Data[3];
	if (U.VInt < -2048)
		return HMC_OWFL;
	pData->MZ = -U.VInt;		//	Zres = -Z;
	//-----------------------------------------------
	U.MSB	= Data[4];
	U.LSB	= Data[5];
	if (U.VInt < -2048)
		return HMC_OWFL;
	pData->MY = U.VInt;			//	Yres =  Y;
	//-----------------------------------------------
	return	HMC_OK;
	}
//=============================================================



