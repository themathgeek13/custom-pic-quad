#include "MXB/MXBLocal.h"
//=====================================================
#ifdef __MAG_Use__
//*****************************************************
#include "TMR/TMR.h"

//************************************************************
// MXB-related Interrupt Routines
//************************************************************

//*************************************************************
void __attribute__((__interrupt__, __no_auto_psv__)) ICInterrupt(void)
	{
	//---------------------------------------------------------
	ICIE	= 0;	// Disable ICx Notification Interrupts
	//-------------
	ICIF 	= 0; 	// Reset ICx interrupt request
	//=========================================================

	ulong	TS;
	//---------------------------------------------------------
	// Obtain timestamp for this interrupt
	//---------------------------------------------------------
	TS	= TMRGetTS();

	//---------------------------------------------------------
	// Process interrupt based upon the captured edge
	//---------------------------------------------------------
	if (ICPORT)
		// Rising edge - start of the measurement cycle -
		// just save the timestamp...
		_MXBStart	= TS;
	else
		// Falling edge - if conditions are right, calculate
		// and save duration of the sound travel (in ticks)
		{
		if (0 != _MXBStart) // The rising edge was captured
			{
			if (0 == _MXBReady || _MXBReady > 8191)
				// Either no sample or too many samples
				{
				_MXBSum = TS - _MXBStart;
				_MXBReady = 1;
				}
			else
				{
				_MXBSum += (TS - _MXBStart);
				_MXBReady++;
				}
			// Reset to wait for rising edge
			_MXBStart = 0;
			// Capture TS of the most recent measurement
			// (may be required for Speed calculation)
			_MXBRecentTS = TS;
			}
		}
	//=========================================================
	// Enable ICx interrupt and wait for next capture event
	//---------------------------------------------------------
	ICIE	= 1;	// Enable ICx Notification Interrupts
	//=========================================================
	return;
	}
//*************************************************************

//====================================================================
#endif	/*# __MXB_Use__ */

