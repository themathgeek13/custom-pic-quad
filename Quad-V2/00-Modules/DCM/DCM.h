#include "System.h"
#include "Vector/Vector.h"
#include "Matrix3D/Matrix3D.h"

//=====================================================
#ifndef __DCM_H
#define __DCM_H
//==================================================================
// DCMResult - results of DCM calculation
//==================================================================
typedef struct
	{
	ulong	TS;		// Timestamp of the cycle
	//-----------------------------------------------
	// Attitude
	//-----------------------------------------------
	float	Roll;
	float	Pitch;
	float	Yaw;
	//--------------
	float	Incl;
	//--------------
	float	Azimuth;
	//-----------------------------------------------
	// Base input data
	//-----------------------------------------------
	Vector	GyroRate;
	Vector	Gravity;
	//--------------
	}	DCMData;
//=============================================================
// DCMReset resets DCM to initial state and resets _DCMReady
//-------------------------------------------------------------
void		DCMReset();
void		DCMSetAzimuth(Vector* pMag);
//=============================================================
// DCMPerformStep returns value of _DCMReady
//-------------------------------------------------------------
uint		DCMPerformStep(	ulong		TS,			// Timestamp of the cycle
							Vector*		pGyroRaw,
							Vector*		pAccRaw,
							DCMData*	pIMUResult);
//=============================================================
// DCMGetMatrix returns current Rotation Matrix.
// NOTE: rows of the DCM represent Earth frame axis in the
//		 Body frame od reference
//-------------------------------------------------------------
Matrix*		DCMGetMatrix(	Matrix*		M);
//=====================================================
Vector*		DCMToEarth(	Vector* pV, Vector* pRes);
Vector*		DCMToBody(	Vector* pV, Vector* pRes);
//=============================================================
// DCMEarthX returns X axis of Earth frame as seen from the
// Body frame (roll axis) from the current DCM matrix
//-------------------------------------------------------------
Vector*		DCMEarthX(Vector* EarthX);
//=============================================================
// DCMEarthY returns Y axis of Earth frame as seen from the
// Body frame (pitch axis) from the current DCM matrix
//-------------------------------------------------------------
Vector*		DCMEarthY(Vector* EarthY);
//=============================================================
// DCMEarthZ returns Z axis of Earth frame as seen from the
// Body frame (yaw axis) from the current DCM matrix
//-------------------------------------------------------------
Vector*		DCMEarthZ(Vector* EarthZ);
//==========================================================================
#endif
