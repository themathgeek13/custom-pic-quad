#include "SR04/SR04_Local.h"

//************************************************************
// Constants
//------------------------------------------------------------
// Conversion factor for converting sound round-trip time in
// timer ticks (0.2 usec) into distance in meters
const float	_SR04CF				= 0.000034557823;

//************************************************************
// Module control values
//------------------------------------------------------------
byte		_SR04IL				= 4;
uint		_SR04Init			= 0;

//************************************************************
// Configuration value(s)
//------------------------------------------------------------
// Hight offset to compensate for initial position of the
// sensor when quad is on the ground
float		_SR04Offset		= 0.0;

//************************************************************
// Interrupt management values
//------------------------------------------------------------
// READY count - non-zero value indicates number of samples
// that were captured so that we may calculate "average"
volatile uint	_SR04Ready		= 0;
// Total duration (in timer ticks) of _SR04Ready samples
volatile ulong	_SR04Sum		= 0;
// Timestamp of the last captured rising edge
volatile ulong	_SR04Start		= 0;
// Time stamp (in timer tics) of the last measurement
volatile ulong	_SR04RecentTS		= 0;





