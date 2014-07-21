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
	byte DLPF	= 3;	// 0 => 1-average	4.21/0.24 msec	| 224 Hz
						// 1 => 2-average	4.17/0.28 msec	| 224 Hz
						// 2 => 4-average
						// 3 => 8-average	8.38/0.53 msec	| 112 Hz

	byte Gain	= 1;	// +/- 1.3 Ga

	HMC_Init(IL, ODR, Gain, DLPF);
	//*******************************************************************
	HMC_RC		RC;
	//----------------------
	ulong		i = 0;
	//-----------------------------------------
	BLISignalOFF();
	//----------------------
	byte		RegA;
	byte		RegB;
	//-------------------------------
	RC = HMC_ReadA(&RegA);
	i++;
	//-------------------------------
	RC = HMC_ReadB(&RegB);
	i++;
	//-------------------------------


	//----------------------
	HMCData		Sample;
	float		Pwr;
	//----------------------
	while (1)
		{
		//-------------------------------
		RC = HMC_ReadSample(&Sample);
		Pwr = VectorSize(&Sample.M);
		BLISignalFlip();
		//-------------------------------
		i++;
		}

//	Gain = 1
//	-243.11922
//	-719.2659
//	 146.78896

	//*******************************************************************
	return 0;
	}

