#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "DBG\DBG.h"

#include "FSIO\FS.h"
#include "Logger\Logger.h"

#include "FSIO\SDFS.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
	//_T1IE 	= 0; 	// Temporarily disable Timer1 interrupt
	//*******************************************************************
	LoggerInit();	// Initialize Data Logger	
	//*******************************************************************
	uint	i;
	char		RData[30];
	char		CData[30];

	for (i = 0; i < 30; i++)
		{
		RData[i] = CData[i] = 0;
		}

	char*		pFN		= "log1.txt";
	void*		pWData	= &"01 02 03 04 05 06 07 08 09";
	//-------------------------------------------------------------------
	
	CETYPE			RC;
	uint			ReadCnt;
	
	FSFILE			File;
	SEARCH_STATE	Search;
	//*******************************************************************
	BLISignalON();
	//*******************************************************************
	
	// Search for every entry in the Root
	RC = FS_FindFirst(	"*", ATTR_NONE,  ATTR_NONE, &Search, &File);	
	while (CE_GOOD == RC)
		{
		RC = FS_FindNext(&Search, &File);
		}

	// Search only for files
	RC = FS_FindFirst(	"*", ATTR_NONE,  ATTR_DIRECTORY, &Search, &File);	
	while (CE_GOOD == RC)
		{
		RC = FS_FindNext(&Search, &File);
		}

	// Search only for directories
Deeper:
	RC = FS_FindFirst(	"*", ATTR_DIRECTORY,  ATTR_NONE, &Search, &File);	
	if (CE_GOOD == RC)
		{
		RC = FS_chDir(&File);
		if (CE_GOOD == RC)
			goto Deeper;
		}
		
Higher:
	RC = FS_GetCWD(&File);
	RC = CE_GOOD;
	RC = FS_chDirUp();
	if (CE_GOOD == RC)
		goto Higher;
		
	//*******************************************************************


	//------------------------------
	// Create (Open) file for Writing and Reading 
	//------------------------------
	RC = FS_CreateFile(pFN, FS_CREATE_NEW, &File);
	while ( RC != CE_GOOD );
	//------------------------------
	// Write sample string to file
	//------------------------------
   	RC = FS_Write (&File, pWData, 26 );
	while (CE_GOOD != RC);
	//------------------------------
	// Check position in the file
	//------------------------------
   	i = FS_GetPosition (&File);
	while (i != 26);
	//------------------------------
	// Seek to start
	//------------------------------
   	FS_SeekStart(&File);
	//------------------------------
	// Reed from start
	//------------------------------
   	RC = FS_Read (&File, RData, 26, &ReadCnt);
	while (CE_GOOD != RC);
	//------------------------------
	// Close the file - save changes
	//------------------------------
	RC = FS_Flush(&File);
   	while ( RC != CE_GOOD );
	//------------------------------

	//------------------------------
	// Open file for Reading 
	//------------------------------
	RC = FS_CreateFile(pFN, FS_READ_ONLY, &File);
	while ( RC != CE_GOOD );
	//------------------------------
	// Reed from start
	//------------------------------
   	RC = FS_Read (&File, CData, 26, &ReadCnt);
	while (CE_GOOD != RC);
	//------------------------------
	// Close the file - save changes
	//------------------------------
	RC = FS_Flush(&File);
   	while ( RC != CE_GOOD );
	//------------------------------
	i = 1 + i;

	//*******************************************************************
	BLISignalOFF();
	//------------------------------
	while(1);
	return 0;
	}

