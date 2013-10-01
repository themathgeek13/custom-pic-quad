
#include "RC\RCLocal.h"

//************************************************************
// Module control values
//------------------------------------------------------------
uchar		_RCIL				= 4; 
uint		_RCInit				= 0; 

//------------------------------------------------------------
// Timer3 rolover control (assuming Fcy = 40 MHz and Timer3
// prescaler is set to 1:64 for 1 tick = 1.6 usec) for 25 msec:
//------------------------------------------------------------
const uint				_RC_Tmr_Count			= 15625;
//------------------------------------------------------------
// Channel time count range values:
//------------------------------------------------------------
const long				_RCTimeCountMinMin		=  4000;	// 0.8 msec - Absolute minimum
const long				_RCTimeCountMin			=  5000;	// 1 msec
const long				_RCTimeCountMidPoint	=  7500;	// 1.5 msec
const long				_RCTimeCountMax			= 10000;	// 2 msec
const long				_RCTimeCountMaxMax		= 11000;	// 2.2 msec - Absolute maximum

//------------------------------------------------------------
// Channel time count normalization values:
//------------------------------------------------------------
const float				_RCPlusRange			= 0.0002f;	// (1/5000) = 0.0002
const float				_RCPlusMinusRange		= 0.0004f;	// (1/2500) = 0.0004

//------------------------------------------------------------
// Control automaton state
//------------------------------------------------------------
volatile uint			_RCState		= 0;
volatile RCTimingData	_RCTimes		= {{0, 0, 0, 0, 0, 0}};

//------------------------------------------------------------
// Sample Flags:
//------------------------------------------------------------
volatile uint			_RCConnActive	= 0;
//------------
volatile uint			_RCSampleReady	= 0;
volatile uint			_RCSampleTimed	= 0;
//------------------------------------------------------------
// RCSample->Control is very critical for operation as when
// this input is set to 0 the code may cut off the engines,
// so it is critical to provide some "safety margin" to filter
// out some random flukes thus Control is set to 0 only if 
// _RCControlMin samples in a row give 0 control value
//------------------------------------------------------------
const	uint			_RCControlMin	= 5;
//------------------------------------------------------------
volatile RCRawData		_RCRawSample	= {0, 0, 0, 0, 0};





