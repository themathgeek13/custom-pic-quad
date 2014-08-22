#include "MPL3115/MPL3115_Local.h"

//==================================================================
volatile byte		_MPL_IL		= 3; 	// MPL (IC1) interrupt level
volatile uint		_MPL_Init	= 0;	// Init flag
//==================================================================

//==================================================================
// MPL3115 device address
//------------------------------------------------------------------
// NOTE: The address above is the "write" address - LSB is set to 0;
//		 The LSB will be set to "1" (changing address to 0xC1) in
//		 the I2C write routine.
//------------------------------------------------------------------
const	 byte		_MPL_Addr		= 0xC0; 	// 1100000-R/W
//==================================================================

//==================================================================
// Absolute altitude at the flight location (in meters)
//------------------------------------------------------------------
volatile float		_MPL_BaseAlt		= 0;
//==================================================================

//==================================================================
// Asynchronous read support
//==================================================================
volatile uint		_MPL_Async;			// Asynchronous read in progress
										// flag
volatile uint		_MPL_State	= 0;	// Step number in the asynchronous
										// read finite automata controller
//------------------------------------------------------------------
// Asynchronous READ intermediate data storage
//------------------------------------------------------------------
// Flag indicating whether asynchronous data is ready; also used as
// a counter of the number of samples accumulated in _MPL_Data for
// subsequent averaging.
//------------------------------------------------------------------
volatile uint		_MPL_Ready		= 0;
// Status of the interrupr line at the entry to the Interrupt
// routine - used to validate Sample.
volatile uint		_MPL_PortLvl	= 0;
// Asynchronous sample...
volatile long		_MPL_Data		= 0;
// TS (in 0.2 usec ticks) of the last asynchronous sample
volatile ulong		_MPL_DataTS		= 0;
// Max interval between consequitive data samples (in 0.2 usec ticks)
// Set in the MPL_Reset Routine bases upon the value of OSR parameter
		 ulong		_MPL_MaxInt		= 0;
//------------------------------------------------------------------
// Asynchronous READ data buffer
//------------------------------------------------------------------
volatile uint		_MPL_BufPos	= 0;
volatile byte		_MPL_Buffer[5];
volatile byte		_MPL_CtrlR1;
//==================================================================

