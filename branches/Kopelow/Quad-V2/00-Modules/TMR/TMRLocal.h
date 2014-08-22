#include "TMR/TMR.h"

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
// Return Elapsed Time value in timer TICKS
//=====================================================
static inline ulong	TMRGetRTCTicks(void)
	{
	ulong	RTCTicks;
	//---------------------------------------------------
	// Read and return Elapsed Time value in timer ticks
	//---------------------------------------------------
	char saved_ipl;
	SET_AND_SAVE_CPU_IPL(saved_ipl,_TMRIL);
	RTCTicks = _TMR_RT_ElapsedTime;
	RESTORE_CPU_IPL(saved_ipl);
	//------------------------------------------------
	return	RTCTicks;
	}
//=====================================================
#endif
