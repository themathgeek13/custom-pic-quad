#include "BLI\BLILocal.h"
#include "TMR\TMRLocal.h"


//************************************************************
void	BLIInit()
	{
	if (_BLIInit)
		return;					// BLI has been initialized
	//----------------------------------------------------
	_BLIInit			= 1;	// BLI Initialized
	//----------------------------------------------------

	//*******************************************************************
	// BLI Component relies on Timer functions, so if Timer is not
	// initialized, it is a good time to initialize it now...
	//-------------------------------------------------------------------
	TMRInitDefault();

	//*******************************************************************
	// LED / Buzzer control port
	//-------------------------------------------------------------------
	// Configure BLI Port as OUTPUT
	__BLITris	= 0;
	__BLILat	= 0;	// Reset port
	//-------------------------------------------------------------------

	return;
	}
//************************************************************

