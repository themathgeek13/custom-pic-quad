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

void	RecoverFiles();
void	LogData();

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
	LogInit();			// Initialize Data Logger	
	//*******************************************************************
	// Switch 2 controls what operation the module is expected to
	// perform.
	//-------------------------------------------------------------------
	if (_SW2)
		RecoverFiles();		// Recovery mode - attempt to "recover" files
							// that were not closed correctly so the FAT
							// entry was not updated with actual file
							// length (which is done at CLOSE)
	else
		LogData();			// Normal data logger operation
	//*******************************************************************
	while(1);
	return 0;
	}

// <editor-fold defaultstate="collapsed" desc="void	LogData()">
//-----------------------------------------------------------------------
void	LogData()
	{
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
	BLISignalON();
	RC = LogNewFile(&File);
	BLISignalOFF();
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
			RC = FS_WriteSector(&File, DataBlock->Buffer);
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
				RC = FS_Write(&File, DataBlock->Buffer, DataBlock->DataLen);
				//-------------------------
				if (CE_GOOD != RC)
					BLIDeadStop("T", 1);	// dah
				//-------------------------
				}

			UARTFreeBlock(DataBlock);

			if (FS_GetSize(&File) > 0)
				{
				// Non-empty file need to be flushed (closed)
				RC = FS_Flush(&File);
				//-------------------------
				if (CE_GOOD != RC)
					BLIDeadStop("T", 1);	// dah
				//-------------------------
				goto NextFile;
				}
			}
		}
	}
//-----------------------------------------------------------------------
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void RecoverFiles()">
//-----------------------------------------------------------------------
void	RecoverFiles()
	{
	//*******************************************************************
	char			pFN[15];
	WORD			RC		= CE_GOOD;

	SEARCH_STATE	Search;
	FSFILE			File;
	//*******************************************************************
	BLISignalON ();
	//------------------------------
	// Initiate file search
	//------------------------------
	RC = FS_FindFirst ("log*", ATTR_NONE, ATTR_DIRECTORY, &Search, &File);
	while ( CE_GOOD == RC)
	  {
		//-----------------------------------------------------------
		// Retrieve and save log file name (for tracking/debugging)
		//-----------------------------------------------------------
		RC = FS_GetName (pFN, 15, &File);
		while ( RC != CE_GOOD );
		//-----------------------------------------------------------
		if (0 == FS_GetSize (&File))
		  {
			// Recover file length based upon allocation
			RC = FS_Recover (&File);
		  }
		//-----------------------------------------------------------
		RC = FS_FindNext (&Search, &File);
	  }
	//*******************************************************************
	BLISignalOFF ();
	//*******************************************************************
	BLIAsyncStart(1000, 500);
	//*******************************************************************
	return;
	}
//-----------------------------------------------------------------------
// </editor-fold>






