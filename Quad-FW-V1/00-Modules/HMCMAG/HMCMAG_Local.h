#include "HMCMAG\HMCMAG.h"
//*************************************************************
#ifdef __MAG_Use__
//*************************************************************
#include "TMR\TMR.h"

//=====================================================
#ifndef __HMCMAG_Local_H
#define __HMCMAG_Local_H
//=====================================================
extern volatile byte	_HMC_IL	; 	// MAG default interrupt level
extern volatile uint	_HMC_Init;	// Init flag
//==================================================================
extern const 	byte	_HMC_Addr;	// Sensor address on I2C bus
//==================================================================
extern volatile ulong	_HMC_Count;	// Sample count
//==================================================================
// Sensor data normalization values
//==================================================================
// MAG Sensitivity: 
extern 		 	float		_HMC_Sensitivity;
// MAG Hard Iron correction vector
extern const	Vector		_HMC_HardIron;
// MAG Soft Iron correction matrix
extern 			Vector		_HMC_SoftIron_X;
extern 			Vector		_HMC_SoftIron_Y;
extern 			Vector		_HMC_SoftIron_Z;


//-----------------------------------------------------
// Raw MAG Data Sample - data length increased from int
// (native to sensor) to long to accommodate accumulation
// in the ISR routine
//-----------------------------------------------------
typedef	struct
	{
	long		MX;
	long		MY;
	long		MZ;
	}	_HMCRawData, *_pHMCRawData;

//==================================================================
// Asynchronous read support
//==================================================================
extern volatile	uint	_HMC_Async;	// Asynchronous read in progress
									// flag
extern volatile	uint	_HMC_State;	// Step number in the asynchronous
									// read finite automata controller
//------------------------------------------------------------------
extern volatile	uint	_HMC_Ready;	// Flag indicating whether asynch-
									// ronous read data is ready
//------------------------------------------------------------------
extern  _HMCRawData		_HMC_Sample;// Asynchronous sample...
//------------------------------------------------------------------
// Asynchronous READ buffer control
//------------------------------------------------------------------
extern volatile uint	_HMC_BufPos;	// Position in MAG read buffer
extern 			byte	_HMC_Buffer[];	// MAG read buffer		
//------------------------------------------------------------------
// Asynchronous READ intermediate data storage
//------------------------------------------------------------------
extern  _HMCRawData		_HMC_Sensor;
//------------------------------------------------------------------
void	_HMCCallBack();
//==================================================================

//==================================================================
// Synchronous helper functions used by other synchronous APIs
//==================================================================
// Synchronous READ (internal)
//------------------------------------------------------------------
uint	_HMCRead(	byte 	Register, 
					byte*	Buffer,
					uint  	BufLen	);
//------------------------------------------------------------------
// Synchronous WRITE (internal)
//------------------------------------------------------------------
uint	_HMCWrite(	byte	 Register, 
					byte*	 Buffer,
					uint	 BufLen );
//------------------------------------------------------------------
// Synchronous Read Raw Sample (internal)
//------------------------------------------------------------------
uint	_HMCReadRawData(_pHMCRawData pRawData);
//==================================================================
#endif

//***************************************************************
#endif /* __MAG_Use__ */


