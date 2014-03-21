#include "SDSPI\SD-SPI.h"		// SD Card Physical Access Layer

#include "FSIO\SDFS.h"

typedef struct
	{
	// The FAT sector buffer
	BYTE   	__attribute__ ((aligned(4)))
				Buffer[MEDIA_SECTOR_SIZE];      
	// Variable indicating which FAT sector was read last
	DWORD       CurrentFATSector;  
	// Status of the FAT sector in the Buffer
	BOOL        IsDirty; 
	}	__FATCacheEntry;
	
__FATCacheEntry		SDFS_FATCache = { {0} ,CLUSTER_FAIL_FAT32, FALSE };


//************************************************************************************
//  Function:		DWORD SDFS_FATCacheFlush()
//  Summary:		Flashes to disk current FAT Cache Buffer
//  Input:			None
//  Return:
//    				0					- Success
//					CLUSTER_FAIL_FAT32	- Unrecoverable error writing to disk
//  Description:
//    				The FATCacheFlash() function will flash to disk current cache
//					Buffer if a) it contains valid cluster, and b) the cluster is
//    				DIRTY.
//************************************************************************************
DWORD SDFS_FATCacheFlush()
	{
	if 	(
			SDFS_FATCache.CurrentFATSector 	== CLUSTER_FAIL_FAT32
		||	
			SDFS_FATCache.IsDirty			== FALSE	 
		)
		return 0;	// Nothing to do - Success!
	//----------------------------------------------------------
	SDFS_FATCache.IsDirty = FALSE;
	//----------------------------------------------------------
	DWORD	FATSectorToWrite = SDFS_FATCache.CurrentFATSector;
	int		i;
	//----------------------------------------------------------
	for (i = 0; i < SDFS_VolumeInfo.fatCnt; i++)
		{
		if ( !SD_SPI_SectorWrite(FATSectorToWrite, SDFS_FATCache.Buffer, FALSE) )
			return CLUSTER_FAIL_FAT32;
		// Advance to the next FAT; Usually Volume contains 2 FATs, but could
		// have more..
		FATSectorToWrite += SDFS_VolumeInfo.fatsize;	
		}
	//----------------------------------------------------------
	return 0;	// Success!
	}	
		
//************************************************************************************
//  Function:		DWORD SDFS_FATCacheRead (DWORD ClusterNumber)
//  Summary:		Reads FAT entry for specified cluster
//  Input:			ClusterNumber - Cluster number for which to read FAT entry
//  Return:
//    				Success: The value of the FAT entry for the cluster
//					Failure: CLUSTER_FAIL_FAT32
//  Description:
//    				The SDFS_FATCacheRead function will load into Cache FAT sector 
//					corresponding to the specified cluster and retrieves
//					FAT entry for this cluster.
//					If the function fails the CLUSTER_FAIL_FAT32 value will be
//					returned instead of the FAT entry.//    				
//					NOTE: the FAT sector that is read is stored in the FAT cache 
//						  buffer. Previous content of the buffer is flashed to disk
//						  if needed.
//************************************************************************************
DWORD SDFS_FATCacheRead (DWORD ClusterNumber)
	{
	//------------------------------------------------------
	// Check ClusterNumber to be valid
	//------------------------------------------------------
	if ( ClusterNumber > SDFS_VolumeInfo.clusterMax )
		return CLUSTER_FAIL_FAT32;
	//------------------------------------------------------

	DWORD	FATEntryNumber	= ClusterNumber << 2;	// ClusterNumber*4 - remember: in
													// FAT32 every entry is 4 bytes!
	
	DWORD	FATSectorToRead	= SDFS_VolumeInfo.fat + (FATEntryNumber / SDFS_VolumeInfo.sectorSize);
	
    DWORD 	FATSectorOffset = FATEntryNumber & (SDFS_VolumeInfo.sectorSize - 1);  
    
    DWORD 	FATEntry = 0;   

	//------------------------------------------------------------------
    // Check if the appropriate FAT sector is already loaded
    if	(FATSectorToRead != SDFS_FATCache.CurrentFATSector)
    	{
	    // Cache buffer need to be re-loaded
	    //--------------------------------------------------
	    // First, flash existing cache buffer..
	    //--------------------------------------------------
	    if (SDFS_FATCacheFlush() != 0)
	    	return CLUSTER_FAIL_FAT32;
	    //--------------------------------------------------
	    // Second, read required sector into cache buffer..
	    //--------------------------------------------------
        if	( !SD_SPI_SectorRead (FATSectorToRead, SDFS_FATCache.Buffer) )
        	{
	        // Failure...
            return SDFS_FATCache.CurrentFATSector = CLUSTER_FAIL_FAT32;  
        	}
	    // Success!
	    SDFS_FATCache.CurrentFATSector 	= FATSectorToRead;
	    SDFS_FATCache.IsDirty 			= FALSE;	// Reset DIRTY flag on READ
    	}
    	
	//------------------------------------------------------------------
    // Required FAT sector is in the Cache Buffer - retrieve the value
    // NOTE: We take advantage of the fact that in FAT numeric values
    //		 are stored in the "little endian" format - same as the
    //		 native data addressing in PIC24/32 MCUs
    FATEntry = *((DWORD*)&SDFS_FATCache.Buffer[FATSectorOffset]);
   	//------------------------------------------------------------------
	return FATEntry;
	}   // SDFS_FATCacheRead



//************************************************************************************
//  Function:		DWORD SDFS_FATCacheWrite (DWORD ClusterNumber, WORD FATEntry)
//  Summary:		Write an entry to the FAT of the mounted Disk
//  Conditions:		Disk should be mounted
//  Input:
//    				ClusterNumber	- The cluster to update
//    				FATEntry 		- The value to write in the cluster entry
//  Return:
//    				0 			- The FAT write was successful
//    				FAIL 		- The FAT could not be written
//  Description:
//    				The SDFS_FATCacheWrite function writes an entry to the FAT.  If the function
//    				is called and the 'forceWrite' argument is TRUE, the function will
//    				write the existing FAT data to the device.  Otherwise, the function
//    				will replace a single entry in the FAT buffer (indicated by 'fileCrntCls')
//    				with a new value (indicated by 'value.')
//************************************************************************************
DWORD SDFS_FATCacheWrite (DWORD ClusterNumber, DWORD FATEntry)
	{
	//------------------------------------------------------
	// Check ClusterNumber to be valid
	//------------------------------------------------------
	if ( ClusterNumber > SDFS_VolumeInfo.clusterMax )
		return CLUSTER_FAIL_FAT32;
	//------------------------------------------------------
	
	DWORD	FATEntryNumber		= ClusterNumber << 2;	// ClusterNumber*4 - remember: in
														// FAT32 every entry is 4 bytes!
	
	DWORD	FATSectorToWrite	= SDFS_VolumeInfo.fat + (FATEntryNumber / SDFS_VolumeInfo.sectorSize);
	
    DWORD 	FATSectorOffset 	= FATEntryNumber & (SDFS_VolumeInfo.sectorSize - 1);  
    

	//------------------------------------------------------------------
    // Check if the appropriate FAT sector is already loaded
    if	(FATSectorToWrite != SDFS_FATCache.CurrentFATSector)
    	{
	    // Cache buffer need to be re-loaded
        if	( SDFS_FATCacheRead(ClusterNumber) == CLUSTER_FAIL_FAT32)
        	{
	        // Failure...
            return CLUSTER_FAIL_FAT32;  
        	}
    	}
    	
	//------------------------------------------------------------------
    // Required FAT sector is in the Cache Buffer - write the value
    // NOTE: We take advantage of the fact that in FAT numeric values
    //		 are stored in the "little endian" format - same as the
    //		 native data addressing in PIC24/32 MCUs
    // The MSB nibble is supposed to be "0" in FAT32. So mask it.
    *((DWORD*)&SDFS_FATCache.Buffer[FATSectorOffset]) = (FATEntry & 0x0FFFFFFF);
	//------------------------------------------------------------------
    // As we updated the FATEntry in the sector we should mark it "DIRTY"
    SDFS_FATCache.IsDirty = TRUE;
	//------------------------------------------------------------------
    return 0;
	}


//************************************************************************************
//  Function:		BYTE SDFS_FATEraseClusterChain (WORD ClusterNumber)
//  Summary:		Erase a chain of clusters
//  Input:			cluster -  The cluster number
//  Return Values:
//    				CE_GOOD 		-  Operation successful
//    				CE_ERASE_FAIL 	- Operation failed
//  Description:
//					This function will parse through a cluster chain starting with 
//					the cluster pointed to by 'cluster' and mark all of the FAT entries 
//					as empty until the end of the chain has been reached or an error 
//					occurs.
//************************************************************************************
CETYPE SDFS_FATEraseClusterChain (DWORD ClusterNumber)
	{
    DWORD	CurrentCluster	= ClusterNumber;
    DWORD	NextCluster		= 0;
	//----------------------------------------------------------------------
    // The first 2 clusters in FAT32 are reserved...
    if	( ClusterNumber < 2)  // Cluster Number can't be "0" and "1"
    	return CE_ERASE_FAIL;
	//----------------------------------------------------------------------
	CETYPE RC = CE_GOOD;  
	  	
	while	(CurrentCluster < EOC_CLUSTER_FAT32)
		{
	    // Get the FAT entry for the Current Cluster
	    if	( (NextCluster = SDFS_FATCacheRead(CurrentCluster)) == CLUSTER_FAIL_FAT32)
	    	{
	        RC = CE_ERASE_FAIL;
	        break;		// Terminate loop...
	     	}
	     
		// Erase (free) Current Cluster
		if	(SDFS_FATCacheWrite(CurrentCluster, CLUSTER_EMPTY) == CLUSTER_FAIL_FAT32)
	    	{
	        RC = CE_ERASE_FAIL;
	        break;		// Terminate loop...
	     	}
		
		// Validate NextCluster value
		if	(
				NextCluster == CLUSTER_EMPTY		// Free cluster cannot be on the chain
													// Also cluster "0" is reserved
			||
				NextCluster == 1					// Cluster "1" is reserved
			||
				NextCluster == BAD_CLUSTER_FAT32	// Bad cluster cannot be on the chain
			)  
			{
			// Invalid FAT32 cluster chain...
	        RC = CE_ERASE_FAIL;
	        break;		// Terminate loop...
			}

	    // Advance to the next cluster in the chain
	    CurrentCluster = NextCluster;
		}	// while status
        	
    SDFS_FATCacheFlush();

    return RC;
	} // Erase cluster chain


















