#include "MCM/MCM.h"
#include "TMR/TMR.h"

//=====================================================
#ifndef __MCMLocal_H
#define __MCMLocal_H
//=====================================================
// Indicator of MC initialization
extern uint		_MC_Init;
//-----------------------------------------------------
// Timer tick count - defines MC frequency
extern uint		_MC_Tmr_Count;
// Timer tick count corresponding to "0" Control Signal
extern uint		_MC_Base_Value;
// Timer tick count corresponding to "1" Control Signal
// (for efficiency reason is defined as "float")
extern float	_MC_OCMax;
//=====================================================
void	MCMInitLocal(float Period, uint UpTime);
//=====================================================
#endif





