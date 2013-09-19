#include "SDSPI\SD-SPI-Profile.h"
#include "SDSPI\SD-SPI-Local.h"

//****************************************************************************
// Global Variables
//****************************************************************************
// Indicates status of SPI Module initialization
// NOTE:	Set to true in SPIM_Init() routine
BYTE				SPIM_InitStatus		= FALSE;
//-------------------------------------------------------------------------------
// SPI Module speed definitions
//-------------------------------------------------------------------------------
// This value defines prescalers to initialize a 16-bit PIC SPI module
// in FAST mode at or below 10 MHz.
// NOTE:	Proper prescaler value is calculated in SPIM_Init() routine
WORD   				SYNC_MODE_FAST    	= 0;
//-------------------------------------------------------------------------------
// This value defines prescalers to initialize a 16-bit PIC SPI module
// in SLOW mode at or below 400 kHz.
// NOTE:	Proper prescaler value is calculated in SPIM_Init() routine
WORD   				SYNC_MODE_SLOW    	= 0;
//-------------------------------------------------------------------------------
	
								
//----------------------------------------------------------------------------
// Description: Used for the mass-storage library to determine media status
//				and attributes
//----------------------------------------------------------------------------
MEDIA_INFORMATION 	mediaInformation		=
		{
		MEDIA_NOT_PRESENT,				// errorCode
		SD_MODE_NORMAL,					// mediaMode
		512,							// sectorSize - fixed at 512
		0								// mediaFinalLBA initialized to 0;
										// will be set to real value in
										// SD_SPI_MediaInitialize() routine.
		};


//*************************************************************************************
//  Function:		BYTE	SD_SPI_MediaVerify()
//  Summary:		Determines whether an SD card is present
//  Return Values:
//    				TRUE -  Card detected
//    				FALSE - No card detected
//  Description:
//    				The SD_SPI_MediaVerify() function determine if an SD card is 
//					connected to the microcontroller by polling the SENSE port - if
//					the card is inserted in the socket respective port is brought
//					to GND level (low); otherwise the weak pull-up will keep it HIGH.
//*************************************************************************************
BYTE SD_SPI_MediaVerify (void)
	{
	uint	RC;
	//--------------------------------------------------------------------------
	// Make sure that all ports are configured
	//--------------------------------------------------------------------------
	SPIM_Init();
 
	//----------------------------------------------------
	// NOTE:	Found through testing: with Weak Pull-Up
	//			it is necessary to read port a few times
	//			to let Weak Pull-Up to take hold of the port
	//----------------------------------------------------
	RC = SD_SENSE_PORT;
	RC = SD_SENSE_PORT;
	RC = SD_SENSE_PORT;
	RC = SD_SENSE_PORT;
	RC = SD_SENSE_PORT;
	RC = SD_SENSE_PORT;
	RC = SD_SENSE_PORT;
	RC = SD_SENSE_PORT;
	//--------------------------------------------------------------------------
	// Check the status of SENSE bit - if SD Card is present, the port is LOW
	//--------------------------------------------------------------------------
	if (0 == RC)
		// SD card is present!
		{
		// let's implement some "delay" for card to power up
		for (RC = 0; RC < 32000; RC++);
		// return "Success"
		return TRUE;
		}
    	    
	//--------------------------------------------------------------------------
	// SD Card is not present...
	//--------------------------------------------------------------------------
	return FALSE;		
	}
//=====================================================================================



//**************************************************************************************
//  Function:		void SPIM_Init(void)
//  Summary:		Configures the SPI module and calculates prescalers for FAST and
//					slow modes of operation.
//  Conditions:		Processor type and Fcy() macro have to be defined correctly
//    				to get the correct SPI frequency.
//  Input:			Uses Fcy() macro value.  
//  Return Values:	None.  
//  Side Effects:	Sets SPI module Initialization flag
//**************************************************************************************
void SPIM_Init(void)
	{
	if (SPIM_InitStatus)
		return;		// SPI Module already initialized
		
	//*******************************************************************
	// Configure SD Card socket SENSE pin
	//*******************************************************************
	SD_SENSE_TRIS	= 1;		// SENSE port set to Input 
	SD_SENSE_PUE	= 1;		// Enable Weak Pull-Up on SENSE port

	
	//*******************************************************************
	// Configure Chip Select (CS) port
	//*******************************************************************
	SD_CS_TRIS		= 0;		// Chip Select port set to Output
	SD_CS_LAT		= 1;		// Diselect CS line (default: SELECT => Low)

	
	//*******************************************************************
	// Pre-configure SPI module
	//*******************************************************************
	SPISTAT	= 0;	// Disable SPI through SPIEN bit, reset all flags
	SPICON1	= 0;	// Reset SPI configuration
	SPICON2	= 0;	// Reset SPI configuration
	//--------------------
	SPIMD	= 0;	// Enable SPI module through PMD 
	//=======================================================
	// NOTE:	While most of the SPI configuration registers
	//			are defined generically in SD-SPI-Profile.h,
	//			pin assignment through PMD is done directly
	//			in this module for specific SPI (1 or 2) mo-
	//			dule due to difficulties of doing so generi-
	//			cally.
	//			Please update code below if design dictates
	//			use of different module/different pins!
	//-------------------------------------------------------
	// NOTE:	If pins beloware shared with the ADC please
	//			configure them for digital I/O outside of
	//			this routine (typically in the general
	//			Init() routine)
	//-----------------------------------------------------
	// Assign SPI1 pins through PPS (Peripheral Pin Select)
	//-----------------------------------------------------
	_TRISB13	= 0;		// RB13 (RP13) set to Output
	_RP13R		= 0b01000;	// RP13 => SCK1

	_TRISB14	= 0;		// RB14 (RP14) set to Output
	_RP14R		= 0b00111;	// RP14 => SDO1

	_TRISB12	= 1;		// RB12 (RP12) set to Input
	_SDI1R		= 12;		// SDI1 => RP13 (RB13)



	//------------------------------------------------------------------------
	// Calculate and store for further use prescalers for slow (SYNC_MODE_SLOW)
	// and fast (SYNC_MODE_FAST) SPI modes.
	// NOTE:	The following calculations assume that macro Fcy() in 
	//			SD-SPI-Profile.h is set to correct value!
	//------------------------------------------------------------------------
	WORD	PrimaryPS;
	WORD	SecondaryPS;
	WORD	RateDivider;
	//------------------------------------------------------------------------
	// First, calculate prescalers for SLOW mode (<= 400 kHz)
	//------------------------------------------------------------------------
	// Set Primary prescaler to fastest (1:1) value and reset Secondary one
	PrimaryPS 	= 0x0003;		// Initialized to 1:1
	SecondaryPS = 0;
	// Calculate minimum rate divider needed for the configured 
	// Instruction clock cycle (Fcy) to bring it down to required
	// SPI speed of less than 400 kHz
	RateDivider = (Fcy() + 399999) / 400000;

	// If Fcy > 400kHz - we need to adjust prescalers to bring
	// Fsck (SPI speed) within the range 100 kHz < Fsck <= 400 kHz
	// NOTE: Combined Primary and Secondary prescalers achieve
	//		 rate drop of 512 times, which is enough to bring
	//		 Fsck within the range even at maximum Fcy of 40MHz.
    while (RateDivider > 0)
    	{
		// Secondary prescaler has the range from 1:1 to 8:1
        if (RateDivider <= 8)
        	{
			// We can satisfy frequency requirements now with just 
			// Secondary prescaler (NOTE: Secondary prescaler value
			// of 0b111 results in 1:1 and value of 0b000 drops the
			// frequency by factor of 8)
			SecondaryPS = (8 - RateDivider) << 2;	// Shift is needed
													// to put it in proper
													// position
			break;		// Both prescalers are set!
        	}
        else
            {
			// RateDivider exceeds the range of Secondary prescaler;
			// we need to increase Primary prescaler rate.
            PrimaryPS--;	// Each step drops the rate by factor of 4
            // Adjust RateDivider by factor of 4 with rounding
            RateDivider = (RateDivider + 3) / 4;
			}
    	} 
	SYNC_MODE_SLOW = ( SecondaryPS | PrimaryPS );

	//------------------------------------------------------------------------
	// Now let's calculate prescalers for FAST mode (<= 10 MHz)
	//------------------------------------------------------------------------
	// Set Primary prescaler to fastest (1:1) value and reset Secondary one
	PrimaryPS 	= 0x0003;		// Initialized to 1:1
	SecondaryPS = 0;
	// Calculate minimum rate divider needed for the configured 
	// Instruction clock cycle (Fcy) to bring it down to required
	// SPI speed of less than 10 MHz
	RateDivider = (Fcy() + 9999999) / 10000000;

	// If Fcy > 10 MHz - we need to adjust prescalers to bring
	// Fsck (SPI speed) within the range Fsck <= 10 MHz
    while (RateDivider > 0)
    	{
		// Secondary prescaler has the range from 1:1 to 8:1
        if (RateDivider <= 8)
        	{
			// We can satisfy frequency requirements now with just 
			// Secondary prescaler (NOTE: Secondary prescaler value
			// of 0b111 results in 1:1 and value of 0b000 drops the
			// frequency by factor of 8)
			SecondaryPS = (8 - RateDivider) << 2;	// Shift is needed
													// to put it in proper
													// position
			break;		// Both prescalers are set!
        	}
        else
            {
			// RateDivider exceeds the range of Secondary prescaler;
			// we need to increase Primary prescaler rate.
            PrimaryPS--;	// Each step drops the rate by factor of 4
            // Adjust RateDivider by factor of 4 with rounding
            RateDivider = (RateDivider + 3) / 4;
			}
    	} 
	SYNC_MODE_FAST = ( SecondaryPS | PrimaryPS );
	//----------------------------------------------------------------------
	SPIM_InitStatus = TRUE;		// Block multiple invocations
	return;
	}    
//=====================================================================================





//**************************************************************************************
//  Function:		MMC_RESPONSE SendSDCmd (BYTE cmd, DWORD address)
//--------------------------------------------------------------------------------------
//  Summary:		Sends a command packet to the SD card.
//  Conditions:		None.
//  Input:			None.
//  Return:			MMC_RESPONSE    - The response from the card
//              	- Bit 0 - Idle state
//              	- Bit 1 - Erase Reset
//               	- Bit 2 - Illegal Command
//              	- Bit 3 - Command CRC Error
//              	- Bit 4 - Erase Sequence Error
//              	- Bit 5 - Address Error
//               	- Bit 6 - Parameter Error
//               	- Bit 7 - Unused. Always 0.
//  Side Effects:	None.
//  Description:	SendSDCmd prepares a command packet and sends it out over the 
//					SPI interface. Response data of type 'R1' (as indicated by the 
//					SD/MMC product manual is returned.
//**************************************************************************************
// Description:  SD Card control commands
//--------------------------------------------------------------------------------------
const SD_CMD SD_cmdTable[] =
	{
	    // cmd                      crc     response
	    {cmdGO_IDLE_STATE,          0x95,   R1,     NODATA	},
	    {cmdSEND_OP_COND,           0xF9,   R1,     NODATA	},
	    {cmdSEND_IF_COND,      		0x87,   R7,     NODATA	},
	    {cmdSEND_CSD,               0xAF,   R1,     MOREDATA},
	    {cmdSEND_CID,               0x1B,   R1,     MOREDATA},
	    {cmdSEND_STATUS,            0xAF,   R2,     NODATA	},
	    {cmdSET_BLOCKLEN,           0xFF,   R1,     NODATA	},
	    {cmdREAD_SINGLE_BLOCK,      0xFF,   R1,     MOREDATA},
	    {cmdWRITE_SINGLE_BLOCK,     0xFF,   R1,     MOREDATA},
	    {cmdSD_SEND_OP_COND,        0xFF,   R7,     NODATA	}, 	// Actual response is R3,
																// but has same number of bytes as R7.
	    {cmdAPP_CMD,                0x73,   R1,     NODATA	},
	    {cmdREAD_OCR,               0x25,   R7,     NODATA	},
	    {cmdCRC_ON_OFF,             0x25,   R1,     NODATA	}
	};
//**************************************************************************************
SD_RESPONSE SendSDCmd(SD_CMD_Name cmdName, DWORD address)
	{
    SD_RESPONSE	    response;

    WORD 			count;

	//---------------------------------------------------------------------------------------
	// Summary: 	An SD command packet
	// Description: This union represents different ways to access an SD card command packet
	//---------------------------------------------------------------------------------------
	union
		{
	    // This structure allows array-style access of command bytes
	    struct
		    {
		     BYTE field[7];
		    };
	    // This structure allows byte-wise access of packet command bytes
	    struct
	    	{
	        BYTE crc;               // The CRC byte
	        BYTE c30filler;     	// Filler space (since bitwise declarations can't cross a WORD boundary)
	        BYTE addr0;             // Address byte 0
	        BYTE addr1;             // Address byte 1
	        BYTE addr2;             // Address byte 2
	        BYTE addr3;             // Address byte 3
	        BYTE cmd;               // Command code byte
	    	};
	    // This structure allows bitwise access to elements of the command bytes
	    struct
	    	{
	        BYTE  END_BIT:1;        // Packet end bit
	        BYTE  CRC7:7;           // CRC value
	        DWORD address;      	// Address
	        BYTE  CMD_INDEX:6;      // Command code
	        BYTE  TRANSMIT_BIT:1;   // Transmit bit
	        BYTE  START_BIT:1;      // Packet start bit
	    	};
		} CmdPacket;

    
    SD_CS_LAT 		= 0;		// Select card
    
    // Copy over data
    CmdPacket.cmd        = SD_cmdTable[cmdName].CmdCode;
    CmdPacket.address    = address;

	// Technically we should calculate CRC for the command,
	// but valid CRCs for respective command codes are pre-
	// calculated and stored in the SD_cmdTable
    CmdPacket.crc        = SD_cmdTable[cmdName].CRC;       
	
    
    CmdPacket.TRANSMIT_BIT = 1;		// Set Tranmission bit
    
    SPIM_Write(CmdPacket.cmd);		// Send Command
    SPIM_Write(CmdPacket.addr3);	// Most Significant Byte
    SPIM_Write(CmdPacket.addr2);
    SPIM_Write(CmdPacket.addr1);
    SPIM_Write(CmdPacket.addr0);	// Least Significant Byte
    SPIM_Write(CmdPacket.crc);		// Send CRC


    // Loop until we get a response from the media.  Delay (NCR) could be up 
    // to 8 SPI byte times.  First byte of response is always the equivalent of 
    // the R1 byte, even for R1b, R2, R3, R7 responses.
    count = NCR_TIMEOUT;
    while (TRUE)
    	{
        response.r1._byte = SPIM_Read();
		//--------------------------------------------
		if (response.r1._byte != MMC_FLOATING_BUS)
			break;	// Non-empty responce received from the
					// card - we may proceed with further processing
		//--------------------------------------------
        count--;
		//--------------------------------------------
		if (count <= 0)
			// Oops! timeout expired...
			//-----------------------------------------------------------------
			// NOTE: 	If the loop above terminates because "count" reaches 0,
			//			received byte (first byte of responce) is 0xFF, which
			//			for any expected responces indicates an error condition.
			return response;	// No further processing for this command;
								// Error condition expected to be handled by
								// caller.
    	}
    
    //Check if we should read more bytes, depending upon the response type expected. 
	switch (SD_cmdTable[cmdName].responseType) 
		{
		case R2:
			// We already received the first byte, just make sure it is in the
			// correct location in the responce structure	
			response.r2._byte1 = response.r1._byte; 
			// Fetch the second byte of the response.
			response.r2._byte0 = SPIM_Read(); 
			break;

		case R7:	// Also could be used for response R3 type
			// Fetch the other four bytes of the R7 (or R3) response.
			// NOTE:	The SD card argument response field is 32-bit,
			//			big endian format. However, the C compiler 
			//			stores 32-bit values in little endian in RAM.
			//			When writing to the _returnVal/argument bytes, 
			//			make sure the order it gets stored in is correct.      
			response.r7.bytewise.argument._byte3 = SPIM_Read();
			response.r7.bytewise.argument._byte2 = SPIM_Read();
			response.r7.bytewise.argument._byte1 = SPIM_Read();
			response.r7.bytewise.argument._byte0 = SPIM_Read();
			break;

		case R1:
		default:
			// One-byte responce already received - nothing else to do
			break;
		}
 
    SPIM_Write(0xFF);	// Device requires at least 8 clock pulses after 
						// the response has been sent, before if can process
						// the next command.  CS may be high or low.

    // See if we are expecting more data or not
    if ( NODATA == SD_cmdTable[cmdName].transmitType )
        SD_CS_LAT = 1;		// Disselect card

    return(response);
	}
//=====================================================================================





