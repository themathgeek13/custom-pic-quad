#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "I2C\I2C.h"
#include "HMCMAG\HMCMAG.h"
#include "HMCMAG\HMCMAG_Local.h"
#include "UART\UART_TX.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	I2CInit(5, 0);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	TMRDelay(1000);		// Wait for 1 sec so that the shake from turning on
						// power switch dissipates...
	//--------------------------
	#ifdef __MAG_Use__
	if (HMCInit(6, 1, 0))	// Initialize magnetic Sensor
							// ODR  = 6 (max, 75 Hz),
							// Gain = 2 (1.3 Gs)
							// DLPF = 0 (no averaging)
		BLIDeadStop("M", 1);
	#endif
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
	// This initialization routine accepts BaudRate in multiples
	// of 2400 bps; Thus:
	// BaudRate =   1	=>   2400 bps
	// BaudRate =   2	=>   4800 bps
	// ...
	// BaudRate =  48	=> 115200 bps
	//------------------------------------------------------------
	// High speed
	//------------------------------------------------------------
	// BaudRate =  100	=>   250,000 bps
	// BaudRate =  200	=>   500,000 bps
	// BaudRate =  250	=>   625,000 bps
	// BaudRate =  350	=>   833,333 bps
	// BaudRate =  500	=> 1,250,000 bps
	// BaudRate = 1000	=> 2,500,000 bps
	//*******************************************************************
	//--------------------------
	#ifdef __MAG_Use__
	uint			RC			= 0;
	HMCSample		MSample;
	//--------------------------
	if (HMCAsyncStart())
		BLIDeadStop("E", 1);
	#endif
	//*******************************************************************
	#ifdef __MAG_Use__
	BLISignalON();
	while(1)
		{
		TMRDelay(100);
		//------------------------	
		RC 	= HMCAsyncReadWhenReady(&MSample);
		if (RC) 
			BLIDeadStop("M", 1);
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&MSample, sizeof(MSample));
		//---------------------------------------------	
		BLISignalFlip();
		}
	#endif
	return 1;
	}

