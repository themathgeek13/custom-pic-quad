#include <stdlib.h>
#include <string.h>

#include "Log\LogLocal.h"

//===============================================================================
void LogInit()
	{
	//-------------------------------------
	// Check for duplicate invocation
	//-------------------------------------
	if (_LogInit)
		return;
	//-------------------------------------
	BLIInit();		// Initialize Signal interface
					// (NOP if already initialized)
					// NOTE: 	This will also initialize TMR module
					//			if not initialized in Main()
	CETYPE	RC = FS_Init();
	//-------------------------------------
	// Wait for media presence
	//-------------------------------------
   	if ( CE_MEDIA_NOT_PRESENT == RC )
		{
		BLIAsyncMorse("SOS", 3);
		//----------------------------
		while ( CE_MEDIA_NOT_PRESENT == (RC = FS_Init()) );
			{TMRDelay(500);}
		//----------------------------
		BLIAsyncStop();
		//----------------------------
		BLISignalON();
		TMRDelay(3000);
		BLISignalOFF();
		}
	//-------------------------------------
	// Verify SD Card operational status
	//-------------------------------------
   	if ( CE_MEDIA_NOT_INITIALIZED == RC )
		{
		BLIDeadStop("R", 1);	// dot-dah-dot
		}
	//-------------------------------------
	// Verify driver initialization status
	//-------------------------------------
   	if ( CE_GOOD != RC )
		BLIDeadStop("O", 1);	// dah-dah-dah
	//-------------------------------------
	_LogInit	= TRUE;
	return;
	}
//===============================================================================
	
	
//===============================================================================
LERROR	LogNewFile(FSFILE* newLog)
	{
	//================================================================
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!_LogInit)
 		return LE_NOT_INITIALIZED;		// Logger is not initialized!
 	if (NULL == newLog)
 		return LE_INVALID_ARGUMENT;		
	//================================================================
	SEARCH_STATE	Search;
	char			Suffix[6];
	WORD			FileID	= 0;
	//----------------------------
	char			Name[15];
	//================================================================
	if (0 == _LogLastID)
		// First entry into the program - need to find highest log
		// number on the disk...
		{
		WORD	LastFounfID	= 0;
		//------------------------------------------------------------
		_LogFSError = FS_FindFirst(	"log+++++.txt", ATTR_NONE,  ATTR_NONE,  
							 		&Search, newLog);
		//------------------------------------------------------------
		while (CE_GOOD == _LogFSError)
			{
			memset(Suffix, 0x00, 6);
			memcpy(Suffix, &newLog->dirFileEntry.DIR_Name[3], 5);
			FileID	= abs(atoi(Suffix));
			LastFounfID = FileID > LastFounfID ? FileID : LastFounfID;
			//-----------------------------------------------------
			_LogFSError = FS_FindNext(&Search, newLog);
			}	
		if (CE_EOF != _LogFSError)
			return LE_FSERROR;	
		//------------------------------------------------------------
		_LogLastID = LastFounfID;
		}					 		
	//================================================================
	_LogLastID++;
	memset(Name, 0x00, 15);
	memcpy(Name, "LOG00000.TXT", sizeof("LOG00000.TXT"));
	wtoa(&Name[3], _LogLastID);
	//================================================================
	_LogFSError = FS_CreateFile (Name, FS_CREATE_NEW, newLog );
	if (CE_GOOD != _LogFSError)
		return LE_FSERROR;					 		
	//================================================================
	return LE_GOOD;
	}	
//===============================================================================

//===============================================================================
CETYPE	LogLastFSError()
	{return _LogFSError;}
//===============================================================================


