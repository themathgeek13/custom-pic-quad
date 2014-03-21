#include "system.h"

#ifndef __SD_SPI_Local_Defines_H
#define __SD_SPI_Local_Defines_H
//===============================================================================


//*******************************************************************************
// Defines and constants                 
//*******************************************************************************

#define INPUT   1
#define OUTPUT  0


//-------------------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------------------
// Bit mask to AND with the write token response
// byte from the media, to clear the don't care bits.
#define WRITE_RESPONSE_TOKEN_MASK   0x1F  	
//-------------------------------------------------------------------------------
											
//-------------------------------------------------------------------------------
// Desription: Media Response Delay Timeouts 
//-------------------------------------------------------------------------------
#define NCR_TIMEOUT     (WORD)20        // Byte times before command response is expected (must be at least 8)


//-------------------------------------------------------------------------------
// The SDMMC Control and Status codes
//-------------------------------------------------------------------------------
// Description: This macro represents an SD card start single data block token 
//				(used for single block writes)
//-------------------------------------------------------------------------------
#define DATA_START_TOKEN            	0xFE
//-------------------------------------------------------------------------------
// Description: This macro represents an SD card data accepted token
//-------------------------------------------------------------------------------
#define DATA_ACCEPTED               	0x05
//-------------------------------------------------------------------------------
// Description: This macro represents a floating SPI bus condition
//-------------------------------------------------------------------------------
#define MMC_FLOATING_BUS    			0xFF
//-------------------------------------------------------------------------------
// Description: This macro represents a bad SD card response byte
#define MMC_BAD_RESPONSE    MMC_FLOATING_BUS
//-------------------------------------------------------------------------------


//===============================================================================
#endif			// #ifndef __SD_SPI_Local_Defines_H
