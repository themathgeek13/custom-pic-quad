//**********************************************************************
#include "QCM\QCMLocal.h"

//************************************************************
_QCMStepData	QSD;
//************************************************************
// Minimum engine throttle to keep the motor(s) "stable"
//------------------------------------------------------------
float const 	_PID_ThrottleMin	= 0.0;
//============================================================
// In some extreme situations PID Controller may generate
// adjustments that may be too large for stable controlled
// flight, so we limit "adjustment" for each axis to a certain
// percentage of the current Throttle level
float const 	_PID_ControlLimit	= 0.25;
//------------------------------------------------------------

//============================================================
// Integration (for integral error) control parameters
//------------------------------------------------------------
// Error integrator is reset when Throttle is below the "NoFly"
// value to prevent integrator "wind-up" when model is not
// in flight mode (armed, but still on the ground)
//------------------------------------------------------------
float const		_PID_ThrottleNoFly	= 0.45;	
//------------------------------------------------------------
// Integrator "slow-down" factor to prevent rapid changes on
// large deviations
//------------------------------------------------------------
float const		_PID_SumWeight		= 0.30;	
//------------------------------------------------------------
// Integrator limits to prevent "wind-up"
//------------------------------------------------------------
float const		_PID_ErrSum_MAX		= 0.10;	// Max:  0.1 rad
float const		_PID_ErrSum_MIN		=-0.10;	// Min: -0.1 rad
//============================================================

//============================================================
// PID parameters
//============================================================
float const		_PID_Roll_Kp		= 0.450;	
float const		_PID_Roll_Kd		= 0.075;		
//============================================================
float const		_PID_Pitch_Kp		= 0.450;
float const		_PID_Pitch_Kd		= 0.075;
//============================================================
float const		_PID_Yaw_Kp			= 0.350;
float const		_PID_Yaw_Kd			= 0.150;
//************************************************************



