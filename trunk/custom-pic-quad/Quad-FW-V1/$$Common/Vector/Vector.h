#include "System.h"
#include <math.h>

//=====================================================
#ifndef __Vector_H
#define __Vector_H
//=====================================================

typedef struct
	{
	// Vector structure represents a 3-dimensional vector.
	//-----------------------------------------------
	float	X;
	float	Y;
	float	Z;
	} Vector, *pVector;
//==============================================================
pVector	inline static VectorSet(float X, float Y, float Z, Vector* pRes)
	{
	pRes->X	= X;	pRes->Y	= Y;	pRes->Z	= Z;
	//-------------------------------------------
	return pRes;
	}
//==============================================================
pVector	inline static VectorCopy(Vector* pV1, Vector* pRes)
	{
	pRes->X	= pV1->X;
	pRes->Y	= pV1->Y;
	pRes->Z	= pV1->Z;
	//--------------------------------------
	return pRes;
	}
//==============================================================
float	inline static VectorDotProduct(Vector* pV1, Vector* pV2)
	{
	return pV1->X*pV2->X + pV1->Y*pV2->Y + pV1->Z*pV2->Z;
	}
//==============================================================
pVector	inline static VectorCrossProduct(Vector* pV1, Vector* pV2, Vector* pRes)
	{
	pRes->X	= pV1->Y*pV2->Z - pV1->Z*pV2->Y;
	pRes->Y	= pV1->Z*pV2->X - pV1->X*pV2->Z;
	pRes->Z	= pV1->X*pV2->Y - pV1->Y*pV2->X;
	//--------------------------------------
	return pRes;
	}
//==============================================================
pVector	inline static VectorAdd(Vector* pV1, Vector* pV2, Vector* pRes)
	{
	pRes->X	= pV1->X + pV2->X;
	pRes->Y	= pV1->Y + pV2->Y;
	pRes->Z	= pV1->Z + pV2->Z;
	//--------------------------------------
	return pRes;
	}
//==============================================================
pVector	inline static VectorSub(Vector* pV1, Vector* pV2, Vector* pRes)
	{
	pRes->X	= pV1->X - pV2->X;
	pRes->Y	= pV1->Y - pV2->Y;
	pRes->Z	= pV1->Z - pV2->Z;
	//--------------------------------------
	return pRes;
	}
//==============================================================
pVector	inline static VectorMultiply(Vector* pV1, float Scalar, Vector* pRes)
	{
	pRes->X	= pV1->X * Scalar;
	pRes->Y	= pV1->Y * Scalar;
	pRes->Z	= pV1->Z * Scalar;
	//--------------------------------------
	return pRes;
	}
//==============================================================
float	inline static VectorSize(Vector* pV1)
	{
	return sqrtf(pV1->X*pV1->X + pV1->Y*pV1->Y + pV1->Z*pV1->Z);
	}
//==============================================================
pVector	inline static VectorNormalize(Vector* pV1, Vector* pRes)
	{
	float 	Size = VectorSize(pV1);
	if (Size < 1.0e-14)
		return VectorSet(0.0, 0.0, 0.0, pRes);
	//----------------------------------------------------------
	float	Norm = 1.0 / Size;
	return 	VectorMultiply(pV1, Norm, pRes);
	}
//==============================================================


//==============================================================
#endif
