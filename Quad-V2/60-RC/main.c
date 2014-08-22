#include "System.h"
//---------------------------------
#include "Init/Init.h"
#include "TMR/TMR.h"
#include "BLI/BLI.h"
#include "MCM/MCM.h"
#include "RC/RC.h"
#include "UART/UART_TX.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	BLIAsyncMorse("S", 1);	// dot-dot-dot
	MCMInitF(50, 2500);	// Initialize Motor Control at 50 Hz with setting
						// Throttle to HIGH for delay interval to let ESC
						// capture Throttle range
	BLIAsyncStop();
	//--------------------------
	RCInit(4);			// Initialize Receiver interface with Priority=4
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
	BLISignalON();
	TMRDelay(2000); 	// Wait for extra 2 sec - to let ESC arm...
						// (finish the song :) )
	BLISignalOFF();
	//==================================================================
	MCMData		MC;
	RCData		RC;
	//-------------------------------------------------
	BLIAsyncMorse("R", 1);	// dot-doh-dot
	RCArm();
	BLIAsyncStop();
	//-------------------------------------------------
	BLISignalON();
	while(1)
		{
		RCReadWhenReady(&RC);
		//---------------------------------------------	
		if (0 == RC.Control)
			MC.F = MC.B	= MC.L = MC.R	= 0.0;
		else
			{	
			MC.F	= RC.Throttle;
			MC.B	= RC.Throttle;
			//--------------
			MC.L	= RC.Throttle;
			MC.R	= RC.Throttle;
			//--------------
			}
		//---------------------------------------------	
		MCMSet(&MC);
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&RC, sizeof(RC));
		//---------------------------------------------	
		BLISignalFlip();
		}
	return 1;
	}



