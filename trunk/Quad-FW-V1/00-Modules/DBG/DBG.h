#include "System.h"

//=====================================================
#ifndef __DBG_H
#define __DBG_H
//=====================================================
// Debugging interface uses two pins allocated to 
// unused (most of the time) UART Receiver pins to
// communicate "debuggin" state changes.
//****************************************************
void	DBGInit();
//----------------------------------------------------
#define DBG_1_ON()   _LATB2	= 1		// Set port
#define DBG_1_OFF()  _LATB2	= 0		// Reset port
#define DBG_1_Flip() _LATB2	^= 1	// Reset port
//----------------------------------------------------
#define DBG_2_ON()   _LATB3	= 1		// Set port
#define DBG_2_OFF()  _LATB3	= 0		// Reset port
#define DBG_2_Flip() _LATB3	^= 1	// Reset port
//=====================================================
#endif

