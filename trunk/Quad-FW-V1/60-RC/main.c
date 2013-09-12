#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "MCM\MCM.h"
#include "RC\RC.h"
#include "RC\RCSym.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "HMCMAG\HMCMAG.h"
#include "UART\UART.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	BLIAsyncMorse("S", 1);	// dot-dot-dot
	MCMInitPPM(2500);	// Initialize Motor Control for PPM with setting
						// Throttle to HIGH for delay interval to let ESC
						// capture Throttle range
	BLIAsyncStop();
	//--------------------------
	RCInit(4);			// Initialize Receiver interface with Priority=4
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
						// BaudRate =  1	=>   2400 bps
						// BaudRate =  2	=>   4800 bps
						// ...
						// BaudRate = 48	=> 115200 bps
						// BaudRate = 99	=> 250000 bps - special case
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



