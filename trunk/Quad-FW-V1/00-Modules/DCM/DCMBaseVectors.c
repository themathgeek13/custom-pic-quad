#include "DCM\DCMLocal.h"

//=============================================================
// DCMGetMatrix returns current Rotation Matrix by rows.
// NOTE: rows of the DCM represent Earth frame axis in the
//		 Body frame od reference
//-------------------------------------------------------------
void		DCMGetMatrix(	Vector*		XEarth,
							Vector*		YEarth,
							Vector*		ZEarth)
	{
	DCMXEarth(&_DCMRM, XEarth);
	DCMYEarth(&_DCMRM, YEarth);
	DCMZEarth(&_DCMRM, ZEarth);
	}
//=============================================================

//=============================================================
// DCMToEarth rotates provided vector from Body frame to Earth
// frame using current DCM matrix
//=============================================================
Vector*	DCMToEarth(Vector* pV, Vector* pRes)
	{
	//--------------------------------------------------
	// Definition of Rotation to Earth:
	//--------------------------------------------------
	// 	Vearth	= R*Vbody
	//--------------------------------------------------
	//	Xe	= XEarth * InBody
	//	Ye	= YEarth * InBody
	//	Ze	= ZEarth * InBody
	//--------------------------------------------------
	pRes->X	= _DCMRM.Rxx*pV->X + _DCMRM.Rxy*pV->Y + _DCMRM.Rxz*pV->Z;
	pRes->Y	= _DCMRM.Ryx*pV->X + _DCMRM.Ryy*pV->Y + _DCMRM.Ryz*pV->Z;
	pRes->Z	= _DCMRM.Rzx*pV->X + _DCMRM.Rzy*pV->Y + _DCMRM.Rzz*pV->Z;
	//---------------------------------------------------------------
	return pRes;
	}

//=============================================================
// DCMToBody rotates provided vector from Earth frame to Body
// frame using current DCM matrix
//=============================================================
Vector*	DCMToBody(Vector* pV, Vector* pRes)
	{
	//--------------------------------------------------
	// Definition of Rotation to Body:
	//--------------------------------------------------
	// 	Vbody	= R(Transposed)*Vearth
	//--------------------------------------------------
	//	Xb	= InEarth * XBody
	//	Yb	= InEarth * YBody
	//	Zb	= InEarth * ZBody
	//--------------------------------------------------
	pRes->X	= pV->X*_DCMRM.Rxx + pV->Y*_DCMRM.Ryx + pV->Z*_DCMRM.Rzx;
	pRes->Y	= pV->X*_DCMRM.Rxy + pV->Y*_DCMRM.Ryy + pV->Z*_DCMRM.Rzy;
	pRes->Z	= pV->X*_DCMRM.Rxz + pV->Y*_DCMRM.Ryz + pV->Z*_DCMRM.Rzz;
	//---------------------------------------------------------------
	return pRes;
	}
//=============================================================







