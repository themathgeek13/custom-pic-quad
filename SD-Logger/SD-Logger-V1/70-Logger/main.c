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
	LogInit();			// Initialize Data Logger	
	//*******************************************************************
	UARTInitRX(6, 350);	// Initialize UART for RX on IPL=6 at 
						// BaudRate =   48	=>   115,200 bps
						//--------------------------------------
						// BaudRate =  100	=>   250,000 bps
						// BaudRate =  200	=>   500,000 bps
						// BaudRate =  250	=>   625,000 bps
						// BaudRate =  350	=>   833,333 bps
						// BaudRate =  500	=> 1,250,000 bps
						// BaudRate = 1000	=> 2,500,000 bps
	//*******************************************************************
	// <editor-fold defaultstate="collapsed" desc="Local variables">
	UARTDataBlock*	DataBlock = NULL;
	//-------------------------------------------------------------------
	FSFILE			File;
	WORD			RC;
	// </editor-fold>

	//*******************************************************************
	// Start Async read on UART in BLOCK mode
	//-------------------------------------------------------------------
	if ( !(RC = UARTRXStartAsyncRead(256, TRUE, TRUE)) )
		BLIDeadStop("U", 1);	// dot-dot-dah
	//-------------------------------------------------------------------
	// Create (Open) Log file for Writing and Reading 
	//-------------------------------------------------------------------
NextFile:
	RC = LogNewFile(&File);
	if ( RC != LE_GOOD )
		BLIDeadStop("E", 1);	// dot	
	//-------------------------------------------------------------------
	// Process UART file
	//-------------------------------------------------------------------
	while (TRUE)
		{
		DataBlock = UARTReadBlock();
		//-----------------------------
		if (512 == DataBlock->DataLen)
			{
			BLISignalON();
			RC = FS_WriteSector(&File, DataBlock->Buffer);
			BLISignalOFF();
			//-------------------------
			UARTFreeBlock(DataBlock);		
			//-------------------------
			if (CE_GOOD != RC)
				BLIDeadStop("T", 1);	// dah	
			//-------------------------
			}	
		else
			{
			// Short block is an indicator that the block is last
			//---------------------------------------------------
			if (DataBlock->DataLen > 0)
				{
				BLISignalON();
				RC = FS_Write(&File, DataBlock->Buffer, DataBlock->DataLen);
				BLISignalOFF();
				//-------------------------
				//-------------------------
				if (CE_GOOD != RC)
					BLIDeadStop("T", 1);	// dah	
				//-------------------------
				}
				
			UARTFreeBlock(DataBlock);
					
			if (FS_GetSize(&File) > 0)
				{
				// Non-empty file need to be flushed (closed)
				BLISignalON();
				RC = FS_Flush(&File);
				BLISignalOFF();
				//-------------------------
				if (CE_GOOD != RC)
					BLIDeadStop("T", 1);	// dah	
				//-------------------------
				goto NextFile;
				}	
			}
		}
	//------------------------------
	while(1);
	return 0;
	}








