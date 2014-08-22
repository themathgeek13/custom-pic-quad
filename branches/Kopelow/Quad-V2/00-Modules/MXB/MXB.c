#include "MXB/MXBLocal.h"
//=====================================================
#ifdef __MAG_Use__
//*****************************************************

//*******************************************************************
// MXBReadWhenReady(...) function - returns calculated Altitude and
// Speed WHEN there is at least one captured sample since last call
// to the function - BLOCKING call!
//====================================================================
uint	MXBReadWhenReady(MXBData*	MXBSample)
	{
	if (0 == _MXBInit)
		return 0;			// Component not initialized
	//---------------------------------------------------------------
	while (0 == _MXBReady); // Wait for at least one sample...
	//---------------------------------------------------------------
	return MXBRead(MXBSample);
	}
//********************************************************************

//********************************************************************
// MXBRead function - returns calculated Altitude and Speed if there
// is at least one captured sample since last call to the function.
//--------------------------------------------------------------------
// Return value indicates whether initialization condition was met and,
// if so, how many samples were available for calculation of resulting
// values.
//--------------------------------------------------
// NOTE: Output data structure updated ONLY if a new
//       sample is available!
//====================================================================
uint	MXBRead(MXBData*	MXBSample)
	{
	if (0 == _MXBInit)
		return 0;		// Component not initialized
	if (0 == _MXBReady)
		return 0;		// New Sample is not ready yet!
						// MXBSample structure left "as-is"
	//----------------------------------------------------------------
	byte 		saved_ipl;     
	//-----------------------
	uint		MXBReadyCount;
	ulong		MXBTimeSum;
	//-----------------------
	ulong		MXBRecentTS;
                  
	//================================================================
	// Enter Critical Section: MXB (Input Capture) interrupt is blocked
	//================================================================
	SET_AND_SAVE_CPU_IPL(saved_ipl,_MXBIL);
	//================================================================
	// Consume current sample
	//----------------------------------------------------------------
	MXBReadyCount	= _MXBReady;
	MXBTimeSum		= _MXBSum;
	//------------------------------
	MXBRecentTS		= _MXBRecentTS;
	//----------------------------------------------------------------
	_MXBReady		= 0;		// Sample is consumed...
	_MXBSum			= 0;
	//================================================================
	// Leave Critical Section
	//================================================================
	RESTORE_CPU_IPL(saved_ipl);
	//================================================================

	//================================================================
	// Calculate Altitude
	//----------------------------------------------------------------
	float	MXBAltitude	= ((float)MXBTimeSum) * _MXBCF;
	if (MXBReadyCount > 1)
		// Several samples were aggregated, let's get average
		MXBAltitude /= (float)MXBReadyCount;
	//----------------------------------------------------------------
	// Update output data structure
	//----------------------------------------------------------------
	MXBSample->TS		= MXBRecentTS;
	MXBSample->Altitude	= MXBAltitude - _MXBOffset;
	//================================================================
	return MXBReadyCount;	// MXBSample updated with new sample 
							// averaged over MXBReadyCount measurements.
	}
//********************************************************************

//*******************************************************************
// MXBSetBase(float Base) function adjust altitude to 0 taking into
// account provided distance from sensor to the ground when quad
// is on the ground.
//====================================================================
uint	MXBSetBase(float Base)
	{
	if (0 == _MXBInit)
		return 0;		// Component not initialized
	if (0.0 < Base)
		return 0;		// Invalid Base value
	//----------------------------------------------------------------
	_MXBOffset	= Base;
	//----------------------------------------------------------------
	return 1;
	}
//====================================================================


//*******************************************************************
// MXBCalculateBase(...) function adjust altitude to 0 by calculating
// distance from sensor to the ground when quad is on the ground.
//====================================================================
uint	MXBCalculateBase(MXBData*	MXBSample)
	{
	//----------------------------------------------------------------
	if (0 == _MXBInit)
		return 0;		// Component not initialized
	//----------------------------------------------------------------
	uint		RC	= 0;
	//----------------------------------------------------------------
	_MXBOffset	= 0.0;				// Reset ground offset
	TMRDelay(55);					// Give time for at least one sample
	if (0 == MXBRead(MXBSample))	// Clear "pipeline"
		return 0;					// Failure!
	
	TMRDelay(1000);					// Let at least 20 samples be captured
	// Read sample averaged over 0.5 sec
	if (0 == (RC = MXBRead(MXBSample)))
		return 0;					// Failure!
	//----------------------------------------------------------------
	// Capture current "altitude" as ground offset
	//----------------------------------------------------------------
	_MXBOffset	= MXBSample->Altitude;

	//----------------------------------------------------------------
	// Reset Altitude in the output data structure
	//----------------------------------------------------------------
	MXBSample->Altitude	= 0.0;
	//----------------------------------------------------------------
	return RC;		// Non-zero value (number of samples averaged) -
					// Success!
	}

//====================================================================
#endif	/*# __MXB_Use__ */



