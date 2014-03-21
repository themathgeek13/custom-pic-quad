#include "System.h"
#include "string.h"
//---------------------------------
#include "Init\Init.h"
#include "Init\Switches.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"

#include "UART\UART_RX.h"
#include "FSIO\FS.h"
#include "LOG\LOG.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
	//_T1IE 	= 0; 	// Temporarily disable Timer1 interrupt
	//*******************************************************************
	LogInit();			// Initialize Data Logger	
	//*******************************************************************
	// Initialize UART for RX on IPL=6 at
	//-------------------------------------------------------------------
	// BaudRate =   48	=>   115,200 bps
	//--------------------------------------
	// BaudRate =  100	=>   250,000 bps
	// BaudRate =  200	=>   500,000 bps
	// BaudRate =  250	=>   625,000 bps
	// BaudRate =  350	=>   833,333 bps
	// BaudRate =  500	=> 1,250,000 bps
	// BaudRate = 1000	=> 2,500,000 bps
	//-------------------------------------------------------------------
	// Switch 1 controls UART speed - if the switch is in the "On"
	// position, UART initialized for high speed (833,333 bps), otherwise
	// UART is initialized at low speed (115,200 bps) compatible with
	// XBee.
	//-------------------------------------------------------------------
	if (_SW1)
		UARTInitRX(6, 350);		// High speed:	833,333 bps
	else
		UARTInitRX(6, 48);		// Low speed:	115,200 bps
	//*******************************************************************
	UARTDataBlock*	DataBlock = NULL;
	UARTRXStat		Stats;
	WORD			RC = 0;
	int				i;
	//-----------------------------------
	// Start Async read on UART in BLOCK mode
	while ( !(RC = UARTRXStartAsyncRead(64, TRUE, TRUE)) ); 		
	for (i = 0; i < 10; i++)
		{
		DataBlock = UARTReadBlock();
		
		BLISignalON();
		TMRDelay(50);
		UARTFreeBlock(DataBlock);		
		BLISignalOFF();
		}
	UARTRXStopAsyncRead();

	UARTRXGetStat(&Stats);
	
	//------------------------------
	i = sizeof(byte*);
	//------------------------------
	while(1);
	
	return 0;
	}







