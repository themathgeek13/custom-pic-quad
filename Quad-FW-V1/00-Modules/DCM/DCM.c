#include "DCM\DCMLocal.h"
#include "TMR\TMR.h"

//==================================================================================
void	DCMReset()
	{
	//------------------------------------------------------------------
	// Initially RM is represented as an
	// "identity" matrix as the Body frame
	// assumed to coincide with the Earth frame
	//------------------------------------------------------------------
	_DCMRM.Rxx = _DCMRM.Ryy = _DCMRM.Rzz	= 1.0;
	_DCMRM.Rxy = _DCMRM.Rxz = _DCMRM.Ryx = _DCMRM.Ryz = _DCMRM.Rzx = _DCMRM.Rzy = 0.0;
	//------------------------------------------------------------------
	// Magnetic Azimuth initially set to 0.0 (assuming North)
	// and initial magnetic vector nullified
	//------------------------------------------------------------------
	_DCM_BaseAzimuth	= 0.0;
	VectorSet(0.0, 0.0, 0.0, &_DCM_BaseMAG);

	//------------------------------------------------------------------
	// Now we need to set indicator that DCM is not synchronized yet
	_DCMReady		=   0;
	// And we need to reset DCM Step Control Variables
	_DCM_TimeRate	= 0.0;	// Ticks to second conversion rate
	_DCM_TS 		=   0;	// Timestamp of the last DCM update
	//------------------------------------------------------------------
	// To identify that "leveling" is complete we start with some "high"
	// level of Roll-Pitch correction and wait until it drops (on sub-
	// sequent) steps below some threshold.
	//------------------------------------------------------------------
	_DCMRPCurrent	= 5.0;
	//==================================================================
	// Accelerometer-based integral correction term is cumulative by
	// nature, so we need to reset its value
	//==================================================================
	VectorSet(0.0, 0.0, 0.0, &_DCMAccIterm);
	//==================================================================
	}
//==================================================================================

//==================================================================================
void	DCMSetAzimuth(Vector* pMag)
	{
	//------------------------------------------------------------------
	// Resets base Azimuth (initial orientation related to magnetic
	// NORTH) based upon Magnetometer sample in the Body Frame
	//------------------------------------------------------------------
	// First, transform to Earth frame
	//-----------------------------------------------
	DCMToEarth(pMag, &_DCM_BaseMAG);
	//-----------------------------------------------
	// then calculate Base Azimuth
	//-----------------------------------------------
	if (0 != _DCM_BaseMAG.X || 0 != _DCM_BaseMAG.Y )
		_DCM_BaseAzimuth = atan2f(-_DCM_BaseMAG.Y, _DCM_BaseMAG.X);
	else
		_DCM_BaseAzimuth = 0.0;
	}
//==================================================================================


//==================================================================================
uint	DCMPerformStep(	Vector*		pGyroRaw,
						Vector*		pAccRaw,
						DCMData*	pIMUResult)
	{
	//==========================================================================
	if (0.0 == _DCM_TimeRate)
		// First (initial) invocation of DCMPerformStep routine...
		{
		TMRInitDefault();	// Hopefully timer is already initialized
							// so this call is just a NOP
		//-----------------------------------------------------------
		_DCM_TimeRate	= TMRGetTSRate();
		_DCM_TS			= TMRGetTS();
		//-----------------------------------------------------------
		return _DCMReady;	// Initialized to "0", indicating that
							// stability is not reached yet...
		}
	//==========================================================================
	ulong	TS 			= TMRGetTS();	// Current time stamp
	float	TimeStep	= _DCM_TimeRate * (TS - _DCM_TS);
			_DCM_TS		= TS;
	//--------------------------------------------------------------------------
	// Sanity check (primarily to allow "breakpoints" during debugging) - if
	// TimeStep exceeds some "reasonable" value (timer is running while we look
	// at the data in the debug window :) we set it back to a "maximum" - let's
	// say, 30 msec. to avoid destabilization of DCM algorithm due to huge in-
	// tegral terms
	//--------------------------------------------------------------------------
	if (TimeStep > 0.030)
		TimeStep = 0.030;
	//==========================================================================

	//--------------------------------------------------------------------------
	// Local variables used in calculations of the Accelerometer-based correction
	//--------------------------------------------------------------------------
	Vector			ZEarth;			// Earth vertical in the Body frame
	Vector			AccNorm;		// Normalized Accelerometer measurement
									// in the Body frame
	Vector			AccError;		// Rotational "error" between the Earth ver-
									// tical (in Body frame) and acceleration
									// vector.
	Vector			AccPterm;		// Proportional term
	Vector			AccIterm;		// Current step component of Integral term
	Vector			AccAdj;			// Current step total Acc-based adjustment
	//--------------------------------------------------------------------------
	// Calculating Accelerometer-based correction
	//--------------------------------------------------------------------------
	{	
	// Normalize Accelerometer measurement
	VectorNormalize(pAccRaw, &AccNorm);
	// Extract Z-axis in the Earth frame as seen from the Body frame
	// from the DCM
	_DCMZEarth(&_DCMRM, &ZEarth);
	//---------------------------------------------------------
	// Cross-product of the axis Z in the Earth frame (as seen
	// from the Body frame) of the DCM with the normalized
	// Accelerometer measurement (true Z-axis of Earth frame
	// as seen from the Body frame ignoring linear accelerations)
	// is the ERROR between DCM and true Z-axis and defines how
	// much the Rotation Matrix need to be rotated so that these
	// vectors match.
	//---------------------------------------------------------
	VectorCrossProduct(&ZEarth, &AccNorm, &AccError);
	//---------------------------------------------------------
	// Accelerometer correction P-Term
	//---------------------------------------------------------
	if (_DCMReady)
		{
		VectorMultiply(&AccError, _DCMAccKp, &AccPterm);	// Normal convergence (weight)
		VectorMultiply(&AccError, (_DCMAccKi * TimeStep), &AccIterm);
		}
	else
		{
		VectorMultiply(&AccError,    0.1,    &AccPterm);	// Fast convergence 
		VectorSet(0.0, 0.0, 0.0, 			 &AccIterm);	// ignoring I-term
		}
	//---------------------------------------------------------
	// Accelerometer correction I-Term
	//---------------------------------------------------------
	VectorAdd(&_DCMAccIterm, &AccIterm, &_DCMAccIterm);
	//---------------------------------------------------------
	// Total Accelerometer-based correction
	//---------------------------------------------------------
	VectorAdd(&AccPterm, &_DCMAccIterm, &AccAdj);
	}
	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	if (0 == _DCMReady)
		{
		//---------------------------------------------------
		// Calculating Weighted filtered Acc adjustment value
		//---------------------------------------------------
		// DCM Z-axis and Accelerometer Z-axis are both nor-
		// malized vectors, so the size of their cross-product
		// is the angle between these axis.
		//---------------------------------------------------
		float	Correction	= VectorSize(&AccError);
		_DCMRPCurrent = (3.0*_DCMRPCurrent + Correction)/4.0;
		//---------------------------------------------------
		if (_DCMRPCurrent < _DCMRPThreshold)
			// Initial Roll-Pitch accounted for
			_DCMReady = 1;
		}

	//--------------------------------------------------------------------------
	// Local variables used in "rotating" Rotational Matrix
	//--------------------------------------------------------------------------
	Vector	RotationDelta;
	DCM		SmallRotation;
	DCM		Rotated;
	//--------------------------------------------------------------------------
	// Calculating total adjustment and "rotate" Rotational Matrix
	//--------------------------------------------------------------------------
	// Calculate rotation delta in body frame in radians through "integration"
	// of the gyro rotation rates
	VectorMultiply(	pGyroRaw, TimeStep, &RotationDelta);
	//--------------------------------------------------------------------------
	VectorAdd(&RotationDelta, &AccAdj, &RotationDelta);
	// Construct "infinitesimal" rotation matrix
	_DCMSmallRotation(&RotationDelta, &SmallRotation);
	// Rotate DCM by "small rotation"
	_DCMMultiply(&_DCMRM, &SmallRotation, &Rotated);
	// Normalize and store current DCM Rotation Matrix
	_DCMNormalize(&Rotated, &_DCMRM);
	//===========================================================================

	//---------------------------------------------------------------------------
	// Load Current orientation parameters into DCMData
	//---------------------------------------------------------------------------
	pIMUResult->Roll	= _DCMRoll(&_DCMRM);
	pIMUResult->Pitch	= _DCMPitch(&_DCMRM);
	pIMUResult->Yaw		= _DCMYaw(&_DCMRM);
	//------------------------------------------------------------
	pIMUResult->Incl	= _DCMIncl(&_DCMRM);
	//---------------------------------------------------------------------------
	pIMUResult->Azimuth	= _DCM_BaseAzimuth + pIMUResult->Yaw;
	//---------------------------------------------------------------------------
	VectorCopy(pGyroRaw, &pIMUResult->GyroRate);
	//----------------------------------------------------------------------------
	return	_DCMReady;
	}
//==================================================================================








