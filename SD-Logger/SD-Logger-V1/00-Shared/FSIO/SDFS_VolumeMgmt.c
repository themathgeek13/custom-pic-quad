#include "SDSPI\SD-SPI.h"		// SD Card Physical Access Layer

#include "FSIO\SDFS.h"
#include "FSIO\SDFS_VolumeMgmt.h"


//====================================================================================
// Prototype for a Data Cache Management helper function to be used ONLY by the
// Volume Management routines for Volume initialization!!!
//====================================================================================
void* _SDFS_DataCacheGetBuffer();


//************************************************************************************
//  Function:		CETYPE SDFS_MountVolume()
//  Summary:		Initialies the device and loads MBR and boot sector information
//  Conditions:		None
//  Input:			None
//  Return Values:
//    				CE_GOOD 					- Disk mounted
//    				CE_INIT_ERROR 				- Initialization error has occured
//    				CE_UNSUPPORTED_SECTOR_SIZE 	- Media sector size bigger than
//                								  MEDIA_SECTOR_SIZE as defined in 
//												  FSconfig.h.
//  Description:
//    				This function will use the function SD_SPI_MediaInitialize
//    				to initialize the device.
//					It then attempts to load the master boot record with the
//    				SDFS_LoadMBR function and the boot sector with the SDFS_LoadBootSector 
//					function. These two functions will be used to initialize a global 
//					SDFS_VolumeInfo structure that will be used when accessing file 
//					information in the future.
//************************************************************************************
CETYPE SDFS_MountVolume()
	{
    CETYPE	RC	= CE_GOOD;	
 	//--------------------------------------------------------
	SDFS_VolumeInfo.firsts 		= 0;			// Assume there is no MBR
	SDFS_VolumeInfo.sectorCnt	= 0xFFFFFFFF;	// Set number of sectors to maximum
 	//--------------------------------------------------------

 	//--------------------------------------------------------
    // Initialize the device and check initialization status
 	//--------------------------------------------------------
    if (SD_SPI_MediaInitialize() != MEDIA_NO_ERROR)
		return CE_INIT_ERROR;
 	//--------------------------------------------------------

 	//--------------------------------------------------------
	// Set Media Sector Size - comes from the Physical Layer	
 	//--------------------------------------------------------
	SDFS_VolumeInfo.sectorSize = MEDIA_SECTOR_SIZE;
 	//--------------------------------------------------------
	
 	//--------------------------------------------------------
	// Load the Master Boot Record (partition)
 	//--------------------------------------------------------
	if( (RC = SDFS_LoadMBR()) != CE_GOOD)
		return RC;
		
 	//--------------------------------------------------------
	// Now load the boot sector and initialize Volume
 	//--------------------------------------------------------
    return SDFS_LoadBootSector();
	} // -- mount



//************************************************************************************
//  Function:		CETYPE SDFS_LoadMBR ()
//  Summary:		Loads the MBR and extracts necessary information
//  Conditions:		None
//  Input:			None
//  Return Values:
//    				CE_GOOD 			- MBR loaded successfully
//    				CE_BAD_SECTOR_READ 	- A bad read occured of a sector
//    				CE_BAD_PARTITION 	- The boot record is bad
//  Side Effects:	
//					Loads SDFS_VolumeInfo.firsts with the address of the first sector
//					of selected partition.
//  Description:
//    				The SDFS_LoadMBR function will use the function SD_SPI_SectorRead
//					to read the 0 sector from the device.
//					If a valid boot signature is obtained, this function
//    				will compare fields in that cached sector to the values that
//    				would be present if that sector was a boot sector.  If all of
//    				those values match, it will be assumed that the device does not
//    				have a master boot record and the 0 sector is actually the boot
//    				sector.  Otherwise, data about the partition and the actual
//    				location of the boot sector will be loaded from the MBR into
//    				the global SDFS_VolumeInfo structure.
//************************************************************************************
CETYPE SDFS_LoadMBR ()
	{
	//--------------------------------------------------------------
	// Retrieve address of the Data Cache Management internal buffer
	//--------------------------------------------------------------
	void *	BufferAddr	= _SDFS_DataCacheGetBuffer();
	//--------------------------------------------------------------
   	__MBR* 	pMBR		= NULL;
    __BS* 	pBootSec	= NULL;
   
 
    // Load the first sector from the drive...
    if ( SD_SPI_SectorRead( 0, BufferAddr) != TRUE)
        return CE_BAD_SECTOR_READ;
    	
	pMBR = (__MBR*)BufferAddr;	// Overaly MBR layout over the buffer	
	//-------------------------------------------------------------------------
    // Verify that this sector has a valid signature
    // NOTE: This "signature" is required for both MBR and
    //		 Boot Sector.
	//-------------------------------------------------------------------------
    if (	(pMBR->Signature0 != FAT_GOOD_SIGN_0)
         ||	(pMBR->Signature1 != FAT_GOOD_SIGN_1)
        )
		return CE_NOT_FORMATTED;
	//-------------------------------------------------------------------------


	//-------------------------------------------------------------------------
	// Make sure that the disk being mounted does have an MBR by confirming
	// that the sector at adress of 0x00 is not a boot sector, which may happen
	// if there is no MBR on the drive.
	//-------------------------------------------------------------------------
    // Assume that the just read sector is a Boot Sector (no MBR)
    pBootSec = (__BS*) BufferAddr;	// Overaly Boot Sector layout over the buffer
    if(		( pBootSec->BS_jmpBoot.array[0] == 0xE9 ) 
    	|| 	((pBootSec->BS_jmpBoot.array[0] == 0xEB) && (pBootSec->BS_jmpBoot.array[2] == 0x90))	)
     	{
	    // JUMP command is in the correct format, we may proceed with
	    // further checks.
	    //------------------------------------------------------------
     	// Technically, the OEM name is not for indication
     	// The alternative is to read the CIS from attribute
     	// memory.  See the PCMCIA metaformat for more details
        if (	(pBootSec->FAT.FAT_16.BS_FSType[0] 	== 'F') 
        	&&
        		(pBootSec->FAT.FAT_16.BS_FSType[1] 	== 'A') 
        	&&
        		(pBootSec->FAT.FAT_16.BS_FSType[2] 	== 'T') 
        	&& 
        		(pBootSec->FAT.FAT_16.BS_BootSig   	== 0x29))
         	{
	        // Looks like this is FAT16 boot sector...
            return CE_GOOD;
         	}

        if (	(pBootSec->FAT.FAT_32.BS_FSType[0] 	== 'F') 
        	&&
        		(pBootSec->FAT.FAT_32.BS_FSType[1] 	== 'A') 
        	&&
        		(pBootSec->FAT.FAT_32.BS_FSType[2] 	== 'T') 
        	&& 
        		(pBootSec->FAT.FAT_32.BS_BootSig   	== 0x29))
         	{
	        // Looks like this is FAT32 boot sector...
            return CE_GOOD;
         	}
    	}
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
    // Sector 0 from the drive does not look like a Boot Sector,
    // so we have to assume that it is MBR...
	// Let's try to find first VALID partition...
	//-------------------------------------------------------------------------
	// Select first partition
    __PTE* partitionEntry = &(pMBR->Partition0);

	int i;
    for(i = 0; i < 4; i++)
    	{                

        // Check if the partition type is acceptable
        switch (partitionEntry->PTE_FSDesc)
        	{
	        // FAT16 acceptable codes (not supported!)
        	//	case 0x04:
            //	case 0x06:
            //	case 0x0E:
            
	        // FAT32 acceptable codes
            case 0x0B:
            case 0x0C:
                // One of the acceptable partition codes...
		        // Get the 32 bit offset to the start of this partition
		        SDFS_VolumeInfo.firsts 	= partitionEntry->PTE_FrstSect;
		        // Get the 32 bit size of this partition
		        SDFS_VolumeInfo.sectorCnt = partitionEntry->PTE_NumSect;
		        //----------------------------------------------
                return CE_GOOD;
                
            default:
                break;

        	} // switch

        // If we are here, we didn't find a matching partition. 
        // We should increment to the next partition table entry 
        partitionEntry++;
    	}
  
    return CE_UNSUPPORTED_FS;
	}// -- SDFS_LoadMBR


//************************************************************************************
//  Function:		CETYPE SDFS_LoadBootSector()
//  Summary:		Load the boot sector and extract the necessary information
//  Conditions:		None
//  Input:			None
//  Return Values:
//    				CE_GOOD 					- Boot sector loaded
//    				CE_BAD_SECTOR_READ 			- A bad read occured of a sector
//    				CE_NOT_FORMATTED 			- The disk is of an unsupported format
//    				CE_UNSUPPORTED_SECTOR_SIZE	- The sector size is not supported
//  Side Effects:
//    				None
//  Description:
//    				SDFS_LoadBootSector will use the function SD_SPI_SectorRead to load 
//					the boot sector, whose location was obtained by a previous call 
//					to SDFS_LoadMBR.
//					If the boot sector is loaded successfully, partition information 
//					will be calcualted from it and copied into the global DISK 
//					structure.
//	NOTE:			FAT32 provides for a back-up boot sector in case the primary one
//					is corrupted. However identification of the type of FS (FAT32 or
//					FAT16) is heavily dependent on the values obtained from the boot
//					sector; moreover, the address of the back-up boot sector is also
//					stored in the primary one (BPB_BkBPB, typically set to "6"). Thus
//					this feature is primarily useful for the dedicated disk repair
//					utilities and is ignored in this code.
//************************************************************************************
CETYPE SDFS_LoadBootSector()
	{
	//--------------------------------------------------------------
	// Retrieve address of the Data Cache Management internal buffer
	//--------------------------------------------------------------
	void *	BufferAddr	= _SDFS_DataCacheGetBuffer();
	//--------------------------------------------------------------
    __BS*     	pBootSec	= NULL;
    
	//--------------------------------------------------------------------------
    // Load the Boot sector...
    // SDFS_VolumeInfo.firsts is either initialized to 0 or pre-loaded
    // with the address of Boot Sector for one of the FAT 
    // partitions from MBR.
	//--------------------------------------------------------------------------
    if ( SD_SPI_SectorRead( SDFS_VolumeInfo.firsts, BufferAddr) != TRUE)
        return CE_BAD_SECTOR_READ;
	//--------------------------------------------------------------------------
        
    pBootSec = (__BS*) BufferAddr;	// Overaly Boot Sector layout over the buffer


	//--------------------------------------------------------------------------
	// Verify that the Boot Sector has a valid signature
	//--------------------------------------------------------------------------
	if	(	(pBootSec->Signature0 != FAT_GOOD_SIGN_0)
	    ||	(pBootSec->Signature1 != FAT_GOOD_SIGN_1)
	   	)
	    return CE_NOT_FORMATTED;

	//--------------------------------------------------------------------------
	// Verify that the Boot Sector has a valid JUMP command
	//--------------------------------------------------------------------------
    if	(	( pBootSec->BS_jmpBoot.array[0] != 0xE9 ) 
    	&& 	( pBootSec->BS_jmpBoot.array[0] != 0xEB  ||  pBootSec->BS_jmpBoot.array[2] != 0x90 )
    	)
	    return CE_NOT_FORMATTED;


	//--------------------------------------------------------------------------
	// Verify that the Sector Size from the Boot Sector matches the one
	// obtained from the media
	//--------------------------------------------------------------------------
	if( SDFS_VolumeInfo.sectorSize != pBootSec->BPB_BytsPerSec )
		return CE_NOT_FORMATTED;	// Or maybe CE_UNSUPPORTED_SECTOR_SIZE?
	
	//--------------------------------------------------------------------------
	// Obtain Sector Count from the Boot Sector and confirm that it does not
	// exceed one from the Partition Table (or the maximum initialization value)
	//--------------------------------------------------------------------------
	DWORD	TotSec = pBootSec->BPB_TotSec16 != 0 ?
							pBootSec->BPB_TotSec16
						:	pBootSec->BPB_TotSec32;
	//------------------------------------
	if( SDFS_VolumeInfo.sectorCnt < TotSec )
	    return CE_NOT_FORMATTED;
	//------------------------------------
	SDFS_VolumeInfo.sectorCnt = TotSec;
	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	// Determine the type of the File system
	//--------------------------------------------------------------------------
	
	// Load the count of FAT tables
	SDFS_VolumeInfo.fatCnt    = pBootSec->BPB_NumFATs;
	
	// Load the size of the FATs
	SDFS_VolumeInfo.fatsize = pBootSec->BPB_FATSz16 != 0 ?
								pBootSec->BPB_FATSz16
							:	pBootSec->FAT.FAT_32.BPB_FATSz32;
							
	
	// Calculate the number of sectors in the root (will be 0 for FAT32)
	DWORD	RootDirSectors = 	(		(pBootSec->BPB_RootEntCnt16 * NUMBER_OF_BYTES_IN_DIR_ENTRY) 
									+ 	(pBootSec->BPB_BytsPerSec - 1)
								) / pBootSec->BPB_BytsPerSec;
						
	// Calculate the number of data sectors on the card
	DWORD	DataSec = TotSec 
					- 	(	pBootSec->BPB_RsvdSecCnt 
						+ 	(SDFS_VolumeInfo.fatCnt * SDFS_VolumeInfo.fatsize)  
						+ 	RootDirSectors
						);
	
	// Load the count of sectors per cluster
	SDFS_VolumeInfo.SecPerClus = pBootSec->BPB_SecPerClus;
	
	// Calculate the maximum number of clusters on the card
	SDFS_VolumeInfo.clusterCnt = DataSec / SDFS_VolumeInfo.SecPerClus;

	// Calculate the highest FAT entry index on the card
	// NOTE: The maximum valid cluster number (FAT entry
	// index) for the volume is clusterCnt + 1, and the
	// “count of clusters including the two reserved clusters”
	// is clusterCnt + 2.	
	SDFS_VolumeInfo.clusterMax = SDFS_VolumeInfo.clusterCnt + 1;

	// Load the sector number of the first FAT sector
	SDFS_VolumeInfo.fat = SDFS_VolumeInfo.firsts + pBootSec->BPB_RsvdSecCnt;
	

	// Now we may determine the file system type based on the number of clusters in the Data section
	if(SDFS_VolumeInfo.clusterCnt < 4085)
		// Should be FAT12, which we do not support...
	    return CE_UNSUPPORTED_FS;

	if(SDFS_VolumeInfo.clusterCnt < 65525)
		// Should be FAT16, which we do not support...
	    return CE_UNSUPPORTED_FS;

	// FAT32 - the only one supported FS
	SDFS_VolumeInfo.rootClsN 	= pBootSec->FAT.FAT_32.BPB_RootClus;
	// Calculate the location of the Data sector (for FAT32 this coincides with the Root directory)
	SDFS_VolumeInfo.data 		= SDFS_VolumeInfo.fat 
								+ (DWORD)(SDFS_VolumeInfo.fatCnt * (DWORD)SDFS_VolumeInfo.fatsize);
	
	//--------------------------------------------------------------------------
	// Verify Boot Sector structure
	//--------------------------------------------------------------------------
	// Confirm some of the fields specific to FAT32
	//Check for possible errors in the formatting
	if	(  	pBootSec->BPB_TotSec16					!= 0
	
	    || pBootSec->FAT.FAT_32.BS_Reserved[0] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[1] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[2] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[3] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[4] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[5] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[6] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[7] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[8] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[9] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[10] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_Reserved[11] 	!= 0
	    || pBootSec->FAT.FAT_32.BS_BootSig		 	!= 0x29
	  	)
	   return CE_NOT_FORMATTED;


    return CE_GOOD;
	}






