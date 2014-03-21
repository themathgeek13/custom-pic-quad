#include "SDSPI\SD-SPI.h"		// SD Card Physical Access Layer

#include "FSIO\SDFS.h"

//*************************************************************************************
//  Function:		CETYPE FS_Init(void)
//-------------------------------------------------------------------------------------
//  Summary:		Function to initialize the device.
//  Input:			None
//  Return Values:	CETYPE enum member
//  Side Effects:	The FSerrno variable will be changed.
//  Description:	This function initializes the file system stack and the 
//					interfacing device. Initializes the static memory slots 
//					for holding file structures. Initializes the device with 
//					the DISKmount function. Loads MBR and boot sector 
//					information. Initializes the current working directory 
//					to the root directory for the device if directory support
//    				is enabled.
//*************************************************************************************
CETYPE FS_Init(void)
	{
	MEDIA_STATUS	MRC;
	CETYPE			RC;
 	//----------------------------------------------------------------
	// Check for duplicate initialization
 	//----------------------------------------------------------------
 	if (SDFS_InitStatus)
 		return CE_GOOD;		// Already initialized!

 	//----------------------------------------------------------------
	// Initialize Physical layer
 	//----------------------------------------------------------------
 	MRC = SD_SPI_MediaInitialize();
 	
 	if (MEDIA_NOT_PRESENT == MRC)
 		return CE_MEDIA_NOT_PRESENT;
 	
 	if (MEDIA_CANNOT_INITIALIZE == MRC)
 		return CE_MEDIA_NOT_INITIALIZED;
 	
 	
 	//----------------------------------------------------------------
	// Mount Volume ...
 	//----------------------------------------------------------------
    if	( (RC = SDFS_MountVolume()) != CE_GOOD)
    	// Failure mounting drive...
    	return RC;
 	//----------------------------------------------------------------
 
 	//================================================================
 	// Initialize File Object representing current working directory
 	//----------------------------------------------------------------
 	if ( (RC = SDFS_DirSetFOtoRoot(&SDFS_CWD)) != CE_GOOD)
 		return RC;
	//================================================================

 	//================================================================
 	SDFS_InitStatus	= TRUE;
 	//----------------------------------------------------------------	
    return CE_GOOD;
	}
//=====================================================================================

//*********************************************************************************
//  Function:   	CETYPE FS_GetDiskProperties(FS_DISK_PROPERTIES* DiskProps)
//  Summary:		Allows user to get the properties of the mounted disk
//  Input:
//    				DiskProps - a pointer to a FS_DISK_PROPERTIES object where the 
//								results should be stored.
//  Return Values:
//    				CETYPE	- expected CE_GOOD if everything is OK, otherwise
//							  one of the error codes depending on the condition
//
//  Side Effects:
//    				Changes value of the global FSerrno variable
//  Description:  
//    				This function returns the information about the mounted drive.  
//					Some of the values in the FS_DISK_PROPERTIES structure will
//					be populated based upon values in the Volume Information
//					structure and are readily available. Others will be read from
//					the disk and may require some time for processing. To calculate
//					number of the free clusters on the disk the whole FAT table
//					need to be scanned, which for large disks mat take significant
//					time.
//      			Scanning FAT table takes approximately 7 seconds per Gigabyte 
//					of drive space. Speed will vary based on the number of sectors 
//					per cluster and the sector size.
//*********************************************************************************
CETYPE FS_GetDiskProperties(FS_DISK_PROPERTIES* DiskProps)
	{
	//=============================================================
	// Verify run-time conditions
	//-------------------------------------------------------------
	if (FALSE == SDFS_InitStatus)
		return CE_NOT_INIT;
	if (NULL == DiskProps)
		return CE_INVALID_ARGUMENT;
	//=============================================================
	// Initialize FS_DISK_PROPERTIES structure and load values
	// from the Volume Information structure
	//-------------------------------------------------------------
	memset(DiskProps->VolLabel, 0x20, NAME_SIZE_8r3); 
	//-------------------------------------------------------------
	DiskProps->TotalClusters 		= SDFS_VolumeInfo.clusterCnt;
	DiskProps->FreeClusters			= 0;	// To be calculated
	DiskProps->SectorSize			= SDFS_VolumeInfo.sectorSize;
	DiskProps->SectorsPerCluster	= SDFS_VolumeInfo.SecPerClus;
	//-------------------------------------------------------------

    CETYPE		RC;
	
	//=============================================================
	// Retrieve Volume Label
	//-------------------------------------------------------------
    FSFILE		RootDir;
    DIRENTRY	dirEntry;
    WORD		ReadCnt;
	//-----------------------------------------------------------------
    if ( CE_GOOD != (RC = SDFS_DirSetFOtoRoot(&RootDir)) )
    	return RC;		
	//-----------------------------------------------------------------
	while (CE_GOOD == RC)
		{
		RC = FS_Read(&RootDir, &dirEntry, sizeof(DIRENTRY), &ReadCnt);
		//------------------------
		if ( CE_EOF == RC )
			break;		// Volume does not have Volume Label - leave all blanks
		//------------------------
		if ( CE_GOOD != RC )
			return RC;	// some serious error took place...
		//------------------------
		if 	( DIR_EMPTY == dirEntry.DIR_Name[0] )
			break;		// Volume does not have Volume Label - leave all blanks
		//------------------------
		if 	( DIR_DEL 	== dirEntry.DIR_Name[0] )
			continue;	// Deleted entry - ignore
		//------------------------
	    if ( (dirEntry.DIR_Attr & ATTR_VOLUME)	== ATTR_VOLUME)
			{
			// Volume Label entry found - retieve Label
			memcpy(DiskProps->VolLabel, dirEntry.DIR_Name, NAME_SIZE_8r3);
			break;
			}
 		}	

	//=============================================================
	// Obtain number of free clusters
	//-------------------------------------------------------------
	DWORD 	ClusterNumber;
	DWORD	FATEntry;
	for (	ClusterNumber  = 2; 
			ClusterNumber <= SDFS_VolumeInfo.clusterMax; 
			ClusterNumber++)
		{
		FATEntry = SDFS_FATCacheRead(ClusterNumber);
		//------------------------------------------
		if (CLUSTER_FAIL_FAT32 == FATEntry)
			return CE_DISK_ERROR;
		//------------------------------------------
		if (0 == FATEntry)
			// Increment count of empty clusters
			DiskProps->FreeClusters++;
		}
	//-------------------------------------------------------------

	//=============================================================
    return CE_GOOD;
	}
//=================================================================================





