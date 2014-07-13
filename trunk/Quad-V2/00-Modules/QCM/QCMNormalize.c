//**********************************************************************
#include "QCM\QCMLocal.h"
//**********************************************************************

//**********************************************************************
void	QCMNormalize(MCMData* MC)
	{
	//***********************************************************
	// Normalize all Throttle values to be >= _PID_ThrottleMin
	//-----------------------------------------------------------
	float	ThrottleMin		= _PID_ThrottleMin;
	float	ThrottleOffset;
	//-----------------------------------------------------------
	if (MC->F < ThrottleMin) ThrottleMin = MC->F;
	if (MC->B < ThrottleMin) ThrottleMin = MC->B;
	if (MC->L < ThrottleMin) ThrottleMin = MC->L;
	if (MC->R < ThrottleMin) ThrottleMin = MC->R;
	//-----------------------------------------------------------
	if (ThrottleMin < _PID_ThrottleMin)
		{
		ThrottleOffset	= _PID_ThrottleMin - ThrottleMin;
		//-----------------------------------------------
		MC->F += ThrottleOffset;
		MC->B += ThrottleOffset;
		//-----------------------------------------------
		MC->R += ThrottleOffset;
		MC->L += ThrottleOffset;
		}
	//***********************************************************

	//***********************************************************
	// Normalize all Throttle values to be 0.0 <= X <= 1.0
	//-----------------------------------------------------------
	float	ThrottleScale		= 1.0;
	//-----------------------------------------------------------
	if (MC->F > ThrottleScale) ThrottleScale = MC->F;
	if (MC->B > ThrottleScale) ThrottleScale = MC->B;
	if (MC->L > ThrottleScale) ThrottleScale = MC->L;
	if (MC->R > ThrottleScale) ThrottleScale = MC->R;
	//-----------------------------------------------------------
	if (ThrottleScale > 1.0)
		{
		float KNorm		= 1.0 / ThrottleScale;
		//-----------------------------------
		MC->F *= KNorm;
		MC->B *= KNorm;
		//--------------
		MC->R *= KNorm;
		MC->L *= KNorm;
		}
	//***********************************************************
	}
//************************************************************





