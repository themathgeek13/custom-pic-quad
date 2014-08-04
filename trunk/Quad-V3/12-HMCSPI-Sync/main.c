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
	//-------------------------------------------------------------------
	BLIAsyncStart(100, 100);
	TMRDelay(5000);			// To avoid false-start at Reset
	BLIAsyncStop();
	BLISignalOFF();
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
	// HMC5983 Magnetometer initialization
	//-------------------------------------------------------------------
	byte IL		= 5;	// Interrupt level
	//------------------------------------------------------
	// <editor-fold defaultstate="collapsed" desc="Output Data Rate (ODR">
	//------------------------------------------------------
	// Typical Data Output Rate (Hz) for various ODR values
	//------------------------------------------------------
	//		ODR =	0:		  0.75
	//		ODR =	2:		  1.5
	//		ODR =	2:		  3
	//		ODR =	3:		  7.5
	//		ODR =	4:		 15		(Default)
	//		ODR =	5:		 30
	//		ODR =	6:		 75
	//		ODR =	7:		220		(fastest)
	// </editor-fold>
 	byte ODR	= 7;	// Rate (fastest):	220 Hz
	// <editor-fold defaultstate="collapsed" desc="Low-pass filtering (DLPF)">
	//------------------------------------------------------
	// Low-pass filtering achieved through sample averaging.
	// Averaging does not affect effective ODR, so I assume
	// that wit averaging enabled each successive reported
	// sample is an average of the new measurement with "n"
	// previous measurements - something like a FIR filter.
	//------------------------------------------------------
	// DLPF = 0 => 1-average	
	// DLPF = 1 => 2-average
	// DLPF = 2 => 4-average
	// DLPF = 3 => 8-average
	//------------------------------------------------------
	// </editor-fold>
 	byte DLPF	= 0;
	// <editor-fold defaultstate="collapsed" desc="Sensor Field Range (Gain)">
	//------------------------------------------------------
	// Recommended sensor field range (Ga) for various Gains
	//------------------------------------------------------
	//		Gain =	0:		0.9
	//		Gain =	1:		1.3
	//		Gain =	2:		1.9
	//		Gain =	3:		2.5
	//		Gain =	4:		4.0
	//		Gain =	5:		4.7
	//		Gain =	6:		5.6
	//		Gain =	7:		8.1
	//------------------------------------------------------
	// The magnitude of Earth magnetic field varies over the
	// surface of the Earth in the range 0.3 to 0.6 Gauss.
	//------------------------------------------------------
	// </editor-fold>
 	byte Gain	= 1;	// +/- 1.3 Ga
	//------------------------------------------------------
	HMC_Init(IL, ODR, Gain, DLPF);
	//*******************************************************************
	HMC_RC		RC;
	//----------------------
	ulong		i = 0;
	//-----------------------------------------
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
	struct
		{
		HMCData		Sample;
		ulong		Count;
		} SDLData;
		SDLData.Count	= 0;
    //----------------------
	while (1)
		{
		//-------------------------------
		if ( HMC_OK != (RC = HMC_ReadSample(&SDLData.Sample)) )
			BLIDeadStop("SOS", 3);
		SDLData.Count++;
		//-------------------------------
		BLISignalFlip();
		//-------------------------------
		SDLPostIfReady((byte*)&SDLData, sizeof(SDLData));
		//-------------------------------
		}

	//*******************************************************************
	return 0;
	}

