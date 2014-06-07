#ifndef HMCSPI_PROFILE_H
#define	HMCSPI_PROFILE_H
//==================================================================
// SPI FIFO buffer depth
//------------------------------------------------------------------
#define _SPI_FIFO		8
//------------------------------------------------------------------
// SPI Module definitions - please update depending on the module
// 							used in the current application.
//------------------------------------------------------------------
// SPI Interrupt routines
//------------------------------------------------------------------
#define SPIInterrupt	_SPI1Interrupt
//------------------------------------------------------------------
// SPI Registers
//------------------------------------------------------------------
// SPI Status and Control register
//------------------------------------------------------------------
#define	SPISTAT			SPI1STAT
//------------------------------------------------------------------
// SPI STATUS bits/flags
//------------------------------------------------------------------
// SPI Module Enable bit
#define SPIEN			SPI1STATbits.SPIEN
// SPI FIFO counter
#define	SPIBEC			SPI1STATbits.SPIBEC
// SPI Shift Register empty bit (1 = empty)
#define SREMPTY			SPI1STATbits.SRMPT
// SPI Receive overflow bit
#define	SPIROV			SPI1STATbits.SPIROV
// SPI Receive FIFO empty bit (1 = Empty)
#define SRXEMPTY		SPI1STATbits.SRXMPT
// SPI Buffer interrupt mode
#define SISEL			SPI1STATbits.SISEL

//------------------------------------------------------------------
// SPI Control register	1
//------------------------------------------------------------------
#define	SPICON1			SPI1CON1
//------------------------------------------------------------------
// SPI Control register 1 bits/flags 
//------------------------------------------------------------------
// SPI Word/Byte Select bit (1 = Word communication)
#define	MODE16			SPI1CON1bits.MODE16
// SPI Clock polarity select bit (1 = idle HIGH)
#define CKP				SPI1CON1bits.CKP
// SPI Master Mode enable bit (1 = Master)
#define	MSTEN			SPI1CON1bits.MSTEN
// SPI Secondary prescaler bits
#define SPRE			SPI1CON1bits.SPRE
//		111 = Secondary prescale 1:1
//		110 = Secondary prescale 2:1
//		?
//		?
//		?
//		000 = Secondary prescale 8:1
// SPI Primary prescaler bits
#define	PPRE			SPI1CON1bits.PPRE
//		11 = Primary prescale 1:1
//		10 = Primary prescale 4:1
//		01 = Primary prescale 16:1
//		00 = Primary prescale 64:1
//------------------------------------------------------------------

//------------------------------------------------------------------
// SPI Control register	2
//------------------------------------------------------------------
#define	SPICON2			SPI1CON2
// SPI Enhanced Buffer (FIFO) Enable bit
#define	SPIBEN			SPI1CON2bits.SPIBEN

//------------------------------------------------------------------
// SPI Read/Write buffer register
//------------------------------------------------------------------
#define SPIBUF			SPI1BUF


//------------------------------------------------------------------
// SPI interrupt bits
//------------------------------------------------------------------
// SPI Interrupt control bit
#define	SPI_IE			_SPI1IE
// SPI Interrupt flag
#define	SPI_IF			_SPI1IF
// SPI Interrupt priority
#define	SPI_IP			_SPI1IP

//------------------------------------------------------------------
// Peripheral Module Disable (PMD) register for selected SPI Module
//------------------------------------------------------------------
#define	SPI_MD			_SPI1MD
//==================================================================

//==================================================================
// IC Module definitions - please update depending on the module
// 						   used in the current application.
//------------------------------------------------------------------
// Definition for the pin that will be used by Input Capture module
// NOTE: Changes to this definition should be coordinated with the
//		 respective changes to the helper function responsible for
//		 mapping pin(s) to Input Capture module _SR04InitPinMap()
//------------------------------------------------------------------
// Input Capture Interrupt routines
//------------------------------------------------------------------
#define ICInterrupt		_IC4Interrupt
//------------------------------------------------------------------
// Input Capture Registers
//------------------------------------------------------------------
// Input Capture Control register
#define	ICCON1			IC4CON1
#define ICCON2			IC4CON2
#define ICBUF			IC4BUF;
//------------------------------------------------------------------
// Input Capture Control bits/flags
//------------------------------------------------------------------
// Input Capture Mode Select bits
// ICM = 0 disables Input Capture module
// ICM = 1 - Capture mode, every edge (rising and falling)
// (ICI bits do not control interrupt generation for this mode)
//------------------------------------------------------------------
#define ICM				IC4CON1bits.ICM
#define ICBNE			IC4CON1bits.ICBNE

//------------------------------------------------------------------
// Input Capture interrupt bits
//------------------------------------------------------------------
// Input Capture interrupt control bit
#define	IC_IE			_IC4IE
// Input Capture interrupt flag
#define	IC_IF			_IC4IF
// Input Capture Interrupt priority
#define	IC_IP			_IC4IP
//------------------------------------------------------------------

//------------------------------------------------------------------
// Peripheral Module Disable (PMD) register for selected
// Input Capture Module
//------------------------------------------------------------------
#define	IC_MD			_IC4MD
//==================================================================



//==================================================================
// Slave Select (SS) port definition
//------------------------------------------------------------------
#define CS_TRIS			_TRISB6
#define	CS_LAT			_LATB6
#define	CS				_RB6
// Slave Select control macros (Active Low)
#define	CS_Start()		CS_LAT = 0
#define	CS_Stop()		CS_LAT = 1

//------------------------------------------------------------------
// Data Ready (DRDY) port definition
// This is the port linked with the ICx module to capture transitions
//------------------------------------------------------------------
#define	DRDY			_RB5

//==================================================================
// Helper function _HMCInitPinMap(void) implements configuration
// (and mapping, if needed) of Control pins
//==================================================================
static inline void _HMCInitPinMap(void)
	{
	//=========================================================
	//	Slave Select Pin 	= RP38/RB6
	//  DRDY Interrupt pin	= RP37/RB5
	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure Slave Select pin
	//---------------------------------------------------------
	CS_TRIS		= 0;	// Pin configured as otput
	CS_Stop();			// Set to inactive state
	//=========================================================
	//	ICx Sense Pin 	= RP6/RB6
	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure DRDY Interrupt pin and link it to ICx
	//---------------------------------------------------------
	_TRISB5	= 1;	// RB5 Pin configured as Input
	_IC4R	= 37; 	// (IN)  IC1 mapped to pin RP37/RB5
	//---------------------------------------------------------
	return;
	}
//==================================================================
#endif	/* HMCSPI_PROFILE_H */

