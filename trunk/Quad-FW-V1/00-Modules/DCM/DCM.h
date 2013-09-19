#include "System.h"
#include "Vector\Vector.h"

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
	Vector	GyroRate;
	//--------------
	}	DCMData;
//=============================================================
// DCMReset resets DCM to initial state and resets _DCMReady
//-------------------------------------------------------------
void		DCMReset();
//=============================================================
// DCMPerformStep returns value of _DCMReady
//-------------------------------------------------------------
uint		DCMPerformStep(	Vector*		pGyroRaw,
							Vector*		pAccRaw,
							DCMData*	pIMUResult);
//=============================================================
// DCMGetMatrix returns current Rotation Matrix by rows.
// NOTE: rows of the DCM represent Earth frame axis in the
//		 Body frame od reference
//-------------------------------------------------------------
void		DCMGetMatrix(	Vector*		XEarth,
							Vector*		YEarth,
							Vector*		ZEarth);
//=====================================================
Vector*	DCMToEarth(	Vector* pV, Vector* pRes);
Vector*	DCMToBody(	Vector* pV, Vector* pRes);
//=============================================================
#endif
