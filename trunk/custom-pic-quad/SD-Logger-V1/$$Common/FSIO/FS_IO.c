#include "SDSPI\SD-SPI.h"		// SD Card Physical Access Layer

#include "FSIO\SDFS.h"


//*************************************************************************
//  Function:		CETYPE	FS_Read(FSFILE* filePtr, void* dest, 
//									WORD length, WORD* ReadCnt)
//  Summary:		Read data from a file
//  Input:
//    				filePtr - File Object pointer
//    				dest 	- Pointer to the destination buffer
//    				length	- Number of bytes to be read
//    				ReadCnt - Pointer to variable receiving the actual
//							  number of bytes read
//  Return:
//    				CE_GOOD - required number of bytes was read
//					CE_EOF	- End-of-file was reached before required
//							  number of bytes was read
//					CETYPE	- other error codes for possible conditions
//  Description:
//    				The FS_FileRead function will read data from the specified file.
//					First, the appropriate sector of the file is loaded.  Then, 
//					data is read into the specified buffer until the specified 
//					number of bytes have been read or EOF is reached
//*************************************************************************
CETYPE		FS_Read(FSFILE* filePtr, void* dest, WORD length, WORD* ReadCnt)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
    if (dest == NULL)
        return CE_INVALID_ARGUMENT;
    // Check if length is valid	
    if (length == 0)
        return CE_INVALID_ARGUMENT;
	//-----------------------------------------------------------------
	DWORD   LBA;
 	BYTE*	ptrTo		= (BYTE*)dest;
 	WORD	ChunkSize;
 	CETYPE	RC;
	//-----------------------------------------------------------------
 	// Reset "ReadCnt" to 0
 	(*ReadCnt) = 0;
	//-----------------------------------------------------------------
    	
    // Read data from the file
    //{
	//------------------------------------------------------------	
    // Loop while reading bytes, exit loop if:
    //	* All bytes are read
    //	* Error encountered
	//------------------------------------------------------------	
 	while (length > 0)
		{
        //----------------------------------------------------
        // Make sure we have defined a place to read from
        //----------------------------------------------------
		//{
        if (filePtr->fileCrntSecPos == SDFS_VolumeInfo.sectorSize)
        	{
	        //----------------------------------------------------
	        // Current sector is read to the end...
	        //----------------------------------------------------
	        // NOTE: fileCrntSec is a 0-based counter (index)
	        //----------------------------------------------------
           	if (filePtr->fileCrntSec == SDFS_VolumeInfo.SecPerClus - 1)
            	{
	 			//----------------------------------------------------
	 			// Current cluster is exhausted - move to the next one
				//----------------------------------------------------
				if ( CE_GOOD != (RC = SDFS_ClusterGetNext(filePtr)) )
					// Bad luck - no cluster to advance to!
	                return RC;
            	}
            else
            	{
	            // It is safe to move to the next sector in the current cluster
	            filePtr->fileCrntSec++;		    // move to the next sector
	            filePtr->fileCrntSecPos = 0;	// reset position
	            }
	        //----------------------------------------------------
         	}   	
		//}
		//-----------------------------------------------------------------   
	    LBA	=	// First, get the LBA of the first sector of the cluster
	    	 	SDFS_FATClusterToLBA(filePtr->fileCrntCls)
				// And then add the sector number in the cluster to it
	  		+ 	filePtr->fileCrntSec;	
		//-----------------------------------------------------------------   
		ChunkSize = length <= SDFS_VolumeInfo.sectorSize - filePtr->fileCrntSecPos ? 
							  length 
							: SDFS_VolumeInfo.sectorSize - filePtr->fileCrntSecPos;
		// Verify that we do not read past the EOF
		if 	(	// FileSize is not being used for directories...
				(filePtr->dirFileEntry.DIR_Attr & ATTR_DIRECTORY) != ATTR_DIRECTORY
			&&
				filePtr->fileSeek + ChunkSize > filePtr->dirFileEntry.DIR_FileSize
			)
			ChunkSize = filePtr->dirFileEntry.DIR_FileSize - filePtr->fileSeek;
		if (ChunkSize <= 0)
			return CE_EOF;
		//-----------------------------------------------------------------   
		if	(CE_GOOD != (RC = SDFS_DataCacheRead (LBA, filePtr->fileCrntSecPos, ChunkSize, ptrTo)) )	
			return RC;					
		//-----------------------------------------------------------------   
		length	 	-= ChunkSize;
		ptrTo		+= ChunkSize;
		(*ReadCnt)	+= ChunkSize;	// Accumulate number of read bytes
		//----------------------
		filePtr->fileCrntSecPos	+= ChunkSize;
		filePtr->fileSeek		+= ChunkSize;
		} 
	//-----------------------------------
    return CE_GOOD;
	} // fread


//*********************************************************************************
//  Function:		CETYPE FS_Write(FSFILE* filePtr, const void* origin, WORD length)
//  Summary:		Write data to a file
//  Conditions:		File opened in FS_CREATE_NEW, FS_APPEND, or FS_OPEN_EXISTING mode
//  Input:
//    				filePtr	-	Pointer to file structure
//    				origin 	-	Pointer to source buffer
//    				length 	-    Length of the source buffer (data to write)
//  Return:
//    				CETYPE 	- 	Error code (expected: CE_GOOD)
//  Description:
//    				The FS_Write function will write data to a file. First, the sector
//					that corresponds to the current position in the file will be loaded 
//					(if it hasn't already been cached in the global data buffer). Data 
//					will then be written to the device from the specified buffer until 
//					the specified amount has been written.    
//					If the end of a cluster is reached, the next cluster will be
// 					loaded, unless the end-of-file flag for the specified file has been 
//					set. If it has, a new cluster will be allocated to the file. Finally, 
//					the new position and filesize will be stored in the FSFILE object.
//*********************************************************************************
CETYPE  FS_Write(FSFILE* filePtr, const void* origin, WORD length )
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    // Check if the file attributes allow write
    if( (filePtr->dirFileEntry.DIR_Attr & ATTR_READONLY) == ATTR_READONLY )
        return CE_READONLY;
    // Check if pointer is valid	
    if (origin == NULL)
        return CE_INVALID_ARGUMENT;
    // Check if length is valid	
    if (length == 0)
        return CE_INVALID_ARGUMENT;
	//-----------------------------------------------------------------
 
	DWORD   LBA;
 	BYTE*	ptrFrom	= (BYTE*)origin;
 	WORD	ChunkSize;
	CETYPE 	RC;
    	
    // Write data to the file
    //{
	//------------------------------------------------------------	
    // Loop while writing bytes, exit loop if:
    //	* All bytes are written
    //	* Error encountered
	//------------------------------------------------------------	
 	while (length > 0)
		{
        //----------------------------------------------------
        // Make sure we have defined a place to write to
        //----------------------------------------------------
		//{
        if (filePtr->fileCrntSecPos == SDFS_VolumeInfo.sectorSize)
        	{
	        //----------------------------------------------------
	        // Current sector is filled in...
	        //----------------------------------------------------
	        // NOTE: fileCrntSec is a 0-based counter (index)
	        //----------------------------------------------------
           	if (filePtr->fileCrntSec == SDFS_VolumeInfo.SecPerClus - 1)
            	{
	 			//----------------------------------------------------
	 			// Current cluster is exhausted - move to the next one
				//----------------------------------------------------
				RC = SDFS_ClusterGetNext(filePtr);
				if ( CE_EOF == RC )
					// Oops! Reached end-of-file - try to add another cluster
					RC = SDFS_ClusterAllocateNew(filePtr);
				//----------------------------------------------------
				if ( CE_GOOD != RC )
					// Bad luck - no cluster to advance to!
	                return RC;
            	}
            else
            	{
	            // It is safe to move to the next sector in the current cluster
	            filePtr->fileCrntSec++;		    // move to the next sector
	            filePtr->fileCrntSecPos = 0;	// reset position
	            }
	        //----------------------------------------------------
         	}   	
		//}
		//-----------------------------------------------------------------   
	    LBA	= SDFS_FATClusterToLBA( filePtr->fileCrntCls)
	    			  		+ filePtr->fileCrntSec;	// add the sector number to it
		ChunkSize = length <= SDFS_VolumeInfo.sectorSize - filePtr->fileCrntSecPos ? 
							  length 
							: SDFS_VolumeInfo.sectorSize - filePtr->fileCrntSecPos;
		//-----------------------------------------------------------------   
		if	(CE_GOOD != (RC = SDFS_DataCacheWrite (LBA, ptrFrom, filePtr->fileCrntSecPos, ChunkSize )))	
			return RC;					
		//-----------------------------------------------------------------   
		length 	-= ChunkSize;
		ptrFrom	+= ChunkSize;
		//----------------------
		filePtr->fileCrntSecPos	+= ChunkSize;
		filePtr->fileSeek		+= ChunkSize;
		if (filePtr->dirFileEntry.DIR_FileSize < filePtr->fileSeek)
			filePtr->dirFileEntry.DIR_FileSize = filePtr->fileSeek;
		} 

	//-----------------------------------
    return CE_GOOD;
	} // write
//=================================================================================


//*********************************************************************************
//  Function:		CETYPE FS_WriteSector(FSFILE* filePtr, const void* origin)
//  Summary:		Write data to a file one sector at a time bypassing CACHE
//  Conditions:		File opened in FS_CREATE_NEW, FS_APPEND, or FS_OPEN_EXISTING mode
//  Input:
//    				filePtr	-	Pointer to file structure
//    				origin 	-	Pointer to source buffer
//  Return:
//    				CETYPE 	- 	Error code (expected: CE_GOOD)
//  Description:
//    				The FS_WriteSector function will write data to a file one sector 
//					at a time bypassing CACHE. The length of the data buffer pointed
//					to by "orogin" expected to be equal to the size of the sector.    
//					If the end of a cluster is reached, the next cluster will be
// 					loaded, unless the end-of-file flag for the specified file has been 
//					set. If it has, a new cluster will be allocated to the file. Finally, 
//					the new position and filesize will be stored in the FSFILE object.
//*********************************************************************************
CETYPE  FS_WriteSector(FSFILE* filePtr, const void* origin)
	{
 	//----------------------------------------------------------------
	// Validate conditions and parameters
 	//----------------------------------------------------------------
 	if (!SDFS_InitStatus)
 		return CE_NOT_INIT;		// FS is not initialized!
 	if (NULL == filePtr)
 		return CE_INVALID_ARGUMENT;		
 	//----------------------------------------------------------------
    // Check if the file attributes allow write
    if( (filePtr->dirFileEntry.DIR_Attr & ATTR_READONLY) == ATTR_READONLY )
        return CE_READONLY;
    // Check if pointer is valid	
    if (origin == NULL)
        return CE_INVALID_ARGUMENT;
	//-----------------------------------------------------------------
 
	DWORD   LBA;
 	BYTE*	ptrFrom	= (BYTE*)origin;
 	WORD	ChunkSize;
	CETYPE 	RC;
    	
	//----------------------------------------------------
	// Make sure we have defined a place to write to
	//----------------------------------------------------
	if (0 != filePtr->fileCrntSecPos)
		// For Sector writes we always start at the EMPTY
		// sector, so the rest of the current sector will
		// be skipped...
		{
		// NOTE: fileCrntSec is a 0-based counter (index)
		//----------------------------------------------------
	  	if (filePtr->fileCrntSec == SDFS_VolumeInfo.SecPerClus - 1)
		   	{
			//----------------------------------------------------
			// Current cluster is exhausted - move to the next one
			//----------------------------------------------------
			RC = SDFS_ClusterGetNext(filePtr);
			if ( CE_EOF == RC )
			// Oops! Reached end-of-file - try to add another cluster
			RC = SDFS_ClusterAllocateNew(filePtr);
			//----------------------------------------------------
			if ( CE_GOOD != RC )
			// Bad luck - no cluster to advance to!
			        return RC;
		   	}
		else
		   	{
		    // It is safe to move to the next sector in the current cluster
		    filePtr->fileCrntSec++;		    // move to the next sector
		    filePtr->fileCrntSecPos = 0;	// reset position
		    }
		}
	//-----------------------------------------------------------------   
    LBA	= SDFS_FATClusterToLBA( filePtr->fileCrntCls)
    			  		+ filePtr->fileCrntSec;	// add the sector number to it
	ChunkSize = SDFS_VolumeInfo.sectorSize;
	//-----------------------------------------------------------------   
	if ( !SD_SPI_SectorWrite(LBA, ptrFrom, FALSE) )
			return CE_WRITE_ERROR;
	//-----------------------------------------------------------------   
	filePtr->fileCrntSecPos	+= ChunkSize;
	filePtr->fileSeek		+= ChunkSize;
	if (filePtr->dirFileEntry.DIR_FileSize < filePtr->fileSeek)
		filePtr->dirFileEntry.DIR_FileSize = filePtr->fileSeek; 
	//-----------------------------------
    return CE_GOOD;
	} // write
//=================================================================================


















