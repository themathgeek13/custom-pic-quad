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
	// Read and return Timer B:C current value
	//---------------------------------------------------
	TmrData.lsw 	= TB_Cnt; 	// Read lsw from the Type B
								// timer register
	TmrData.msw 	= TC_Hold;	// Read msw from the Type C
								// timer holding register
	//---------------------------------------------------
	return	TmrData.TS;
	}
//************************************************************


//************************************************************
// Return Elapsed Time value (in milliseconds)
//************************************************************
ulong	TMRGetRTC(void)
	{
	//======================================================
	// Important NOTE: Timer counter updated every 125 usec!
	//------------------------------------------------------
	// Convert to milliseconds and Return Elapsed Time
	//------------------------------------------------------
	return	((TMRGetRTCTicks() + 4) >> 3); // Round and convert to msec
	}
//************************************************************

//************************************************************
// Blocks for "Delay" milliseconds
//************************************************************
void	TMRDelay(ulong Delay)
	{
	//----------------------------------------------------
	// Implements "delay" by combining setting Alarm and
	// waiting for the Alarm in one function
	//----------------------------------------------------
	TMRWaitAlarm(TMRSetAlarm(Delay));
	//---------------------------------------------------
	return;
	}
//************************************************************

//************************************************************
// Blocks for "Delay" ticks
//************************************************************
void	TMRDelayTicks(ulong Delay)
	{
	//----------------------------------------------------
	// Implements "delay" by combining setting Alarm and
	// waiting for the Alarm in one function
	//----------------------------------------------------
	TMRWaitAlarm(TMRSetAlarmTicks(Delay + 1));
	//---------------------------------------------------
	return;
	}
//************************************************************

//************************************************************
// Sets "alarm" time "AlarmDelay" milliseconds in the future
//************************************************************
ulong	TMRSetAlarm(ulong AlarmDelay)
	{
	//======================================================
	// Read Elapsed Time value (in timer units - 125 usec)
	// and combine with AlarmDelay converted to ticks
	//------------------------------------------------------
	// Return alarm timestamp
	return	(TMRGetRTCTicks() + (AlarmDelay << 3) + 1);
	}
//************************************************************

//************************************************************
// Sets "alarm" time "AlarmTicks" ticks in the future
//************************************************************
ulong	TMRSetAlarmTicks(ulong AlarmTicks)
	{
	//======================================================
	// Read Elapsed Time value (in timer ticks - 125 usec)
	// and combine with AlarmTicks converted to ticks
	//------------------------------------------------------
	// Return alarm timestamp
	return	(TMRGetRTCTicks() + AlarmTicks);
	}
//************************************************************

//************************************************************
// Checks "alarm" time and return TRUE if Alarm time achieved
//************************************************************
BOOL	TMRCheckAlarm(ulong AlarmTime)
	{
	if (AlarmTime > TMRGetRTCTicks())
		return FALSE;
	else
		return TRUE;
	}
//************************************************************

//************************************************************
// Waits until the previously set "alarm" time expires
//************************************************************
void	TMRWaitAlarm(ulong AlarmTime)
	{
	//======================================================
	// Read and Check Time value (in timer units - 125 usec)
	//------------------------------------------------------
	while (AlarmTime > TMRGetRTCTicks());
	return;		// Current time is past Alarm time
	}
//************************************************************


//************************************************************
// Registers callback in "OffsetMS" milliseconds
//************************************************************
void	TMRCallBackAfter(	ulong 		OffsetMS, 
							TMRCallBack callBack)
	{
	//======================================================
	char saved_ipl;                       
	SET_AND_SAVE_CPU_IPL(saved_ipl,_TMRIL);
	//--------------------------------------------------
	// Reset/Enable CTMU (callback) interrupt
	//--------------------------------------------------
	_CRCIF 	= 0; 		// Clear CRC interrupt flag
	_CRCIE 	= 1; 		// Enable CRC interrupt
	//--------------------------------------------------
	// Set callback request
	//--------------------------------------------------
	_TMR_CallBack				= callBack;
	//======================================================
	// Important NOTE: Timer counter updated every 125 usec!
	//------------------------------------------------------
	// Time offset need to be converted to timer units
	//------------------------------------------------------
	_TMR_CallBack_TriggerTime 	= _TMR_RT_ElapsedTime 
								+ (OffsetMS << 3);
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
	_CRCIE 	= 0; 		// Disable CRC interrupt
	_CRCIF 	= 0; 		// Clear CRC interrupt flag
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


