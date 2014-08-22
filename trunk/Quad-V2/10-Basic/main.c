#include "System.h"
//---------------------------------
#include "Init/Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
//---------------------------------


//---------------------------------
int main(void)
	{

	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
//	_T1IE 	= 0; 		// Temporarily disable Timer1 interrupt
	//*******************************************************************
//	_TRISA10 = 0;
//	_LATA10 = 0;

	long i	= 0;
	for (i = 0; i < 1000; i++);

	ulong	Delay = 10;
	ulong	RTC;
	ulong	Alarm;

	RTC		= TMRGetRTC();
	Alarm	= TMRSetAlarm(Delay);

	i++;

	BLISignalON();
	while (1)
	  {
		TMRDelay(1000);
		BLISignalFlip();
	  }
	


	BLISignalON();
	while (1)
		{
		TMRDelay(30);
//		for (i=0; i < 1000001; i++);
//		_LATA10 ^=1;
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

