#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "Init\Switches.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "SDL\SDL.h"
//---------------------------------
#include "HMCSPI\HMCSPI.h"

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

	byte IL		= 5;	// Interrupt level
	byte ODR	= 7;	// Fastest rate: 220 Hz
	byte Gain	= 1;	// +/- 1.3 Ga
						// The magnitude of Earth magnetic field varies
						// over the surface of the Earth in the range
						// 0.3 to 0.6 Gauss.
	byte DLPF	= 0;	// 0 => 1-average	4.21/0.24 msec	| 224 Hz
						// 1 => 2-average	4.17/0.28 msec	| 224 Hz
						// 2 => 4-average
						// 3 => 8-average	8.38/0.53 msec	| 112 Hz
	HMC_Init(IL, ODR, Gain, DLPF);
	//*******************************************************************
	HMCData		MSample;
	HMC_RC		RC;
	ulong		Alarm;
	//----------------------
	RC = HMC_AsyncStart();
	//----------------------
	BLISignalOFF();
	while (1)
		{
		Alarm = TMRSetAlarm(100);
		//-------------------------------
		RC = HMC_AsyncReadWhenReady(&MSample);
		if (HMC_OK != RC)
			BLIDeadStop("SOS", 3);
		//-------------------------------
		SDLPostIfReady(	(byte*) &MSample, sizeof(MSample));
		//-------------------------------
		BLISignalFlip();
		//-------------------------------
		TMRWaitAlarm(Alarm);
		}

	HMC_AsyncStop();

	//*******************************************************************
	return 0;
	}

