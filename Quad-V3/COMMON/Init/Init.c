#include "Init.h"

//**********************************************************************
// Configuration fuses:
//----------------------------------------------------------------------
// Register FOSCSEL (0xf80006)
//----------------------------------------------------------------------
_FOSCSEL	( FNOSC_FRC & IESO_OFF)		
								// Initial Oscillator: Fast RC oscillator
								// Two-speed Oscillator Startup: Disabled
//----------------------------------------------------------------------
// Register FOSC (0xf80008)
//----------------------------------------------------------------------
_FOSC		( FCKSM_CSECMD & POSCMD_HS & IOL1WAY_OFF)	
								// Only clock switching is enabled
								// HS Oscillator enabled (for 12 MHz)
								// Force single configuration for re-
								// mappable IO: Disabled
//----------------------------------------------------------------------
// Register FWDT (0xf8000a)
//----------------------------------------------------------------------
_FWDT		( FWDTEN_OFF );		//  Watchdog Timer: Disabled
//----------------------------------------------------------------------
// Register FPOR (0xf8000c)
//----------------------------------------------------------------------
_FPOR		( ALTI2C1_OFF );
								// I2C1 mapped to SDA1/SCL1 pins
//----------------------------------------------------------------------
// Register FICD (0xf8000e) 
//----------------------------------------------------------------------
_FICD		( ICS_PGD3 & JTAGEN_OFF);
								// Communicate on PGEC1 and PGED1
								// JTAG Port: Disabled
//**********************************************************************

//----------------------------------------------------------------------
// This board contains four DIP switches; their values are read and
// stored for subsequent use in this Initialization routine
//----------------------------------------------------------------------
uint	_SW1		= 0;
uint	_SW2		= 0;
uint	_SW3		= 0;
uint	_SW4		= 0;

void	Init()
	{
	//*****************************************************************
	// Switch to operation at 64 MHz driven by external 12 MHz crystall
	//-----------------------------------------------------------------
	// PLL Pre-scaler
	_PLLPRE = 1;		// N1 	= (PLLPRE + 2) 	= 3;
						// Fref	= 12 MHz / 3 	= 4 MHz;
	// PLL Multiplier
	_PLLDIV = 62;		// M	= (PLLDIV + 2)	= 64;
						// Fvco = Fref * M		= 256 MHz
	// PLL Post-scaler
	_PLLPOST = 0;		// N2 	= (PLLPOST + 2) = 2;
						// Fosc	= Fvco / N2		= 128 MHz

	// By definition, Fcy = Fosc/2 = 128 MHz / 2 = 64 MHz
	//--------------------------------------------------------------------
	// Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
	__builtin_write_OSCCONH(0x03);		// Set OSCCONbits.NOSC = 0b011
	__builtin_write_OSCCONL(0x01);		// Request oscillator switch
				// NOTE: Statement above also sets IOLOCK=0, enabling
				// reconfiguration of remappable peripherals.
				//-----------------------------------------------------
	// Wait for Clock switch to occur
	while (_COSC != 0b011);	// Wait for COSC = NOSC
	// Wait for PLL to lock
	while( !_LOCK);			// Wait for PLL Lock
	
	//***********************************************
	// NOTE: on POR all ports are configured as INPUT
	//***********************************************

	//***********************************************
	// Disable all HW modules 
	// (using PERIPHERAL MODULE DISABLE CONTROL)
	//***********************************************
	PMD1 = 0xFFFF;
	PMD2 = 0xFFFF;
	PMD3 = 0xFFFF;	
	PMD4 = 0xFFFF;
	PMD5 = 0xFFFF;
	PMD6 = 0xFFFF;	
	PMD7 = 0xFFFF;

	//***********************************************
	// Put ALL Analog pins into Digital mode
	//***********************************************
	ANSELB = 0x0000;
	ANSELC = 0x0000;
	ANSELD = 0x0000;
	ANSELE = 0x0000;
	ANSELG = 0x0000;

	//***********************************************
	// Configure Global Interrupt Control
	//***********************************************
	INTCON1			= 0;	// ...nested interrupts
							// enabled...
	INTCON2			= 0;	// ... globally disables
							// all interrupts...
	//***********************************************
	// Disable ALL Interrupts individually
	//***********************************************
	IEC0	= 0;
	IEC1	= 0;
	IEC2	= 0;
	IEC3	= 0;
	IEC4	= 0;
	IEC5	= 0;
	IEC6	= 0;
	IEC7	= 0;
	IEC8	= 0;
	//***********************************************
	// Clear ALL Interrupt Flags
	//***********************************************
	IFS0	= 0;
	IFS1	= 0;
	IFS2	= 0;
	IFS3	= 0;
	IFS4	= 0;
	IFS5	= 0;
	IFS6	= 0;
	IFS7	= 0;
	IFS8	= 0;
	//***********************************************
	// Now that ALL Interrupts are individually
	// disabled, we may enable interrup processing
	// globally
	//***********************************************
	_GIE	= 0b1;

	//------------------------------------------------------
	// Configure ports RD8 (SW1), RD9 (SW2), RD10 (SW3) and
	// RD11 (SW4) connected to the 4-position DIP Switch.
	//------------------------------------------------------
	// NOTE: In the "ON" position switch connects respective
	//		 port to ground, so we need to reverse read
	//		 value.
	//------------------------------------------------------
	// Configure ports for Input
	_TRISD8		= 1;
	_TRISD9		= 1;
	_TRISD10	= 1;
	_TRISD11	= 1;
	// Enable weak pull-up on these ports
	_CNPUD8		= 1;
	_CNPUD9		= 1;
	_CNPUD10	= 1;
	_CNPUD11	= 1;
	// Give ports some time to stabilize after enabling weak pull-up
	Nop();
	Nop();
	Nop();
	Nop();
	//--------------------------------------------
	// Check port values associated with switches
	//--------------------------------------------
	if (_RD8)
	  _SW1 = 0;
	else
	  _SW1 = 1;
	//----------
	if (_RD9)
	  _SW2 = 0;
	else
	  _SW2 = 1;
	//----------
	if (_RD10)
	  _SW3 = 0;
	else
	  _SW3 = 1;
	//----------
	if (_RD11)
	  _SW4 = 0;
	else
	  _SW4 = 1;
	//--------------------------------------------
	}


