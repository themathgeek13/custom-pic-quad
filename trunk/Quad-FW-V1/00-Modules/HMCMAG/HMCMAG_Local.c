#include "HMCMAG\HMCMAG_Local.h"
//*******************************************************
#ifdef __MAG_Use__
//*******************************************************


//==================================================================
volatile byte		_HMC_IL		= 0; 	// MAG (INT2) interrupt level
volatile uint		_HMC_Init	= 0;	// Init flag
//==================================================================

// MAG3110 device address:
const	byte		_HMC_Addr		= 0x3C; 	
// NOTE: The address above is the "write" address - LSB is set to 0;
//		 The LSB will be set to "1" (changing address to 0x1D) in
//		 the I2C write routine.
//==================================================================
volatile ulong		_HMC_Count;			// Sample count
//==================================================================
// Sensor data normalization values
//==================================================================
// MAG Sensitivity in mGs/LSB, adjusted in the Reset(...) routine
	 	float		_HMC_Sensitivity	=0.729927; 	
// Earth magnetic field is around 0.25-0.65 Gs, so measurements should
// be in the range of 250 <= |M| <= 650
//------------------------------------------------------------------
// MAG Hard Iron correction vector
const	Vector		_HMC_HardIron		=  {-90.19,	-37.08,	-123.92};
// MAG Soft Iron correction matrix
		Vector		_HMC_SoftIron_X		=  {1.00000, 0.00194, 0.04416};
		Vector		_HMC_SoftIron_Y		=  {0.00194, 1.00000, 0.00716};
		Vector		_HMC_SoftIron_Z		=  {0.04416, 0.00716, 1.25741};

//==================================================================
// Asynchronous read support
//==================================================================
volatile uint		_HMC_Async	= 0;	// Asynchronous read in progress
										// flag
volatile uint		_HMC_State	= 0;	// Step number in the asynchronous
										// read finite automata controller
//------------------------------------------------------------------
volatile uint		_HMC_Ready	= 0;	// Flag indicating whether asynch-
										// ronous read data is ready
//------------------------------------------------------------------
_HMCRawData			_HMC_Sample;		// Asynchronous sample...
//------------------------------------------------------------------
// Asynchronous READ buffer control
//------------------------------------------------------------------
volatile uint		_HMC_BufPos	= 0;	// Position in HMC read buffer
		 byte		_HMC_Buffer[6];		// HMC read buffer		
//------------------------------------------------------------------
// Asynchronous READ intermediate data storage
//------------------------------------------------------------------
_HMCRawData			_HMC_Sensor;
//==================================================================


//***************************************************************
#endif /* __MAG_Use__ */

