#include "FSIO\SDFS.h"

//*************************************************************************************
//  Function:		CETYPE FS_FileSeekAbs (FSFILE * filePtr, DWORD Seek)
//-------------------------------------------------------------------------------------
//  Summary:		Moves current position in the file to Seek.
//  Input:			
//					filePtr	- pointer to the File Object structure
//					Seek	- new position in the file
//  Return Values:
//					CETYPE enum member (expected CE_GOOD)
//  Side Effects:
//					None
//  Description:
//					This function moves the current position in the file to the byte
//					specified by Seek. If "Seek" exceeds the size of the file, file
//					will be positioned at the end and return code will be "CE_EOF".
//*************************************************************************************
CETYPE 		FS_SeekAbs (FSFILE * filePtr, DWORD Seek)
	{
	CETYPE	SeekRC	= CE_GOOD;
	CETYPE	TempRC;
	//================================================================
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
	//================================================================
	// Validate Seek
 	//----------------------------------------------------------------
 	if (0 == Seek)
 		// Easy case :)
 		return FS_SeekStart(filePtr);
 	//----------------------------------------------------------------
	if (Seek > filePtr->dirFileEntry.DIR_FileSize)
		{
		// Set EOF code and adjust Seek to the End-of-File
		SeekRC	= CE_EOF;
		Seek 	= filePtr->dirFileEntry.DIR_FileSize;
		}
	//================================================================
	
	DWORD	ClusterSize		= SDFS_VolumeInfo.sectorSize * SDFS_VolumeInfo.SecPerClus;

	//================================================================
	// Seek to the beginning of the current cluster: optimistic :)
	//================================================================
	filePtr->fileSeek		= filePtr->fileSeek 
							- filePtr->fileCrntSec*SDFS_VolumeInfo.sectorSize
							- filePtr->fileCrntSecPos;
	filePtr->fileCrntSec	= 0;							
	filePtr->fileCrntSecPos	= 0;
 	//----------------------------------------------------------------
 	// Verify that Seek can be satified moving forward from the
 	// start of the current cluster 
 	//----------------------------------------------------------------
 	if (Seek < filePtr->fileSeek)
 	 	// No such luck! Move back to the start of the file...
 		FS_SeekStart(filePtr);
		
	//================================================================
	// Now we are assured that we need to seek forward - the ONLY way
	// we may seek in the file as this coincides with the direction of
	// the FAT Cluster Chain for a file.
	//================================================================
	DWORD	ClusterOffset	= Seek - filePtr->fileSeek;
	
	//================================================================
	// Advance through file clusters starting with the current one
	// until ClusterOffset will be contained in the current cluster
 	//----------------------------------------------------------------
	while ( ClusterSize < ClusterOffset)	
		{
		// Offset exceeds the size of the cluster...
		// let's move to next cluster and adjust offset
		if ( CE_GOOD != (TempRC = SDFS_ClusterGetNext(filePtr)) )
			// I/O error or bad cluster chain...
			return TempRC;
		// Adjust offset accounting for the new cluster
		ClusterOffset -= ClusterSize;
		// Now check again
		} 
	
	//================================================================
	// Adjust position within the current cluster to satisfy Seek
 	//----------------------------------------------------------------
	filePtr->fileCrntSec	= ClusterOffset / SDFS_VolumeInfo.sectorSize;							
	// Check for "border" condition
	if (filePtr->fileCrntSec == SDFS_VolumeInfo.SecPerClus)
		{
		// "Border" condition
		filePtr->fileCrntSec--;
		filePtr->fileCrntSecPos	= SDFS_VolumeInfo.sectorSize;
		}
	else
		// Normal condition
		filePtr->fileCrntSecPos = ClusterOffset 
								- (filePtr->fileCrntSec * SDFS_VolumeInfo.sectorSize); 	
	//================================================================
 	return SeekRC;
	}
//=====================================================================================


//*************************************************************************************
//  Function:		CETYPE FS_Attrib (FSFILE * filePtr, ATTR_TYPE Attributes)
//-------------------------------------------------------------------------------------
//  Summary:		Change the attributes of a file/directory
//  Conditions:		File opened
//  Input:
//    				filePtr		-	Pointer to file structure
//    				Attributes	-  	The attribute flags to set for the file
//               					A combination of various (compatible) flags
//									from the ATTR_TYPE enumerator 
//  Return Values:
//    				CETYPE 		-	Expected CE_GOOD 
//  Description:
//    				The FS_Attrib(...) funciton will set the attributes of the specified 
//					file or directory to the (set of) attributes passed in by the user.  
//					The function checks for a valid combination of attribute flags.
//    				If the specified file is a directory, the DIRECTORY attribute will 
//					be preserved.
//*************************************************************************************
CETYPE FS_Attrib (FSFILE * filePtr, ATTR_TYPE Attributes)
	{
	//================================================================
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    // Check for valid attributes
 	//----------------------------------------------------------------
    if ((Attributes & ~ATTR_ALL) != 0)
        return CE_INVALID_ARGUMENT;
	//================================================================

 	//----------------------------------------------------------------
    // Ensure that we do not remove the directory attribute from DIR
    // files or do not inadverently set DIRECTORY attribute on a file
 	//----------------------------------------------------------------
    if (FS_IsDirectory(filePtr))
        filePtr->dirFileEntry.DIR_Attr = (Attributes | ATTR_DIRECTORY);
    else
        filePtr->dirFileEntry.DIR_Attr = (Attributes & ~ATTR_DIRECTORY);

 	//----------------------------------------------------------------
    // Save updated directory entry entry
 	//----------------------------------------------------------------
    return SDFS_DataCacheWrite(filePtr->dirLBA, &filePtr->dirFileEntry,
						   	   filePtr->dirOffset, sizeof(DIRENTRY) );
	}
//=================================================================================




