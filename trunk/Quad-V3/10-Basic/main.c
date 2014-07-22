#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "Init\Switches.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"


int main(void)
	{

	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************

	BLISignalON();

//	ulong	i;
//	ulong	j	= 307400;			// 1 msec, 500 Hz
//	while(1)
//		{
//		for (i=0; i < j; i++);
//		BLISignalFlip();
//		}

//	while (1)
//		{
//		TMRDelay(100);
//		BLISignalFlip();
//		}

	byte Mult	= ((_SW1* 2 + _SW2)*2 + _SW3)* 2 + _SW4 + 1;
	uint Freq	= 50 * Mult;

	while(1)
		{
		BLIAsyncStart(Freq, 2 * Freq);
		TMRDelay(5000);		// Delay 5 sec
		//--------------------------------
		BLIAsyncMorse("SOS", 3);
		TMRDelay(5000);		// Delay 5 sec
		}
	//*******************************************************************

	return 1;
	}

