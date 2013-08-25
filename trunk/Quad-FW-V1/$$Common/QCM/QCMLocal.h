#include "QCM\QCM.h"

//=====================================================
#ifndef __QCMLocal_H
#define __QCMLocal_H
//=====================================================
// HW Components
//-------------------------
#include "TMR\TMR.h"
#include "ADC\ADC.h"

//-------------------------
// Step local storage
//-------------------------
#include "QCM\QCMStepData.h"
//=====================================================


//*****************************************************
// QCM internal data objects
//*****************************************************
// PID coefficients/parameters for Motor Control
//-----------------------------------------------------
extern		float const		_PID_ThrottleMin;
//============================================================
extern		float const		_PID_ThrottleNoFly;
//------------------------------------------------------------
extern		float const		_PID_ControlLimit;
//------------------------------------------------------------
extern		float const		_PID_SumWeight;
//------------------------------------------------------------
extern		float const		_PID_ErrSum_MAX;
extern		float const		_PID_ErrSum_MIN;
//============================================================
extern		float const		_PID_Roll_Kp;
extern		float const		_PID_Roll_Kd;
//=====================================================
extern		float const		_PID_Pitch_Kp;
extern		float const		_PID_Pitch_Kd;
//=====================================================
extern		float const		_PID_Yaw_Kp;
extern		float const		_PID_Yaw_Kd;
//*****************************************************
void	QCMNormalize(MCMData* MC);
//=====================================================

//*****************************************************
// QCM helper routine to normalize Value to +/- Pi
//*****************************************************
float inline static QCMRangeToPi(float Value)
	{
	if (Value < -3.14159265)
		return (Value + 6.2831853);
	if (Value >  3.14159265)
		return (Value - 6.2831853);
	return Value;
	}
//*****************************************************

//*****************************************************
// QCM helper routine to normalize Value to +/- Pi/2
//*****************************************************
float inline static QCMRangeToHalfPi(float Value)
	{
	if (Value < -1.57079632)
		return (Value + 3.14159264);
	if (Value >  1.57079632)
		return (Value - 3.14159264);
	return Value;
	}
//*****************************************************


//*****************************************************
// Local static variables used in Differentiation routine
//*****************************************************
static float	_QCM_LastRollErr	= 0.0;
static float	_QCM_LastPitchErr	= 0.0;
static float	_QCM_LastYawErr		= 0.0;
//*****************************************************
// QCM Step Differentiation routine
//*****************************************************
void inline static QCMStepDifferentiator()
	{
	if (QSD.dT > 0.001)		// On the first step after
							// RESET QSD.dT set to 0.0
		{
		float Frequency		= 1.0 / QSD.dT;
		//---------------------------------
		QSD.RollErrDer	= QCMRangeToPi(		QSD.RollError  - _QCM_LastRollErr) 	* Frequency;
		QSD.PitchErrDer	= QCMRangeToHalfPi(	QSD.PitchError - _QCM_LastPitchErr) * Frequency;
		QSD.YawErrDer	= QCMRangeToPi(		QSD.YawError   - _QCM_LastYawErr) 	* Frequency;
		}
	else
		{
		QSD.RollErrDer		= 0.0;
		QSD.PitchErrDer		= 0.0;
		QSD.YawErrDer		= 0.0;
		}
	//-------------------------------------------------
	// Capture current Roll, Pitch, and Yaw errors for
	// subsequent error change differentiation 
	//-------------------------------------------------
	_QCM_LastRollErr	= QSD.RollError;
	_QCM_LastPitchErr	= QSD.PitchError;
	_QCM_LastYawErr		= QSD.YawError;
	//-------------------------------------------------		
	}
	
		
//*****************************************************
// QCM Step Integration routine
//*****************************************************
void inline static QCMStepIntegrator()
	{
	if (QSD.Throttle < _PID_ThrottleNoFly)
		// A no-fly throttle - reset integrators
		{
		//--------------------------
		// Unwind integrators
		//--------------------------
		QSD.RollErrorSum	= 0.0;
		QSD.PitchErrorSum	= 0.0;
		QSD.YawErrorSum		= 0.0;
		//--------------------------
		return;
		}
	//------------------------------------------------------------
	// With Throttle above _PID_ThrottleNoFly we assume that the
	// Quad is off the ground and actively controls its attitude
	//------------------------------------------------------------
	
	//============================================================
	// Integrate Error variables by axis
	//------------------------------------------------------------
	float	Fint		= QSD.dT * _PID_SumWeight;
	//------------------------------------------------------------
	// Update error sums for Roll and Pitch
	//------------------------------------------------------------
	QSD.RollErrorSum	+= QSD.RollError 	* Fint;
	QSD.PitchErrorSum	+= QSD.PitchError 	* Fint;
	QSD.YawErrorSum		+= QSD.YawError 	* Fint;
	//------------------------------------------------------------
	// Limit error sums to prevent integrator "wind-up"
	//------------------------------------------------------------
	if (QSD.RollErrorSum 	> _PID_ErrSum_MAX)
		QSD.RollErrorSum 	= _PID_ErrSum_MAX;
	if (QSD.RollErrorSum 	< _PID_ErrSum_MIN)
		QSD.RollErrorSum 	= _PID_ErrSum_MIN;
	//-------------------------------------
	if (QSD.PitchErrorSum	> _PID_ErrSum_MAX)
		QSD.PitchErrorSum 	= _PID_ErrSum_MAX;
	if (QSD.PitchErrorSum 	< _PID_ErrSum_MIN)
		QSD.PitchErrorSum 	= _PID_ErrSum_MIN;
	//-------------------------------------
	if (QSD.YawErrorSum 	> _PID_ErrSum_MAX)
		QSD.YawErrorSum 	= _PID_ErrSum_MAX;
	if (QSD.YawErrorSum 	< _PID_ErrSum_MIN)
		QSD.YawErrorSum 	= _PID_ErrSum_MIN;
	//-------------------------------------
	}


//=====================================================
#endif

