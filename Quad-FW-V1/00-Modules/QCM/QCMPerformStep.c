//**********************************************************************
#include "QCM\QCMLocal.h"
//**********************************************************************

//**********************************************************************
void	QCMPerformStep(RCData* RC, DCMData* IMU, MCMData* MC)
	{

	//============================================================
	// Identify Integration/Differentiation time interval for the
	// current step; initialize LastRC values on start.
	//------------------------------------------------------------
	//{
	ulong	CurrentTS	= IMU->TS;	// Capture timestamp of last
									// IMU update
	//------------------------------------------------------------
	if (0 == QSD.LastTS)
		{
		// The first step in the current flight
		QSD.dT = 0.0;
		// Capture current Roll, Pitch, and Yaw for subsequent
		// differentiation to identify state change derivatives
		QSD.LastRoll	= IMU->Roll;
		QSD.LastPitch	= IMU->Pitch;
		QSD.LastYaw		= IMU->Yaw;
		}
	else
		{
		// Not the first step, we have saved values from last step
		QSD.dT = ((float)(CurrentTS - QSD.LastTS)) * TMRGetTSRate();
		}
	// Store current timestamp for next iteration
	QSD.LastTS = CurrentTS;
	//}
	//============================================================
			

	//************************************************************
	// Process Throttle
	//************************************************************
	//{
	QSD.Throttle = RC->Throttle;
	//------------------------------------------------------------
	// Calculate throttle "adjustment" based upon Inclination
	//------------------------------------------------------------
	// Adjust Throttle to compensate for the loss of lift due
	// to Inclination.
	//------------------------------------------------------------
	if (IMU->Incl > 0.0)
		{
		float	K = IMU->Incl;
		if (K < 0.8)	K = 0.8;	// Limit correction to 25%
		QSD.Throttle /= K;
		}
	//------------------------------------------------------------
	// Limit Throttle input to leave space for attitude control.
	//------------------------------------------------------------
	if (QSD.Throttle > 0.85)
		QSD.Throttle = 0.85;
	//}
	//************************************************************



	//************************************************************
	// Calculate Roll-Pitch-Yaw "adjustments" based upon IMU and
	// RC control input
	//************************************************************
	//{
	// First, calculate direct control error(s) AND bring them
	// into the proper range...
	// Makes sense to do it while the model is still on the ground
	// so if it is not level it will not swing to the side on
	// the lift-off.
	//------------------------------------------------------------
	QSD.RollError	= QCMRangeToPi(		RC->Roll  - IMU->Roll);
	QSD.PitchError	= QCMRangeToHalfPi(	RC->Pitch - IMU->Pitch);
	QSD.YawError	= QCMRangeToPi(		RC->Yaw   - IMU->Yaw);

	//------------------------------------------------------------
	// Calculate Proportional term
	//---------------------------------------------
	QSD.DeltaRollProp 	= _PID_Roll_Kp   * QSD.RollError;
	QSD.DeltaPitchProp 	= _PID_Pitch_Kp  * QSD.PitchError;
	QSD.DeltaYawProp 	= _PID_Yaw_Kp  	 * QSD.YawError;
	//}
	//************************************************************
		
	//************************************************************
	// Calculate Roll-Pitch-Yaw "adjustment" based upon State
	// Change derivatives
	//************************************************************
	//{
	//------------------------------------------------------------
	// Calculate state derivative - to improve stability we use PID
	// method based upon the Derivative of the Process Variable (PV)
	//------------------------------------------------------------
	if (QSD.dT > 0.001) // Just to be sure...
		{
		float Frequency		= 1.0 / QSD.dT;
		//---------------------------------
		QSD.RollDer		= QCMRangeToPi(		IMU->Roll  - QSD.LastRoll) 	* Frequency;
		QSD.PitchDer	= QCMRangeToHalfPi(	IMU->Pitch - QSD.LastPitch) * Frequency;
		QSD.YawDer		= QCMRangeToPi(		IMU->Yaw   - QSD.LastYaw) 	* Frequency;
		}
	else
		{
		QSD.RollDer		= 0.0;
		QSD.PitchDer	= 0.0;
		QSD.YawDer		= 0.0;
		}
	// Capture current Roll, Pitch, and Yaw for subsequent
	// differentiation to identify state change derivatives
	QSD.LastRoll	= IMU->Roll;
	QSD.LastPitch	= IMU->Pitch;
	QSD.LastYaw		= IMU->Yaw;
	//------------------------------------------------------------
	// Caculate Differential term; PID-weighted derivative terms
	// are negated so that differential term "works" against
	// process change derivative 
	//------------------------------------------------------------
	QSD.DeltaRollDiff	= -_PID_Roll_Kd  * QSD.RollDer;
	QSD.DeltaPitchDiff	= -_PID_Pitch_Kd * QSD.PitchDer;
	QSD.DeltaYawDiff	= -_PID_Yaw_Kd   * QSD.YawDer;
	//}
	//************************************************************

	//************************************************************
	// Calculate Roll-Pitch-Yaw "adjustment" based upon State
	// Change derivatives
	//************************************************************
	//{
	//------------------------------------------------------------
	// Calculate Integral term
	//------------------------------------------------------------
	QCMStepIntegrator();	// First, update Integrator variables
	//------------------------------------------------------------
	// Now calculate adjustment as an additional contribution to
	// the proportional term 
	QSD.DeltaRollInt 	= _PID_Roll_Kp   * QSD.RollErrorSum;
	QSD.DeltaPitchInt 	= _PID_Pitch_Kp  * QSD.PitchErrorSum;
	QSD.DeltaYawInt 	= _PID_Yaw_Kp	 * QSD.YawErrorSum;
	//}
	//************************************************************

	//************************************************************
	// Calculate total 3-D adjustment
	//************************************************************
	QSD.DeltaRoll	= QSD.DeltaRollProp			// Proportional
					+ QSD.DeltaRollDiff			// Differential
					+ QSD.DeltaRollInt;			// Integral
	//-------------------
	QSD.DeltaPitch	= QSD.DeltaPitchProp		// Proportional
					+ QSD.DeltaPitchDiff		// Differential
					+ QSD.DeltaPitchInt;		// Integral

	//-------------------
	QSD.DeltaYaw	= QSD.DeltaYawProp			// Proportional
					+ QSD.DeltaYawDiff			// Differential
					+ QSD.DeltaYawInt;			// Integral
	//************************************************************

	//************************************************************
	// Implement CONTROL limits
	//************************************************************
	// Identify vurrent control limit based upon the Throttle
	// value and pre-set control limit
	float CM	= RC->Throttle * _PID_ControlLimit;	 // QSD.Throttle 

	// Roll ----------------------------------------
	if (QSD.DeltaRoll >  CM)	QSD.DeltaRoll 	=  CM;
	if (QSD.DeltaRoll < -CM)	QSD.DeltaRoll 	= -CM;
	// Pitch ---------------------------------------
	if (QSD.DeltaPitch >  CM)	QSD.DeltaPitch 	=  CM;
	if (QSD.DeltaPitch < -CM)	QSD.DeltaPitch 	= -CM;
	// Yaw ---------------------------------------
	if (QSD.DeltaYaw >    CM)	QSD.DeltaYaw 	=  CM;
	if (QSD.DeltaYaw <   -CM)	QSD.DeltaYaw 	= -CM;
	
	//************************************************************
	// Implement Motor Balance adjustment for Roll-Pitch
	//************************************************************
	// NOTE: this adjustment is not subject to control limit
	QSD.Voltage = ADCGetBatteryVoltage();
	//------------------------------------------------------------
	float Power = QSD.Throttle * QSD.Voltage;
	// Using calculated constants....
	// These constants are dependent on motors, props, and
	// C.G. placement - should be adjusted if anything changes...
	QSD.DeltaRoll 	+= 0.0030 * Power;
//	QSD.DeltaPitch	+= 0.0000 * Power;
//	QSD.DeltaYaw	-= 0.0050 * Power;
	
	
	//************************************************************
	// Implement motor power adjustments
	//************************************************************
	//{
	//************************************************************
	// Throttle adjustment for the transverse direction
	// REMEBER: Roll angle is positive when we bank right
	//------------------------------------------------------------
	MC->R	= QSD.Throttle - QSD.DeltaRoll;	
	MC->L	= QSD.Throttle + QSD.DeltaRoll;
	//------------------------------------------------------------
	// Throttle adjustment in the longitudinal direction
	// REMEMBER: Pitch angle is positive when the nose points UP
	//------------------------------------------------------------
	MC->B	= QSD.Throttle - QSD.DeltaPitch;
	MC->F	= QSD.Throttle + QSD.DeltaPitch;
	//------------------------------------------------------------
	// Throttle adjustment for Yaw compensation
	// REMEMBER: Yaw is positive for clockwise rotation
	// F-B props rotate quad counterclockwise, while
	// L-R - rotate quad clockwise
	MC->B -= QSD.DeltaYaw;
	MC->F -= QSD.DeltaYaw;
	//--------------
	MC->R += QSD.DeltaYaw;
	MC->L += QSD.DeltaYaw;
	//--------------
	//}
	//************************************************************

	//***********************************************************
	// Normalize all calculated Throttle values 
	//-----------------------------------------------------------
	QCMNormalize(MC);
	//***********************************************************
	}
//************************************************************





