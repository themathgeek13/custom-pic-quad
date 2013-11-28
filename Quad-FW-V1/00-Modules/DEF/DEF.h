#include "TMR\TMRLocal.h"

#ifndef DEF_H
#define	DEF_H
//===================================================================
// Definitions and Functions supporting implementation of the
// Double Exponential Filter
//===================================================================
typedef struct
	{
	long	TSL;		// Timestamp of the last cycle
	//-----------------------------------------------------
	float	St;			// Last filtered value
	float	Bt;			// Last filtered "slope"
	//-----------------------------------------------------
	float	StLag;		// Filtering (smooting) factor
	float	StNorm;		// Normalization factor: (StLag +1)*StNorm == 1
	//-----------------------------------------------------
	float	BtLag;		// Trend filtering (smooting) factor
	float	BtNorm;		// Trend normalization factor: 
						//	(BtLag +1)*BtNorm == 1
	//-----------------------------------------------------
	} DEF;
//===================================================================
static inline uint	DEFFilterInit(	float	SFactor,
									float	BFactor,
									DEF*	Filter	)
	{
	Filter->TSL		= 0;
	Filter->St		= 0.0;
	Filter->Bt		= 0.0;
	//--------------------
	Filter->StNorm	= 0.0;		// Indicator that Filter is
	Filter->BtNorm	= 0.0;		// not initialized....
	//---------------------------------------------------------
	if (SFactor < 1.0 || BFactor < 1.0)
		return 1;				// Failure: invalid parameters!
	//---------------------------------------------------------
	Filter->StLag	= SFactor - 1.0;	// StLag >= 0.0
	Filter->BtLag	= BFactor - 1.0;	// BtLag >= 0.0
	//---------------------------------------------------------
	Filter->StNorm	= 1.0 / SFactor;
	Filter->BtNorm	= 1.0 / BFactor;
	//---------------------------------------------------------
	return 0;					// Filter initialized successfully!
	}
//===================================================================
static inline float	DEFFilterApply(	float X, long TS, DEF*	Filter)
	{
	//------------------------------------------------------------------
	// Verify Filter state
	//------------------------------------------------------------------
	if (Filter->BtNorm <= 0.0 || Filter->BtNorm <= 0.0)
		// Filter is not initialized...
		return X;
	//------------------------------------------------------------------
	// Check whether this is the initial call for this filter
	//------------------------------------------------------------------
	if ( 0 == Filter->TSL)
		// First invocation of the Filter
		{
		Filter->TSL		= TS;
		Filter->St		= X;
		Filter->Bt		= 0.0;
		//--------------------------
		return X;
		}
	//------------------------------------------------------------------
	// Subsequent invocations of the Filter - now we can actually
	// start applying filtering...
	//------------------------------------------------------------------
	float	dT		= TMRGetTSRate() * (float)(TS - Filter->TSL);
	//------------------------------------------------------------------
	// Calculate new estimate based upon the Filter state and new time
	// series value X
	//------------------------------------------------------------------
	float	newSt	= (Filter->StLag*(Filter->St + Filter->Bt*dT) + X)*Filter->StNorm;
	//------------------------------------------------------------------
	// Update estimated time series slope (gradient) based upon the
	// past slope value and current estimate of the slope
	//------------------------------------------------------------------
	if (dT > 0.0001)	// Sanity check...
		Filter->Bt	= (Filter->BtLag*Filter->Bt + (newSt - Filter->St)/dT)*Filter->BtNorm;
	//------------------------------------------------------------------
	// Update Filter state variables
	//------------------------------------------------------------------
	Filter->TSL		= TS;
	Filter->St		= newSt;
	//---------------------------------------------------------
	return newSt;	// Return new filtered value...
	}
//===================================================================

#endif	/* DEF_H */

