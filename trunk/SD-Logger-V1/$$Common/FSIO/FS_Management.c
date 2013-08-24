#include "FSIO\SDFS.h"


//*************************************************************************************
//  Function:		CETYPE FS_CreateFile (	const char * 	FileName, 
//											FILE_MODE 		mode,
//											FSFILE* 		filePtr )
//  Summary:		Creates/Opens a file with ascii name provided in FileName
//  Input:
//					FileName 	- The name of the file to open
//  		  		mode 		- File open mode (FILE_MODE enum)
//        			- FS_CREATE_NEW		- Create a new file or replace an existing file.
//        			- FS_OPEN_EXISTING	- Open existing file for read/write access or 
//										  creates a new file; file is positioned at the
//										  beginning.
//         			- FS_APPEND			- Open existing file for read/write access or 
//										  creates a new file; file is positioned just
//										  past the last byte.
//        			- FS_READ_ONLY		- Open existing file in read-only mode; file
//										  positioned at the beginning.
//					filePtr		- pointer to FSFILE data structure that will be confi-
//								  gured ro provide access to the file if function
//								  succeeds.
//  Return Values:
//    				CETYPE - Expected CE_GOOD, but may have other codes depending on
//							 various error conditions.
//  Description:
//    				This function will create and/or open specified file.
//    				The specified file name will be formatted to ensure that it's in 8.3
//					format. Next, the search for the specified file name will be
//					performed. If the name is found, the action will be taken based
//					upon the requested File Mode.  
//*************************************************************************************
CETYPE FS_CreateFile (	const char* FileName, FILE_MODE mode, FSFILE* filePtr )
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == FileName)
 		return CE_INVALID_ARGUMENT;		
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
	//-----------------------------------------------------------------
	
	CETYPE 	RC			= CE_GOOD;
	char	fmtName[NAME_SIZE_8r3];
	
	//-----------------------------------------------------------------
	// Validate new name and convert it to 8.3 FAT format
	//-----------------------------------------------------------------
	if ( !SDFS_Format8dot3Name(FileName, fmtName, FALSE) )
		return CE_INVALID_FILENAME;

 	//================================================================
 	// Make sure that the name provided is unique...
 	//----------------------------------------------------------------
 	FS_SeekStart(&SDFS_CWD);		// Rewind Current Working Directory
 	RC = SDFS_DirFindNext(&SDFS_CWD, filePtr, ATTR_NONE,  ATTR_NONE, fmtName);
 	//----------------------------------------------------------------
 	if (CE_EOF == RC)
 		// There is no object with the same name
 		goto NotFound;
 	//----------------------------------------------------------------			
 	if (CE_GOOD != RC)
 		// Some other error (except for CE_EOF) had happened...
 		return RC;
 	//----------------------------------------------------------------			
 	if ( FS_IsDirectory(filePtr) )
 		// The object found is a Directory...
 		{
	 	SDFS_InitFSFILE(filePtr, NULL, ATTR_NONE);	// Reset output FSFILE structure
	 	return CE_FILENAME_EXISTS;
 		}
 	//----------------------------------------------------------------			


 	//================================================================
 	// The file with the specified name present on the disk...
 	//----------------------------------------------------------------
	switch(mode)
       	{
		case FS_CREATE_NEW:
            // File exists, we want to create a new one, so remove it first
            if ( CE_GOOD != (RC = FS_Delete(filePtr)) )
            	// Delete failed...
            	{
		 		SDFS_InitFSFILE(filePtr, NULL, ATTR_NONE);	// Reset output FSFILE structure
            	return RC;
            	}
            //-----------------------------------------
            // Nope, does not exist any more :)
            goto NotFound;

               	
		case FS_APPEND:
            // File exists, we want to position it at the end
            if ( CE_GOOD != (RC = FS_SeekEnd(filePtr)) )
            	// Seek failed...
            	{
		 		SDFS_InitFSFILE(filePtr, NULL, ATTR_NONE);	// Reset output FSFILE structure
            	return RC;
            	}
            //-----------------------------------------
            // Everything is fine!
            return CE_GOOD;
            

		case FS_READ_ONLY:
			// Set READONLY attribute on the FO data structure to prevent WRITEs
			filePtr->dirFileEntry.DIR_Attr |= ATTR_READONLY;
			// Fall-through to OPEN_EXISTING
		case FS_OPEN_EXISTING:
			FS_SeekStart(filePtr);
			return CE_GOOD;
			
			
		default:
	 		SDFS_InitFSFILE(filePtr, NULL, ATTR_NONE);	// Reset output FSFILE structure
           	return CE_INVALID_ARGUMENT;
       	}


 	//================================================================
 	// The file with the specified name does not exist on disk...
 	//----------------------------------------------------------------
 NotFound:
	switch(mode)
       	{
		case FS_CREATE_NEW:
		case FS_APPEND:
		case FS_OPEN_EXISTING:
			// For all of the cases above proceed to creating new file
			break;
			

		case FS_READ_ONLY:
			// Bad luck...
	 		SDFS_InitFSFILE(filePtr, NULL, ATTR_NONE);	// Reset output FSFILE structure
           	return CE_NOT_FOUND;
			
			
		default:
	 		SDFS_InitFSFILE(filePtr, NULL, ATTR_NONE);	// Reset output FSFILE structure
           	return CE_INVALID_ARGUMENT;
       	}


 	//================================================================
 	// Now it is time to create a new file
 	//----------------------------------------------------------------
 	// First, try to create Directory Entry
 	//----------------------------------------------------------------
 	if ( (RC = SDFS_DirFindEmpty(&SDFS_CWD, filePtr)) != CE_GOOD)
 		return RC;		// Could not create directory entry...
 	//----------------------------------------------------------------
 	// Second, allocate a cluster to the file
 	//----------------------------------------------------------------
 	if ( CE_GOOD != (RC = SDFS_ClusterAllocateNew(filePtr)) )
 		{
 		SDFS_InitFSFILE(filePtr, NULL, ATTR_NONE);	// Reset output FSFILE structure
	 	return RC;	
 		}
 	//----------------------------------------------------------------
 	// Third, set the name and Attributes of the new entry
 	//----------------------------------------------------------------
 	memcpy(filePtr->dirFileEntry.DIR_Name, fmtName, NAME_SIZE_8r3);
 	filePtr->dirFileEntry.DIR_Attr = ATTR_ARCHIVE;	
 	//----------------------------------------------------------------
 	// That's basically it - just need to save changes to disk
 	//----------------------------------------------------------------
 	return FS_Flush(filePtr);
	}
//=====================================================================================

//*************************************************************************
//  Function:		CETYPE FS_Flush(FSFILE* filePtr)
//  Summary:		Update file information and FAT entry for the file
//  Input:
//    				filePtr -  Pointer to the file to flush to disk
//  Return Values:
//    				CE_GOOD 	- File flushed successfully 
//    				Other code 	- Error closing the file
//  Description:
//    				This function will update the directory entry for the 
//   				file pointed to by 'fo' with the information contained
//    				in 'fo,' including the new file size and attributes.
//    				Timestamp information will also be updated. The file 
//					entry will then be written to the device.  Finally, 
//					the memory used for the specified file object will be 
//					freed from the array of FSFILE objects.
//  Remarks:
//    				A function to flush data to the device without closing 
//					the file can be created by removing the portion of this
//    				function that frees the memory and the line that clears
//    				the write flag.
//*************************************************************************
CETYPE FS_Flush(FSFILE   *filePtr)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    CETYPE 	RC;
 	//----------------------------------------------------------------
    if	( !FS_IsReadOnly(filePtr) )
    	{
        // Save directory entry for the file
    	RC = SDFS_DataCacheWrite(	filePtr->dirLBA, &filePtr->dirFileEntry,
						   	   		filePtr->dirOffset, sizeof(DIRENTRY) );
		if (CE_GOOD != RC)
			return RC;
	    // Flush data
        if ( (RC = SDFS_DataCacheFlush()) != CE_GOOD)
			return RC;
    	}
 	//----------------------------------------------------------------
    return CE_GOOD;
	} 
//=====================================================================================



//*********************************************************************************
//  Function:		CETYPE	FS_Delete (FSFILE* filePtr)
//---------------------------------------------------------------------------------
//  Summary:		Deletes the file identified by the filePtr
//  Input:
//    				filePtr -  	Pointer to the File Object structure identifying the
//								file to be deleted
//  Return Values:
//    				CE_GOOD	-	File was deleted successfully
//								Other return codes may identify various error 
//								conditions as required.
//*********************************************************************************
CETYPE	FS_Delete (FSFILE* filePtr)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    // Check if this is a file and not a Directory
    if( FS_IsDirectory(filePtr) )
        return CE_DELETE_DIR;
    // Check if the file attributes allow write
    if( FS_IsReadOnly(filePtr) )
        return CE_READONLY;
	//-----------------------------------------------------------------
	CETYPE 	RC		= CE_GOOD;
	DWORD	ClsNum	= SDFS_DirGetFirstCluster(&filePtr->dirFileEntry);
	//----------------------------------------------------------------- 
	// Free Cluster Chain and flush changes to disk
	//----------------------------------------------------------------- 
	if (CE_GOOD != (RC = SDFS_FATEraseClusterChain(ClsNum)))
		return RC;
	ClsNum = SDFS_FATCacheFlush();
	if (CLUSTER_FAIL_FAT32 == ClsNum)
		return CE_DISK_ERROR;
	//----------------------------------------------------------------- 
	// Mark Directory Entry as "deleted" and flush updates to disk
	//----------------------------------------------------------------- 
	filePtr->dirFileEntry.DIR_Name[0] = DIR_DEL;
	if (CE_GOOD != (RC = FS_Flush(filePtr)))
		return RC;
	//----------------------------------------------------------------- 
	 return  SDFS_InitFSFILE(filePtr, NULL, ATTR_NONE);
	}
//=================================================================================




//*********************************************************************************
//  Function:		CETYPE FS_Rename (FSFILE* filePtr, const char * newName)
//---------------------------------------------------------------------------------
//  Summary:		Renames the file or directory identified by the filePtr
//  Input:
//    				filePtr -  	Pointer to the File Object structure identifying the
//								file to be renamed
//					newName	-	Character string providing new name
//  Return Values:
//    				CE_GOOD	-	File was deleted successfully
//								Other return codes may identify various error 
//								conditions as required.
//  Description:
//    				The FS_Rename(...) function will attempt to rename file or 
//					directory. First, it will search the directory where the entry 
//					is located for an object matching the new name - if such object 
//					found, the operation will fail; otherwise the object will be 
//					renamed.
//*********************************************************************************
CETYPE	FS_Rename (FSFILE* filePtr, const char * newName)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
 	if (NULL == newName)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    // Check if the file attributes allow write
    if ( (filePtr->dirFileEntry.DIR_Attr & ATTR_READONLY) == ATTR_READONLY )
        return CE_READONLY;
	//-----------------------------------------------------------------
	CETYPE 	RC			= CE_GOOD;
	char	fmtName[NAME_SIZE_8r3];
	FSFILE	Drtr;
	FSFILE	srchRes;
	DWORD	frstClsNum	= 0;
	//-----------------------------------------------------------------
	// Validate new name and convert it to 8.3 FAT format
	//-----------------------------------------------------------------
	if ( !SDFS_Format8dot3Name(newName, fmtName, FALSE) )
		return CE_INVALID_FILENAME;
	//-----------------------------------------------------------------
	// Prepare Directory File Object to perform search in the file's
	// Directory (Directory where the entry for this file is located)
	//-----------------------------------------------------------------
	// Obtain first cluster number of the file's directory
	frstClsNum = SDFS_DirGetFirstCluster(&filePtr->dirFileEntry);
	// Initialize File Object for file's directory
	SDFS_InitFSFILE(&Drtr, NULL, ATTR_DIRECTORY);
	// Set first cluster of the file's directory
	SDFS_DirSetFirstCluster(&Drtr.dirFileEntry, frstClsNum);
	// Set the current cluster of the file's directory
	Drtr.fileCrntCls = frstClsNum;
	//-----------------------------------------------------------------
	// Perform search for the new name in file's directory
	//-----------------------------------------------------------------
	RC = SDFS_DirFindNext(&Drtr, &srchRes, ATTR_NONE, ATTR_NONE,fmtName);
	if (CE_GOOD == RC)
		// Oops! object with this name already present
		return CE_FILENAME_EXISTS;
	if (CE_EOF != RC)	
		// Some unexpected error code - abort RENAME
		return RC;
	//-----------------------------------------------------------------
	// Name not found - rename the file
	//-----------------------------------------------------------------
	// Update the Name field in the Directory Entry
	memcpy(filePtr->dirFileEntry.DIR_Name, fmtName, NAME_SIZE_8r3);
	// Save updated entry to disk
	return FS_Flush(filePtr);
	}
//=================================================================================



//*********************************************************************************
//  Function:		CETYPE	FS_FindFirst(	const char* Pattern,
//							ATTR_TYPE FindAttr,  ATTR_TYPE SkipAttr,  
//						 	SEARCH_STATE* statePtr, FSFILE* foundPtr)
//---------------------------------------------------------------------------------
//  Summary:		Sets the Search structure and performs the search for the first
//					matching entry in the Current Working Directory.
//  Input:
//    				Pattern -  	Pointer to a null-terminated string identifying
//								search name/pattern.
//					FindAttr	- Combination of Attribute flags that must be set
//					SkipAttr	- Combination of Attribute flags that must NOT be set
//					statePtr	- Pointer to the Search State structure preserving
//								  search state between calls
//					foundPtr	- Pointer to the new File Object matching search
//  Return Values:
//    				CE_GOOD	-	File was deleted successfully
//								Other return codes may identify various error 
//								conditions as required.
//  Description:
//  				The FS_FindFirst(...) function sets the Search structure and 
//					performs the search for the first matching entry in the Current 
//					Working Directory.
//    				The Pattern provided as search argument could be a regular 8.3 
//					file or directory name or could be a wildcard search pattern;
//					special symbols in the pattern have the following meaning:
//					"*"	- matches any number of characters
//					"?" - matches exactly one alpha-numeric character
//					"+" - matches exactly one numeric character
//*********************************************************************************
CETYPE 		FS_FindFirst(	const char* Pattern,
							ATTR_TYPE FindAttr,  ATTR_TYPE SkipAttr,  
						 	SEARCH_STATE* statePtr, FSFILE* foundPtr)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == Pattern)
 		return CE_INVALID_ARGUMENT;		
 	if (NULL == statePtr)
 		return CE_INVALID_ARGUMENT;		
 	if (NULL == foundPtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    // Initialize search result File Object to default state
	//-----------------------------------------------------------------
	SDFS_InitFSFILE(foundPtr, NULL, ATTR_NONE);
 	//----------------------------------------------------------------
    // Check if the valid name/pattern provided
	//-----------------------------------------------------------------
    if( !SDFS_Format8dot3Name (	Pattern, statePtr->SearchName, TRUE) )
        return CE_INVALID_FILENAME;
 	//----------------------------------------------------------------
    // Initialize the rest of the fields in the SEARCH_STATE structure
	//-----------------------------------------------------------------
	statePtr->FindAttr	= FindAttr;
	statePtr->SkipAttr	= SkipAttr;
	// Copy Current Working Directory
	SDFS_CopyFSFILE(&statePtr->SrcDir, &SDFS_CWD);
	// "Rewind" search directory to beginning
	FS_SeekStart (&statePtr->SrcDir);
 	//----------------------------------------------------------------
    // Perform search and return result
	//-----------------------------------------------------------------
	return SDFS_DirFindNext(&statePtr->SrcDir, foundPtr,
							statePtr->FindAttr,  statePtr->SkipAttr,  
							statePtr->SearchName );
	}						 	
//=================================================================================


//*********************************************************************************
//  Function:		CETYPE	FS_FindNext(SEARCH_STATE* statePtr, FSFILE* foundPtr)
//---------------------------------------------------------------------------------
//  Summary:		Continues search for other matching entries starting from where
//					previous call to FS_FindFirst(...) or FS_FindNext(...) left.
//  Input:
//					statePtr	- Pointer to the Search State structure preserving
//								  search state between calls
//					foundPtr	- Pointer to the new File Object matching search
//  Return Values:
//    				CE_GOOD	-	File was deleted successfully
//								Other return codes may identify various error 
//								conditions as required.
//*********************************************************************************
CETYPE 		FS_FindNext(	SEARCH_STATE* statePtr, FSFILE* foundPtr)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == statePtr)
 		return CE_INVALID_ARGUMENT;		
 	if (NULL == foundPtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    // Initialize search result File Object to the default state
	//-----------------------------------------------------------------
	SDFS_InitFSFILE(foundPtr, NULL, ATTR_NONE);
 	//----------------------------------------------------------------
    // Perform search and return result
	//-----------------------------------------------------------------
	return SDFS_DirFindNext(&statePtr->SrcDir, foundPtr,
							statePtr->FindAttr,  statePtr->SkipAttr,  
							statePtr->SearchName );
	}						 	
//=================================================================================


//*********************************************************************************
//  Function:		CETYPE	FS_GetName(char* Name, WORD Length, FSFILE* filePtr)
//---------------------------------------------------------------------------------
//  Summary:		Extract File Object name from the FSFILE structure.
//  Input:
//					Name		- Location to store file name to
//					Length		- Size of the destination location
//					filePtr		- Pointer to the File Object to retrieve name from
//  Return Values:
//    				CE_GOOD	-	Name was retrieved successfully
//								Other return codes may identify various error 
//								conditions as required.
//*********************************************************************************
CETYPE 		FS_GetName(char* Name, WORD Length, FSFILE* filePtr)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	//---------------------------------------------------
 	if (NULL == Name)
 		return CE_INVALID_ARGUMENT;		
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
 	// Max 8.3 name size + radix + NULL terminator
 	if (Length < NAME_SIZE_8r3 + 2)		
 		return CE_FILENAME_DEST_TOO_SMALL;		
 	//---------------------------------------------------
 	if (DIR_DEL == filePtr->dirFileEntry.DIR_Name[0])
 		return CE_NOT_A_FILE;
 	if (DIR_EMPTY == filePtr->dirFileEntry.DIR_Name[0])
 		return CE_NOT_A_FILE;
 	if (' ' == filePtr->dirFileEntry.DIR_Name[0])
 		// Valid file object name cannot start with blank...
 		return CE_NOT_A_FILE;
 	//----------------------------------------------------------------
    // Initialize destination
	//----------------------------------------------------------------
	memset(Name, 0x00, Length);
	WORD	dPos	= 0;
	WORD	fPos	= 0;
 	//----------------------------------------------------------------
    // Copy name from file object to destination
	//-----------------------------------------------------------------
	for (fPos = 0; fPos < NAME_SIZE_8r3; fPos++)
		{
		if (' ' == filePtr->dirFileEntry.DIR_Name[fPos])
			continue;	// Ignore blanks...
		if (8 == fPos)
			// First character of extension is not blank...
			// Insert "dot" into the name
			Name[dPos++] = '.';
		Name[dPos++] = filePtr->dirFileEntry.DIR_Name[fPos];
		}
	//-----------------------------------------------------------------
	return CE_GOOD;
	}						 	
//=================================================================================



//*********************************************************************************
//  Function:		CETYPE	FS_Recover(FSFILE* filePtr)
//---------------------------------------------------------------------------------
//  Summary:		Recovers the length of a 0-length file identified by the filePtr
//					based upon the number of allocated clusters
//  Input:
//    				filePtr -  	Pointer to the File Object structure identifying the
//								file to be recovered
//  Return Values:
//    				CE_GOOD	-	File was recovered successfully
//								Other return codes may identify various error 
//								conditions as required.
//*********************************************************************************
CETYPE	FS_Recover(FSFILE* filePtr)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    // Check if this is a file and not a Directory
    if( FS_IsDirectory(filePtr) )
        return CE_DIRECTORY;
    // Check if the file is actually 0-length
    if( FS_GetSize(filePtr) > 0 )
        return CE_GOOD;
	//-----------------------------------------------------------------
	DWORD	ClsSize	= (DWORD)SDFS_VolumeInfo.SecPerClus 
						   * SDFS_VolumeInfo.sectorSize;
	DWORD	ClsNum	= SDFS_DirGetFirstCluster(&filePtr->dirFileEntry);
	//-----------------------------------------------------------------
	while (ClsNum < EOC_CLUSTER_FAT32)
		{
	    //-------------------------------------------------------
		// Process cluster chain
	    //-------------------------------------------------------
	    // The first 2 clusters in FAT32 are reserved...
	    if	( ClsNum < 2)  // Cluster Number can't be "0" and "1"
	    	return CE_RECOVERY_FAIL;
	    //-------------------------------------------------------
	    filePtr->dirFileEntry.DIR_FileSize += ClsSize;
	    //-------------------------------------------------------
	    // Load next cluster in the chain
	    //-------------------------------------------------------
	    ClsNum = SDFS_FATCacheRead(ClsNum);
		}
	//----------------------------------------------------------------- 
	// Flush updates to disk
	//----------------------------------------------------------------- 
	return FS_Flush(filePtr);
	}
//=================================================================================






