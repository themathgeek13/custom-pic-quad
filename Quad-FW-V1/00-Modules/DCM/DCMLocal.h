#include "DCM\DCM.h"
#ifdef __MAG_Use__
	#include "HMCMAG\HMCMAG.h"
#endif

//=====================================================
#ifndef __DCMLocal_H
#define __DCMLocal_H
//=====================================================
typedef struct
	{
	// DCM is a rotation matrix that rotates vectors
	// in the Body (moving) frame of reference 
	// to the Earth (static) frame of reference.
	//==================================================================================
	// Body axis in the Earth frame of reference are
	// the columns of the Rotation Matrix
	//----------------------------------------------
	// Earth axis in the Body frame of reference are
	// the rows of the Rotation Matrix
	//==================================================================================
	//		Xb/e Yb/e Zb/e
	//----------------------
	float	Rxx, Rxy, Rxz;	// Xe/b - X axis of Earth frame seen from the Body frame
	float	Ryx, Ryy, Ryz;	// Ye/b - Y axis of Earth frame seen from the Body frame
	float	Rzx, Rzy, Rzz;	// Ze/b - Z axis of Earth frame seen from the Body frame
	} DCM;
//-------------------------------------------------------------
extern	DCM			_DCMRM;				// Rotation matrix
//-------------------------------------------------------------
extern	float		_DCM_BaseAzimuth;	// Initial magnetic Azimuth
extern	Vector		_DCM_BaseMAG;		// Initial Magnetic vector (Earth Frame)
//=============================================================
// DCM Algorith Step Control Variables
//-------------------------------------------------------------
extern		 float	_DCM_TimeRate;	// Ticks to second conversion rate
extern		 ulong	_DCM_TS;		// Timestamp of the last DCM update
//-------------------------------------------------------------
extern		 uint	_DCMReady;
//-------------------------------------------------------------
extern const float	_DCMRPThreshold;
extern		 float	_DCMRPCurrent;
//-----------------------------------------------------
extern const float	_DCMAccKp;				// Kp = 2/tau
extern const float	_DCMAccKi;				// Ki = (1/tau)**2
//------------------------------------------------------------------
extern 	Vector		_DCMAccIterm;
//------------------------------------------------------------------

//=============================================================
DCM*	_DCMCopy(DCM* pBaseDCM, DCM* pNewDCM);
DCM*	_DCMSmallRotation(Vector* pDR, DCM* pNewDCM);
//=============================================================
DCM*	_DCMMultiply(DCM* pLeft, DCM* pRight, DCM* pResult);
DCM*	_DCMNormalize(DCM* pBase, DCM* pNorm);
//=============================================================


//==========================================================================
// Roll, Pitch, and Yaw of the Body in reference to Earth
// NOTE: We accept the following convention regarding rotation:
//==========================================================================
//	  -Pi <= Roll  <=  +Pi
//-------------------------------------------------------------
float	inline static _DCMRoll(DCM* pBase)
	{
	if (0 == pBase->Rzy && 0 == pBase->Rzz )
		return 0.0;	// Special case
	//--------------------------------------------------
	return atan2f(pBase->Rzy, pBase->Rzz); 
	}
//-------------------------------------------------------------
//	-Pi/2 <= Pitch <= +Pi/2
//-------------------------------------------------------------
float	inline static _DCMPitch(DCM* pBase)
	{
	if (pBase->Rzx >=  1.0)	return -1.570796;
	if (pBase->Rzx <= -1.0)	return +1.570796;
	//--------------------------------------
	return -asinf(pBase->Rzx);	
	}
//-------------------------------------------------------------
//	  -Pi <= Yaw   <=  +Pi
//-------------------------------------------------------------
float	inline static _DCMYaw(DCM* pBase)
	{
	if (0 == pBase->Ryx && 0 == pBase->Rxx )
		return 0.0;	// Special case
	//--------------------------------------------------
	return atan2f(pBase->Ryx, pBase->Rxx); 
	}
//==========================================================================
// Inclination measures Cosine between Ze and Zb;
// For "level" position Incl ~= 1.0 (Cos(0) = 1.0)
// For "upside-down" position Incl ~= -1.0 (Cos(Pi) = -1.0)
//-------------------------------------------------------------
float	inline static _DCMIncl(DCM* pBase)	//   -1.0 <= Incl  <= +1.0
	{ return pBase->Rzz; }
//==========================================================================

//==========================================================================
// Body axis in the Earth frame of reference are
// the columns of the Rotation Matrix
//==========================================================================
inline static Vector* _DCMBodyX(DCM* pBaseDCM, Vector* pRes)
	{ return VectorSet(pBaseDCM->Rxx, pBaseDCM->Ryx, pBaseDCM->Rzx, pRes); }
//------------------------------------------------
inline static Vector* _DCMBodyY(DCM* pBaseDCM, Vector* pRes)
	{ return VectorSet(pBaseDCM->Rxy, pBaseDCM->Ryy, pBaseDCM->Rzy, pRes); }
//------------------------------------------------
inline static Vector* _DCMBodyZ(DCM* pBaseDCM, Vector* pRes)
	{ return VectorSet(pBaseDCM->Rxz, pBaseDCM->Ryz, pBaseDCM->Rzz, pRes); }
//==========================================================================

//==========================================================================
// Earth axis in the Body frame of reference are
// the rows of the Rotation Matrix
//==========================================================================
inline static Vector* _DCMEarthX(DCM* pBaseDCM, Vector* pRes)
	{ return VectorSet(pBaseDCM->Rxx, pBaseDCM->Rxy, pBaseDCM->Rxz, pRes); }
//------------------------------------------------
inline static Vector* _DCMEarthY(DCM* pBaseDCM, Vector* pRes)
	{ return VectorSet(pBaseDCM->Ryx, pBaseDCM->Ryy, pBaseDCM->Ryz, pRes); }
//------------------------------------------------
inline static Vector* _DCMEarthZ(DCM* pBaseDCM, Vector* pRes)
	{ return VectorSet(pBaseDCM->Rzx, pBaseDCM->Rzy, pBaseDCM->Rzz, pRes); }
//==========================================================================

//==========================================================================
#endif

