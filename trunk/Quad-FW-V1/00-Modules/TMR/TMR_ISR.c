#include "TMR\TMRLocal.h"

//*************************************************************
void __attribute__((__interrupt__, __no_auto_psv__)) _T1Interrupt(void)
	{
	// Happens every 125 microsecond...
	_T1IF = 0; 					// Clear Timer1 interrupt flag
	_TMR_RT_ElapsedTime++;		// Increment real time counter
	//--------------------------------------------------------
	// Trigger RTCC interrupt if the trigger time was reached
	//--------------------------------------------------------
	if (_TMR_RT_ElapsedTime > _TMR_CallBack_TriggerTime)
		{
		// Reset trigger time to "Infinity"
		_TMR_CallBack_TriggerTime = -1;
		// Activate callback (if present)
		if (_TMR_CallBack)
			_RTCIF 		= 1 ; 	// Raise RTCC interrupt flag
		}
	//--------------------------------------------------------
	return;
	}
//*************************************************************

//*************************************************************
// Callback "thread"

//*************************************************************
// Running at the lowest interrupt priority of 1
//-------------------------------------------------------------
void __attribute__((__interrupt__, __no_auto_psv__)) _RTCCInterrupt (void)
	{
	_RTCIF 		= 0 ; 		// Clear RTC interrupt flag
	//-----------------------------------------------
	// Store callback pointer value locally to avoid
	// "race condition" with the following test
	TMRCallBack	 _callback	=	_TMR_CallBack;	
	if (_callback)
		{
		// Invoke callback function
		(*_callback)();
		}
	//--------------------------------------------------------
	return;
	}
//*************************************************************


/*
// Alternative callback option - using Hard trap
//-------------------------------------------------------------
void __attribute__((interrupt,no_auto_psv)) _HardTrapError(void) 
	{
	//-----------------------------------------------
	// Reset interrupt request
	//-----------------------------------------------
	_SWTRAP	= 0;	// Reset SW-generated Hard Trap Request
	_SGHT	= 0;	// Reset SW-generated Hard Trap Status
	//-----------------------------------------------
	// Reset priority of call-back function to the
	// lowest interrupt priority - 1
	_IPL3 = 0;
	_IPL  = 1;
	//-----------------------------------------------
	// Store callback pointer value locally to avoid
	// "race condition" with the following test
	TMRCallBack	 _callback	=	_TMR_CallBack;	
	if (_callback)
		// Invoke callback function
		(*_callback)();
	return;
	}
*/





