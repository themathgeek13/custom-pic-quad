#include "System.h"

//=====================================================
#ifndef __TRM_H
#define __TRM_H
//=====================================================

//****************************************************
// The following group of functions initializes and
// control Timers ("interval" and "real time") and 
// provides utility functions facilitating operation
// with Timer(s).
// Timers are configured under the assumption that the
// MCU is running at Fcy = 64 MHz.
//----------------------------------------------------
// Timer 1 is configured to generate interrupt every
// 125 usec; the interrupt will increment "tick
// time counter", which can be converted into milli-
// second counter that is accessible through
// TMRGetRealTime() function.
// "Tick counter" wraps around in about 6 days.
//----------------------------------------------------
// Timers B and C (specific timers are defined in the
// "TMRProfile.h") will be combined into a one
// free-running (no interrupts) 32-bit interval timer,
// which provides high-resolution ( 1 usec) time
// stamps accessible through TMRGetTS() function.
// Time stamps can be used to calculate time intervals
// up to about ~70 min.
//****************************************************


void			TMRInitDefault();	
void			TMRInit(uint IL);

//----------------------------------------------------
// In this application we measure time to the precision
// of 1 usec, thus to convert "ticks" into seconds we
// use the following rate: 0.000001
//----------------------------------------------------
#define	TMRGetTSRate() 0.000001
//----------------------------------------------------
// Get current time stamp with 1 usec resolution
//----------------------------------------------------
ulong	TMRGetTS();
//----------------------------------------------------
//  Return Elapsed Time value in milliseconds
//----------------------------------------------------
ulong	TMRGetRTC(void);


//************************************************************
// Blocks execution for "Delay" milliseconds
//************************************************************
void	TMRDelay(ulong Delay);
//************************************************************
// Blocks for "Delay" ticks (1 tick = 125 usec)
//************************************************************
void	TMRDelayTicks(ulong Delay);
//************************************************************
// Sets "alarm" time "AlarmDelay" milliseconds in the future
//************************************************************
ulong	TMRSetAlarm(ulong AlarmDelay);
//************************************************************
// Sets "alarm" time "AlarmTicks" ticks in the future
//************************************************************
ulong	TMRSetAlarmTicks(ulong AlarmTicks);
//************************************************************
// Checks "alarm" time and return TRUE if alarm still active
//************************************************************
BOOL	TMRCheckAlarm(ulong AlarmTime);
//************************************************************
// Blocks execution until the previously set "alarm" time expires
//************************************************************
void	TMRWaitAlarm(ulong AlarmTime);


//----------------------------------------------------
// The following 2 routines allow to request a callback
// some time in the future or to discard an outstanding
// callback request.
//----------------------------------------------------
// Callback function is executed asynchronously at the
// lowest interrupt routine priority of 1.
//----------------------------------------------------
// Only one request may be active at any time; any 
// subsequent request overrides any existing request.
//----------------------------------------------------
// Callback function prototype.
typedef	void (*TMRCallBack)(void);
//----------------------------------------------------
// Execute callback "OffsetMS" milliseconds from now:
void	TMRCallBackAfter(ulong OffsetMS, TMRCallBack callBack);
// Discard existing callback request:
void	TMRCallBackDiscard();

//=====================================================
#endif
