#include "SR04\SR04.h"
#include "SR04\SR04_Profile.h"

#include "TMR\TMR.h"

//=====================================================
#ifndef SR04LOCAL_H
#define	SR04LOCAL_H

//************************************************************
// Constants
//------------------------------------------------------------
// Conversion factor for converting sound round-trip time in
// timer ticks (0.2 usec) into distance in meters
extern const float	_SR04CF;

//************************************************************
// Module control values
//------------------------------------------------------------
extern byte		_SR04IL; 	// Default interrupt priority
extern uint		_SR04Init;	// Initialization flag

//************************************************************
// Configuration value(s)
//------------------------------------------------------------
// Hight offset to compensate for initial position of the
// sensor when quad is on the ground
extern float	_SR04Offset;

//************************************************************
// Interrupt management values
//------------------------------------------------------------
// READY count - non-zero value indicates number of samples
// that were captured so that we may calculate "average"
extern volatile uint	_SR04Ready;
// Total duration (in timer ticks) of _SR04Ready samples
extern volatile ulong	_SR04Sum;
// Timestamp of the last captured rising edge
extern volatile ulong	_SR04Start;
// Time stamp (in timer tics) of the last measurement
extern volatile ulong	_SR04RecentTS;


#endif	/* SR04LOCAL_H */

