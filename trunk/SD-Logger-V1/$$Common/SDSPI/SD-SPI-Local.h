#include "system.h"
#include "TMR\TMR.h"

#include "SDSPI\SD-SPI.h"
#include "SDSPI\SD-SPI-Local-Defines.h"
#include "SDSPI\SD-SPI-Local-Types.h"

#ifndef __SD_SPI_Local_H
#define __SD_SPI_Local_H
//===============================================================================

//****************************************************************************
// Global Variables
//****************************************************************************
//****************************************************************************
// Global Variables
//****************************************************************************
// Until media Initialized = 0; when Initialized (and capacity parameters
// below are set and valid) = 1
extern	BYTE				SPIM_InitStatus;
	
//----------------------------------------------------------------------------
// Description:  SPI prescaler masks; calculated in SPIM_Init() module
//----------------------------------------------------------------------------
extern	WORD   				SYNC_MODE_FAST;
extern	WORD   				SYNC_MODE_SLOW;	
							
//----------------------------------------------------------------------------
// Description: mediaInformation structure contains media status and certain
//				media attributes; loaded in SD_SPI_MediaInitialize() routine
//----------------------------------------------------------------------------
extern 	MEDIA_INFORMATION 	mediaInformation;


//****************************************************************************
// Helper Function Prototypes - Forward declarations
//****************************************************************************
void 				SPIM_Init(void);
BYTE 				SD_SPI_MediaVerify(void);

SD_RESPONSE 		SendSDCmd(SD_CMD_Name cmdName, DWORD address);

//*****************************************************************************
//  Function:		void SPIM_Open (WORD Speed)
//  Summary:	    Initializes the SPI module
//  Conditions:		None.
//  Input:			Speed - Input parameter that sets the SPI speed
//					(Primary and Secondary prescalers)
//  Return:			None.
//  Side Effects:	None.
//  Description:	The SPIM_Open function will enable and configure the 
//					SPI module.
//  Remarks:		None.
//*****************************************************************************
static inline void SPIM_Open( WORD Speed)
	{
    SPISTAT  = 0x0000;             	// Power-on state; also disables
									// SPI Module by setting bit 15
									// (SPISTATbits.SPIEN) to 0

	// Now we may configure SPI Module:
	//-------------------------------------------------------------------------
    SPICON1  			= Speed;    // Set prescalers (bits 4-2 and 1-0) 
    SPICON1 		   &= 0x001F;   // Reset all bits but the prescalers
	//-------------------------------------------------------------------------
	SPICON1bits.MSTEN	= 1;		// SPI Module set to operate in MASTER mode
    SPICON1bits.CKP 	= 1;		// Idle state for clock is a high level; 
									// active state is a low level
    SPICON1bits.CKE 	= 0;		// Serial output data changes on transition
									// from Idle clock state to active clock state
									// (refer to bit CKP)
	//-------------------------------------------------------------------------
	SPICON2				= 0x0000;	// Disable framed SPI
	//-------------------------------------------------------------------------
    SPIENABLE 	= 1;            	// Enable synchronous serial port
	}


//*****************************************************************************
//  Function:		BYTE SPIM_Write (BYTE data_out)
//  Summary:		Writes byte of data to the SD card.
//  Conditions:		SPI configured and enabled.
//  Input:			data_out - The data to write.
//  Return:			None.
//  Side Effects:	None.
//  Description:	The SPIM_Write function will write a byte of data from the 
//					microcontroller to the SD card using SPI.
//  Remarks:		None.
//*******************************************************************************
static inline void SPIM_Write(BYTE data_out )
	{
    BYTE   	ignore;
	//------------------
    SPIBUF = data_out;          // write byte to SSP1BUF register
    while( !SPISTAT_RBF ); 		// wait until bus cycle complete
    ignore = SPIBUF;			// fake reas to clear the SPI buffer
	}



//*****************************************************************************
//  Function:		BYTE SPIM_Read (void)
//  Summary:		Reads a byte of data from the SD card.
//  Conditions:		SPI configured and enabled.
//  Input:			None.
//  Return:			The byte read.
//  Side Effects:	None.
//  Description:	The SPIM_Read function will read one byte from the SPI port.
//  Remarks:		None.
//*****************************************************************************
static inline BYTE SPIM_Read(void)
	{
    SPIBUF = 0xFF;                  	// Data Out - Logic ones, expected by the SD Card
    while(!SPISTAT_RBF);              	// Wait until cycle complete
    return(SPIBUF);               		// Return with byte read
	}

//===============================================================================
#endif			// #ifndef __SD_SPI_Local_H
