#include "SR04\SR04_Local.h"

//*******************************************************************
// SR04ReadWhenReady(...) function - returns calculated Altitude and
// Speed WHEN there is at least one captured sample since last call
// to the function - BLOCKING call!
//====================================================================
uint	SR04ReadWhenReady(SR04Data*	SR04Sample)
	{
	if (0 == _SR04Init)
		return -1;			// Component not initialized
	//---------------------------------------------------------------
	while (0 == _SR04Ready); // Wait for at least one sample...
	//---------------------------------------------------------------
	return SR04Read(SR04Sample);
	}
//********************************************************************


//********************************************************************
// SR04Read function - returns calculated Altitude and Speed if there
// is at least one captured sample since last call to the function.
//--------------------------------------------------------------------
// Return value indicates whether initialization condition was met and,
// if so, how many samples were available for calculation of resulting
// values.
//--------------------------------------------------
// NOTE: Output data structure updated ONLY if a new
//       sample is available!
//====================================================================
uint	SR04Read(SR04Data*	SR04Sample)
	{
	if (0 == _SR04Init)
		return -1;		// Component not initialized
	if (0 == _SR04Ready)
		return 0;		// New Sample is not ready yet!
						// SR04Sample structure left "as-is"
	//----------------------------------------------------------------
	byte 		saved_ipl;     
	//-----------------------
	uint		SR04ReadyCount;
	ulong		SR04TimeSum;
	//-----------------------
	ulong		SR04RecentTS;
                  
	//================================================================
	// Enter Critical Section: SR04 (Input Capture) interrupt is blocked
	//================================================================
	SET_AND_SAVE_CPU_IPL(saved_ipl,_SR04IL);
	//================================================================
	// Consume current sample
	//----------------------------------------------------------------
	SR04ReadyCount	= _SR04Ready;
	SR04TimeSum		= _SR04Sum;
	//------------------------------
	SR04RecentTS	= _SR04RecentTS;
	//----------------------------------------------------------------
	_SR04Ready		= 0;		// Sample is consumed...
	_SR04Sum		= 0;
	_SR04RecentTS	= 0;
	//================================================================
	// Leave Critical Section
	//================================================================
	RESTORE_CPU_IPL(saved_ipl);
	//================================================================

	//================================================================
	// Calculate Altitude
	//----------------------------------------------------------------
	SR04Sample->Altitude	= ((float)SR04TimeSum) * _SR04CF;
	if (SR04ReadyCount > 1)
		// Several samples were aggregated, let's get average
		SR04Sample->Altitude /= (float)SR04ReadyCount;
	//----------------------------------------------------------------
	// Update output data structure
	//----------------------------------------------------------------
	SR04Sample->Altitude	-= _SR04Offset;
	SR04Sample->TS			 = SR04RecentTS;
	//================================================================
	return SR04ReadyCount;		// SR04Sample updated with new sample 
	}
//********************************************************************

//*******************************************************************
// SR04ResetBase() function adjust altitude to 0 taking into account
// distance from sensor to the ground when quad is on the ground.
//====================================================================
uint	SR04ResetBase()
	{
	if (0 == _SR04Init)
		return -1;		// Component not initialized
	//----------------------------------------------------------------
	SR04Data		LocalSample;
	//----------------------------------------------------------------
	_SR04Offset	= 0.0;					// Reset ground offset
	SR04ReadWhenReady(&LocalSample);	// Clear "pipeline"
	TMRDelay(500);						// Let at least 10 samples be captured
	SR04ReadWhenReady(&LocalSample);	// Read sample averaged over 0.5 sec
	//----------------------------------------------------------------
	// Capture current "altitude" as ground offset
	//----------------------------------------------------------------
	_SR04Offset	= LocalSample.Altitude;
	//----------------------------------------------------------------
	return 0;
	}




