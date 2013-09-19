#include "SDSPI\SD-SPI-Profile.h"
#include "SDSPI\SD-SPI-Local.h"


//------------------------------------------------------------------------------
// NOTE: During the media initialization sequence, it is necessary to clock the
// media at no more than 400kHz SPI speeds, since some media types power up in
// open drain output mode and cannot run fast initially.
// On PIC32/PIC24/dsPIC devices, the SPI module is flexible enough to reach
// <400 kHz speeds regardless of CPU frequency. Therefore, during initialization
// we use various prescalers to bring SPI speed to <400 kHz.
//------------------------------------------------------------------------------





//*************************************************************************************
//  Function:		MEDIA_STATUS SD_SPI_ReadStatus (void)
//  Summary:		Returns the status of the SD card
//  Conditions:		SD_SPI_MediaInitialize() is complete
//  Input:			None
//  Return:			Returns the status of the SD card
//*************************************************************************************
MEDIA_STATUS	SD_SPI_ReadStatus(void)
	{ return mediaInformation.mediaStatus; }
//=====================================================================================


//*************************************************************************************
//  Function:		WORD SD_SPI_ReadSectorSize(void)
//  Summary:		Returns the sector size of the SD card
//  Conditions:		SD_SPI_MediaInitialize() is complete
//  Input:			None
//  Return:			The sector size of the device
//*************************************************************************************
WORD 			SD_SPI_ReadSectorSize(void)
	{ 
	if (MEDIA_NO_ERROR == mediaInformation.mediaStatus)
		return (mediaInformation.sectorSize);
	else
		return 0; 
	}
//=====================================================================================


//*************************************************************************************
//  Function:		DWORD SD_SPI_ReadCapacity (void)
//  Summary:		Returns the capacity of the SD card
//  Conditions:		SD_SPI_MediaInitialize() is complete
//  Input:			None
//  Return:			The capacity of the device
//  Side Effects:	None.
//  Description:	The SD_SPI_ReadCapacity function is used by the mass storage 
//					driver to obtain the total number of sectors on the card.
//*************************************************************************************
DWORD 			SD_SPI_ReadCapacity(void)
	{ 
	if (MEDIA_NO_ERROR == mediaInformation.mediaStatus)
		return (mediaInformation.mediaFinalLBA);
	else
		return 0; 
	}
//=====================================================================================


//*************************************************************************************
//  Function:		BYTE SD_SPI_ShutdownMedia (void)
//  Summary:		Disables the SD card
//  Conditions:		None.
//  Input:			None
//  Return:			None
//  Side Effects:	Stops the SPI module
//  Description:	This function will disable the SPI port and deselect the SD card.
//  Remarks:		None
//*************************************************************************************
void SD_SPI_ShutdownMedia(void)
	{
    SPISTAT  = 0x0000;		// Power-on state; also disables
							// SPI Module by setting bit 15
							// (SPISTATbits.SPIEN) to 0 and resets
							// all conditions.
							
    SD_CS_LAT = 1;			// Deselect the device
	//-----------
    return;
	}
//=====================================================================================



//*************************************************************************************
//  Function:	BYTE SD_SPI_SectorRead (DWORD sector_addr, BYTE * buffer)
//  Summary:	Reads a sector of data from an SD card.
//  Conditions:	Media initialized with the call to SD_SPI_MediaInitialize()
//				and has no initialization errors.
//  Input:
//    			sector_addr - The address of the sector on the card.
//    			buffer 		- The buffer where the retrieved data will be stored.
//							  The size of the buffer should be at least 512 bytes.
//							 
//  Return Values:
//    			TRUE 		- The sector was read successfully
//    			FALSE 		- The sector could not be read
//
//  Side Effects:	None
//  Description:	The SD_SPI_SectorRead function reads a sector of data bytes 
//					(512 bytes) of data from the SD card starting at the sector 
//					address and stores them in the location pointed to by 'buffer'
//
//  Remarks:		The card expects the address field in the command packet to be 
//					a byte address. The sector_addr value is converted to a byte 
//					address by shifting it left nine times (multiplying by 512).
//
//    				This function performs a synchronous read operation.  In other 
//					words, this function is a blocking function, and will not return 
//					until either the data has been fully been read, or, a timeout 
//					or other error occurred.
//*************************************************************************************
BYTE SD_SPI_SectorRead(DWORD sector_addr, BYTE* buffer)
	{
	// Parameter validation
	if (NULL == buffer)	
		return FALSE;		// Failed...
	//------------------------------------------------
	// Condition validation
	if (MEDIA_NO_ERROR != mediaInformation.mediaStatus)
		return FALSE;		// Failed...
	//------------------------------------------------

    DWORD			Address 			= sector_addr;
    BYTE*			pTarget				= buffer;

    WORD			ByteIndex			= 0; 

    BYTE 			bData;
    SD_RESPONSE 	response;
    ulong 			TIMEOUT;
    

	//---------------------------------------------------------
    // Start the read request sequence.  
	//---------------------------------------------------------
 
	// SDHC cards are addressed on a 512 byte block basis.  This is 1:1 equivalent
	// to LBA addressing.  For standard capacity media, the media is expecting
	// a complete byte address.  Therefore, to convert from the LBA address to the
	// byte address, we need to multiply by 512.
	if (mediaInformation.mediaMode == SD_MODE_NORMAL)
	    Address <<= 9; //Equivalent to multiply by 512
 
	response = SendSDCmd(READ_SINGLE_BLOCK, Address);
	
	// NOTE: SendMMCmd() sends 8 SPI clock cycles after getting the
	//		 response.  This meets the NAC min timing paramemter, so
	//		 we don't need additional clocking here.
	//---------------------------------------------------------------
	// Make sure the command was accepted successfully
	//---------------------------------------------------------------
	if(response.r1._byte != 0x00)
		// Perhaps the card isn't initialized or present.
		goto READ_ABORT;
          
	//---------------------------------------------------------------
	// We successfully sent the READ_SINGLE_BLOCK command to the media.
	// We now need to keep polling the media until it sends us the data
	// start token byte.
	// This could typically take a couple/few milliseconds, up to a
	// maximum of 100 ms (or more for SDHC and SDXC).
	//---------------------------------------------------------------
	// Set Cut Off Time 250 ms from NOW
	TIMEOUT 		= TMRGetRTC() + 250u; 
	// Poll card for non-empty responce subject to TIMEOUT  
	while (TRUE)
		{
		bData = SPIM_Read();
		//-----------------------------
		if( bData != MMC_FLOATING_BUS )
			// Non-empty responce received from card -
			// exit wait loop and analyze Responce
			break;	
		//-----------------------------
		if (TMRGetRTC() > TIMEOUT)
			// The media didn't respond in the timeout
			// interval allowed.  Operation failed...
			goto READ_ABORT; 
		//-----------------------------
		// Continue waiting...
 		} 

	// We are expecting DATA_START_TOKEN if everything is OK
	if	(bData != DATA_START_TOKEN)
		{
		// We got an unexpected non-0xFF, non-start token byte back?
		// Some kind of error must have occurred. 
		goto READ_ABORT; 
		}        
    

	// We have sent the READ_SINGLE_BLOCK command and have successfully
	// received the data start token byte.  Therefore, we are ready
	// to receive 512 byte (one sector) of raw data bytes from the media.
	for (ByteIndex = 0; ByteIndex < 512; ByteIndex++)
		{
		pTarget[ByteIndex] = SPIM_Read();
    	}    
 
	// Read two bytes to receive the CRC-16 value on the data block.
	SPIM_Read();
	SPIM_Read();

	// We completed the read operation successfully and have returned
	// all data bytes requested.
	SD_CS_LAT = 1;  		// De-select media
	SPIM_Write(0xFF); 		// Clear SPI BUS  
	
	// Read block suceeded!
	return TRUE;


READ_ABORT:
	// Some error must have happened.
	SD_CS_LAT = 1;  		// De-select media
	SPIM_Write(0xFF); 		// Clear SPI BUS  
     
    // Read block failed!
    return FALSE;
	}    
//=====================================================================================

 

//*************************************************************************************
//  Function:	BYTE SD_SPI_SectorWrite (DWORD sector_addr, BYTE * buffer, 
//										 BYTE allowWriteToZero)
//  Summary:	Writes a sector of data to an SD card.
//  Conditions:	Media initialized with the call to SD_SPI_MediaInitialize()
//				and has no initialization errors.
//  Input:
//    			sector_addr -      The address of the sector on the card.
//    			buffer -           The buffer with the data to write.
//    			allowWriteToZero -
//                     - TRUE -  Writes to the 0 sector (MBR) are allowed
//                     - FALSE - Any write to the 0 sector will fail.
//
//  Return:
//    				TRUE -  The sector was written successfully.
//    				FALSE - The sector could not be written.
//
//  Side Effects:	None.
//  Description:	The SD_SPI_SectorWrite function writes one sector of data 
//					(512 bytes) of data from the location pointed to by 'buffer'
//					to the specified sector of the SD card.
//
//  Remarks:		The card expects the address field in the command packet 
//					to be a byte address. The sector_addr value is ocnverted 
//					to a byte address by shifting it left nine times 
//					(multiplying by 512).
//*************************************************************************************
BYTE SD_SPI_SectorWrite(DWORD sector_addr, BYTE* buffer, BYTE allowWriteToZero)
	{
    if(allowWriteToZero == FALSE && sector_addr == 0x00000000)
        return FALSE;		// Parameter validation
	if (NULL == buffer)	
		return TRUE;		// Parameter validation
	//------------------------------------------------
	// Condition validation
	if (MEDIA_NO_ERROR != mediaInformation.mediaStatus)
		return FALSE;		// Failed...
	//------------------------------------------------
	
    DWORD			Address 			= sector_addr;
    BYTE*			pSource				= buffer;

    WORD			ByteIndex			= 0; 

    SD_RESPONSE 	response;
    ulong 			TIMEOUT;



	// The sector_addr parameter (Address) is the block address.
	// For standard capacity SD cards, the card expects a complete byte address.
	// To convert the block address into a byte address, we multiply by the block size (512).
	// For SDHC (high capacity) cards, the card expects a block address already, so no
	// address cconversion is needed
	if (mediaInformation.mediaMode == SD_MODE_NORMAL)  
	    Address <<= 9;   //Equivalent to multiply by 512
   
	// Send the write single block command, with the LBA or byte 
	// address (depeding upon SDHC or standard capacity card)
	response = SendSDCmd(WRITE_SINGLE_BLOCK, Address);    

	//---------------------------------------------------------------
	// Make sure the command was accepted successfully
	//---------------------------------------------------------------
	if(response.r1._byte != 0x00)
		// Perhaps the card isn't initialized or present.
		goto WRITE_ABORT;

	// Initialize Single Block Write
	SPIM_Write(DATA_START_TOKEN);   
	
               
	// We have sent the DATA_START_TOKEN. Therefore, we are ready
	// to send 512 byte (one sector) of raw data bytes to the media.
	for (ByteIndex = 0; ByteIndex < 512; ByteIndex++)
		{
		SPIM_Write(pSource[ByteIndex]);
    	}    
	
	//---------------------------------------------------------------------
	// We have finshed sending a 512 byte block.  Now we need
	// to receive 16-bit CRC, and retrieve the data_response token
	//---------------------------------------------------------------------
	// By default, the media doesn't use CRC unless it is enabled
	// manually during the card initialization sequence (which
	// we do not do in this application).
	//---------------------------------------------------------------------
	//Send 16-bit (dummy) CRC for the data block just sent
	SPIM_Write(0xFF);
	SPIM_Write(0xFF);

                
	// Read response token byte from media, mask out top three don't 
	// care bits, and check if there was an error
	if((SPIM_Read() & WRITE_RESPONSE_TOKEN_MASK) != DATA_ACCEPTED)
	    // Something went wrong.  Try and terminate as gracefully as 
	    // possible, so as allow possible recovery.
	    goto WRITE_ABORT;
                
	// Dummy read to gobble up a byte
	// (ex: to ensure we meet NBR timing parameter)
	SPIM_Write(0xFF); 		// Clear SPI BUS  
 
	// The media will now send busy token (0x00) bytes until
	// it is internally ready again (after the block is successfully
	// writen).
	// This could typically take a couple/few milliseconds, up to a
	// maximum of 500 ms.
	//---------------------------------------------------------------
	// Set Cut Off Time 500 ms from NOW
	TIMEOUT 		= TMRGetRTC() + 500u; 
	// Poll card for non-empty responce subject to TIMEOUT  
	while (TRUE)
		{
		// Poll the media.  Will return 0x00 if still busy.  
		// Will return non-0x00 if writing data block complete.
        if(SPIM_Read() != 0x00)
			break;
		//-----------------------------
		if (TMRGetRTC() > TIMEOUT)
			// The media didn't respond in the timeout
			// interval allowed.  Operation failed...
			goto WRITE_ABORT; 
		//-----------------------------
		// Continue waiting...
 		} 


	// The media is done and is no longer busy. As we were doing a
	// single block write, we are now fully complete with the write
	// operation.
	SD_CS_LAT = 1;  		// De-select media
	SPIM_Write(0xFF); 		// Clear SPI BUS  
                
	// Write Sector suceeded!
	return TRUE;  

WRITE_ABORT:
	// An error occurred, and we need to stop the write sequence so as
	// to try and allow for recovery/re-attempt later.
	SD_CS_LAT = 1;  	// deselect media
	SPIM_Write(0xFF); 		// Clear SPI BUS  
	return FALSE;
    
	}    
//=====================================================================================




//*************************************************************************************
//  Function:		MEDIA_STATUS  SD_SPI_MediaInitialize (void)
//  Summary:		Initializes the SD card and returns MEDIA_INFORMATION data
//					structure
//  Conditions:		None.
//  Input:			None.
//  Return Values:	The function returns a pointer to the MEDIA_INFORMATION 
//					structure. The mediaStatus member may contain the following 
//					values:
//					* MEDIA_NO_ERROR - The media initialized successfully
//					* MEDIA_CANNOT_INITIALIZE - Cannot initialize the media.  
//  Side Effects:	None.
//  Description:	This function will send initialization commands to and SD card.
//  Remarks:		Psuedo-code flow for the media initialization process is as follows:
//
//-------------------------------------------------------------------------------------------
//SD Card SPI Initialization Sequence (for physical layer v1.x or v2.0 device) is as follows:
//-------------------------------------------------------------------------------------------
//	0. 	Power up tasks
//    	a.	Initialize microcontroller SPI module to no more than 400kbps rate so as to 
//			support	MMC devices.
//    	b.  Add delay for SD card power up, prior to sending it any commands.  It wants the 
//        	longer of: 1ms, the Vdd ramp time (time from 2.7V to Vdd stable), and 74+ clock 
//			pulses.
//
//	1.	Send CMD0 (GO_IDLE_STATE) with CS = 0.  This puts the media in SPI mode and software 
//		resets the SD/MMC card.
//	2.  Send CMD8 (SEND_IF_COND).  This requests what voltage the card wants to run at. 
//    	NOTE: Some cards will not support this command.
//    	a.  If illegal command response is received, this implies either a v1.x physical spec 
//			device, or not an SD card (ex: MMC).
//    	b.  If normal response is received, then it must be a v2.0 or later SD memory card.
//
//	If v1.x device:
//-----------------
//	3.  Send CMD1 repeatedly, until initialization complete (indicated by R1 response byte/idle 
//		bit == 0).
//	4.  Basic initialization is complete.  May now switch to higher SPI frequencies.
//	5.  Send CMD9 to read the CSD structure.  This will tell us the total flash size and other 
//		info which will be useful later.
//	6.  Parse CSD structure bits (based on v1.x structure format) and extract useful information 
//		about the media.
//	7.  The card is now ready to perform application data transfers.
//
//	If v2.0+ device:
//-----------------
//	3.  Verify the voltage range is feasible.  If not, unusable card, should notify user that the 
//		card is incompatible with this host.
//	4.  Send CMD58 (Read OCR).
//	5.  Send CMD55, then ACMD41 (SD_SEND_OP_COND, with HCS = 1).
//    	a.  Loop CMD55/ACMD41 until R1 response byte == 0x00 (indicating the card is no longer
//			busy/no longer in idle state).  
//	6.  Send CMD58 (Get CCS).
//    	a.  If CCS = 1 --> SDHC card.
//    	b.  If CCS = 0 --> Standard capacity SD card (which is v2.0+).
//	7.  Basic initialization is complete.  May now switch to higher SPI frequencies.
//	8.  Send CMD9 to read the CSD structure.  This will tell us the total flash size and other info 
//		which will be useful later.
//	9.  Parse CSD structure bits (based on v2.0 structure format) and extract useful information 
//		about the media.
// 10. 	The card is now ready to perform application data transfers.
//
//*************************************************************************************
MEDIA_STATUS  SD_SPI_MediaInitialize(void)
	{
    SD_RESPONSE 	response;

	BYTE 			CSDResponse[20];
	DWORD 			c_size;
	BYTE 			c_size_mult;
	BYTE 			block_len;

	WORD 			count;
	WORD			index;

    DWORD 			TIMEOUT;
	
	//--------------------------------------------------------------------------
	// Verify that SD Card is present
	//--------------------------------------------------------------------------
	if (FALSE == SD_SPI_MediaVerify())
		return mediaInformation.mediaStatus = MEDIA_NOT_PRESENT;

	//--------------------------------------------------------------------------
	// Check for previous initialization.
	//--------------------------------------------------------------------------
	if (MEDIA_NO_ERROR == mediaInformation.mediaStatus)
		return mediaInformation.mediaStatus;		// Already initialized...

	//--------------------------------------------------------------------------
	// Make sure that SPI Module is initialized
	//--------------------------------------------------------------------------
	SPIM_Init();
 
	//--------------------------------------------------------------------------
    // Initialize global variables.  Will get updated later with valid data once
    // the data is known.
	//--------------------------------------------------------------------------
    mediaInformation.mediaStatus			= MEDIA_CANNOT_INITIALIZE;
    mediaInformation.mediaMode				= SD_MODE_NORMAL;   // Will get updated later with real value, 
																// once we know based on initialization flow.
    mediaInformation.mediaFinalLBA			= 0x00000000;		// Will compute a valid size later, 
																// from the CSD register values we get from the card

    SD_CS_LAT 								= 1;         		// Initialize Chip Select line (1 = card not selected)

    // MMC media powers up in the open-drain mode and 
	// cannot handle a clock faster than 400kHz.
	// Initialize SPI port to <= 400kHz
	SPIM_Open(SYNC_MODE_SLOW);
    

    // Media wants the longer of: Vdd ramp time, 1 ms fixed delay, or 74+ clock pulses.
    // According to spec, CS should be high during the 74+ clock pulses.
    // In practice it is preferrable to wait much longer than 1ms, in case of
    // contact bounce, or incomplete mechanical insertion (by the time we start
    // accessing the media). 
    TMRDelay(30);

    // Generate 80 clock pulses (prior to selecting the card)
    for(count = 0; count < 10; count++)
        SPIM_Write(0xFF);


    TIMEOUT = TMRGetRTC() + 500;	// Set timeout to 500 msec so even if the card
									// is busy with the WRITE programming it has
									// enough time to finish and accept GO_IDLE
    while (TRUE)
    	{
        // Toggle chip select, to make media abandon whatever it may have been doing
        // before.  This ensures the CMD0 is sent freshly after CS is asserted low,
        // minimizing risk of SPI clock pulse master/slave syncronization problems, 
        // due to possible application noise on the SCK line.
        SD_CS_LAT = 1;
        SPIM_Write(0xFF);	// Send some "extraneous" clock pulses.  If a previous
        					// command was terminated before it completed normally,
                			// the card might not have received the required clocking
                  			// following the transfer.
  
    	// Send CMD0 (with CS = 0) to reset the media and put SD cards into SPI mode.
        response = SendSDCmd(GO_IDLE_STATE, 0x0);
		if ( response.r1.IN_IDLE_STATE )
			// Success: card is IDLE
			break;
		//-------------------------------------------------------------------------
		if (TIMEOUT > TMRGetRTC())
			// Timeout expired without the card properly
			// accepting CMD0: GO_IDLE_STATE
			{
            SD_CS_LAT = 1;       // deselect the devices
            return mediaInformation.mediaStatus;
			}
    	} 

         
	//----------------------------------------------------------------------
	// Media successfully processed CMD0
	//----------------------------------------------------------------------

    // Send CMD8 (SEND_IF_COND) to specify/request the SD card interface condition
	// (ex: indicate what voltage the host runs at).
    // 0x000001AA --> VHS = 0001b = 2.7V to 3.6V.  The 0xAA LSB is the check pattern,
	// and is arbitrary, but 0xAA is recommended (good blend of 0's and '1's).
    // The SD card has to echo back the check pattern correctly however, in the R7 response.
    // If the SD card doesn't support the operating voltage range of the host, then it may not respond.
    // If it does support the range, it will respond with a type R7 reponse packet (6 bytes/48 bits).	        
    // Additionally, if the SD card is MMC or SD card v1.x spec device, then it may respond with
    // invalid command. 
	// If it is a v2.0 spec SD card, then it is mandatory that the card respond to CMD8.

    response = SendSDCmd(SEND_IF_COND, 0x1AA);   	// Note: If changing "0x1AA",
													// CRC value in table must also change.

    if	( 	((response.r7.bytewise.argument._returnVal & 0xFFF) == 0x1AA) 
		&&	(!response.r7.bitwise.bits.ILLEGAL_CMD)							)
   		{
        // If we get to here, the device supported the CMD8 command and didn't
		// complain about our host voltage range.
        // Most likely this means it is either a v2.0 spec standard or high
		// capacity SD card (SDHC)

		// Send CMD58 (Read OCR [operating conditions register]).  Reponse type is R3, which has 5 bytes.
		// Byte 4 = normal R1 response byte, Bytes 3-0 are = OCR register value.
        response = SendSDCmd(READ_OCR, 0x0);

        // Now that we have the OCR register value in the reponse packet, we could parse
        // the register contents and learn what voltage the SD card wants to run at.
        // If our host circuitry has variable power supply capability, it could 
        // theoretically adjust the SD card Vdd to the minimum of the OCR to save power.
		
		// Now send CMD55/ACMD41 in a loop, until the card is finished with its internal initialization.
		// Note: SD card specs recommend >= 1 second timeout while waiting for ACMD41 to signal non-busy.
		TIMEOUT = TMRGetRTC() + 2000;
		while (TRUE)
			{				
			// Send CMD55 (lets SD card know that the next command is application specific (going to be ACMD41)).
			SendSDCmd(APP_CMD, 0x00000000);
			
			// Send ACMD41.  This is to check if the SD card is finished booting up/ready for full frequency and all
			// further commands.  Response is R3 type (6 bytes/48 bits, middle four bytes contain potentially useful data).
            // Note: When sending ACMD41, the HCS bit is bit 30, and must be = 1 to tell SD card the host supports SDHC
			response = SendSDCmd(SD_SEND_OP_COND,0x40000000); //bit 30 set
			
			// The R1 response should be = 0x00, meaning the card is now in the "standby" state, instead of
			// the "idle" state (which is the default initialization state after CMD0 reset is issued). 
			// Once in the "standby" state, the SD card is finished with basic intitialization and is ready 
			// for read/write and other commands.
			if	( response.r1._byte == 0x00 )
				//Break out of for() loop.  Card is finished initializing.
				break;  
            //---------------------------------------------------------------					
			if	( TMRGetRTC() > TIMEOUT )
	            // Media Timeout on CMD55/ACMD41...
				{
            	SD_CS_LAT = 1;       // deselect the devices
            	return mediaInformation.mediaStatus;
	        	}				
			}	
	
		
		
        // Now send CMD58 (Read OCR register).  The OCR register contains important
        // info we will want to know about the card (ex: standard capacity vs. SDHC).
        response = SendSDCmd(READ_OCR, 0x0); 

		// Now check the CCS bit (OCR bit 30) in the OCR register, which is in our response packet.
		// This will tell us if it is a SD high capacity (SDHC) or standard capacity device.
		if(response.r7.bytewise.argument._returnVal & 0x40000000)	// Note the HCS bit is only valid
																	// when the busy bit is also set
																	// (indicating device ready).
			{
			// Media successfully processed CMD58: SD card is 
			// SDHC v2.0 (or later) physical spec type.
			mediaInformation.mediaMode = SD_MODE_HC;
        	}				
        else
        	{
			// Media successfully processed CMD58: SD card is
			// standard capacity v2.0 (or later) spec.
            mediaInformation.mediaMode = SD_MODE_NORMAL;
        	} 

		//-------------------------------------------------------------------------------------
        //SD Card should now be finished with initialization sequence.  Device should be ready
        //for read/write commands.
		//-------------------------------------------------------------------------------------
		}	//if(((response.r7.bytewise._returnVal & 0xFFF) == 0x1AA) && (!response.r7.bitwise.bits.ILLEGAL_CMD))
    else
		{
        // The CMD8 wasn't supported.  This means the card is not a v2.0 card.
        // Presumably the card is v1.x device, standard capacity (not SDHC).
       mediaInformation.mediaMode = SD_MODE_NORMAL;

        SD_CS_LAT = 1;                              // deselect the devices
        TMRDelay(2);
        SD_CS_LAT = 0;                              // select the device

 
    	// According to the spec CMD1 must be repeated until the card is fully initialized
    	TIMEOUT = TMRGetRTC() + 2000u;
        while (TRUE)
       		{
            // Send CMD1 to initialize the media.
			// When argument is 0x00000000, this queries MMC
			// cards for operating voltage range
            response = SendSDCmd(SEND_OP_COND, 0x00000000);  
			if	(response.r1._byte == 0x00) 
				break;	// Successful responce...
						// However we ignore operating voltage range
						// as all cards support 3.3 V
			//------------------------------------------------------ 
			if	( TMRGetRTC() > TIMEOUT )
	            // Media Timeout on CMD1...
				{
            	SD_CS_LAT = 1;       // deselect the devices
            	return mediaInformation.mediaStatus;
	        	}				
        	};

		// CMD1 Successfully processed, media is no longer busy.
		//---------------------------------------------------------------------
		// Set read/write block length to 512 bytes.  Note: commented out since
		// this theoretically isn't necessary, since all cards v1 and v2 are 
		// required to support 512 byte block size, and this is supposed to be
		// the default size selected on cards that support other sizes as well.
		/*
		response = SendSDCmd(SET_BLOCKLEN, 0x00000200);    //Set read/write block length to 512 bytes
		*/
       
		}


    //Temporarily deselect device
    SD_CS_LAT = 1;
    
    // Basic initialization of media is now complete.  The card will now use push/pull
    // outputs with fast drivers.  Therefore, we can now increase SPI speed to 
    // either the maximum of the microcontroller or maximum of media, whichever 
    // is slower.  MMC media is typically good for at least 20Mbps SPI speeds.  
    // SD cards would typically operate at up to 25Mbps or higher SPI speeds.
    SPIM_Open(SYNC_MODE_FAST);

	SD_CS_LAT = 0;

	// Send the CMD9 to read the CSD register 
    count = NCR_TIMEOUT;
    while (TRUE)
    	{
        //Send CMD9: Read CSD data structure.
		response = SendSDCmd(SEND_CSD, 0x00);
		if ( response.r1._byte == 0x00)
			break; // CSD register successfully read!
        //------------------------------------------------
		count--;
	    if	( count <= 0)
	 		{
	        //Media failed to respond to the read CSD register operation.
	        SD_CS_LAT = 1;
	        return mediaInformation.mediaStatus;
	    	}  
    	}

  
    // CMD9 Successfully processed...
 
	// According to the simplified spec, section 7.2.6, the card will respond
	// with a standard response token, followed by a data block of 16 bytes
	// suffixed with a 16-bit CRC.
	//----------------------------------------------------------------------
	index = 0;
	for (count = 0; count < 20u; count ++)
		{
		CSDResponse[index] = SPIM_Read();
		index++;			
		// Hopefully the first byte is the datatoken, however, some cards do
		// not send the response token before the CSD register.
		if((count == 0) && (CSDResponse[0] == DATA_START_TOKEN))
			{
			// As the first byte was the datatoken, we can drop it.
			index = 0;	// Reset index to first position
			}
		}


	//-------------------------------------------------------------
	// Extract some fields from the response for computing the card capacity.
	// Note: The structure format depends on if it is a CSD V1 or V2 device.
	// Therefore, need to first determine version of the specs that the card 
	// is designed for, before interpreting the individual fields.
	//-------------------------------------------------------------
	// READ_BL_LEN: CSD Structure v1 cards always support 512 byte
	// read and write block lengths.  Some v1 cards may optionally report
	// READ_BL_LEN = 1024 or 2048 bytes (and therefore WRITE_BL_LEN also 
	// 1024 or 2048).  However, even on these cards, 512 byte partial reads
	// and 512 byte write are required to be supported.
	// On CSD structure v2 cards, it is always required that READ_BL_LEN 
	// (and therefore WRITE_BL_LEN) be 512 bytes, and partial reads and
	// writes are not allowed.
	// Therefore, all cards support 512 byte reads/writes, but only a subset
	// of cards support other sizes.  For best compatibility with all cards,
	// and the simplest firmware design, it is therefore preferrable to 
	// simply ignore the READ_BL_LEN and WRITE_BL_LEN values altogether,
	// and simply hardcode the read/write block size as 512 bytes.
	//-------------------------------------------------------------
	// Hardcoding of "mediaInformation.sectorSize = 512" is done
	// at the initialization of this data structure
	//-------------------------------------------------------------

	//-------------------------------------------------------------
	// Calculate the mediaFinalLBA (see SD card physical layer simplified
	// spec 2.0, section 5.3.2).
	// In USB mass storage applications, we will need this information to 
	// correctly respond to SCSI get capacity requests. 
	// NOTE:	method of computing SDMedia_FinalLBA depends on CSD 
	//			structure spec version (either v1 or v2).
	//-------------------------------------------------------------
	if(CSDResponse[0] & 0xC0)	// Check CSD_STRUCTURE field for v2+ struct device
		{
		// Must be a v2 device (or a reserved higher version, that doesn't currently exist)
		// Extract the C_SIZE field from the response.  It is a 22-bit number in bit
		// position 69:48.  This is different from v1. It spans bytes 7, 8, and 9 of the response.
		//---------------------------------------------------------------------------------
		c_size = (((DWORD)CSDResponse[7] & 0x3F) << 16) | ((WORD)CSDResponse[8] << 8) | CSDResponse[9];
		// "-1" on end is correction factor, since LBA is zero-based.
		mediaInformation.mediaFinalLBA = ((DWORD)(c_size + 1) * (WORD)(1024u)) - 1; 
		}
	else 
		{
		// Check CSD_STRUCTURE field for v1 struct device
		// Must be a v1 device.
		// Extract the C_SIZE field from the response.  It is a 12-bit number in bit position 73:62.  
		// Although it is only a 12-bit number, it spans bytes 6, 7, and 8, since it isn't byte aligned.
		//---------------------------------------------------------------------------------------------
		// Get the bytes in the correct positions
		c_size = ((DWORD)CSDResponse[6] << 16) | ((WORD)CSDResponse[7] << 8) | CSDResponse[8];	
		//---------------------------------------------------------------------------------------------
		c_size &= 0x0003FFC0;	// Clear all bits that aren't part of the C_SIZE
		c_size = c_size >> 6;	// Shift value down, so the 12-bit C_SIZE is properly right justified
								// in the DWORD.
		
		//Extract the C_SIZE_MULT field from the response.  It is a 3-bit number in bit position 49:47.
		c_size_mult = ((WORD)((CSDResponse[9] & 0x03) << 1)) | ((WORD)((CSDResponse[10] & 0x80) >> 7));

        //Extract the BLOCK_LEN field from the response. It is a 4-bit number in bit position 83:80.
        block_len = CSDResponse[5] & 0x0F;

        block_len = 1 << (block_len - 9); //-9 because we report the size in sectors of 512 bytes each
		
		//Calculate the SDMedia_FinalLBA (see SD card physical layer simplified spec 2.0, section 5.3.2).
		//In USB mass storage applications, we will need this information to 
		//correctly respond to SCSI get capacity requests (which will cause SD_SPI_ReadCapacity() to get called).
		// "-1" on end is correction factor, since LBA = 0 is zero-based.
		mediaInformation.mediaFinalLBA = ((DWORD)(c_size + 1) * (WORD)((WORD)1 << (c_size_mult + 2)) * block_len) - 1;		
		}	

    // Turn off CRC7 if we can, might be an invalid cmd on some cards (CMD59)
    // Note: POR default for the media is normally with CRC checking off in SPI 
    // mode anyway, so this is typically redundant.
    SendSDCmd(CRC_ON_OFF, 0x0);

    // Now set the block length to media sector size. It should be already set to this.
    SendSDCmd(SET_BLOCKLEN, 512u);

    // Deselect media while not actively accessing the card.
    SD_CS_LAT = 1;

	mediaInformation.mediaStatus	= MEDIA_NO_ERROR;

    return mediaInformation.mediaStatus;
	}	// --------end MediaInitialize--------

