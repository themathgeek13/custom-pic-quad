#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "Matrix3d\Matrix3D.h"

int main(void)
	{

	//*******************************************************************
	Init();
	//*******************************************************************
	float Roll	= Rad(15);
	float Pitch	= Rad(30);
	float Yaw	= Rad(45);

	Matrix	mAtt;
	Matrix	mRotBack;
	Matrix	mRollPitch;

	MatrixEulerRotation(Roll, Pitch, Yaw, &mAtt);
	MatrixEulerRotation(0, 0, -Yaw, &mRotBack);
	MatrixMult(&mRotBack, &mAtt, &mRollPitch);
	//===================================================================

	//===================================================================
	// Control board front does not coincide with the model front
	Matrix	CB_To_Model;
	// Build rotation matrix to adjust for orientation discrepancy
	MatrixYawRotation(Rad(-45), &CB_To_Model);

	Vector RC;
	Vector	RCRotated;
	VectorSet(0.0, 0.3, 0.0, &RC);
	MatrixTimesVector(&CB_To_Model, &RC, &RCRotated);


	//*******************************************************************
	return 1;
	}

