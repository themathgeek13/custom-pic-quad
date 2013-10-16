#include "MXB\MXB.h"
//=====================================================
#ifdef __MAG_Use__
//*****************************************************
#include "MXB\MXBProfile.h"
#include "TMR\TMR.h"
//=====================================================

#ifndef MXBLOCAL_H
#define	MXBLOCAL_H

//************************************************************
// Constants
//------------------------------------------------------------
// Conversion factor for converting sound round-trip time in
// timer ticks (0.2 usec) into distance in meters
extern const float	_MXBCF;

//************************************************************
// Module control values
//------------------------------------------------------------
extern byte			_MXBIL; 	// Default interrupt priority
extern uint			_MXBInit;	// Initialization flag

//************************************************************
// Configuration value(s)
//------------------------------------------------------------
// Hight offset to compensate for initial position of the
// sensor when quad is on the ground
extern float		_MXBOffset;

//************************************************************
// Temporary values used in DLPF calculation
//------------------------------------------------------------
extern MXBData		_NewMXBReading;

//************************************************************
// Temporary values used in Speed calculation
//------------------------------------------------------------
// Previous measurement used in calculating Speed
extern float		_MXBLastAlt;
// Time stamp (in timer tics) of last measurement
extern ulong		_MXBLastTS;
//------------------------------------------------
// Time stamp (in timer tics) of the most recent measurement
extern ulong		_MXBRecentTS;

//************************************************************
// Interrupt management values
//------------------------------------------------------------
// READY count - non-zero value indicates number of samples
// that were captured so that we may calculate "average"
extern volatile uint	_MXBReady;
// Total duration (in timer ticks) of _MXBReady samples
extern volatile ulong	_MXBSum;
// Timestamp of the last captured rising edge
extern volatile ulong	_MXBStart;

//====================================================================
#endif	/* MXBLOCAL_H */
//====================================================================
#endif	/*# __MXB_Use__ */

