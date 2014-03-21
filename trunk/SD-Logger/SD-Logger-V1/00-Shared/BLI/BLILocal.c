#include "BLI\BLILocal.h"

//************************************************************
uint			_BLIInit 	= 0;	// BLI initializtion flag
byte			_BLIIL	 	= 1;	// BLI default interrupt level
//-----------------------------------------------------
// BLI Asynch flag
// "0" - no asynchronous request outstanding
// _BLIAsync > 0 represents the size of the array of On-Off times
volatile uint	_BLIAsync			= 0;	
//-----------------------------------------------------
// Current position in the "timing" array
volatile uint	_BLIAsyncPos	= 0;
// On-Off "timing" array
volatile uint	_BLIAsyncTimes[_BLIAsynchMax];									
//*************************************************************

//*************************************************************
void _BLICallBack (void)
	{
	//-----------------------
	if (0 == _BLIAsync)
		return;		// No Asynch operation in progress ...
	//--------------------------------------------------------
	if (_BLIAsyncPos >= _BLIAsync)
		{
		//--------------------------------------------
		// Perform sequence RESET
		//--------------------------------------------
		__BLILat		= 0;	// Turn off Signal
		_BLIAsyncPos	= 0;	// Initialize sequence		
		}
	//--------------------------------------------------------
	// Flip Signal
	//--------------------------------------------------------
	__BLILat		   ^= 1;	// Flip Signal
	//--------------------------------------------------------
	// As the callback in this program runs at the lowest
	// interrupt priority of "1" we may break the rule and
	// call external function...
	//--------------------------------------------------------
	// Request next wake-up...
	TMRCallBackAfter(_BLIAsyncTimes[_BLIAsyncPos], &_BLICallBack);
	// Increment step
	_BLIAsyncPos++;	
	//--------------------------------------------------------
	return;
	}
//*************************************************************






