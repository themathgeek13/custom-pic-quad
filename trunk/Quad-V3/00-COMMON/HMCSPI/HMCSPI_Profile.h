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
#define SPIInterrupt	_SPI2Interrupt
//------------------------------------------------------------------
// SPI Registers
//------------------------------------------------------------------
// SPI Status and Control register
//------------------------------------------------------------------
#define	SPISTAT			SPI2STAT
//------------------------------------------------------------------
// SPI STATUS bits/flags
//------------------------------------------------------------------
// SPI Module Enable bit
#define SPIEN			SPI2STATbits.SPIEN
// SPI FIFO counter
#define	SPIBEC			SPI2STATbits.SPIBEC
// SPI Shift Register empty bit (1 = empty)
#define SREMPTY			SPI2STATbits.SRMPT
// SPI Receive overflow bit
#define	SPIROV			SPI2STATbits.SPIROV
// SPI Receive FIFO empty bit (1 = Empty)
#define SRXEMPTY		SPI2STATbits.SRXMPT
// SPI Buffer interrupt mode
#define SISEL			SPI2STATbits.SISEL

//------------------------------------------------------------------
// SPI Control register	1
//------------------------------------------------------------------
#define	SPICON1			SPI2CON1
//------------------------------------------------------------------
// SPI Control register 1 bits/flags 
//------------------------------------------------------------------
// SPI Word/Byte Select bit (1 = Word communication)
#define	MODE16			SPI2CON1bits.MODE16
// SPI Clock polarity select bit (1 = idle HIGH)
#define CKP				SPI2CON1bits.CKP
// SPI Master Mode enable bit (1 = Master)
#define	MSTEN			SPI2CON1bits.MSTEN
// SPI Secondary prescaler bits
#define SPRE			SPI2CON1bits.SPRE
//		111 = Secondary prescale 1:1
//		110 = Secondary prescale 2:1
//		?
//		?
//		?
//		000 = Secondary prescale 8:1
// SPI Primary prescaler bits
#define	PPRE			SPI2CON1bits.PPRE
//		11 = Primary prescale 1:1
//		10 = Primary prescale 4:1
//		01 = Primary prescale 16:1
//		00 = Primary prescale 64:1
//------------------------------------------------------------------

//------------------------------------------------------------------
// SPI Control register	2
//------------------------------------------------------------------
#define	SPICON2			SPI2CON2
// SPI Enhanced Buffer (FIFO) Enable bit
#define	SPIBEN			SPI2CON2bits.SPIBEN

//------------------------------------------------------------------
// SPI Read/Write buffer register
//------------------------------------------------------------------
#define SPIBUF			SPI2BUF


//------------------------------------------------------------------
// SPI interrupt bits
//------------------------------------------------------------------
// SPI Interrupt control bit
#define	SPI_IE			_SPI2IE
// SPI Interrupt flag
#define	SPI_IF			_SPI2IF
// SPI Interrupt priority
#define	SPI_IP			_SPI2IP

//------------------------------------------------------------------
// Peripheral Module Disable (PMD) register for selected SPI Module
//------------------------------------------------------------------
#define	SPI_MD			_SPI2MD
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
#define ICInterrupt		_IC5Interrupt
//------------------------------------------------------------------
// Input Capture Registers
//------------------------------------------------------------------
// Input Capture Control register
#define	ICCON1			IC5CON1
#define ICCON2			IC5CON2
#define ICBUF			IC5BUF;
//------------------------------------------------------------------
// Input Capture Control bits/flags
//------------------------------------------------------------------
// Input Capture Mode Select bits
// ICM = 0 disables Input Capture module
// ICM = 1 - Capture mode, every edge (rising and falling)
// (ICI bits do not control interrupt generation for this mode)
//------------------------------------------------------------------
#define ICM				IC5CON1bits.ICM
#define ICBNE			IC5CON1bits.ICBNE

//------------------------------------------------------------------
// Input Capture interrupt bits
//------------------------------------------------------------------
// Input Capture interrupt control bit
#define	IC_IE			_IC5IE
// Input Capture interrupt flag
#define	IC_IF			_IC5IF
// Input Capture Interrupt priority
#define	IC_IP			_IC5IP
//------------------------------------------------------------------

//------------------------------------------------------------------
// Peripheral Module Disable (PMD) register for selected
// Input Capture Module
//------------------------------------------------------------------
#define	IC_MD			_IC5MD
//==================================================================



//==================================================================
// Slave Select (SS) port definition
//------------------------------------------------------------------
#define CS_TRIS			_TRISE5
#define	CS_LAT			_LATE5
#define	CS				_RE5
// Slave Select control macros (Active Low)
#define	CS_Start()		CS_LAT = 0
#define	CS_Stop()		CS_LAT = 1

//------------------------------------------------------------------
// Data Ready (DRDY) port definition
// This is the port linked with the ICx module to capture transitions
//------------------------------------------------------------------
#define	DRDY			_RE6

//==================================================================
// Helper function _HMCInitPinMap(void) implements configuration
// (and mapping, if needed) of Control pins
//==================================================================
static inline void _HMCInitPinMap(void)
	{
	//=========================================================
	//	Slave Select Pin 	= RP85/RE5
	//  DRDY Interrupt pin	= RPI86/RE6
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
	_TRISE6	= 1;	// RE6 Pin configured as Input
	_IC5R	= 86; 	// (IN) IC1 mapped to pin RPI86/RE6
	//---------------------------------------------------------
	return;
	}
//==================================================================
#endif	/* HMCSPI_PROFILE_H */

