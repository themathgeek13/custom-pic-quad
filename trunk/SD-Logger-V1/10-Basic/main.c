#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "DBG\DBG.h"


int main(void)
	{

	//*******************************************************************
	DBGInit();		// Initialize Debug interface

	DBG_1_ON();
	Init();
	DBG_1_Flip();

	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
//	_T1IE 	= 0; 		// Temporarily disable Timer1 interrupt
	//*******************************************************************
	ulong	i;

	DBG_1_ON();
	BLIAsyncMorse("SSS", 3);
	while(1)
		{
		TMRDelay(50);		// Delay 50 msec
		DBG_1_Flip();
		DBG_2_Flip();
		}


/*
	BLIAsyncStart(30, 30);
	while(1)
		{TMRDelay(30);}
*/
	BLISignalON();
	while (1)
		{
//		TMRDelay(50);
		for (i=0; i < 1000001; i++);
		BLISignalFlip();
		}

	while(1);
		{
		for (i=0; i < 1000001; i++);
		BLISignalFlip();
		}


	while(1)
		{
		BLIAsyncStart(500, 1000);
		TMRDelay(5000);		// Delay 5 sec
		//--------------------------------
		BLIAsyncMorse("SOS", 3);
		TMRDelay(5000);		// Delay 5 sec
		}
	//*******************************************************************

	return 1;
	}

