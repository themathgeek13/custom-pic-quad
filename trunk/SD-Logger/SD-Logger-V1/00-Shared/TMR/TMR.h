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
// MCU is running at Fcy = 40 MHz.
//----------------------------------------------------
// Timer 1 is configured to generate interrupt every
// millisecond; the interrupt will increment "real 
// time counter", which is accessible through
// TMRGetRealTime() function.
//----------------------------------------------------
// Timers 4 and 5 will be combined into a one
// free-running (no interrupts) 32-bit interval timer,
// which provides high-resolution ( 0.16 usec) time
// stamps accessible through TMRGetTS() function.
// Time stamps can be used to calculate time intervals
// up to about ~11.5 min.
//****************************************************


void			TMRInitDefault();	
void			TMRInit(uint IL);

//----------------------------------------------------
// In this application we measure time to the precision
// of 0.2 usec, thus to convert "ticks" into seconds we
// use the following rate: 0.0000002
//----------------------------------------------------
#define	TMRGetTSRate() 0.0000002
//----------------------------------------------------
// Get current time stamp with 0.2 usec resolution
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
// Blocks for "Delay" ticks
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
// Blocks execution until the previously set "alarm" time expires
//************************************************************
void	TMRWaitAlarm(ulong AlarmTime);


//----------------------------------------------------
// The following 2 routines allow to request raising
// of CTMU ("software") interrupt some time in the fu-
// re or discarding an outstanding request.
// Only one request may be active at any time; any 
// subsequent request overrides any existing request.
//----------------------------------------------------

typedef	void (*TMRCallBack)(void);

// Execute callback "OffsetMS" milliseconds from now:
void	TMRCallBackAfter(ulong OffsetMS, TMRCallBack callBack);
// Discard existing callback request:
void	TMRCallBackDiscard();

//=====================================================
#endif
