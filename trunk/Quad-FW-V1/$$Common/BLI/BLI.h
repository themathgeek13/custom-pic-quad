#include "System.h"

//=====================================================
#ifndef __BLI_H
#define __BLI_H
//=====================================================

//****************************************************
// The following group of functions initializes and
// control SIGNAL operations for LED or BUZZER.
//----------------------------------------------------
// NOTE: It is assumed that RA1 is used as Signal 
//		 Interface - that is the LED or Buzzer is
//		 connected to RA1.
//----------------------------------------------------
// Timing options are configured under the assumption
// that the MCU is running at Fcy = 50 MHz.
//----------------------------------------------------
// NOTE: BLI component uses Timer1 (part of "TMR" set
//		 of routines); It is preferable to initialize
//		 TMR component before calling BLIInit().
//****************************************************
// Buzzer and LED Interface ALWAYS runs at the lowest
// interrupt priority of 1.
void			BLIInit();
//----------------------------------------------------
// Synchronous control 
// NOTE: Synchronous actions are IGNORED if asynchronous
// 		 operation is in progress
//----------------------------------------------------
void	BLISignalON(void);
void	BLISignalOFF(void);
void	BLISignalFlip(void);
//----------------------------------------------------
void	BLIAsyncStart(	uint OnTime, uint OffTime);
void	BLIAsyncMorse(	char * pStr, uint Length);
void	BLIAsyncStop(void);
//----------------------------------------------------
void 	BLIDeadStop(char * pStr, uint Length);
//=====================================================
#endif
