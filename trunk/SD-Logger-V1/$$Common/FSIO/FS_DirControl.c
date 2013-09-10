
#include "FSIO\SDFS.h"

//*************************************************************************************
//  Function:		CETYPE 		FS_GetCWD(FSFILE* cwdPtr)
//-------------------------------------------------------------------------------------
//  Summary:		Sets the File Object at cwdPtr to point to the Current Working
//					Directory.
//  Input:			
//					cwdPtr	- pointer to the File Object structure that on SUCCESS
//							  will be set to the Current Working Directory.
//  Return Values:
//					CETYPE enum member (expected CE_GOOD)
//					Other codes depending on encountered error conditions
//*************************************************************************************
CETYPE 		FS_GetCWD(FSFILE* cwdPtr)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == cwdPtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
 	SDFS_CopyFSFILE(cwdPtr, &SDFS_CWD);
 	return 	FS_SeekStart (cwdPtr);
	}
//=====================================================================================




//*************************************************************************************
//  Function:		CETYPE FS_mkDir (char * Name, ATTR_TYPE Attr, FSFILE* newDir)
//-------------------------------------------------------------------------------------
//  Summary:		Creates directory with the specified name in the current working
//					directory.
//  Input:			
//					Name	- Name of the new directory
//					Attr	- Additional attributes of the new directory
//					newDir	- pointer to the File Object structure that on SUCCESS
//							  will be set to the newly created directory.
//  Return Values:
//					CETYPE enum member (expected CE_GOOD)
//					Other codes depending on encountered error conditions
//*************************************************************************************
CETYPE FS_mkDir (char * Name, ATTR_TYPE Attr, FSFILE* newDir)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == Name)
 		return CE_INVALID_FILENAME;		
 	if (NULL == newDir)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
 	char	fmtName[NAME_SIZE_8r3];
 	CETYPE	RC;
 	//----------------------------------------------------------------
 	// Verify/Format provided Directory name (for direct match)
 	//----------------------------------------------------------------
 	if ( !SDFS_Format8dot3Name (Name, fmtName, FALSE) )
 		return CE_INVALID_FILENAME;	// Invalid/missing name
 	//----------------------------------------------------------------
 	// Make sure that the name provided is unique...
 	//----------------------------------------------------------------
 	FS_SeekStart(&SDFS_CWD);		// Rewind Current Working Directory
 	RC = SDFS_DirFindNext(&SDFS_CWD, newDir, ATTR_NONE,  ATTR_NONE, fmtName);
 	//----------------------------------------------------------------
 	if (CE_GOOD == RC)
 		{
	 	if ( FS_IsDirectory(newDir) )
	 		// Directory with the same name is found...
	 		return CE_GOOD;
	 	else
	 		// There exists file with the same name...
	 		{
		 	SDFS_InitFSFILE(newDir, NULL, ATTR_NONE);	// Reset output FSFILE structure
		 	return CE_FILENAME_EXISTS;
	 		}
 		}
 	if (CE_EOF != RC)
 		return RC;		// Some other error happend on the way...
 	//----------------------------------------------------------------
 	// The name provided is unique; Try to create Directory Entry
 	//----------------------------------------------------------------
 	if ( (RC = SDFS_DirFindEmpty(&SDFS_CWD, newDir)) != CE_GOOD)
 		return RC;		// Could not create directory entry...
 	//----------------------------------------------------------------
 	// Success; Set the name and Attributes of the new entry
 	//----------------------------------------------------------------
 	memcpy(newDir->dirFileEntry.DIR_Name, fmtName, NAME_SIZE_8r3);
 	newDir->dirFileEntry.DIR_Attr = ATTR_DIRECTORY | ATTR_ARCHIVE;	
 	//----------------------------------------------------------------
 	// Allocate a cluster for the new Directory and create mandatory
 	// "." and ".." entries
 	//----------------------------------------------------------------
 	if ( (RC = SDFS_ClusterAllocateNew(newDir)) != CE_GOOD)
 		// Failure allocating cluster...
 		{
	 	SDFS_InitFSFILE(newDir, NULL, ATTR_NONE);	// Reset output FSFILE structure
	 	return RC;
 		}
 	//----------------------------------------------------------------
 	DIRENTRY	spcDir;
 	DWORD		dirCluster;
 	// Set template Directory record for "." and ".." entries
 	SDFS_DirResetEntry(	&spcDir, NULL, ATTR_DIRECTORY);
 	//----------------------------------------------------------------
 	// Create and store "." entry
 	//----------------------------------------------------------------
 	spcDir.DIR_Name[0] = '.';
 	dirCluster = SDFS_DirGetFirstCluster(&newDir->dirFileEntry);
 	SDFS_DirSetFirstCluster (&spcDir, dirCluster);
 	FS_Write(newDir, &spcDir, sizeof(DIRENTRY));
 	//----------------------------------------------------------------
 	// Create and store ".." entry
 	//----------------------------------------------------------------
 	spcDir.DIR_Name[1] = '.';
 	dirCluster = SDFS_DirGetFirstCluster(&SDFS_CWD.dirFileEntry);
 	if (dirCluster == SDFS_VolumeInfo.rootClsN)
 		// Parent is the Root directory of the volume
 		dirCluster = 0; // FAT32 rule for pointers to Root
 	SDFS_DirSetFirstCluster (&spcDir, dirCluster);
 	FS_Write(newDir, &spcDir, sizeof(DIRENTRY));
 	//----------------------------------------------------------------
 	return FS_Flush(newDir);
	}
//=====================================================================================



//*************************************************************************************
//  Function:		CETYPE FS_chDir (FSFILE* chDir)
//-------------------------------------------------------------------------------------
//  Summary:		Changes Current Working Directory (CWD) to the directory pointed to
//					by chDir
//  Input:			
//					chDir	- pointer to the File Object structure that on SUCCESS
//							  will become the new CWD.
//  Return Values:
//					CETYPE enum member (expected CE_GOOD)
//					Other codes depending on encountered error conditions
//*************************************************************************************
CETYPE 		FS_chDir (FSFILE* chDir)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == chDir)
 		return CE_INVALID_ARGUMENT;
 	if (!FS_IsDirectory(chDir))	
 		return CE_NOT_A_DIRECTORY;
 	//----------------------------------------------------------------
 	SDFS_CopyFSFILE(&SDFS_CWD, chDir);
 	//----------------------------------------------------------------
	return CE_GOOD;
	}
//=====================================================================================


//*************************************************************************************
//  Function:		CETYPE FS_chDirUp()
//-------------------------------------------------------------------------------------
//  Summary:		Changes Current Working Directory (CWD) to the parent of the
//					Current Working Directory
//  Input:			
//					None
//  Return Values:
//					CETYPE enum member (expected CE_GOOD)
//					Other codes depending on encountered error conditions
//*************************************************************************************
CETYPE 		FS_chDirUp()
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	//----------------------------------------------------------------
 	// Check for CWD being at Root
 	//----------------------------------------------------------------
 	if ( SDFS_DirGetFirstCluster(&SDFS_CWD.dirFileEntry) == SDFS_VolumeInfo.rootClsN )
 		return CE_ROOT_DIRECTORY;		// We are the Root directory
 	//----------------------------------------------------------------
 	
 	CETYPE			RC;
 	FSFILE			UpDir;			// Will become the new CWD
 	FSFILE			UpUpDir;		// Parent of the new CWD - required to find
 									// CWD's name by searching for matching entry
 	
 	WORD	ReadCnt;
 	DWORD	FirstCls;
 	
 	//----------------------------------------------------------------
 	// Initialize Directory file objects
 	//----------------------------------------------------------------
 	SDFS_InitFSFILE(&UpDir,   NULL, ATTR_NONE);
 	SDFS_InitFSFILE(&UpUpDir, NULL, ATTR_NONE);
 	//----------------------------------------------------------------
 	// Rewind CWD and read "." and ".." entries (we need just the "..")
 	//----------------------------------------------------------------
 	FS_SeekStart(&SDFS_CWD);	// Always returns CE_GOOD...
 	// Read "." entry...
 	if (CE_GOOD != (RC = FS_Read(&SDFS_CWD, &UpDir, sizeof(DIRENTRY), &ReadCnt)) )
 		// Failure...
 		return RC;
 	if ('.' != UpDir.dirFileEntry.DIR_Name[0])
 		// Missing "." entry - FORMAT error
 		return CE_INVALID_FORMAT;
 	// Read ".." entry...
 	if (CE_GOOD != (RC = FS_Read(&SDFS_CWD, &UpDir, sizeof(DIRENTRY), &ReadCnt)) )
 		// Failure...
 		return RC;
 	if ( ('.' != UpDir.dirFileEntry.DIR_Name[0]) || ('.' != UpDir.dirFileEntry.DIR_Name[1]))
 		// Missing ".." entry - FORMAT error
 		return CE_INVALID_FORMAT;
 	//----------------------------------------------------------------
 	// Is UpDir - root?
 	//----------------------------------------------------------------
 	FirstCls = SDFS_DirGetFirstCluster(&UpDir.dirFileEntry);
 	if ( 0 ==  FirstCls)
 		// Parent Directory is Root - it is well-defined :)
 		return SDFS_DirSetFOtoRoot(&SDFS_CWD);
 	//----------------------------------------------------------------
 	// UpDir - is not root; make it into a "real" file and read ".." entry
 	//----------------------------------------------------------------
 	UpDir.fileCrntCls = FirstCls;
 	// Read "." entry...
 	if (CE_GOOD != (RC = FS_Read(&UpDir, &UpUpDir, sizeof(DIRENTRY), &ReadCnt)) )
 		// Failure...
 		return RC;
 	if ('.' != UpUpDir.dirFileEntry.DIR_Name[0])
 		// Missing "." entry - FORMAT error
 		return CE_INVALID_FORMAT;
 	// Read ".." entry...
 	if (CE_GOOD != (RC = FS_Read(&UpDir, &UpUpDir, sizeof(DIRENTRY), &ReadCnt)) )
 		// Failure...
 		return RC;
 	if ( ('.' != UpUpDir.dirFileEntry.DIR_Name[0]) || ('.' != UpUpDir.dirFileEntry.DIR_Name[1]))
 		// Missing ".." entry - FORMAT error
 		return CE_INVALID_FORMAT;
 	//----------------------------------------------------------------
 	// Finalize set up of the UpUpDire
 	//----------------------------------------------------------------
 	if ( 0 ==  SDFS_DirGetFirstCluster(&UpUpDir.dirFileEntry))
 		// Parent's Parent Directory is Root - it is well-defined :)
 		SDFS_DirSetFOtoRoot(&UpUpDir);
 	else
 		UpUpDir.fileCrntCls = SDFS_DirGetFirstCluster(&UpUpDir.dirFileEntry);
 	//----------------------------------------------------------------
 	// Now search in the Parent's Parent directory for a directory
 	// entry with the first cluster matching first cluster (FirstCls)
 	// of the parent defined by the ".." entry
 	//----------------------------------------------------------------
 	RC = SDFS_DirFindNext(&UpUpDir, &UpDir, ATTR_DIRECTORY, ATTR_NONE, NULL);
 	while (CE_GOOD == RC)
 		{
	 	if ( SDFS_DirGetFirstCluster(&UpDir.dirFileEntry) == FirstCls)
	 		// Proper entry found!
	 		{
		 	SDFS_CopyFSFILE(&SDFS_CWD, &UpDir);
		 	return CE_GOOD;
	 		}
	 	RC = SDFS_DirFindNext(&UpUpDir, &UpDir, ATTR_DIRECTORY, ATTR_NONE, NULL);
 		}
 	//----------------------------------------------------------------
 	if (CE_EOF == RC)	
 		return CE_INVALID_FORMAT;
 	else
 		return RC; 	
	}
//=====================================================================================


//*************************************************************************************
//  Function:		CETYPE FS_chDirToRoot()
//-------------------------------------------------------------------------------------
//  Summary:		Changes Current Working Directory (CWD) to the root directory of 
//					the volume
//  Input:			
//					None
//  Return Values:
//					CETYPE enum member (expected CE_GOOD)
//					Other codes depending on encountered error conditions
//*************************************************************************************
CETYPE 		FS_chDirToRoot()
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	//----------------------------------------------------------------
	return SDFS_DirSetFOtoRoot(&SDFS_CWD);
	}
//=====================================================================================



/**************************************************************************
  Function:
    int FSrmdir (char * path)
  Summary:
    Deletes the directory as per the ascii input path (PIC24/PIC32/dsPIC).
  Conditions:
    None
  Input:
    path -      The path of the directory to remove
    rmsubdirs - 
              - TRUE -  All sub-dirs and files in the target dir will be removed
              - FALSE - FSrmdir will not remove non-empty directories
  Return Values:
    0 -   The specified directory was deleted successfully
    EOF - The specified directory could not be deleted
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    Deletes the directory as per the ascii input path (PIC24/PIC32/dsPIC).
    This function wont delete the current working directory.
  Remarks:
    None.
  **************************************************************************/

CETYPE 		FS_rmDir (FSFILE* rmDir, BOOL DelTree)
	{
	return CE_GOOD;
	}








