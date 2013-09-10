#include "DCM\DCMLocal.h"

//==================================================================
// Rotation Matrix - defines rotations experienced by the body
//==================================================================
DCM		_DCMRM =
		{
		1.0,	0.0,	0.0,	// Initially RM is represented as an
		0.0,	1.0,	0.0,	// "identity" matrix as the Body frame
		0.0,	0.0,	1.0		// assumed to coincide with the Earth frame
		};

//-------------------------------------------------------------
// DCM Algorith Step Control Variables
//-------------------------------------------------------------
float	_DCM_TimeRate	= 0.0;	// Ticks to second conversion rate
ulong	_DCM_TS 		=   0;	// Timestamp of the last DCM update

//==================================================================
// If initial orientation of the IMU is not level, we need to adjust
// Rotational Matrix (based upon accelerometers) to reflect original
// Roll and Pitch prior to calculating Azimuth and Magnetometer
// correction. _DCMReady will be set to "1" when "leveling" is done.
//==================================================================
uint	_DCMReady		=   0;
//------------------------------------------------------------------
// To identify that "leveling" is complete we start with some "high"
// level of Roll-Pitch correction and wait until it drops (on sub-
// sequent) steps below some threshold.
//------------------------------------------------------------------
float			_DCMRPCurrent	= 5.0;
const float		_DCMRPThreshold	= 0.004; // ~0.25 degree difference

//==================================================================
// Accelerometer is used to generate correction terms to adjust
// rotation as measured by Gyroscope using PI(D) algorithm
// (Derivative term is ignored). The following coefficients define
// P and I terms of the correction algorithm:
//==================================================================
const float		_DCMAccKp		= 0.004;		// Kp = 2/tau
const float		_DCMAccKi		= 0.000004;		// Ki = (1/tau)**2


//==================================================================
// Accelerometer-based integral correction term is cumulative by
// nature, so we need to maintain its value
//==================================================================
Vector			_DCMAccIterm	= {0.0, 0.0, 0.0};







