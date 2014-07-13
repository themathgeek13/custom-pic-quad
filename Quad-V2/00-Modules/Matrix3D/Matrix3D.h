#include "System.h"
#include <math.h>

#include "Vector\Vector.h"
//=====================================================================
#ifndef __MATRIX3D_H
#define	__MATRIX3D_H
//=====================================================================
#define	Deg(x)   ((float)x * 57.29578)
#define Rad(x)	 ((float)x * 0.0174533)
//=====================================================================
typedef struct
	{
	float	M_1_1, M_1_2, M_1_3;		// First row
	float	M_2_1, M_2_2, M_2_3;		// Second row
	float	M_3_1, M_3_2, M_3_3;		// First row
	} Matrix;
//=====================================================================
static inline Matrix*	MatrixSetIdentity(Matrix* I)
	{
	//----------------------------------------
	// Main Diagonal
	//----------------------------------------
	I->M_1_1 = I->M_2_2 = I->M_3_3 = 1.0;
	//---------------------
	// All other elements
	//----------------------------------------
	I->M_2_1 = I->M_3_1 = I->M_1_2 = I->M_3_2 = I->M_1_3 = I->M_2_3 = 0.0;
	//----------------------------------------
	return I;
	}
//=====================================================================
static inline Matrix*	MatrixTranspose(Matrix* S, Matrix* T)
	{
	T->M_1_1	= S->M_1_1;
	T->M_1_2	= S->M_2_1;
	T->M_1_3	= S->M_3_1;
	//---------------------
	T->M_2_1	= S->M_1_2;
	T->M_2_2	= S->M_2_2;
	T->M_2_3	= S->M_3_2;
	//---------------------
	T->M_3_1	= S->M_1_3;
	T->M_3_2	= S->M_2_3;
	T->M_3_3	= S->M_3_3;
	//---------------------
	return T;
	}
//=====================================================================
static inline Matrix*	MatrixEulerRotation(float	Roll,
											float	Pitch,
											float	Yaw,
											Matrix* T)
	{
	float	SinRoll		= sinf(Roll);
	float	CosRoll		= cosf(Roll);
	float	SinPitch	= sinf(Pitch);
	float	CosPitch	= cosf(Pitch);
	float	SinYaw		= sinf(Yaw);
	float	CosYaw		= cosf(Yaw);
	//----------------------------------------
	// First column
	//----------------------------------------
	T->M_1_1	= CosPitch * CosYaw;
	T->M_2_1	= CosPitch * SinYaw;
	T->M_3_1	= -SinPitch;
	//---------------------
	// Second column
	//----------------------------------------
	T->M_1_2	= SinRoll * SinPitch * CosYaw - CosRoll * SinYaw;
	T->M_2_2	= SinRoll * SinPitch * SinYaw + CosRoll * CosYaw;
	T->M_3_2	= SinRoll * CosPitch;
	//---------------------
	// Third column
	//----------------------------------------
	T->M_1_3	= CosRoll * SinPitch * CosYaw + SinRoll * SinYaw;
	T->M_2_3	= CosRoll * SinPitch * SinYaw - SinRoll * CosYaw;
	T->M_3_3	= CosRoll * CosPitch;
	//----------------------------------------
	return T;
	}
//=====================================================================
static inline Matrix*	MatrixRollRotation(float Roll, Matrix* T)
	{
	float	SinRoll		= sinf(Roll);
	float	CosRoll		= cosf(Roll);
	//----------------------------------------
	// First column
	//----------------------------------------
	T->M_1_1	=  1.0;
	T->M_2_1	=  0.0;
	T->M_3_1	=  0.0;
	//---------------------
	// Second column
	//----------------------------------------
	T->M_1_2	=  0.0;
	T->M_2_2	=  CosRoll;
	T->M_3_2	=  SinRoll;
	//---------------------
	// Third column
	//----------------------------------------
	T->M_1_3	=  0.0;
	T->M_2_3	= -SinRoll;
	T->M_3_3	=  CosRoll;
	//----------------------------------------
	return T;
	}
//=====================================================================
static inline Matrix*	MatrixPitchRotation(float Pitch, Matrix* T)
	{
	float	SinPitch	= sinf(Pitch);
	float	CosPitch	= cosf(Pitch);
	//----------------------------------------
	// First column
	//----------------------------------------
	T->M_1_1	=  CosPitch;
	T->M_2_1	=  0.0;
	T->M_3_1	= -SinPitch;
	//---------------------
	// Second column
	//----------------------------------------
	T->M_1_2	=  0.0;
	T->M_2_2	=  1.0;
	T->M_3_2	=  0.0;
	//---------------------
	// Third column
	//----------------------------------------
	T->M_1_3	=  SinPitch;
	T->M_2_3	=  0.0;
	T->M_3_3	=  CosPitch;
	//----------------------------------------
	return T;
	}
//=====================================================================
static inline Matrix*	MatrixYawRotation(float	Yaw, Matrix* T)
	{
	float	SinYaw		= sinf(Yaw);
	float	CosYaw		= cosf(Yaw);
	//----------------------------------------
	// First column
	//----------------------------------------
	T->M_1_1	=  CosYaw;
	T->M_2_1	=  SinYaw;
	T->M_3_1	=  0.0;
	//---------------------
	// Second column
	//----------------------------------------
	T->M_1_2	= -SinYaw;
	T->M_2_2	=  CosYaw;
	T->M_3_2	=  0.0;
	//---------------------
	// Third column
	//----------------------------------------
	T->M_1_3	=  0.0;
	T->M_2_3	=  0.0;
	T->M_3_3	=  1.0;
	//----------------------------------------
	return T;
	}
//=====================================================================
static inline Vector*	MatrixGetRow(Matrix* M, uint Row, Vector* T)
	{
	switch (Row)
		{
		case 1:
			return VectorSet(M->M_1_1, M->M_1_2, M->M_1_3, T);
		case 2:
			return VectorSet(M->M_2_1, M->M_2_2, M->M_2_3, T);
		case 3:
		default:
			return VectorSet(M->M_3_1, M->M_3_2, M->M_3_3, T);
		}
	}
//=====================================================================
static inline Vector*	MatrixGetCol(Matrix* M, uint Col, Vector* T)
	{
	switch (Col)
		{
		case 1:
			return VectorSet(M->M_1_1, M->M_2_1, M->M_3_1, T);
		case 2:
			return VectorSet(M->M_1_2, M->M_2_2, M->M_3_2, T);
		case 3:
		default:
			return VectorSet(M->M_1_3, M->M_2_3, M->M_3_3, T);
		}
	}
//=====================================================================
static inline Matrix*	MatrixMult(Matrix* L, Matrix* R, Matrix* T)
	{
	Vector	Row;
	Vector	Col1, Col2, Col3;
	//------------------------------------
	MatrixGetCol(R, 1, &Col1);
	MatrixGetCol(R, 2, &Col2);
	MatrixGetCol(R, 3, &Col3);
	//------------------------------------
	MatrixGetRow(L, 1, &Row);
	T->M_1_1	= VectorDotProduct(&Row, &Col1);
	T->M_1_2	= VectorDotProduct(&Row, &Col2);
	T->M_1_3	= VectorDotProduct(&Row, &Col3);
	//------------------------------------
	MatrixGetRow(L, 2, &Row);
	T->M_2_1	= VectorDotProduct(&Row, &Col1);
	T->M_2_2	= VectorDotProduct(&Row, &Col2);
	T->M_2_3	= VectorDotProduct(&Row, &Col3);
	//------------------------------------
	MatrixGetRow(L, 3, &Row);
	T->M_3_1	= VectorDotProduct(&Row, &Col1);
	T->M_3_2	= VectorDotProduct(&Row, &Col2);
	T->M_3_3	= VectorDotProduct(&Row, &Col3);
	//------------------------------------
	return T;
	}
//=====================================================================
static inline Vector*	MatrixTimesVector(Matrix* L, Vector* R, Vector* T)
	{
	Vector	Row;
	//------------------------------------
	T->X	= VectorDotProduct(MatrixGetRow(L, 1, &Row), R);
	T->Y	= VectorDotProduct(MatrixGetRow(L, 2, &Row), R);
	T->Z	= VectorDotProduct(MatrixGetRow(L, 3, &Row), R);
	//------------------------------------
	return T;
	}
//=====================================================================
static inline Vector*	VectorTimesMatrix(Vector* L, Matrix* R, Vector* T)
	{
	Vector	Col;
	//------------------------------------
	T->X	= VectorDotProduct(L, MatrixGetCol(R, 1, &Col));
	T->Y	= VectorDotProduct(L, MatrixGetCol(R, 2, &Col));
	T->Z	= VectorDotProduct(L, MatrixGetCol(R, 3, &Col));
	//------------------------------------
	return T;
	}

//=====================================================================
#endif	/* __MATRIX3D_H */

