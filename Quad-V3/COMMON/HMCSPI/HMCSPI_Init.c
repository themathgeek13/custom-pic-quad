#include "HMCSPI\HMCSPI_Local.h"

//*************************************************************
// Forward declaration of initialization helper functions
//-------------------------------------------------------------
void	_HMC_SPIInit();	
void	_HMC_ICxInit();	
						
//*************************************************************
HMC_RC	HMC_Init(byte IL, byte ODR, byte Gain, byte DLPF)
	{
	if (_HMC_Init)
	  return HMC_OK;		// Avoid duplicate initialization
	//---------------------------------------------------------
	_HMC_Init = 1;	// Mark that module is initialized
	//---------------------------------------------------------
	// This module uses timer; hopefully Timer is already
	// initialized, but...
	//---------------------------------------------------------
	TMRInitDefault();
	//---------------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_HMC_IL	= IL;
	//---------------------------------------------------------
	// Prepare SPI and ICx Modules for configuration
	//---------------------------------------------------------
	SPISTAT		= 0;	// Disable ICx for configuration
	ICCON1		= 0;	// Disable ICx for configuration
	//---------------------------------------------------------
	// Please NOTE that the Init program disables all PERIPHERAL
	// MODULES using PMDx registers. To continue configuring and
	// later enabling Input Capture module we need to enable
	// module in PMDx
	//---------------------------------------------------------
	SPI_MD		= 0;	// Enable SPI module
	IC_MD		= 0;	// Enable ICx module
	Nop();				// Skip one cycle to let modules enable
	//---------------------------------------------------------
	// Configure relevant pins of the MCU
	//---------------------------------------------------------
	_HMCInitPinMap ();
	//---------------------------------------------------------
	// Configure SPI Module
	//---------------------------------------------------------
	_HMC_SPIInit();
	//---------------------------------------------------------
	// Configure ICx Module
	//---------------------------------------------------------
	_HMC_ICxInit();
	//---------------------------------------------------------
	return HMC_ReSet(ODR, Gain, DLPF);
	}
//*************************************************************

//*************************************************************
// <editor-fold defaultstate="collapsed" desc="void	_HMC_SPIInit()">
void	_HMC_SPIInit()
	{
	//---------------------------------------------------------
	// Configure SPI Module parameters
	//---------------------------------------------------------
	CKP		= 1;		// Clock - Idle High
	MSTEN	= 1;		// MCU is the master
	SPRE	= 0b111;	// Secondary PRE = 1:1
	PPRE	= 0b01;		// Primary	 PRE = 16:1 for SPI clock
	// speed of 4 MHz assuming MCU runs at
	// 64 MHz
	SPIBEN	= 0b1;		// Enable "enhanced" mode (FIFO)
	//---------------------------------------------------------
	// Configure SPI interrupts
	//---------------------------------------------------------
	SPI_IE	= 0;			// Disable interrupts
	SPI_IF	= 0;			// Reset interrupt request (if any)
	SPI_IP	= _HMC_IL;		// Set interrupt priority
	// Set SPI Buffer interrupt mode (valid only in FIFO Mode)
	SISEL	= 0b101;		// Interrupt when the last bit is
							// shifted out of SPIxSR and the
							// transmit is complete
	//---------------------------------------------------------
	// Start SPI Module
	//---------------------------------------------------------
	SPIEN	= 1;
	//---------------------------------------------------------
	// NOTE: Interrupts for SPI module are still disabled; they
	//		 will be enabled in ICx interrupt routine before
	//		 innitiation of I/O operation
	//---------------------------------------------------------
	return;
	}
// </editor-fold>
//*************************************************************

//*************************************************************
// <editor-fold defaultstate="collapsed" desc="void	_HMC_ICxInit()">
void	_HMC_ICxInit()
	{
	//---------------------------------------------------------
	// NOTE: In this module ICx serves as just interrupt trigger,
	//		 without actually capturing interrupt time. As
	//		 such we should configure it to use some timer -
	//		 the only restriction is that this timer should not
	//		 be part of a 32-bit timer to avoid blocking the
	//		 timer. ICCON = 0 also configures ICx to use
	//		 Timer3, which is free in this application.
	//---------------------------------------------------------
	// Put ICx into the trigger mode
	//---------------------------------------------------------
	ICCON2 = 0;
	//---------------------------------------------------------
	// Configure ICx interrupts
	//---------------------------------------------------------
	IC_IE		= 0;			// Disable ICx interrupt
	IC_IF		= 0; 			// Clear ICx interrupt flag
	IC_IP		= _HMC_IL;		// Set ICx interrupt priority
	//---------------------------------------------------------
	// NOTE: We are leaving ICx Module in DISABLED state;
	//		 It will be enabled when we start HMC Async read.
	//---------------------------------------------------------
	return;
	}
// </editor-fold>
//*************************************************************

