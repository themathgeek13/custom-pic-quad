#include "DCM/DCMLocal.h"

//==================================================================================
DCM*	_DCMCopy(DCM* pBaseDCM, DCM* pNewDCM)
	{
	//------------------------------------------------------------------------------
	pNewDCM->Rxx = pBaseDCM->Rxx;	pNewDCM->Rxy = pBaseDCM->Rxy;	pNewDCM->Rxz = pBaseDCM->Rxz;
	pNewDCM->Ryx = pBaseDCM->Ryx;	pNewDCM->Ryy = pBaseDCM->Ryy;	pNewDCM->Ryz = pBaseDCM->Ryz;
	pNewDCM->Rzx = pBaseDCM->Rzx;	pNewDCM->Rzy = pBaseDCM->Rzy;	pNewDCM->Rzz = pBaseDCM->Rzz;
	//------------------------------------------------------------------------------
	return pNewDCM;
	}
//==================================================================================
DCM*	_DCMSmallRotation(Vector* pDR, DCM* pNewDCM)
	{
	// DR (Delta Rotation) pseudo-vector represents small
	// rotations: around X (roll), around Y (pitch), and
	// around Z (yaw)
	//--------------------------------------------
	// Infinitesimal Rotation Approximation...
	pNewDCM->Rxx	=  1.0F;	pNewDCM->Rxy = -pDR->Z;		pNewDCM->Rxz =  pDR->Y;
	pNewDCM->Ryx =  pDR->Z;		pNewDCM->Ryy =  1.0F;		pNewDCM->Ryz = -pDR->X;
	pNewDCM->Rzx = -pDR->Y;		pNewDCM->Rzy =  pDR->X;		pNewDCM->Rzz =  1.0F;
	//--------------------------------------------
	//		1		-sin(Yaw)		 sin(Pitch)
	//	 sin(Yaw)		1			-sin(Roll)
	//	-sin(Pitch)	 sin(Roll)			1
	//--------------------------------------------
	return pNewDCM;
	}
//==================================================================================

