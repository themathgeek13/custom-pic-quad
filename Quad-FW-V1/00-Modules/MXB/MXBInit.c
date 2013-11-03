#include "MXB\MXBLocal.h"
//=====================================================
#ifdef __MAG_Use__
//*****************************************************
#include "TMR\TMR.h"

//**********************************************************
// MXBInit(...) function initializes MXB interface and
// respective IC Module.
//**********************************************************
uint	MXBInit(int IL,	// Parameter (1<=IL<=7) defines the
						// priority of IC interrupt routine.
				MXBData*	MXBSample)
	{
	if (_MXBInit)
		// Component already initialized...
		return 1;		// Success (already initialized)
	//----------------------------------------------------
	_MXBInit	= 1;	// Set initialization flag
	//====================================================
	
	//----------------------------------------------------
	// Validate requested Interrup Level value
	//----------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_MXBIL	= IL;
	//----------------------------------------------------

	//************************************************
	// MXB group of functions depend on timer providing
	// timestamps for interval measurement, thus we
	// make sure that timer is intitialized.
	//************************************************
	TMRInitDefault();

	//---------------------------------------------------------
	ICCON			= 0;	// Disable ICx for configuration
	//---------------------------------------------------------
	// Please NOTE that the Init program disables all PERIPHERAL
	// MODULES using PMDx registers. To continue configuring and
	// later enabling Input Capture module we need to enable
	// module in PMDx
	//---------------------------------------------------------
	ICMD	= 0;			// Enable ICx module
	//---------------------------------------------------------

	//---------------------------------------------------------
	// Map MCU pins used by Input Capture module through
	// REMAPPABLE PIN SELECT feature.
	//---------------------------------------------------------
	 _MXBInitPinMap();

	//---------------------------------------------------------
	// Configure Interrupts
	//---------------------------------------------------------
	ICIE		= 0;			// Disable ICx interrupt	
	ICIF		= 0; 			// Clear ICx interrupt flag
	ICIP		= _MXBIL;		// Set ICx interrupt priority
	//---------------------------------------------------------
	ICIE		= 1;			// Enable ICx interrupt
	
	//---------------------------------------------------------
	// After configuration complete enable ICx module	
	//---------------------------------------------------------
	// NOTE: For this application we do not capture the 
	//		 actual timer value associated with the module
	//		 (we will use common timer module), so we do not
	//		 care configuring timer associated with ICx
	//---------------------------------------------------------
	ICM	= 1;	// Capture mode, interrupt on every edge
	//---------------------------------------------------------
	// Read 10 samples as part of initialization
	int i;
	for (i = 0; i < 10; i++)
		MXBReadWhenReady(MXBSample);
	// Initialization completed...
	return MXBReadWhenReady(MXBSample);
	}
//----------------------------------------------------------

//====================================================================
#endif	/*# __MXB_Use__ */



