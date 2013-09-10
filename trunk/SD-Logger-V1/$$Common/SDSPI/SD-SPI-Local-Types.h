#include "system.h"

#include "SDSPI\SD-SPI.h"
#include "SDSPI\SD-SPI-Local-Defines.h"

#ifndef __SD_SPI_Local_Types_H
#define __SD_SPI_Local_Types_H
//===============================================================================

//-------------------------------------------------------------------------------
// Desription: Media type 
//-------------------------------------------------------------------------------
typedef enum
	{
	SD_MODE_NORMAL,
	SD_MODE_HC
	} MEDIA_MODE;
//-------------------------------------------------------------------------------

//------------------------------------------------------------------------
// Description: Media Information structure
//-----------------------------------------------------------------------------
typedef struct 
	{
    MEDIA_STATUS    mediaStatus;
	MEDIA_MODE		mediaMode;
    WORD    		sectorSize;
	DWORD			mediaFinalLBA;
	} 	MEDIA_INFORMATION;


//--------------------------------------------------------------------------------
// Description: Definitions supporting SD Command data structure.
//--------------------------------------------------------------------------------
// Summary: 	An enumeration of SD commands (by name).
// Description: This enumeration corresponds to the position of each command in the 
//				sdmmc_cmdtable array and allows for accessing commands by name.
//              These macros indicate to the SendMMCCmd function which element of 
//				the sdmmc_cmdtable array to retrieve command code information from.
//---------------------------------------------------------------------------------
typedef enum
	{
    GO_IDLE_STATE,			// Description: This macro defines the command code to reset the SD card
    SEND_OP_COND,			// Description: This macro defines the command code to initialize the SD card
    SEND_IF_COND,
    SEND_CSD,
    SEND_CID,
    SEND_STATUS,
    SET_BLOCKLEN,
    READ_SINGLE_BLOCK,
    WRITE_SINGLE_BLOCK,
	SD_SEND_OP_COND,
    APP_CMD,
    READ_OCR,
    CRC_ON_OFF
 	}	SD_CMD_Name;		
//-------------------------------------------------------------------------------
// Summary:		An enumeration of SD command codes
//-------------------------------------------------------------------------------
typedef enum
	{
	cmdGO_IDLE_STATE			=  0,		// command code to reset the SD card
	cmdSEND_OP_COND				=  1,   	// command code to initialize the SD card   
	cmdSEND_IF_COND				=  8,		// command code to check for sector addressing
	cmdSEND_CSD					=  9,		// command code to get the Card Specific Data
	cmdSEND_CID					= 10,		// command code to get the Card Information
	cmdSEND_STATUS				= 13,		// command code to get the card status information
	cmdSET_BLOCKLEN				= 16,		// command code to set the block length of the card
	cmdREAD_SINGLE_BLOCK		= 17,		// command code to read one block from the card
	cmdWRITE_SINGLE_BLOCK		= 24,    	// command code to write one block to the card
	cmdSD_SEND_OP_COND			= 41,		// command code to intitialize an SD card and provide the CSD register value.
											// NOTE:	this is an "application specific" command (specific to SD cards)
											//			and must be preceded by cmdAPP_CMD.
	cmdAPP_CMD					= 55,		// command code to begin application specific command inputs
	cmdREAD_OCR					= 58,		// command code to get the OCR register information from the card
	cmdCRC_ON_OFF				= 59		// command code to disable CRC checking
	}	SD_CMD_Code;

//-----------------------------------------------------------------------------
// Description: Enumeration of different SD response types
//-----------------------------------------------------------------------------
typedef enum
	{
    R1,     // R1 type response
    R1b,    // R1b type response
    R2,     // R2 type response
    R3,     // R3 type response 
    R7      // R7 type response 
	}	RESPONCE_TYPE;

typedef enum
	{
	NODATA,		// SD card DOES NOT expect to transmit
				// or receive more data for this command
	MOREDATA	// SD card EXPECTED to transmit
				// or receive more data for this command
	}	TRANSMIT_TYPE;


//-----------------------------------------------------------------------------
// Summary: 	SD card command data structure
// Description: The typMMC_CMD structure is used to create a command table of 
// 				information needed for each relevant SD command
//-----------------------------------------------------------------------------
typedef struct
	{
    BYTE			CmdCode;          	// The command code
    BYTE    		CRC;              	// The CRC value for that command
    RESPONCE_TYPE	responseType;		// Expected response type for this command
    TRANSMIT_TYPE	transmitType;		// Set to MOREDATA or NODATA, depending on
										// whether more data is expected or not
	} SD_CMD;




//---------------------------------------------------------------------------------------
// Summary: 	The format of an R1 type response
// Description: This union represents different ways to access an SD card R1 type 
//				response packet.
//---------------------------------------------------------------------------------------
typedef union
	{
    BYTE _byte;                         // Byte-wise access
	//-----------------------------------------------------
    // This structure allows bitwise access of the response
	//-----------------------------------------------------
    struct
    	{
        unsigned IN_IDLE_STATE:1;       // Card is in idle state
        unsigned ERASE_RESET:1;         // Erase reset flag
        unsigned ILLEGAL_CMD:1;         // Illegal command flag
        unsigned CRC_ERR:1;             // CRC error flag
        unsigned ERASE_SEQ_ERR:1;       // Erase sequence error flag
        unsigned ADDRESS_ERR:1;         // Address error flag
        unsigned PARAM_ERR:1;           // Parameter flag   
        unsigned B7:1;                  // Unused bit 7
    	};
	} RESPONSE_1;

//---------------------------------------------------------------------------------------
// Summary: 	The format of an R2 type response
// Description: This union represents different ways to access an SD card R2 type 
//				response packet
//---------------------------------------------------------------------------------------
typedef union
	{
    WORD _word;
    struct
    	{
        BYTE      _byte0;
        BYTE      _byte1;
    	};
    struct
    	{
        unsigned IN_IDLE_STATE:1;
        unsigned ERASE_RESET:1;
        unsigned ILLEGAL_CMD:1;
        unsigned CRC_ERR:1;
        unsigned ERASE_SEQ_ERR:1;
        unsigned ADDRESS_ERR:1;
        unsigned PARAM_ERR:1;
        unsigned B7:1;
        unsigned CARD_IS_LOCKED:1;
        unsigned WP_ERASE_SKIP_LK_FAIL:1;
        unsigned ERROR:1;
        unsigned CC_ERROR:1;
        unsigned CARD_ECC_FAIL:1;
        unsigned WP_VIOLATION:1;
        unsigned ERASE_PARAM:1;
        unsigned OUTRANGE_CSD_OVERWRITE:1;
    	};
	} RESPONSE_2;

//---------------------------------------------------------------------------------------
// Summary: 	The format of an R7 or R3 type response
// Description: This union represents different ways to access an SD card R7 type 
//				response packet.
//---------------------------------------------------------------------------------------
typedef union
	{
    struct
    	{
        BYTE _byte;                         // Byte-wise access
        union
       		{
            // NOTE: The SD card argument response field is 32-bit, big endian format.
            // However, the C compiler stores 32-bit values in little endian in RAM.
            // When writing to the _returnVal/argument bytes, make sure to byte
            // swap the order from which it arrived over the SPI from the SD card.
            DWORD _returnVal;
            struct
           		{
                BYTE _byte0;
                BYTE _byte1;
                BYTE _byte2;
                BYTE _byte3;
            	};    
        	}	argument;    
   	 	} bytewise;
	//-----------------------------------------------------
    // This structure allows bitwise access of the response
	//-----------------------------------------------------
    struct
    	{
        struct
        	{
            unsigned IN_IDLE_STATE:1;       // Card is in idle state
            unsigned ERASE_RESET:1;         // Erase reset flag
            unsigned ILLEGAL_CMD:1;         // Illegal command flag
            unsigned CRC_ERR:1;             // CRC error flag
            unsigned ERASE_SEQ_ERR:1;       // Erase sequence error flag
            unsigned ADDRESS_ERR:1;         // Address error flag
            unsigned PARAM_ERR:1;           // Parameter flag   
            unsigned B7:1;                  // Unused bit 7
        	}bits;
        DWORD _returnVal;
    	} bitwise;
	} RESPONSE_7;

//---------------------------------------------------------------------------------------
// Summary: 	A union of responses from an SD card
// Description: The MMC_RESPONSE union represents any of the possible responses that an 
//				SD card can return after being issued a command.
//---------------------------------------------------------------------------------------
typedef union
	{
    RESPONSE_1  r1;  
    RESPONSE_2  r2;
    RESPONSE_7  r7;
	}	SD_RESPONSE;

//---------------------------------------------------------------------------------------
// Summary: 	A description of the card specific data register
// Description: This union represents different ways to access information in a packet 
//				with SD card CSD informaiton.  For more information on the CSD register, 
//				consult an SD card user's manual.
//---------------------------------------------------------------------------------------
typedef union
	{
    struct
    	{
        DWORD _u320;
        DWORD _u321;
        DWORD _u322;
        DWORD _u323;
    	};
    struct
    	{
        BYTE _byte[16];
    	};
    struct
    	{
        unsigned NOT_USED           :1;
        unsigned CRC                :7;
        unsigned ECC                :2;
        unsigned FILE_FORMAT        :2;
        unsigned TMP_WRITE_PROTECT  :1;
        unsigned PERM_WRITE_PROTECT :1;
        unsigned COPY               :1;
        unsigned FILE_FORMAT_GRP    :1;
        unsigned RESERVED_1         :5;
        unsigned WRITE_BL_PARTIAL   :1;
        unsigned WRITE_BL_LEN_L     :2;
        unsigned WRITE_BL_LEN_H     :2;
        unsigned R2W_FACTOR         :3;
        unsigned DEFAULT_ECC        :2;
        unsigned WP_GRP_ENABLE      :1;
        unsigned WP_GRP_SIZE        :5;
        unsigned ERASE_GRP_SIZE_L   :3;
        unsigned ERASE_GRP_SIZE_H   :2;
        unsigned SECTOR_SIZE        :5;
        unsigned C_SIZE_MULT_L      :1;
        unsigned C_SIZE_MULT_H      :2;
        unsigned VDD_W_CURR_MAX     :3;
        unsigned VDD_W_CUR_MIN      :3;
        unsigned VDD_R_CURR_MAX     :3;
        unsigned VDD_R_CURR_MIN     :3;
        unsigned C_SIZE_L           :2;
        unsigned C_SIZE_H           :8;
        unsigned C_SIZE_U           :2;
        unsigned RESERVED_2         :2;
        unsigned DSR_IMP            :1;
        unsigned READ_BLK_MISALIGN  :1;
        unsigned WRITE_BLK_MISALIGN :1;
        unsigned READ_BL_PARTIAL    :1;
        unsigned READ_BL_LEN        :4;
        unsigned CCC_L              :4;
        unsigned CCC_H              :8;
        unsigned TRAN_SPEED         :8;
        unsigned NSAC               :8;
        unsigned TAAC               :8;
        unsigned RESERVED_3         :2;
        unsigned SPEC_VERS          :4;
        unsigned CSD_STRUCTURE      :2;
    	};
	} CSD;


// Summary: A description of the card information register
// Description: This union represents different ways to access information in a packet with SD card CID register informaiton.  For more
//              information on the CID register, consult an SD card user's manual.
typedef union
	{
    struct
    	{
        DWORD _u320;
        DWORD _u321;
        DWORD _u322;
        DWORD _u323;
    	};
    struct
    	{
        BYTE _byte[16];
   		};
    struct
    	{
        unsigned    NOT_USED            :1;
        unsigned    CRC                 :7;
        unsigned    MDT                 :8;
        DWORD       PSN;
        unsigned    PRV                 :8;
        char        PNM[6];
        WORD        OID;
        unsigned    MID                 :8;
    	};
	} CID;


//===============================================================================
#endif			// #ifndef __SD_SPI_Local_Types_H
