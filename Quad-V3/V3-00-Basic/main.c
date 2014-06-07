#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"


int main(void)
	{

	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************

//	BLIAsyncStart(30, 30);
//	while(1)
//		{TMRDelay(30);}

	BLISignalON();
//	while (1)
//		{
//		TMRDelay(50);
////		for (i=0; i < 1000001; i++);
////		_LATA10 ^=1;
//		BLISignalFlip();
//		}

//	ulong	i;
////	ulong	j	= 153720;		// 50 msec
//	ulong	j	= 307400;			// 1 msec, 500 Hz
//	while(1)
//		{
//		for (i=0; i < j; i++);
//		BLISignalFlip();
//		}

	BLIAsyncStart(500, 1000);
	while(1);

//	BLIAsyncMorse("SOS", 3);
//	while(1);

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

