//******************************************************************************
// *
// *                Microchip Memory Disk Drive File System
// *
//******************************************************************************
// * FileName:        HardwareProfile.h
// * Dependencies:    None
// * Processor:       PIC24/dsPIC30/dsPIC33
//*****************************************************************************


#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_
//===============================================================================

//*****************************************************************************
// Define your clock speed here
//*****************************************************************************
#define Fosc()        80000000
// For PIC24/dsPIC30/dsPIC33 Instruction cycle speed is
// half of the Oscillator speed
#define Fcy()   	(Fosc() / 2)

//-----------------------------------------------------
// Will generate an error if the clock speed is too low
// to interface to the card
//-----------------------------------------------------
#if (Fosc() < 100000)
    #error Oscillator clock speed must exceed 100 kHz
#endif    



//*****************************************************************************
//******************* Special Pin and Register Definitions ********************
//*****************************************************************************
// SD Card definitions: Change these to fit your application when using
// an SD-card-based physical layer 

//*****************************************************************************
// Pin definition for Media-Detect 
//*****************************************************************************
// The SD_SPI Card Sense Port bit
#define SD_SENSE_PORT		_RB11			// RB11 (CN15) linked to SENSE pin
// The SD_SPI Card Sense TRIS bit
#define SD_SENSE_TRIS		_TRISB11		
// The SD_SPI Card Sense Weak Pull-Up bit
#define SD_SENSE_PUE		_CN15PUE

//*****************************************************************************
// Pin definition (LAT and TRIS) for CS (card-select) line
//*****************************************************************************
// Description: SD-SPI Chip Select TRIS bit
#define SD_CS_TRIS          _TRISB15
// Description: SD-SPI Chip Select Output bit
#define SD_CS_LAT			_LATB15

//*****************************************************************************
// Pins for SCK/SDI/SDO lines
//*****************************************************************************
// Should be assigned and mapped to respective SPI registers in SPI
// initialization routine BEFORE invoking any routines in SD-SPI.

//*****************************************************************************
// Registers for the SPI module you want to use
//*****************************************************************************
// PMD bit for selected SPI module
#define	SPIMD				_SPI1MD
// The main SPI control register
#define SPICON1             SPI1CON1
// The bitwise define for the SPI control register (i.e. _____bits)
#define SPICON1bits         SPI1CON1bits

// The supplementary SPI control register
#define SPICON2             SPI1CON2

// The SPI status register
#define SPISTAT             SPI1STAT
// The bitwise define for the SPI status register (i.e. _____bits)
#define SPISTATbits         SPI1STATbits
// The enable bit for the SPI module
#define SPIENABLE           SPISTATbits.SPIEN
// The receive buffer full bit in the SPI status register
#define SPISTAT_RBF         SPI1STATbits.SPIRBF

// Description: The SPI Buffer
#define SPIBUF              SPI1BUF



//===============================================================================
#endif				// #ifndef _HARDWAREPROFILE_H_
