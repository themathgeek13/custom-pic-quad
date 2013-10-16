#include "MXB\MXBLocal.h"
//=====================================================
#ifdef __MAG_Use__
//*****************************************************

//************************************************************
// Constants
//------------------------------------------------------------
// Conversion factor for converting sound round-trip time in
// timer ticks (0.2 usec) into distance in meters
const float	_MXBCF				= 0.000034557823;

//************************************************************
// Module control values
//------------------------------------------------------------
byte		_MXBIL				= 4;
uint		_MXBInit			= 0;

//************************************************************
// Configuration value(s)
//------------------------------------------------------------
// Hight offset to compensate for initial position of the
// sensor when quad is on the ground
float		_MXBOffset		= 0.0;

//************************************************************
// Temporary values used in DLPF calculation
//------------------------------------------------------------
MXBData		_NewMXBReading	= {0.0, 0.0};

//************************************************************
// Temporary values used in Speed calculation
//------------------------------------------------------------
// Previous measurement used in calculating Speed
float		_MXBLastAlt			= 0.0;
// Time stamp (in timer tics) of last measurement
ulong		_MXBLastTS			= 0;
// Time stamp (in timer tics) of current measurement
ulong		_MXBRecentTS		= 0;

//************************************************************
// Interrupt management values
//------------------------------------------------------------
// READY count - non-zero value indicates number of samples
// that were captured so that we may calculate "average"
volatile uint	_MXBReady		= 0;
// Total duration (in timer ticks) of _MXBReady samples
volatile ulong	_MXBSum			= 0;
// Timestamp of the last captured rising edge
volatile ulong	_MXBStart		= 0;

//====================================================================
#endif	/*# __MXB_Use__ */




