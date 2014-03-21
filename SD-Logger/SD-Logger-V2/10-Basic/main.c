#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "Init\Switches.h"
//---------------------------------
#include "TMR\TMR.h"
#include "BLI\BLI.h"


int main(void)
	{

	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
	ulong	i;
//
//	if (_SW1)
//		BLIAsyncMorse("OSO", 3);
//	else
//		BLIAsyncMorse("SOS", 3);
//
//	while(1);

/*
	BLIAsyncStart(30, 30);
	while(1)
		{TMRDelay(30);}
*/
	BLISignalON();
	while (1)
		{
		TMRDelay(1000);
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

