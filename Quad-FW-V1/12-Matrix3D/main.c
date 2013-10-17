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

	MatrixBuildRotation(Roll, Pitch, Yaw, &mAtt);
	MatrixBuildRotation(0, 0, -Yaw, &mRotBack);
	MatrixMult(&mRotBack, &mAtt, &mRollPitch);

	//*******************************************************************
	return 1;
	}

