#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "DBG\DBG.h"

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
	LogInit();	// Initialize Data Logger	
	//*******************************************************************
	char			pFN[15];
	WORD			RC		= CE_GOOD;
	
	BYTE			Block[512];
	WORD			ReadCnt;
	
	SEARCH_STATE	Search;
	FSFILE			File;
	//*******************************************************************
	BLISignalON();
	//------------------------------
	// Initiate file search
	//------------------------------
	RC = FS_FindFirst("log*", ATTR_NONE, ATTR_DIRECTORY, &Search, &File);
	while ( CE_GOOD == RC)
		{
		//-----------------------------------------------------------
		// Retrieve and save log file name (for tracking/debugging)
		//-----------------------------------------------------------
		RC = FS_GetName(pFN, 15, &File);
		while ( RC != CE_GOOD );
		//-----------------------------------------------------------
		if (0 == FS_GetSize(&File))
			{
			// Recover file length based upon allocation
			RC = FS_Recover(&File);
			}
		//-----------------------------------------------------------
		RC = FS_FindNext(&Search, &File);
		}
	//*******************************************************************
	BLISignalOFF();
	//------------------------------
	while(1);
	return 0;
	}




