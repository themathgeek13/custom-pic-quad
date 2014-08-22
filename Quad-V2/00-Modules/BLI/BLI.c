#include "BLI/BLILocal.h"

void	BLISignalON(void)
	{
	if (!_BLIAsync)
		_LATA10		= 1;	// Set port
	}
//-----------------------------------------------------------------------
void	BLISignalOFF(void)
	{
	if (!_BLIAsync)
		_LATA10		= 0;	// Re-set port
	}
//-----------------------------------------------------------------------
void	BLISignalFlip(void)
	{
	if (!_BLIAsync)
		_LATA10	   ^= 1;	// Flip port
	}
//=======================================================================


//************************************************************
void	BLIAsyncStart(uint OnTime, uint OffTime)
	{
	//---------------------------------------------------
	// First, stop current Asynch operation, if any
	//---------------------------------------------------
	if (_BLIAsync)
		BLIAsyncStop();
	//---------------------------------------------------
	// Second, if not initialized - Initialize!
	//---------------------------------------------------
	if (0 == _BLIInit)
		BLIInit();
	//---------------------------------------------------
	// Third, all ASYNC operations should start in the
	// OFF State for UI
	//---------------------------------------------------
	BLISignalOFF();
	//---------------------------------------------------
	_BLIAsyncPos		= 0;
	_BLIAsyncTimes[0]	= OnTime;
	_BLIAsyncTimes[1]	= OffTime;
	//---------------------------------------------------
	// Set size of timing array:
	_BLIAsync			= 2;	// Flag Asynch operation;
	//---------------------------------------------------
	// Request immediate callback to initialize the sequence
	//---------------------------------------------------
	TMRCallBackAfter(0, &_BLICallBack); 			
	//---------------------------------------------------
	return;
	}
//************************************************************

//************************************************************
void	BLIAsyncStop(void)
	{
	if (_BLIAsync)
		// Asynchronous operation is in progress
		{	
		//---------------------------------------------------
		TMRCallBackDiscard();	// Discard callback request, if any
		//----------------------
		_BLIAsync		= 0;	// Clear Asynch flag
		//---------------------------------------------------
		return;
		}
	//---------------------------------------------------
	// Reset interface (if STOPed in ON state)
	//---------------------------------------------------
	BLISignalOFF();
	//---------------------------------------------------
	return;
	}
//************************************************************

//*************************************************************
void BLIDeadStop(char * pStr, uint Length)
	{
	// Stop current operation, if any...
	BLIAsyncStop();
	// Start "pumping" signal
	BLIAsyncMorse(pStr, Length);
	// Dead stop...
	while (1);
	}
//*************************************************************


