#include "System.h"

#ifndef __MCM_H
#define __MCM_H
//===========================================================
// MC (Motor Control) data structure
//-----------------------------------------------------------
// MC (Motor Control) module provides PWM or PPM control sig-
// nals depending on the initialization parameters.
//-----------------------------------------------------------
// MC values for each channel are provided as fractional num-
// bers in the range of 0.0 (0% duty cycle for PWM or 5% duty
// cycle at 50 Hz for PPM) to 1.0 (100% duty cycle for PWM 
// mode or 10% duty cycle at 50 Hz for PPM mode). Control 
// numbers outside this range are brought into the range so
// that values less than 0.0 are treated as 0.0 and
// values exceeding 1.0 are treated as 1.0.
//-----------------------------------------------------------
typedef struct 
	{
	//----------------------------
	float	F;		// OC1 - front
	float	B;		// OC2 - back
	//----------------------------
	float	L;		// OC3 - left
	float	R;		// OC4 - right
	//----------------------------
	} MCMData;

//**********************************************************************
// The Output Compare module uses default Timer2.
//-----------------------------------------------------
// MCMInitLocal(...) function besides initializing OC1-OC4 also
// initializes Timer2 module for the requested refresh frequency/period.
// Please Do Not Change Timer2 settings to avoid breaking
// MC operation.
//-----------------------------------------------------
// Control Board uses the following pins:
//		RB7/RP7  -> OC1 (Front)
//		RB8/RP8  -> OC2 (Back)
//		RB9/RP9  -> OC3 (Left)
//		RC6/RP22 -> OC4 (Right)
//-----------------------------------------------------
// NOTE: uses TMR (timer) module for calculating time
//		 interval; Please issue TMRInit(...) prior to
//		 this call - otherwise Timer will be initialized
//		 with default IL.
//**********************************************************************
// MCMInitF(...) and MCMInitT(...) initialize Motor Control Module
// for PPM mode. For both functions second parameter, UpTime, defines
// the time (in msec.) during which the ouput will be maintained at
// 100% on each of the channels, after which it will be dropped to 0%
// to allow ESC to capture Throttle range on each of the channels.
//**********************************************************************

//======================================================================
// Parameter "Freq" (50 <= Freq <= 400) defines PPM refresh frequency in
// Hertz; acceptable values correspond to periods from 20 to 2.5 msec.
//-----------------------------------------------------
void	MCMInitF(uint Freq, uint UpTime);

//======================================================================
// Parameter "Period" (2.5 <= Period <= 20) defines PPM refresh period
// in msec.; acceptable vallues correspond to frequencies in the range
// from 50 to 400 Hz.
//-----------------------------------------------------
void	MCMInitT(float Period, uint UpTime);


//======================================================================
void	MCMSet(MCMData*	MCData);
//======================================================================
#endif





