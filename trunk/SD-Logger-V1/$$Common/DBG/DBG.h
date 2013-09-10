#include "System.h"

//=====================================================
#ifndef __DBG_H
#define __DBG_H
//=====================================================
// Debugging interface uses two pins to
// communicate "debuggin" state changes.
//=====================================================
// Port configuration setting
//=====================================================	
// Port RB5 assigned to DBG-1:
#define	__DBG_1_Tris	_TRISB5
#define	__DBG_1_Lat		_LATB5
//-----------------------------------------------------
// Port RB9 assigned to DBG-2:
#define	__DBG_2_Tris	_TRISB9
#define	__DBG_2_Lat		_LATB9
//=====================================================
void	DBGInit();
//----------------------------------------------------
#define DBG_1_ON()   __DBG_1_Lat	= 1		// Set port
#define DBG_1_OFF()  __DBG_1_Lat	= 0		// Reset port
#define DBG_1_Flip() __DBG_1_Lat   ^= 1		// Reset port
//----------------------------------------------------
#define DBG_2_ON()   __DBG_2_Lat	= 1		// Set port
#define DBG_2_OFF()  __DBG_2_Lat	= 0		// Reset port
#define DBG_2_Flip() __DBG_2_Lat   ^= 1		// Reset port
//=====================================================
#endif

