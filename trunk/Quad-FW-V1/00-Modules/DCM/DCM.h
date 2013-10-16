#include "System.h"
#include "Vector\Vector.h"
#include "Matrix3D\Matrix3D.h"

//=====================================================
#ifndef __DCM_H
#define __DCM_H
//==================================================================
// DCMResult - results of DCM calculation
//==================================================================
typedef struct
	{
	float	Roll;
	float	Pitch;
	float	Yaw;
	//--------------
	float	Incl;
	//--------------
	float	Azimuth;
	//--------------
	Vector	GyroRate;
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
uint		DCMPerformStep(	Vector*		pGyroRaw,
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
#endif
