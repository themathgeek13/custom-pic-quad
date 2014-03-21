#include "Init.h"

//**********************************************************************
// Configuration fuses:
//----------------------------------------------------------------------
// Register FICD (0xf8000e) 
//----------------------------------------------------------------------
_FICD		( ICS_PGD1 & JTAGEN_OFF);	
								// Communicate on PGEC1 and PGED1
								// JTAG Port: Disabled
//----------------------------------------------------------------------
// Register FPOR (0xf8000c)
//----------------------------------------------------------------------
_FPOR		( FPWRT_PWR64 );	
								// Power-on Reset Value: 64 ms
//----------------------------------------------------------------------
// Register FWDT (0xf8000a)
//----------------------------------------------------------------------
_FWDT		( FWDTEN_OFF );		//  Watchdog Timer: Disabled
//----------------------------------------------------------------------
// Register FOSC (0xf80008)
//----------------------------------------------------------------------
_FOSC		( FCKSM_CSECMD & POSCMD_HS & IOL1WAY_OFF)	
								// Only clock switching is enabled
								// HS Oscillator enabled (for 12 MHz)
								// Force single configuration for re-
								// mappable IO: Disabled
//----------------------------------------------------------------------
// Register FOSCSEL (0xf80006)
//----------------------------------------------------------------------
_FOSCSEL	( FNOSC_FRC & IESO_OFF)		
								// Initial Oscillator: Fast RC oscillator
								// Two-speed Oscillator Startup: Disabled
//**********************************************************************

//----------------------------------------------------------------------
// This board contains two DIP switches; their values are read and
// stored for subsequent use in this Initialization routine
//----------------------------------------------------------------------
uint	_SW1		= 0;
uint	_SW2		= 0;

void	Init()
	{
	//*****************************************************************
	// Switch to operation at 40 MHz driven by external 12 MHz crystall
	//-----------------------------------------------------------------
	// PLL Pre-scaler
	_PLLPRE = 1;		// N1 	= (PLLPRE + 2) 	= 3;
						// Fref	= 12 MHz / 3 	= 4 MHz;
	// PLL Multiplier
	_PLLDIV = 38;		// M	= (PLLDIV + 2)	= 40;
						// Fvco = Fref * M		= 160 MHz
	// PLL Post-scaler
	_PLLPOST = 0;		// N2 	= (PLLPOST + 2) = 2;
						// Fosc	= Fvco / N2		= 80 MHz

	// By definition, Fcy = Fosc/2 = 80 MHz / 2 = 40 MHz
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

	//***********************************************
	// Put ALL Analog pins into Digital mode
	//***********************************************
	AD1PCFGL = 0xFFFF;

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
	//***********************************************
	// Clear ALL Interrupt Flags
	//***********************************************
	IFS0	= 0;
	IFS1	= 0;
	IFS2	= 0;
	IFS3	= 0;
	IFS4	= 0;
	
	//------------------------------------------------------
	// Configure ports RB2 (SW1) and RB3 (SW2)connected to
	// 2-position DIP Switch. These ports are multiplexed
	// with AN4 and AN5, but all analog ports are already
	// put into Digital mode above.
	//------------------------------------------------------
	// NOTE: In the "ON" position switch connects respective
	//		 port to ground, so we need to reverse read
	//		 value.
	//------------------------------------------------------
	// Configure ports for Input
	_TRISB2	= 1;
	_TRISB3 = 1;
	// Enable weak pull-up on these ports
	_CN6PUE	= 1;
	_CN7PUE = 1;
	// Give ports some time to stabilize after enabling weak pull-up
	Nop();
	Nop();
	Nop();
	Nop();
	// Check port values associated with switches
	if (_RB2)
	  _SW1 = 0;
	else
	  _SW1 = 1;
	if (_RB3)
	  _SW2 = 0;
	else
	  _SW2 = 1;
	}


