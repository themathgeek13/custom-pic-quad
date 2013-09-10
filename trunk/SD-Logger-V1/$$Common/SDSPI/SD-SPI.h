#include "system.h"
#include "stddef.h"

#ifndef __SDSPI_H
#define __SDSPI_H
//===============================================================================

//===============================================================================
// Media specifications
//===============================================================================
// The MEDIA_SECTOR_SIZE macro will define the size of a sector on the FAT file
// system. According to FAT specification this value must equal to 512, 1024,
// 2048, or 4096 bytes. However SD (SDHX, SDXC) only support sector size of 512
// bytes so for this application we fix MEDIA_SECTOR_SIZE at 512 bytes.
#define MEDIA_SECTOR_SIZE 		512
//===============================================================================


//*****************************************************************************
// Public Parameter Prototypes                         
//*****************************************************************************
// Description: Media status error codes
//------------------------------------------------------------------------
typedef enum 
	{
    MEDIA_NO_ERROR,                     // No errors
    MEDIA_NOT_PRESENT,					// No media in the socket
    MEDIA_CANNOT_INITIALIZE             // Cannot initialize media
	} MEDIA_STATUS;                


//*****************************************************************************
// Public Interface (API) Function Prototypes                         
//*****************************************************************************
MEDIA_STATUS		SD_SPI_MediaInitialize(void);

MEDIA_STATUS		SD_SPI_ReadStatus(void);
WORD 				SD_SPI_ReadSectorSize(void);
DWORD 				SD_SPI_ReadCapacity(void);

BYTE 				SD_SPI_SectorRead(DWORD sector_addr, BYTE* buffer);
BYTE 				SD_SPI_SectorWrite(DWORD sector_addr, BYTE* buffer, BYTE allowWriteToZero);

void 				SD_SPI_ShutdownMedia(void);
//===============================================================================
#endif			// #ifndef __SDSPI_H
