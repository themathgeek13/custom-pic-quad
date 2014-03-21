#include "System.h"
#include "string.h"
//---------------------------------
#include "Init\Init.h"
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
	LogInit();			// Initialize Data Logger	
	UARTInitRX(6, 48);	// Initialize UART RX at 115,200 baud
	//*******************************************************************
	//{
	//-------------------------------------------------------------------
	UARTDataBlock*	DataBlock = NULL;
	UARTRXStat		Stats;
	//-------------------------------------------------------------------
	char			pFN[15];
	FSFILE			File;
	byte			Data[512];
	
	WORD			RC;
	uint			i;
	
	uint			ReadCnt;
	uint			RecordCnt	= 0;
	//}
	
	//*******************************************************************
	// Create (Open) Log file for Writing and Reading 
	//-------------------------------------------------------------------
	RC = LogNewFile(&File);
	while ( RC != LE_GOOD );
	//-------------------------------------------------------------------
	// Retrieve and save for future new log file name 
	//-------------------------------------------------------------------
	RC = FS_GetName(pFN, 15, &File);
	while ( RC != LE_GOOD );
	//-------------------------------------------------------------------
	// Start Async read on UART in BLOCK mode
	//-------------------------------------------------------------------
	while ( !(RC = UARTRXStartAsyncRead(64, TRUE, TRUE)) ); 		
	//-------------------------------------------------------------------
	// Write 10 blocks of data
	//-------------------------------------------------------------------
	for (i = 0; i < 10; i++)
		{
		DataBlock = UARTReadBlock();
		
		BLISignalON();
		RC = FS_WriteSector(&File, DataBlock->Buffer);
		while (CE_GOOD != RC);		
		BLISignalOFF();
		
		UARTFreeBlock(DataBlock);		
		}
	//-------------------------------------------------------------------
	UARTRXStopAsyncRead();
	//---------------------
	UARTRXGetStat(&Stats);
	//-------------------------------------------------------------------
	// Close the file - save changes
	//-------------------------------------------------------------------
	RC = FS_Flush(&File);
   	while ( RC != CE_GOOD );
	//-------------------------------------------------------------------

	//------------------------------
	RecordCnt	= 0;
	//------------------------------

	
	//-------------------------------------------------------------------
	// Open file for Reading 
	//-------------------------------------------------------------------
	RC = FS_CreateFile(pFN, FS_READ_ONLY, &File);
	while ( RC != CE_GOOD );
	//-------------------------------------------------------------------
	// Read records
	//-------------------------------------------------------------------
	while (TRUE)
		{
		BLISignalON();
	   	RC = FS_Read (&File, &Data, sizeof(Data), &ReadCnt);
		BLISignalOFF();
		//--------------------------
	   	if (CE_EOF == RC) break;
		//--------------------------
		while (CE_GOOD != RC);
		//--------------------------
		RecordCnt++;
		}
	//-------------------------------------------------------------------
	// Close the file - save changes
	//-------------------------------------------------------------------
	RC = FS_Flush(&File);
   	while ( RC != CE_GOOD );
	//*******************************************************************
	i = 1 + i;
	//------------------------------
	while(1);
	return 0;
	}








