#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "MCM\MCM.h"
#include "RC\RC.h"
#include "RC\RCSym.h"
#include "UART\UART.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	MCMInitF(50, 0);	// Initialize Motor Control at 50 Hz
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
	MCMData		MC;
	RCData		RC;
	//-------------------------------------------------
	BLIAsyncMorse(	"SOS", 3);
	RCSymArm();	
	BLIAsyncStop();
	//-------------------------------------------------
	BLISignalON();
	while(1)
		{
		RCSymReadWhenReady(&RC);
		//---------------------------------------------	
		MC.F	= RC.Throttle;
		MC.B	= RC.Yaw;
		//--------------
		MC.L	= RC.Roll;
		MC.R	= RC.Pitch;
		//--------------
		MCMSet(&MC);
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&RC, sizeof(RC));
		//---------------------------------------------	
		BLISignalFlip();
		}
	return 1;
	}



