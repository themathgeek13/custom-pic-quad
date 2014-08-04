#include "System.h"
#include "Vector\Vector.h"
//=====================================================
#ifndef HMCSPI_H
#define	HMCSPI_H
//=====================================================
typedef enum _HMC_RC
	{
        HMC_OK		= 0,		// No error
	HMC_InvArg,				// Invalid call arguments
	HMC_NotInit,			// Module is not initialized
	HMC_OWFL,				// Range exceeded - reduce gain!
	//-----------------------------
        HMC_NoAsync,			// Async mode not started
	HMC_AsyncNotRdy			// Async data is not ready yet
	}	HMC_RC;
//=====================================================
typedef struct
	{
	ulong	TS;		// Measurement time stamp
	//---------------------------------------
	Vector	M;
	}	HMCData;
//=====================================================

//=====================================================
// Initialization/Configuration routines
//=====================================================
HMC_RC	HMC_Init(byte IL, byte ODR, byte Gain, byte DLPF);
//-----------------------------------------------------
HMC_RC	HMC_ReSet(byte ODR, byte Gain, byte DLPF);
//-----------------------------------------------------
// Single byte register reads
//-----------------------------------------------------
HMC_RC	HMC_ReadA(byte* A);
HMC_RC	HMC_ReadB(byte* B);
HMC_RC	HMC_ReadMode(byte* Mode);
HMC_RC	HMC_ReadStatus(byte* Status);
//-----------------------------------------------------
// Multi-byte register reads
//-----------------------------------------------------
HMC_RC	HMC_ReadControl(byte* Config);
HMC_RC	HMC_ReadID(byte* ID);
//=====================================================

//=====================================================
// Synchronous data retrieval routines
//=====================================================
// Read (sync) raw sensor data
//-----------------------------------------------------
HMC_RC	HMC_ReadRaw(int* X, int* Y, int* Z);
//-----------------------------------------------------
// Read (sync) normalized sensor data
//-----------------------------------------------------
HMC_RC	HMC_ReadSample(HMCData* Sample);
//=====================================================

//=====================================================
// Asyncronous control and data retrieval routines
//=====================================================
HMC_RC		HMC_AsyncStart();
HMC_RC		HMC_AsyncStop();
HMC_RC		HMC_AsyncReadIfReady(HMCData* Sample);
HMC_RC		HMC_AsyncReadWhenReady(HMCData* Sample);
//=====================================================
#endif	/* HMCSPI_H */

