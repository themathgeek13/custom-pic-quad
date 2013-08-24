#include "SDSPI\SD-SPI.h"		// SD Card Physical Access Layer

#include "FSIO\SDFS.h"

typedef struct
	{
	// The Data sector buffer
	BYTE   	__attribute__ ((aligned(4)))
				Buffer[MEDIA_SECTOR_SIZE];      
	// Variable indicating which FAT sector was read last
	DWORD       LBA;  
	// Status of the Data sector in the Buffer
	BOOL        IsDirty; 
	// content of the Data sector in the Buffer
	BOOL        IsZero; 
	}	__DataCacheEntry;
	
__DataCacheEntry		SDFS_DataCache = { {0} , 0, FALSE, FALSE };

//====================================================================================
// Data Cache Management local helper functions
//====================================================================================
//  Function:		void* _SDFS_DataCacheGetBuffer()
//  Summary:		Return pointer to the internal cache buffer
//  Input:			None
//  Return:
//    				void* : 			Pointer to the internal buffer
//  Description:
//    				The _SDFS_DataCacheGetBuffer function will return pointer to the
//					internal buffer bypassing all cache management!
//					NOTE: this function is to be used ONLY by Volume Management
//						  routines for Volume initialization.
//************************************************************************************
void* _SDFS_DataCacheGetBuffer()
	{
	//------------------------------------------------------------------
    // Return "naked" buffer pointer bypassing cache management!!!
	//------------------------------------------------------------------
	return SDFS_DataCache.Buffer;
    //------------------------------------------------------------------
	} 

//====================================================================================
//  Function:		CETYPE _SDFS_DataCacheLoadSector(DWORD SectorNumber)
//  Summary:		Loads specified sector into the data cache
//  Input:			SectorNumber - Sector number from which to read data
//  Return:
//    				CE_GOOD: 			Requested Sector successfully loaded
//					CE_WRITE_ERROR:		Unrecoverable error flashing DIRTY sector
//					CE_BAD_SECTOR_READ:	Unrecoverable error reading sector
//  Description:
//    				The _SDFS_DataCacheLoadSector(...) function will load into Data 
//					Cache required sector (if it is not there).
//					NOTE: the data sector that is read is stored in the data cache 
//						  buffer. Previous content of the buffer is flashed to disk
//						  if needed.
//************************************************************************************
CETYPE static inline _SDFS_DataCacheLoadSector(DWORD SectorNumber)
	{
	CETYPE	RC = CE_GOOD;
	
	//------------------------------------------------------------------
    // Check if the appropriate data sector is already loaded
	//------------------------------------------------------------------
    if	(SectorNumber == SDFS_DataCache.LBA)
    	return CE_GOOD;	// Nothing to do...
    	
    //--------------------------------------------------
    // Cache buffer need to be re-loaded
    //--------------------------------------------------
    // First, flash existing data cache buffer..
    //--------------------------------------------------
	if 	( (RC = SDFS_DataCacheFlush()) != CE_GOOD )
		return RC;		// Failure...
    //--------------------------------------------------
    // Second, read required sector into cache buffer..
    //--------------------------------------------------
       if	( !SD_SPI_SectorRead (SectorNumber, SDFS_DataCache.Buffer) )
       	{
        // Failure...
           return CE_BAD_SECTOR_READ;  
       	}
    // Success! Set cache buffer Properties and Flags
    SDFS_DataCache.LBA 		= SectorNumber;
	SDFS_DataCache.IsDirty 	= FALSE;
	SDFS_DataCache.IsZero  	= FALSE;
    //------------------------------------------------------------------
	return CE_GOOD;
	} 

	
		
//====================================================================================
// Data Cache Management interface functions
//====================================================================================
//  Function:		CETYPE SDFS_DataCacheFlush()
//  Summary:		Flashes to disk current Data Cache Buffer
//  Input:			None
//  Return:
//    				CE_GOOD			- Success
//					CE_WRITE_ERROR	- Unrecoverable error writing to disk
//  Description:
//    				The SDFS_DataCacheFlush() function will flash to disk current 
//					cache Buffer if a) it contains valid sector, and b) the sector
//					is DIRTY.
//************************************************************************************
CETYPE SDFS_DataCacheFlush()
	{
	if 	(
			SDFS_DataCache.LBA 		== 0		// Sector "0" cannot be valid for data
		||										// operations.
			SDFS_DataCache.IsDirty	== FALSE	 
		)
		return CE_GOOD;	// Nothing to do - Success!
	//----------------------------------------------------------
	SDFS_DataCache.IsDirty = FALSE;
	//----------------------------------------------------------
	if ( !SD_SPI_SectorWrite(SDFS_DataCache.LBA, SDFS_DataCache.Buffer, FALSE) )
			return CE_WRITE_ERROR;
	//----------------------------------------------------------
	return CE_GOOD;	// Success!
	}	
		
//************************************************************************************
//  Function:		CETYPE SDFS_DataCacheRead (DWORD SectorNumber, WORD Offset,
//											  WORD	Length, void * pDest)
//  Summary:		Reads data chunk from the specified sector into the Dest
//  Input:			SectorNumber - Sector number from which to read data
//					Offset 		 - Data chunk offset within sector
//					Length		 - Data Chunk length
//					pDest		 - Pointer to the destination buffer for
//								   the data chunk
//  Return:
//    				CE_GOOD: 			Requested data chunk successfully loaded
//					CE_WRITE_ERROR:		Unrecoverable error flashing DIRTY sector
//					CE_BAD_SECTOR_READ:	Unrecoverable error reading sector
//					CE_INVALID_ARGUMENT: Offset and/or Length are invalid
//  Description:
//    				The SDFS_DataCacheRead function will load into Data Cache 
//					required sector (if it is not there) and retrieve specified
//					data chunk from it.
//					NOTE: the data sector that is read is stored in the data cache 
//						  buffer. Previous content of the buffer is flashed to disk
//						  if needed.
//************************************************************************************
CETYPE SDFS_DataCacheRead (DWORD SectorNumber, WORD Offset,
						  WORD	Length, void * pDest)
	{
	//------------------------------------------------------------------
    // Verify parameters
	//------------------------------------------------------------------
	if ( Offset + Length > MEDIA_SECTOR_SIZE )
		return CE_INVALID_ARGUMENT;
	if ( NULL == pDest )
		return CE_INVALID_ARGUMENT;
	//------------------------------------------------------------------
	
	CETYPE	RC;
		
	//------------------------------------------------------------------
    // Make sure the appropriate data sector is loaded into the buffer
	//------------------------------------------------------------------
    if	( CE_GOOD != (RC = _SDFS_DataCacheLoadSector(SectorNumber)) )
    	return RC;
    	
	//------------------------------------------------------------------
    // Required data sector is in the Cache Buffer - retrieve the chunk
	//------------------------------------------------------------------
    memcpy(pDest, &SDFS_DataCache.Buffer[Offset], Length);
    //------------------------------------------------------------------
	return CE_GOOD;
	}   

//************************************************************************************
//  Function:		CETYPE SDFS_DataCacheWrite(DWORD SectorNumber, void * pSource,
//											  WORD Offset, WORD	Length )
//  Summary:		Writes data chunk from the Source into specified sector on disk
//  Input:			SectorNumber - Sector number from which to read data
//					pSource		 - Pointer to the source buffer for the data chunk
//					Offset 		 - Data chunk offset within sector
//					Length		 - Data Chunk length							   
//  Return:
//    				CE_GOOD: 			Provided data chunk successfully stored
//					CE_WRITE_ERROR:		Unrecoverable error flashing DIRTY sector
//					CE_BAD_SECTOR_READ:	Unrecoverable error reading sector
//					CE_INVALID_ARGUMENT: Offset and/or Length are invalid
//  Description:
//    				The SDFS_DataCacheWrite function will load into Data Cache 
//					required sector (if it is not there) and store specified
//					data chunk in it.
//					NOTE: the data sector that is read is stored in the data cache 
//						  buffer. Previous content of the buffer is flashed to disk
//						  if needed.
//************************************************************************************
CETYPE SDFS_DataCacheWrite (DWORD SectorNumber, void * pSource,
						   WORD Offset, WORD	Length )
	{
	//------------------------------------------------------------------
    // Verify parameters
	//------------------------------------------------------------------
	if ( Offset + Length > MEDIA_SECTOR_SIZE )
		return CE_INVALID_ARGUMENT;
	if ( NULL == pSource )
		return CE_INVALID_ARGUMENT;
	//------------------------------------------------------------------
		
	//------------------------------------------------------------------
    // Make sure the appropriate data sector is loaded into the buffer
	//------------------------------------------------------------------
	CETYPE	RC;
    if	( CE_GOOD != (RC = _SDFS_DataCacheLoadSector(SectorNumber)) )
    	return RC;
    	
	//------------------------------------------------------------------
    // Required data sector is in the Cache Buffer - store the chunk
	//------------------------------------------------------------------
	SDFS_DataCache.IsDirty = TRUE;
    memcpy(&SDFS_DataCache.Buffer[Offset], pSource, Length);
    //------------------------------------------------------------------
	return CE_GOOD;
	}


//************************************************************************************
//  Function:		CETYPE SDFS_DataCacheSectorSet(DWORD SectorNumber)
//  Summary:		Zeroe-out cache data buffer and points it to a sector on disk
//  Input:			SectorNumber - Sector number from which to read data
//  Return:
//    				CE_GOOD: 			Provided data chunk successfully stored
//					CE_WRITE_ERROR:		Unrecoverable error flashing DIRTY sector
//  Description:
//    				The SDFS_DataCacheSectorSet function will zero out Data Cache 
//					buffer and point it to the specified sector on disk without
//					actually reading sector data from disk (overwrites sector).
//					NOTE:Previous content of the buffer is flashed to disk if needed.
//************************************************************************************
CETYPE SDFS_DataCacheSectorZeroOut (DWORD SectorNumber)
	{
	CETYPE RC;
    //--------------------------------------------------
    // First, flash existing data cache buffer...
    //--------------------------------------------------
	if 	( (RC = SDFS_DataCacheFlush()) != CE_GOOD )
		return RC;		// Failure...
		
    //--------------------------------------------------
    // Second, zero out data cache buffer...
    //--------------------------------------------------
	if (FALSE == SDFS_DataCache.IsZero)
		// Zero-out buffer
		memset(SDFS_DataCache.Buffer, 0x00, MEDIA_SECTOR_SIZE);
    	
	//------------------------------------------------------------------
    // Buffer is zeroed-out, set Properties and Flags
	//------------------------------------------------------------------
	SDFS_DataCache.LBA 		= SectorNumber;		
	SDFS_DataCache.IsDirty 	= TRUE;
	SDFS_DataCache.IsZero 	= TRUE;
    //------------------------------------------------------------------
	return CE_GOOD;	// Success!
	}




