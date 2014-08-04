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
// Slave Select (SS) port definition
//------------------------------------------------------------------
#define CS_TRIS			_TRISE5
#define	CS_LAT			_LATE5
#define	CS				_RE5
// Slave Select control macros (Active Low)
#define	CS_Start()		CS_LAT = 0
#define	CS_Stop()		CS_LAT = 1
//==================================================================

//==================================================================
// HMC5983 needs to be associated with one of the INTx Modules -
// please update definitions below depending on the allocation of
// external interrup modules INTx to respective HMC5983 interrupt
// line.
//------------------------------------------------------------------
// INT1 module of the PIC MCU allocated to HMC5983 interrupt line
//------------------------------------------------------------------
// INTx interrupt bits
//--------------------------------------------------------------
// INTx interrupt control bit
#define	HMC_IE			_INT1IE
// INTx interrupt flag
#define	HMC_IF			_INT1IF
// INTx Interrupt priority
#define	HMC_IP			_INT1IP
// INTx Edge Detect Polarity Select bit
#define HMC_EP			_INT1EP
//--------------------------------------------------------------
// INTx Interrupt routines
//--------------------------------------------------------------
#define HMC_Interrupt           _INT1Interrupt
//------------------------------------------------------------------
// Data Ready (DRDY) port definition
// This is the port linked with the INTx module to capture Data
// Ready notification from the sensor.
//------------------------------------------------------------------
#define	DRDY			_RE6
//==================================================================


//==================================================================
// Helper function _HMCInitPinMap(void) implements configuration
// (and mapping, if needed) of Control pins
//==================================================================
static inline void _HMCInitPinMap(void)
	{
	//=========================================================
	//	Slave Select Pin 	= RP85/RE5
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
	CS_Stop();		// Set to inactive state
	//=========================================================
	//	INTx (DRDY)Trigger Pin 	= RPI86/RE6
	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure DRDY Interrupt pin and link it to INTx
	//---------------------------------------------------------
	_TRISE6	= 1;	// RE6 Pin configured as Input
	_INT1R	= 86; 	// (IN) INT1 mapped to pin RPI86/RE6
	//---------------------------------------------------------
	return;
	}
//==================================================================
#endif	/* HMCSPI_PROFILE_H */

