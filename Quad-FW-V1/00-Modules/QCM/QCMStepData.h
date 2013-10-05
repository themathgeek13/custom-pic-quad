#include "System.h"

//=====================================================
#ifndef __QCMStepData_H
#define __QCMStepData_H
//=====================================================
typedef struct
	{
	//=================================================
	// Variables used in calculating State Change
	// Derivatives and error integrals
	//-------------------------------------------------
	ulong	LastTS;		// TS of last step - for integration
	float	dT;			// Integration/Differentiation time
						// step (in seconds)
	//-------------------------------------------------
	// Saved to facilitate calculation of State Derivative
	//-------------------------------------------------
	float	LastRoll;
	float	LastPitch;
	float	LastYaw;
	//-------------------------------------------------
	
	//=================================================
	float	Throttle;
	//=================================================
	// Error variables by axis
	//-------------------------------------------------
	float	RollError;
	float	PitchError;
	float	YawError;
	//-------------------------------------------------
	// Accumulated error sum variables by axis
	//-------------------------------------------------
	float	RollErrorSum;
	float	PitchErrorSum;
	float	YawErrorSum;
	//=================================================
	// State change derivatives
	//-------------------------------------------------
	float	RollDer;
	float	PitchDer;
	float	YawDer;		
	//=================================================
	// Proportional components of motor control
	//-------------------------------------------------
	float	DeltaRollProp;
	float	DeltaPitchProp;
	float	DeltaYawProp;
	//-------------------------------------------------
	// Differential components of motor control
	//-------------------------------------------------
	float	DeltaRollDiff;
	float	DeltaPitchDiff;
	float	DeltaYawDiff;
	//-------------------------------------------------
	// Integral components of motor control
	//-------------------------------------------------
	float	DeltaRollInt;
	float	DeltaPitchInt;
	float	DeltaYawInt;
	//-------------------------------------------------
	// Total motor control adjustmens
	//-------------------------------------------------
	float	DeltaRoll;			
	float	DeltaPitch;
	float	DeltaYaw;
	//-------------------------------------------------
	// Battery Voltage
	//-------------------------------------------------
	float	Voltage;
	//-------------------------------------------------
	} _QCMStepData;
//=====================================================
extern	_QCMStepData		QSD;

//*****************************************************
// QCM Step ReSet routine
//*****************************************************
void inline static QCMReset()
	{
	QSD.LastTS	= 0;
	}

//=====================================================

#endif


