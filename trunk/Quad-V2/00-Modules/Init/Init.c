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
_FPOR		( FPWRT_PWR64 & ALTI2C_ON);	
								// Power-on Reset Value: 64 ms
								// I2C mapped to ASDA1/ASCL1 pins
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


void	Init()
	{
	//*****************************************************************
	// Switch to operation at 50 MHz driven by external 12 MHz crystall
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
	// NOTE: Pins configured as digital inputs do not
	// convert an analog input. Analog levels on any
	// pin defined as a digital input (including the
	// ANx pins) can cause the input buffer to consume
	// current that exceeds the device specifications.
	//-----------------------------------------------
	// Thus, for safety reason, we leave all pins
	// shared with ANx pins in default ANALOG state.
	//***********************************************
	// Disable ADC through the control register
	//----------------------------------------------- 
	// As we did not disable ADC through the PMD fea-
	// ture (to avoid overloading corresponding pins),
	// we should disable it through the Control Regis-
	// ter (this does not have effect on the ANx pins -
	// they are still in the ANALOG mode)
	//***********************************************
	AD1CON1 = 0x0000;

	//***********************************************
	// Disable all HW modules except ADC
	// (using PERIPHERAL MODULE DISABLE CONTROL)
	//***********************************************
	PMD1 = 0xFFFE;		// AD1MD = 0 => Shared ANx
						// pins are left at default
						// ANALOG mode
	PMD2 = 0xFFFF;
	PMD3 = 0xFFFF;	


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
	
	}


