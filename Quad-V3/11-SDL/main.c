#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "Init\Switches.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
//---------------------------------
#include "SDL\SDL.h"


int main(void)
	{

	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
	// Switch 1 controls the Serial Data Logger (SDL) communication speed
	//-------------------------------------------------------------------
	if (_SW1)
		// Switch 1 is ON - Configuring SDL for PIC-to-PIC
		// high-speed communication at 1 MBaud
		SDLInit(3, BAUD_1M);
	else
		// Switch 1 is OFF - Configuring SDL for ZigBEE
		// wireless communication at 115.2 KBaud
		SDLInit(3, BAUD_115200);
	//*******************************************************************
	struct
		{
		ulong	Alarm;
		ulong	TS;
		}	Data;

	BLISignalON();
	while(TRUE)
		{
		Data.Alarm = TMRSetAlarm(100);
		//-----------------------
		Data.TS = TMRGetTS();
		SDLPostIfReady((byte*)&Data, sizeof(Data));
		//-----------------------
		TMRWaitAlarm(Data.Alarm);
		BLISignalFlip();
		}

	//*******************************************************************
	return 0;
	}

