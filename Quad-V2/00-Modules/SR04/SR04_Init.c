#include "SR04/SR04_Local.h"

#include "TMR/TMR.h"

//**********************************************************
// SR04Init(...) function initializes SR04 interface and
// respective IC Module.
//**********************************************************
void	SR04Init(int IL)	// Parameter (1<=IL<=7) defines the
						// priority of IC interrupt routine.
	{
	if (_SR04Init)
		return;			// Component already initialized
	_SR04Init	= 1;	// Set initialization flag
	//====================================================
	
	//----------------------------------------------------
	// Validate requested Interrup Level value
	//----------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_SR04IL	= IL;
	//----------------------------------------------------

	//************************************************
	// SR04 group of functions depend on timer providing
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
	Nop();					// Skip one cycle to let module enable
	//---------------------------------------------------------
	// Configure Interrupts
	//---------------------------------------------------------
	ICIE		= 0;			// Disable ICx interrupt
	ICIF		= 0; 			// Clear ICx interrupt flag
	ICIP		= _SR04IL;		// Set ICx interrupt priority
	//---------------------------------------------------------


	//---------------------------------------------------------
	// Map MCU pins used by Input Capture module through
	// REMAPPABLE PIN SELECT feature.
	//---------------------------------------------------------
	 _SR04InitPinMap();

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
	// Start processing pulses...
	//---------------------------------------------------------
	ICIE		= 1; 			// Enable ICx interrupts
	//---------------------------------------------------------
	return;
	}
//----------------------------------------------------------




