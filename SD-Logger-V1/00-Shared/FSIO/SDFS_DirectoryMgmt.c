#include "FSIO\SDFS.h"


//************************************************************************************
//  Function:		CETYPE	SDFS_DirSetFOtoRoot(FSFILE* filePtr)
//------------------------------------------------------------------------------------
//  Summary:		Sets FileObject to point to Root Directory
//  Input:			pDirEntry	- Pointer to the data structure to be initialized
//					FileName	- Pointer to the file name
//					FileAttr	- Attributes to be set for this entry
//  Return Values:
//    				CETYPE - 	Error code (expected: CE_GOOD)
//  Description:
//    				The SDFS_DirSetFOtoRoot(...) function initializes sets provided
//					File Object to point to the Root Directory of the Volume.
//************************************************************************************
CETYPE				SDFS_DirSetFOtoRoot(FSFILE* filePtr)
	{
	//===========================================================================
 	// Validate parameters
 	//---------------------------------------------------------------------------
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;
	//===========================================================================
 	// Initialize File Object representing current working directory
 	//----------------------------------------------------------------
 	SDFS_InitFSFILE(filePtr, NULL, ATTR_DIRECTORY);

 	//===========================================================================
	// Point File Object representing current global working directory
	// to the Volume root directory
 	//===========================================================================
 	// Configure Directory Entry of this File Object
    //---------------------------------------------------------------------------
	// Set the Name of the current (root) directory to "\   "
	// NOTE: It is already blanked out by SDFS_InitFSFILE(...)
	filePtr->dirFileEntry.DIR_Name[0] 	= '\\';
    //---------------------------------------------------------------------------
	// First Cluster of the Directory pointed to by this File Object
	// NOTE: Root Directory Entry points to itself - "SDFS_VolumeInfo.rootClsN"
	//		 indicates the start of the Root Directory
    //---------------------------------------------------------------------------
    SDFS_DirSetFirstCluster (&filePtr->dirFileEntry, SDFS_VolumeInfo.rootClsN);
	//===========================================================================
    // Disk location of the Directory entry for this File Object
	// NOTE: Root directory does not have Directory Entry and Parent Directory!
    //---------------------------------------------------------------------------
	filePtr->dirFrstCls 	= CLUSTER_FAIL_FAT32;	
	filePtr->dirLBA		 	= CLUSTER_FAIL_FAT32;	// Invalid LBA as well...	
	filePtr->dirOffset	 	= 0;		
    //---------------------------------------------------------------------------
	// Current cluster of the File Object set to be the same as the first cluster
    //---------------------------------------------------------------------------
    filePtr->fileCrntCls 	= SDFS_VolumeInfo.rootClsN;		
	//===========================================================================
	return CE_GOOD;
	}
//=====================================================================================


//************************************************************************************
//  Function:		CETYPE	SDFS_DirResetEntry(	DIRENTRY* 	pDirEntry,
//												const char* FileName, 
//												ATTR_TYPE 	FileAttr)
//------------------------------------------------------------------------------------
//  Summary:		Performs basic initialization of the Directory Entry structure
//  Input:			pDirEntry	- Pointer to the data structure to be initialized
//					FileName	- Pointer to the file name
//					FileAttr	- Attributes to be set for this entry
//  Return Values:
//    				CETYPE - 	Error code (expected: CE_GOOD)
//  Description:
//    				The SDFS_DirResetEntry(...) function initializes DIRENTRY data 
//					structure. If FileName is not NULL, it will be formatted as
//					required for the Directory Entry and stored as the file name
//					in the DIRECTORY section of the structure. Otherwise file name
//					section will be filled with blanks.
//************************************************************************************
CETYPE	SDFS_DirResetEntry(	DIRENTRY* 	pDirEntry,
						 	const char* FileName, 
							ATTR_TYPE 	FileAttr)
	{
 	//================================================================
 	// Validate parameters
 	//----------------------------------------------------------------
 	if (NULL == pDirEntry)
 		return CE_INVALID_ARGUMENT;
 	//================================================================
 	// Configure Directory Entry
 	//----------------------------------------------------------------
 	// Process FileName
 	//----------------------------------------------------------------
 	if (NULL == FileName)
 		// Blank-out file name
 		memset(pDirEntry->DIR_Name, 0x20, NAME_SIZE_8r3);
 	else
 		{
    	if (!SDFS_Format8dot3Name(FileName, pDirEntry->DIR_Name, FALSE))
    		return CE_INVALID_FILENAME;
   		} 	
 	//----------------------------------------------------------------
    pDirEntry->DIR_Attr 		= FileAttr;
    pDirEntry->DIR_FstClusHI	= 0;
    pDirEntry->DIR_FstClusLO 	= 0;
    //--------------------------------------------------
    pDirEntry->DIR_WrtTime 		= 0x0000;   // last update time - Midnight
    pDirEntry->DIR_WrtDate 		= 0x4221;	// last update date - Jan 1 2013	
	pDirEntry->DIR_FileSize		= 0;		// Ignored for directories...
  	//----------------------------------------------------------------
 	// Optional Directory properties - set to "0"
 	//----------------------------------------------------------------
    pDirEntry->DIR_NTRes			= 0;	// Reserved byte
    pDirEntry->DIR_CrtTimeTenth_Opt	= 0;	// Create time (millisecond field)
    pDirEntry->DIR_CrtTime_Opt		= 0;	// Create time (second, minute, hour field)
    pDirEntry->DIR_CrtDate_Opt		= 0;	// Create date
    pDirEntry->DIR_LstAccDate_Opt	= 0;	// Last access date	- Optional!!!
 	//================================================================
	return CE_GOOD;
	}
//=====================================================================================


//************************************************************************************
//  Function:		CETYPE SDFS_DirGetNext(FSFILE* filePtr, DIRENTRY* pDirEntry)
//------------------------------------------------------------------------------------
//  Summary:		Reads next directory entry from a Directory file
//  Input:
//					filePtr		- Pointer to the File Object representing Directory
//					pDirEntry	- Pointer to the DIRENTRY data structure
//  Return Values:
//    				CETYPE - 	Error code (expected: CE_GOOD)
//  Description:
//    				The SDFS_DirGetNext(...) function verifies that the File Object
//					provided represents Directory and reads next directory entry
//					skipping LFN entries.
//************************************************************************************
CETYPE				SDFS_DirGetNext(FSFILE* filePtr, DIRENTRY* pDirEntry)
	{
	//-----------------------------------------------------------------
	// Validate input parameters
	//-----------------------------------------------------------------
    // Check if pointer is valid	
    if (filePtr == NULL)
        return CE_INVALID_ARGUMENT;
    // Check if length is valid	
    if (pDirEntry == NULL)
        return CE_INVALID_ARGUMENT;
    // Check file to represent a Directory
    if ( (filePtr->dirFileEntry.DIR_Attr & ATTR_DIRECTORY) != ATTR_DIRECTORY)
		return CE_NOT_A_DIRECTORY;
	//-----------------------------------------------------------------
	CETYPE	RC;
	WORD	ReadCnt;
	//-----------------------------------------------------------------
Retry:
	if ( CE_GOOD != (RC = FS_Read(filePtr, pDirEntry, sizeof(DIRENTRY), &ReadCnt)) )
		return RC;
    if ( (pDirEntry->DIR_Attr & ATTR_VOLUME)	== ATTR_VOLUME)
		goto Retry;		// Skip Volume label
    if ( (pDirEntry->DIR_Attr & ATTR_LFN) 		== ATTR_LFN)
		goto Retry;		// Skip LFN entry
	//-----------------------------------------------------------------
 	return CE_GOOD;
	}
//=====================================================================================


//************************************************************************************
//  Function:		CETYPE SDFS_DirFindEmpty(FSFILE* dirPtr, FSFILE* fileEmpty)
//------------------------------------------------------------------------------------
//  Summary:		Finds empty directory entry in a Directory file and positions
//					this directory file to the just read entry
//  Input:
//					dirPtr		- Pointer to the File Object representing Directory
//					fileEmpty	- Pointer to the File Object that will be set for the 
//								  found empty directory slot
//  Return Values:
//    				CETYPE - 	Error code (expected: CE_GOOD)
//  Description:
//    				The SDFS_DirGetEmpty(...) function verifies that the File Object
//					provided represents Directory and Finds empty directory entry in 
//					this Directory file. If operation succeeds, the File Object pointed
//					to by the fileEmpty will be initialized as a File Object associated
//					with this empty entry.
//					NOTE: if the file is read to the end and no empty entry was found,
//						  a new cluster will be allocated to this directory and empty
//						  entry provided from this cluster.
//************************************************************************************
CETYPE				SDFS_DirFindEmpty(FSFILE* dirPtr, FSFILE* fileEmpty)
	{
	//-----------------------------------------------------------------
	// Validate input parameters
	//-----------------------------------------------------------------
    // Check if pointer is valid	
    if (dirPtr == NULL)
        return CE_INVALID_ARGUMENT;
	//-----------------------------------------------------------------
	CETYPE		RC = CE_GOOD;
	BYTE		ControlChar;

	//-----------------------------------------------------------------
	FS_SeekStart(dirPtr);
	//-----------------------------------------------------------------
	while (TRUE)
		{
		RC = SDFS_DirGetNext(dirPtr, &fileEmpty->dirFileEntry);
		//------------------------------------------
		if (CE_EOF == RC)
			{
			// Extend Directory file
			if ( CE_GOOD != (RC = SDFS_ClusterAllocateNew(dirPtr)) )
				return RC;
			continue;	// Try reading next entry
			}
		//------------------------------------------
		if (CE_GOOD != RC)
			// Any other error but the CE_EOF
			return RC;
		//------------------------------------------
		ControlChar = fileEmpty->dirFileEntry.DIR_Name[0];
		//------------------------------------------
		if 	(DIR_DEL 	== ControlChar)
			// Deleted directory entry found!
			break;
		//------------------------------------------
		if 	(DIR_EMPTY 	== ControlChar)
			// Empty directory entry found!
			break;
		//------------------------------------------
		}
	//=================================================================
	// Finalize configuration of the just found File Object
	//-----------------------------------------------------------------
	// Initialize data structure
	SDFS_InitFSFILE(fileEmpty, NULL, ATTR_NONE);
	// Configure File Object properties reflecting directory entry itself
	fileEmpty->dirFrstCls 	= SDFS_DirGetFirstCluster(&dirPtr->dirFileEntry);
	fileEmpty->dirLBA	 	= SDFS_FATClusterToLBA( dirPtr->fileCrntCls)
	    			  	 	+ dirPtr->fileCrntSec;	// add the sector number to it
	// Each sector contains the whole number of Directory Entries, so
	// "stepping back" from the current fileCrntSecPos is safe!
	fileEmpty->dirOffset	 	= dirPtr->fileCrntSecPos - sizeof(DIRENTRY);
	//-----------------------------------------------------------------
	// For safety reason mark this Directory Entry as DELETED for now
	//-----------------------------------------------------------------
	fileEmpty->dirFileEntry.DIR_Name[0] = DIR_DEL;
	//=================================================================
 	return CE_GOOD;
	}
//=====================================================================================


//************************************************************************************
//  Function:		CETYPE SDFS_DirFindNext(FSFILE* dirPtr, FSFILE* foundPtr,
//											ATTR_TYPE FindAttr,  ATTR_TYPE SkipAttr,  
//											char Name[NAME_SIZE_8r3],BOOL WildCard )
//------------------------------------------------------------------------------------
//  Summary:		Searches Directory for the entry matching search criteria
//  Input:
//					dirPtr		- Pointer to the File Object representing Directory
//					foundPtr	- Pointer to the new File Object matching search
//					FindAttr	- Combination of Attribute flags that must be set
//					SkipAttr	- Combination of Attribute flags that must NOT be set
//					Name		- name or name pattern to look for; if Name = NULL,
//								  any name would be considered a "match"
//			NOTE:	ATTR_NONE value for each of the attribute parameters makes search
//					ignore respective condition.
//  Return Values:
//    				CETYPE - 	Error code (expected: CE_GOOD)
//  Description:
//    				The SDFS_DirFindNext(...) function searches directory represented
//					by dirPtr from its current position forward for an entry matching
//					ALL specified search conditions. If matching entry is found, File
//					Object pointed to by foundPtr is set to represent an open file
//					associated with the found directory entry.
//************************************************************************************
CETYPE SDFS_DirFindNext(FSFILE* dirPtr, FSFILE* foundPtr,
						ATTR_TYPE FindAttr,  ATTR_TYPE SkipAttr,  
						char Name[NAME_SIZE_8r3] )
	{
	//-----------------------------------------------------------------
	// Validate input parameters
	//-----------------------------------------------------------------
    if (foundPtr == NULL)
        return CE_INVALID_ARGUMENT;
    // NOTE: dirPtr is validated inside SDFS_DirGetNext(...)
	//-----------------------------------------------------------------
	CETYPE		RC;
	BYTE		ControlChar;
	//-----------------------------------------------------------------
	while (CE_GOOD == (RC = SDFS_DirGetNext(dirPtr, &foundPtr->dirFileEntry)) )
		{
		ControlChar = foundPtr->dirFileEntry.DIR_Name[0];
		//---------------------------------------------------------
		if 	(DIR_EMPTY 	== ControlChar)
			return CE_EOF;	// End of directory has been reached
		//---------------------------------------------------------
		if 	(DIR_DEL 	== ControlChar)
			continue;	// Skip deleted directory entry
		//---------------------------------------------------------
		if 	('.' 	== ControlChar)
			continue;	// Skip "." and ".." special directory entries
		//---------------------------------------------------------
		if ( (FindAttr & foundPtr->dirFileEntry.DIR_Attr) != FindAttr)
			continue;	// Required attributes not set
		//---------------------------------------------------
		if ( (SkipAttr & foundPtr->dirFileEntry.DIR_Attr) != ATTR_NONE)
			continue;	// At least one of the skip attributes is set
		//---------------------------------------------------
		if (NULL == Name)
			// Ignore name comparizon
			goto Found;
		//---------------------------------------------------
		if ( SDFS_Compare8dot3Name(Name, foundPtr->dirFileEntry.DIR_Name) )
			goto Found;	// All conditions are met - entry found!!!
		}
 	return RC;	// Return last encountered return code - error or EOF
	//-----------------------------------------------------------------
Found:
	//=================================================================
	// Finalize configuration of the just found File Object
	//-----------------------------------------------------------------
	foundPtr->dirFrstCls 	= SDFS_DirGetFirstCluster(&dirPtr->dirFileEntry);
	foundPtr->dirLBA	 	= SDFS_FATClusterToLBA( dirPtr->fileCrntCls)
	    			  	 	+ dirPtr->fileCrntSec;	// add the sector number to it
	// Each sector contains the whole number of Directory Entries, so
	// "stepping back" from the current fileCrntSecPos is safe!
	foundPtr->dirOffset	 	= dirPtr->fileCrntSecPos - sizeof(DIRENTRY);
	//-----------------------------------------------------------------
	foundPtr->fileCrntCls	= SDFS_DirGetFirstCluster(&foundPtr->dirFileEntry);
	foundPtr->fileSeek			= 0;
	foundPtr->fileCrntSec		= 0;
	foundPtr->fileCrntSecPos	= 0;
	//=================================================================
	return CE_GOOD;
	}									
//=====================================================================================













