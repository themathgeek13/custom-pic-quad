#include "TMR\TMR.h"
#include "I2C\I2C_Profile.h"
//--------------------------------------
#include "MPL3115\MPL3115.h"
#include "MPL3115\MPL3115_Profile.h"
//==================================================================

//==================================================================
#ifndef __MPL3115_Local_H
#define __MPL3115_Local_H
//==================================================================
extern volatile byte	_MPL_IL	; 	// MPL default interrupt level
extern volatile uint	_MPL_Init;	// Init flag
//==================================================================
extern const 	byte	_MPL_Addr;		// Sensor address on I2C bus
//==================================================================

//==================================================================
// Absolute altitude at the flight location (in meters)
//------------------------------------------------------------------
extern volatile float	_MPL_BaseAlt;
//==================================================================

//==================================================================
// CtrlR1 is one of the most important registers and will be written
// to quite often to initialize OST (One Shot mode). Thus we provide
// several #defines related to this register.
//==================================================================
#define CtrlR1Addr		0x26
//---------------------------
#define CtrlR1ClrOST	0xFD
#define CtrlR1SetOST	0x02


//==================================================================
// Asynchronous read support
//==================================================================
extern volatile	uint	_MPL_Async;	// Asynchronous read in progress
									// flag
extern volatile	uint	_MPL_State;	// Step number in the asynchronous
									// read finite automata controller
//------------------------------------------------------------------
// Asynchronous READ intermediate data storage
//------------------------------------------------------------------
// Flag indicating whether asynch ronous read data is ready
extern volatile	uint	_MPL_Ready;
// Status of the interrupr line at the entry to the Interrupt
// routine - used to validate Sample.
extern volatile uint	_MPL_PortLvl;
// Asynchronous sample...
extern volatile long	_MPL_Data;	
// TS (in 0.2 usec ticks) of the last asynchronous sample
extern volatile ulong	_MPL_DataTS;
// Max interval between consequitive data samples (in 0.2 usec ticks)
// Set in the MPL_Reset Routine bases upon the value of OSR parameter
extern			ulong	_MPL_MaxInt;
//------------------------------------------------------------------
// Asynchronous READ data buffer
//------------------------------------------------------------------
extern volatile uint	_MPL_BufPos;
extern volatile byte	_MPL_Buffer[5];
extern volatile byte	_MPL_CtrlR1;
//------------------------------------------------------------------


//==================================================================
// Callback function for I2C subscription
//------------------------------------------------------------------
void	_MPLCallBack();
//==================================================================

//==================================================================
// Synchronous helper functions used by other synchronous APIs
//==================================================================
// Synchronous READ (internal)
//------------------------------------------------------------------
uint	_MPLRead(	byte 	Register, 
					byte*	Buffer,
					uint  	BufLen	);
//------------------------------------------------------------------
// Synchronous WRITE (internal)
//------------------------------------------------------------------
uint	_MPLWrite(	byte	 Register, 
					byte*	 Buffer,
					uint	 BufLen );
//------------------------------------------------------------------
// Synchronous Read Raw Sample (internal)
//------------------------------------------------------------------
uint	_MPLReadRawData(long* pAlt);
//==================================================================
#endif
