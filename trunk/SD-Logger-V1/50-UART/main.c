#include "System.h"
#include "string.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "DBG\DBG.h"

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
	UARTInitRX(6, 48);	// Initialize UART RX at 115,200 baud
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







