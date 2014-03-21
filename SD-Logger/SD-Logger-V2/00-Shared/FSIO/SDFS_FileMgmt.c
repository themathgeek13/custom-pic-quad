#include "FSIO\SDFS.h"


//************************************************************************************
//  Function:		CETYPE SDFS_InitFSFILE(	FSFILE*	filePtr, const char * FileName, 
//											ATTR_TYPE FileAttr)
//  Summary:		Performs basic initialization of the FSFILE data structure
//  Input:			filePtr		- Pointer to the data structure to be initialized
//					FileName	- Pointer to the file name
//					FileAttr	- Attributes of the new file
//  Return Values:
//    				CETYPE - 	Error code (expected: CE_GOOD)
//  Side Effects:
//    				Sets FSerrno variable to result code
//  Description:
//    				The SDFS_InitFSFILE(...) function initializes FSFILE data 
//					structure. If FileName is not NULL, it will be formatted as
//					required for the Directory Entry and stored as the file name
//					in the DIRECTORY section of the structure. Otherwise file name
//					section will be filled with blanks.
//************************************************************************************
CETYPE SDFS_InitFSFILE(	FSFILE*	filePtr, const char * FileName,	ATTR_TYPE FileAttr)
	{
 	//================================================================
 	// Validate parameters
 	//----------------------------------------------------------------
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;
 	//================================================================
 	// Configure Directory Entry of this File Object
 	//----------------------------------------------------------------
   	if (CE_GOOD != SDFS_DirResetEntry(&filePtr->dirFileEntry, FileName, FileAttr))
    		return CE_INVALID_FILENAME;	
  	//================================================================
    // Disk location of the Directory entry for this File Object
    //---------------------------------------------------------------------------
	// Point to current position in the current working directory
	filePtr->dirFrstCls 	= 0;
	filePtr->dirLBA		 	= 0;
	filePtr->dirOffset 		= 0;
    //---------------------------------------------------------------------------
	// File Object current position 
    //---------------------------------------------------------------------------
    filePtr->fileCrntCls 	= 0;		// The current cluster of the file
    filePtr->fileSeek		= 0;		// The absolute position in the file
    filePtr->fileCrntSec	= 0;		// The current sector in the current cluster of the file
    filePtr->fileCrntSecPos	= 0;		// The position in the current sector
 	//================================================================
 	return CE_GOOD;
	}
//=====================================================================================


//************************************************************************************
//  Function:		CETYPE SDFS_ClusterZeroOut(DWORD ClusterNumber)
//  Summary:		Erases (zeroes-out) a cluster
//  Input:			ClusterNumber - Cluster to be zeroed out
//  Return Values:
//    				CE_GOOD 		- File closed successfully
//    				CE_WRITE_ERROR 	- Could not write to the sector
//  Description:
//    				The SDFS_ClusterZeroOut(...) function will write a 0 value into 
//					every byte of the every sector of the specified cluster.
//************************************************************************************
CETYPE SDFS_ClusterZeroOut(DWORD ClusterNumber)
	{
    BYTE 	index;
    DWORD 	SectorNumber;
    CETYPE	RC;

    SectorNumber = SDFS_FATClusterToLBA(ClusterNumber);

    // Now clear them out
    for(index = 0; index < SDFS_VolumeInfo.SecPerClus; index++)
    	{
        if ( (RC = SDFS_DataCacheSectorZeroOut (SectorNumber)) != CE_GOOD)
    		return RC;
    	}

    return SDFS_DataCacheFlush();	// Just to be sure :)
	}
//=====================================================================================

//************************************************************************************
//  Function:		CETYPE SDFS_ClusterGetNext(FSFILE* filePtr)
//  Summary:		Advances in the cluster chain for the file to next cluster
//  Input:
//    				filePtr - Pointer to the File Object to get the next cluster for
//  Return Values:
//    				CE_GOOD 			- Operation successful
//    				CE_BAD_SECTOR_READ 	- A bad read occured of a sector
//    				CE_INVALID_CLUSTER 	- Invalid cluster value/bad chain
//    				CE_EOF 				- Attempt to read beyond EOF
//  Description:
//    				This function will advance in the cluster chain to the next
//					cluster following filePtr->fileCrntCls; if operation successful
//					filePtr->fileCrntCls will be advanced and sector an position
//					in the sector reset for the new current cluster. 
//************************************************************************************
CETYPE SDFS_ClusterGetNext(FSFILE* filePtr)
	{
	// Read next FAT Entry in the cluster Chain for the file
	DWORD	NextCluster = SDFS_FATCacheRead(filePtr->fileCrntCls);

	// Check if FAT READ was successful
	if ( CLUSTER_FAIL_FAT32 == NextCluster)
		return CE_BAD_SECTOR_READ;

	// Check FAT Entry for end-of-chain
	if ( NextCluster >= EOC_CLUSTER_FAT32)    
		return CE_EOF;

	// Check FAT Entry to be valid
	//------------------------------------------------------
	if ( NextCluster > SDFS_VolumeInfo.clusterMax )
		return CE_INVALID_CLUSTER;
	
	//---------------------------------------------------------------------
	// Everything is in order advance to the next Cluster
	//---------------------------------------------------------------------
	filePtr->fileCrntCls 	= NextCluster;	// Advance to the next cluster
	filePtr->fileCrntSec 	= 0;			// Reset current sector to the
											// first in the next cluster
	filePtr->fileCrntSecPos = 0;			// Reset current position to
											// the beginning of the sector
	//---------------------------------------------------------------------
	return CE_GOOD;
	} 
//=====================================================================================

	
//************************************************************************************
//  Function:		CETYPE SDFS_ClusterAllocateNew(FSFILE* filePtr)
//  Summary:		Allocates new cluster for the file and adds it to the cluster chain
//  Input:
//    				filePtr - Pointer to the File Object to get the new cluster for
//  Return Values:
//    				CE_GOOD 		- Operation successful
//    				CE_DISK_ERROR 	- I/O error accessing disk
//    				CE_DISK_FULL	- No more free space in the volume
//  Description:
//    				This function will attempt to allocate new cluster for the file;
//					if operation successful the newly allocated cluster will be added
//					to the cluster chain of the file, the filePtr->fileCrntCls will 
//					be advanced to the new cluster and sector an position in the 
//					sector reset for the new current cluster. 
//************************************************************************************
CETYPE 				SDFS_ClusterAllocateNew(FSFILE* filePtr)
	{
	DWORD	SearchPoint;
	DWORD	NextCluster;
	DWORD	FATEntry;
	//---------------------------------------------------------------------
	// Verify that the current chain exists and is actually exhausted
	//---------------------------------------------------------------------
	if (filePtr->fileCrntCls > 1)		// Valid current cluster
		{
		// Read next FAT Entry in the cluster Chain for the file
		FATEntry = SDFS_FATCacheRead(filePtr->fileCrntCls);
		// Check if FAT READ was successful
		if ( CLUSTER_FAIL_FAT32 == FATEntry)
			return CE_DISK_ERROR;	
		// Check FAT Entry for end-of-chain
		if ( FATEntry < EOC_CLUSTER_FAT32)  
			// Nope, the chain exists and we are not at the end...  
			// Request should be satisfied by moving to the next
			// cluster...
			return SDFS_ClusterGetNext(filePtr);
		}

	//---------------------------------------------------------------------
	// OK, first let's try to find an unallocated cluster starting from
	// the cluster following the last cluster of the file
	//---------------------------------------------------------------------
	SearchPoint = filePtr->fileCrntCls == 0 ? 2 : filePtr->fileCrntCls + 1;
	//---------------------------------------------------------------------					
	for (	NextCluster  = SearchPoint; 
			NextCluster <= SDFS_VolumeInfo.clusterMax;
			NextCluster++)
		{
		if ( (FATEntry = SDFS_FATCacheRead(NextCluster)) == CLUSTER_FAIL_FAT32)
			// Unrecoverable I/O operation...
			return CE_BAD_SECTOR_READ;
		if (CLUSTER_EMPTY == FATEntry)	
			// Unallocated cluster found!
			goto AllocateClusterToFile;
		}
	//---------------------------------------------------------------------
	// No luck easy way :) Let's try to find an unallocated cluster
	// starting from the beginning of the FAT to just before the last search
	//---------------------------------------------------------------------
	SearchPoint -= 2; 	// Set SearchPoint just before filePtr->fileCrntCls
						// (or "0" if there is no clusters allocated to file)
		
	//---------------------------------------------------------------------					
	for (	NextCluster  = 2; 		// Skip reserved clusters
			NextCluster <= SearchPoint;
			NextCluster++)
		{
		if ( (FATEntry = SDFS_FATCacheRead(NextCluster)) == CLUSTER_FAIL_FAT32)
			// Unrecoverable I/O operation...
			return CE_BAD_SECTOR_READ;
		if (CLUSTER_EMPTY == FATEntry)	
			// Unallocated cluster found!
			goto AllocateClusterToFile;
		}
	//---------------------------------------------------------------------
	// Again no luck - apparently disk is full...
	//---------------------------------------------------------------------
	return CE_DISK_FULL;
	//---------------------------------------------------------------------

AllocateClusterToFile:
	//---------------------------------------------------------------------
	// Success! NextCluster points to empty cluster!
	//---------------------------------------------------------------------
	// First, let's "grab" this cluster
	FATEntry = SDFS_FATCacheWrite(NextCluster, EOC_CLUSTER_FAT32);
	if ( CLUSTER_FAIL_FAT32 == FATEntry)
		return CE_DISK_ERROR;	
	// Second, to avoid FAT corruption, let's flush changes to disk
	if ( CLUSTER_FAIL_FAT32 == SDFS_FATCacheFlush() )
		return CE_DISK_ERROR;	
	// Third, let's either set or extend the chain for the file
	if (0 == filePtr->fileCrntCls)		
		// First cluster in a chain - set the chain for file
		SDFS_DirSetFirstCluster (&filePtr->dirFileEntry, NextCluster);
	else
		{
		// Chain exists - just extend it
		FATEntry = SDFS_FATCacheWrite(filePtr->fileCrntCls, NextCluster);
		if ( CLUSTER_FAIL_FAT32 == FATEntry)
			return CE_DISK_ERROR;	
		}
	//---------------------------------------------------------------------
	// Everything is in order advance to the next Cluster
	//---------------------------------------------------------------------
	filePtr->fileCrntCls 	= NextCluster;	// Advance to the next cluster
	filePtr->fileCrntSec 	= 0;			// Reset current sector to the
											// first in the next cluster
	filePtr->fileCrntSecPos = 0;			// Reset current position to
											// the beginning of the sector
	//---------------------------------------------------------------------
	// If current file is a directory, the new cluster need to be zeroed-out
	//---------------------------------------------------------------------
	if ( FS_IsDirectory(filePtr) )
		return SDFS_ClusterZeroOut(NextCluster);	
	//---------------------------------------------------------------------
	return CE_GOOD;
	} 
//=====================================================================================
	
	

