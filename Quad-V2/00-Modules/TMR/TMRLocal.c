#include "TMR\TMRLocal.h"

//************************************************************
uint		_TMRInit = 0;	// Timer initializtion flag
byte		_TMRIL	 = 2;	// Timer default interrupt level

ulong	volatile	_TMR_RT_ElapsedTime			= 0;

ulong	volatile	_TMR_CallBack_TriggerTime	=-1;	// Infinite...
TMRCallBack
		volatile	_TMR_CallBack				= 0;	// CallBack function pointer

//*************************************************************





