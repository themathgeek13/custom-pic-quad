#include "DBG\DBG.h"

//************************************************************
void	DBGInit()
	{
	//=========================================
	// Debugging interface uses two pins to
	// communicate "debuggin" state changes.
	//=========================================
	// Now let's configure these pins for
	// Digital Output and set them to 0
	//-----------------------------------------
	// Configure DBG-1 port as OUTPUT
	__DBG_1_Tris	= 0;
	DBG_1_OFF();	// Reset port
	//-----------------------------------------
	// Configure DBG-2 port as OUTPUT
	__DBG_2_Tris		= 0;
	DBG_2_OFF();	// Reset port
	//-----------------------------------------
	return;
	}
//************************************************************






