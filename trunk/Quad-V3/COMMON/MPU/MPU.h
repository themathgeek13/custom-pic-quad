#include "System.h"
#include "I2C\I2C.h"
#include "Vector\Vector.h"

//=====================================================
#ifndef __MPU_H
#define __MPU_H
//=====================================================
#define	MPU_OK		 I2CRC_OK
//---------------------------------
#define MPU_ABSY	 I2CRC_MAX + 1
#define MPU_NRDY	 I2CRC_MAX + 2
#define MPU_NACT	 I2CRC_MAX + 3
#define MPU_NOTINIT	 I2CRC_MAX + 4
#define MPU_FAIL	 I2CRC_MAX + 5
#define MPU_NOTA	 I2CRC_MAX + 6
#define MPU_TMOUT	 I2CRC_MAX + 7
//==================================================================

//-----------------------------------------
// MPU-6050 Gyro sensitivity in degrees/sec
//-----------------------------------------
typedef enum
	{
	MPU_GYRO_250ds,
	MPU_GYRO_500ds,
	MPU_GYRO_1000ds,
	MPU_GYRO_2000ds
	}	MPU_FS_SEL;

//-----------------------------------------
// MPU-6050 Acc sensitivity in "g"
//-----------------------------------------
typedef enum
	{
	MPU_ACC_2g,
	MPU_ACC_4g,
	MPU_ACC_8g,
	MPU_ACC_16g,
	}	MPU_AFS_SEL;


//-----------------------------------------------------
// Processed MPU Data Sample
//-----------------------------------------------------
typedef	struct
	{
	ulong	TS;		// Timestamp of the cycle
	//-----------------------------------------------
	// Temperature	(in degrees C)
	//-----------------------------------------------
	float	Temp;
	//-----------------------------------------------
	// Accelerometer (in units of G)
	//-----------------------------------------------
	Vector	A;
	//-----------------------------------------------
	// Gyroscopes	(in Rad/sec)
	//-----------------------------------------------
	Vector	G;
	//-----------------------------------------------
	}	MPUData;


//-----------------------------------------------------
// Custom MPU functions
//-----------------------------------------------------
uint	MPUInit(byte RateDiv,	byte DLPF,
				MPU_FS_SEL GS,	MPU_AFS_SEL AS);
//-----------------------------------------------------
// Low-pass filter (DLPF) configuration:
//-----------------------------------------------------
//	DLPF	Accelerometer (Fs=1kHz) 	Gyroscope  
//			BW (Hz)	Delay (ms)			BW (Hz)	Delay (ms)	Fs (kHz)
//	0		260		 0.0				256		 0.98		8
//	1		184		 2.0				188		 1.9		1
//	2		 94		 3.0				 98		 2.8		1
//	3		 44		 4.9				 42		 4.8		1
//	4		 21		 8.5				 20		 8.3		1
//	5		 10		13.8				 10		13.4		1
//	6		  5		19.0				  5		18.6		1
//	7		RSV		----				RSV		----		8
//-----------------------------------------------------
uint	MPUReset(uint MPUx,	// Index (1-based) of the sensor
				 byte RateDiv, byte DLPF, MPU_FS_SEL GS,
			     MPU_AFS_SEL AS);
//-----------------------------------------------------
uint	MPUCalibrate(uint MPUx);
//-----------------------------------------------------


//-----------------------------------------------------
uint	MPUGetByte(uint MPUx, byte Address, byte* Value);
uint	MPUSetByte(uint MPUx, byte Address, byte  Value);
//-----------------------------------------------------
uint	MPUReadID(	uint MPUx, byte*	 mpuID);
uint	MPUGetDLPF(	uint MPUx, byte*	 mpuDLPF);
uint	MPUGetINT(	uint MPUx, byte*	 mpuINT);
uint	MPUGetPWRM1(uint MPUx, byte*	 mpuPWRM1);
//-----------------------------------------------------

//-----------------------------------------------------
// Synchronous interface
//-----------------------------------------------------
uint	MPUReadSample(uint MPUx, MPUData* pSample);
//-------------------------------------------------------------
uint	MPUReadRawSample(uint MPUx, MPUData* pSample);

//-----------------------------------------------------
// Asynchronous interface
//-----------------------------------------------------
uint	MPUAsyncStart(uint MPUx);
uint	MPUAsyncStop(uint MPUx);

uint	MPUAsyncRead(uint MPUx, MPUData* pSample);
uint	MPUAsyncReadIfReady(uint MPUx, MPUData* pSample);
uint	MPUAsyncReadWhenReady(uint MPUx, MPUData* pSample);

//=====================================================
#endif		// __MPU_H
