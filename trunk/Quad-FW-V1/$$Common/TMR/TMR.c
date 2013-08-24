#include "TMR\TMRLocal.h"



//************************************************************
ulong	TMRGetTS(void)
	{
	union
		{
		ulong	TS;
		struct
			{
			uint	lsw;
			uint	msw;
			};
		}	TmrData;
	//---------------------------------------------------
	// Read and return Timer4:5 current value
	//---------------------------------------------------
	TmrData.lsw 	= TMR4; 	// Read lsw from the Type B
								// timer register
	TmrData.msw 	= TMR5HLD; 	// Read msw from the Type C
								// timer holding register
	//---------------------------------------------------
	return	TmrData.TS;
	}
//************************************************************

//************************************************************
ulong	TMRGetRTC(void)
	{
	ulong	Time;
	//---------------------------------------------------
	// Read and return Elapsed Time value (in milliseconds)
	//---------------------------------------------------
	char saved_ipl;                       
	SET_AND_SAVE_CPU_IPL(saved_ipl,_TMRIL);
	Time = _TMR_RT_ElapsedTime;
	RESTORE_CPU_IPL(saved_ipl);
	//---------------------------------------------------
	return	Time;
	}
//************************************************************

//************************************************************
// Blocks for "Delay" milliseconds
//************************************************************
void	TMRDelay(ulong Delay)
	{
	ulong Time	= TMRGetRTC();
	ulong Threshold = Time + Delay; 
	//----------------------------------------------------
	// Implement dealy
	//----------------------------------------------------
	while (Time < Threshold)
	    {Time = TMRGetRTC();}
	//---------------------------------------------------
	return;
	}
//************************************************************


//************************************************************
void	TMRCallBackAfter(	ulong 		OffsetMS, 
							TMRCallBack callBack)
	{
	char saved_ipl;                       
	SET_AND_SAVE_CPU_IPL(saved_ipl,_TMRIL);
	//--------------------------------------------------
	// Reset/Enable CTMU (callback) interrupt
	//--------------------------------------------------
	_RTCIF 	= 0; 		// Clear RTCC interrupt flag
	_RTCIE 	= 1; 		// Enable RTCC interrupt
	//--------------------------------------------------
	// Reset callback request
	//--------------------------------------------------
	_TMR_CallBack				= callBack;
	_TMR_CallBack_TriggerTime 	= _TMR_RT_ElapsedTime + OffsetMS;
	//--------------------------------------------------
	RESTORE_CPU_IPL(saved_ipl);
	//---------------------------------------------------
	return;
	}
//************************************************************


//************************************************************
void	TMRCallBackDiscard()
	{
	char saved_ipl;                       
	SET_AND_SAVE_CPU_IPL(saved_ipl,_TMRIL);
	//--------------------------------------------------
	// Disable/Reset CTMU (callback) interrupt
	//--------------------------------------------------
	_RTCIE 	= 0; 		// Disable RTCC interrupt
	_RTCIF 	= 0; 		// Clear RTCC interrupt flag
	//--------------------------------------------------
	// Reset callback request
	//--------------------------------------------------
	_TMR_CallBack_TriggerTime 	= -1;	// Infinite...
	_TMR_CallBack				=  0;	// Reset callback address
	//--------------------------------------------------
	RESTORE_CPU_IPL(saved_ipl);
	//---------------------------------------------------
	return;
	}
//************************************************************


