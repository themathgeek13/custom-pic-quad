#include "System.h"
//*****************************************************
#include "Vector\Vector.h"

//=====================================================
#ifndef __HMCMAG_H
#define __HMCMAG_H
//=====================================================
#define	HMC_OK		 I2CRC_OK
#define HMC_ABSY	 I2CRC_MAX + 1
#define HMC_NRDY	 I2CRC_MAX + 2
#define HMC_NACT	 I2CRC_MAX + 3
#define HMC_NOTINIT	 I2CRC_MAX + 4
#define HMC_OWFL	 I2CRC_MAX + 5

//-----------------------------------------------------
// Custom HMC Data Sample
//-----------------------------------------------------
typedef	struct
	{
	ulong	TS;		// Timestamp of the cycle
	//-----------------------------------------------
	ulong	Count;	// Sequential number of the sample
	//-----------------------------------------------
	// Magnetometer measurement (in mGs)
	//-----------------------------------------------
	Vector	M;
	//-----------------------------------------------
	}	HMCSample;

//-----------------------------------------------------
// Custom HMC functions
//-----------------------------------------------------
// ODR - Output Data Rate (3-bit field)
//		 0	-  0.75 Hz
//		 1	-  1.50 Hz
//		 2	-  3.00 Hz
//		 3	-  7.50 Hz
//		 4	- 15.00 Hz (default)
//		 5	- 30.00 Hz
//		 6	- 75.00 Hz
//		 7	- Reserved
// Gain - Sensitivity gain (3-bit field)
//		 0	-  +/- 0.88 Ga
//		 1	-  +/- 1.30 Ga
//		 2	-  +/- 1.90 Ga
//		 3	-  +/- 2.50 Ga
//		 4	-  +/- 4.00 Ga
//		 5	-  +/- 4.70 Ga
//		 6	-  +/- 5.60 Ga
//		 7	-  +/- 8.10 Ga
// DLPF - 2^DLPF mumber of samples averaged (1 to 8)
//		  per measurement output (2-bit field)
//		 0	-  1 (default)
//		 1	-  2
//		 2	-  4
//		 3	-  8

uint	HMCInit(byte ODR, byte Gain, byte DLPF);
uint	HMCReset(byte ODR, byte Gain, byte DLPF);

//-----------------------------------------------------
// Management functions (synchronous interface)
//-----------------------------------------------------
uint	HMCReadID(		byte*	 Buffer,
						uint	 BufLen );

uint	HMCReadStatus(	byte*	 Status);

uint	HMCGetMode(		byte*	 Mode);
uint	HMCSetMode(		byte	 Mode);

uint	HMCGetRegA(		byte*	 RegA);
uint	HMCSetRegA(		byte	 RegA);

uint	HMCGetRegB(		byte*	 RegB);
uint	HMCSetRegB(		byte	 RegB);

//-----------------------------------------------------
// Synchronous interface
//-----------------------------------------------------
uint	HMCReadSample(HMCSample* pSample);

//-----------------------------------------------------
// Asynchronous interface
//-----------------------------------------------------
uint	HMCAsyncStart();
uint	HMCAsyncStop();

uint	HMCAsyncRead(HMCSample* pSample);
uint	HMCAsyncReadIfReady(HMCSample* pSample);
uint	HMCAsyncReadWhenReady(HMCSample* pSample);

//=====================================================
#endif

