#include "System.h"
#include <math.h>

#include "Vector\Vector.h"
//=====================================================================
#ifndef __MATRIX3D_H
#define	__MATRIX3D_H
//=====================================================================
typedef struct
	{
	float	M_1_1, M_1_2, M_1_3;		// First row
	float	M_2_1, M_2_2, M_2_3;		// Second row
	float	M_3_1, M_3_2, M_3_3;		// First row
	} Matrix;
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

