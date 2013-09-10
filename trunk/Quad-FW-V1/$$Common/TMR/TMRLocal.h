#include "TMR\TMR.h"

//=====================================================
#ifndef __TRMLocal_H
#define __TRMLocal_H
//=====================================================
extern uint		_TMRInit;	// Timer initializtion flag
extern byte		_TMRIL;		// Real time timer default 
									// interrupt level
extern ulong	volatile	_TMR_RT_ElapsedTime;

extern ulong	volatile	_TMR_CallBack_TriggerTime;

extern TMRCallBack
				volatile	_TMR_CallBack;

//=====================================================
#endif
