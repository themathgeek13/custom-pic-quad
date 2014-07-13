#include "System.h"
#include "I2C\I2C.h"
#include "Vector\Vector.h"

//=====================================================
#ifndef __MPU6050_H
#define __MPU6050_H
//=====================================================
#define	MPU_OK		 I2CRC_OK
//---------------------------------
#define MPU_ABSY	 I2CRC_MAX + 1
#define MPU_NRDY	 I2CRC_MAX + 2
#define MPU_NACT	 I2CRC_MAX + 3
#define MPU_NOTINIT	 I2CRC_MAX + 4

//-----------------------------------------------------
// Custom MPU Data Sample
//-----------------------------------------------------
typedef	struct
	{
	ulong	TS;		// Timestamp of the cycle
	//-----------------------------------------------
	ulong	Count;	// Sequential number of the sample
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
uint	MPUInit(byte RateDiv, byte DLPF);
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
uint	MPUReset(byte RateDiv, byte DLPF);
//-----------------------------------------------------
uint	MPUCalibrate();
//-----------------------------------------------------


//-----------------------------------------------------
uint	MPUReadID(	byte*	 mpuID);
uint	MPUGetDLPF(	byte*	 mpuDLPF);
uint	MPUGetINT(	byte*	 mpuINT);
uint	MPUGetPWRM1(byte*	 mpuPWRM1);
//-----------------------------------------------------

//-----------------------------------------------------
// Synchronous interface
//-----------------------------------------------------
uint	MPUReadSample(MPUData* pSample);

//-----------------------------------------------------
// Asynchronous interface
//-----------------------------------------------------
uint	MPUAsyncStart();
uint	MPUAsyncStop();

uint	MPUAsyncRead(MPUData* pSample);
uint	MPUAsyncReadIfReady(MPUData* pSample);
uint	MPUAsyncReadWhenReady(MPUData* pSample);

//=====================================================
#endif
