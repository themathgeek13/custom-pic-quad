#include "DCM\DCMLocal.h"

//==================================================================================
pDCM	_DCMMultiply(DCM* pLeft, DCM* pRight, DCM* pResult)
	{
	// Perform multiplication:
	// First row...
	pResult->Rxx = pLeft->Rxx*pRight->Rxx + pLeft->Rxy*pRight->Ryx + pLeft->Rxz*pRight->Rzx;
	pResult->Rxy = pLeft->Rxx*pRight->Rxy + pLeft->Rxy*pRight->Ryy + pLeft->Rxz*pRight->Rzy;
	pResult->Rxz = pLeft->Rxx*pRight->Rxz + pLeft->Rxy*pRight->Ryz + pLeft->Rxz*pRight->Rzz;
	// Second row...
	pResult->Ryx = pLeft->Ryx*pRight->Rxx + pLeft->Ryy*pRight->Ryx + pLeft->Ryz*pRight->Rzx;
	pResult->Ryy = pLeft->Ryx*pRight->Rxy + pLeft->Ryy*pRight->Ryy + pLeft->Ryz*pRight->Rzy;
	pResult->Ryz = pLeft->Ryx*pRight->Rxz + pLeft->Ryy*pRight->Ryz + pLeft->Ryz*pRight->Rzz;
	// Third row...
	pResult->Rzx = pLeft->Rzx*pRight->Rxx + pLeft->Rzy*pRight->Ryx + pLeft->Rzz*pRight->Rzx;
	pResult->Rzy = pLeft->Rzx*pRight->Rxy + pLeft->Rzy*pRight->Ryy + pLeft->Rzz*pRight->Rzy;
	pResult->Rzz = pLeft->Rzx*pRight->Rxz + pLeft->Rzy*pRight->Ryz + pLeft->Rzz*pRight->Rzz;
	//--------------------------------------------
	return pResult;
	}
//==================================================================================

//==================================================================================
DCM*	_DCMNormalize(DCM* pBase, DCM* pNorm)
	{
	float	Error	= 0;
	//======================================
	// Adjust orthogonality of the rows
	//======================================
	// Calculate Error based upon the orthogonality of the
	// first two rows:
	Error 	= pBase->Rxx*pBase->Ryx 
			+ pBase->Rxy*pBase->Ryy 
			+ pBase->Rxz*pBase->Ryz;
	// Apply correction to first two row:
	// Xb = Xb - (Error/2)*Yb;
	// Yb = Yb - (Error/2)*Xb;
	//----------------------------------------
	Error = Error/2;	// Preparation...
	//----------------------------------------
	// First row...
	pNorm->Rxx = pBase->Rxx - Error*pBase->Ryx;
	pNorm->Rxy = pBase->Rxy - Error*pBase->Ryy;
	pNorm->Rxz = pBase->Rxz - Error*pBase->Ryz;
	// Second row...
	pNorm->Ryx = pBase->Ryx - Error*pBase->Rxx;
	pNorm->Ryy = pBase->Ryy - Error*pBase->Rxy;
	pNorm->Ryz = pBase->Ryz - Error*pBase->Rxz;
	//----------------------------------------
	// Third row - a cross-product of the
	// first two: (A=Rx, B=Ry)
	//----------------------------------------
	pNorm->Rzx = pBase->Rxy*pBase->Ryz - pBase->Rxz*pBase->Ryy;
	pNorm->Rzy = pBase->Rxz*pBase->Ryx - pBase->Rxx*pBase->Ryz;
	pNorm->Rzz = pBase->Rxx*pBase->Ryy - pBase->Rxy*pBase->Ryx;
	//-----------------------------------------

	//======================================
	// Normalize the length of axis vectors
	//======================================
	float Scale;
	//-----------------------------------------
	// First row...
	Scale = (3 - (pNorm->Rxx*pNorm->Rxx + pNorm->Rxy*pNorm->Rxy + pNorm->Rxz*pNorm->Rxz))/2;
	pNorm->Rxx = Scale*pNorm->Rxx;
	pNorm->Rxy = Scale*pNorm->Rxy;
	pNorm->Rxz = Scale*pNorm->Rxz;
	// Second row...
	Scale = (3 - (pNorm->Ryx*pNorm->Ryx + pNorm->Ryy*pNorm->Ryy + pNorm->Ryz*pNorm->Ryz))/2;
	pNorm->Ryx = Scale*pNorm->Ryx;
	pNorm->Ryy = Scale*pNorm->Ryy;
	pNorm->Ryz = Scale*pNorm->Ryz;
	//----------------------------------------
	// Third row...
	//----------------------------------------
	Scale = (3 - (pNorm->Rzx*pNorm->Rzx + pNorm->Rzy*pNorm->Rzy + pNorm->Rzz*pNorm->Rzz))/2;
	pNorm->Rzx = Scale*pNorm->Rzx;
	pNorm->Rzy = Scale*pNorm->Rzy;
	pNorm->Rzz = Scale*pNorm->Rzz;
	//======================================

	return pNorm;
	}
//==================================================================================
