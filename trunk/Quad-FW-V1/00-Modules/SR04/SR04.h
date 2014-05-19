#include "System.h"
//=====================================================
#ifndef SR04_H
#define	SR04_H

//******************************************************
// NOTE: Functions in this group facilitate reading
//		 distance measurements from SR04 Ultrasound
//		 range finder and calculating vertical speed.
//------------------------------------------------------
// Pulse width is being evaluated using the tick counts
// from the timing module based  upon the 32-bit timer
// comprised of Timer4 and Timer5. It is assumed that
// the timer tick is 0.2 usec.
//------------------------------------------------------
// NOTE: Please initialize TMR component prior to calling
//		 SR04Init(...).
//------------------------------------------------------
// Range finder is connected to the following pin:
// PW (pulse-width interface):		RP6/RB6
// Trigger:							RP5/RB5
//------------------------------------------------------
// Pulse width indicative of the distance is measured
// using "Input Capture" facility Channel 1
//******************************************************

//----------------------------------------------------------
// SR04 range finder data interface
//----------------------------------------------------------
typedef struct
	{
	ulong		TS;			// Timestamp of the measurement
	float		Altitude;	// In meters
	} SR04Data;


//**********************************************************
// SR04Init(...) function initializes SR04 interface and
// respective IC Module.
//**********************************************************
void	SR04Init(int IL);	// Parameter (1<=IL<=7) defines the
							// priority of IC interrupt routine.
//----------------------------------------------------------

//*******************************************************************
// SR04Read function - returns calculated Altitude if there is at
// least one captured sample since last call to the function.
//====================================================================
uint	SR04Read(SR04Data*	SR04Sample);

//*******************************************************************
// SR04ReadWhenReady(...) function - returns calculated Altitude and
// Speed WHEN there is at least one captured sample since last call
// to the function - BLOCKING call!
//====================================================================
uint	SR04ReadWhenReady(SR04Data*	SR04Sample);

//*******************************************************************
// SR04ResetBase() function adjust altitude to 0 taking into account 
// distance from sensor to the ground when quad is on the ground.
//====================================================================
uint	SR04ResetBase();



#endif	/* SR04_H */

