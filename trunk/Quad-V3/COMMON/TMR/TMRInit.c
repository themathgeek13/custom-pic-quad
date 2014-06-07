#include "TMR\TMRLocal.h"

//*************************************************************
void	TMRInitDefault()
	{TMRInit(_TMRIL);}
//*************************************************************


//************************************************************
void	TMRInit(uint IL)
	//----------------------------------------------------
	// NOTE: Please check "TMR.h" for expected assumptions
	//		 regarding system clock.
	//----------------------------------------------------
	{
	if (_TMRInit)
		return;					// Timer has been initialized
	//----------------------------------------------------
	_TMRInit			= 1;	// Timers Initialized
	//----------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_TMRIL	= IL;
	//----------------------------------------------------
	
	//****************************************************
	// Configure TMR4:5 - timestamp generator
	//----------------------------------------------------
	// For a 32-bit timer, Timer4 control registers control
	// parameters, while Timer5 control registers control
	// interrupts.
	//****************************************************
	// Stop both timers:
	T4CON				= 0;
	T5CON				= 0;
	//****************************************************
	// Enable Timer4:5 modules, if disabled through PMD
	//****************************************************
	_T4MD	= 0;	// Timer4 module enabled
	_T5MD	= 0;	// Timer5 module enabled
	
	// Re-set both timers:
	TMR4				= 0;
	TMR5				= 0;
	// Reset timer "threshold":
	PR4					= 0xffff;
	PR5					= 0xffff;
	//----------------------------------------------------------
	T4CONbits.T32		= 0b1;	// Create 32-bit timer
	T4CONbits.TCKPS		= 0b10;	// 1:64 prescaler, timer resolu-
								// tion: 1 usec, total timer
								// rotation ~ 70 min
	//=========================================================
	// Configure Timer4:5 interrupts
	//---------------------------------------------------------							
	_T5IF 			= 0 ; 		// Clear TMR5 interrupt flag
	_T5IE 			= 0 ;   	// Disable TMR5 CPU interrupt

	//=========================================================
	T4CONbits.TON	= 1;		// Start 32-bit interval timer...
	//---------------------------------------------------------


	//=========================================================
	// Initialize and Configure Timer1 as Real Time timer
	//---------------------------------------------------------
	T1CON			= 0;		// Stop timer
								// Select internal instruction cycle Fcy
								// Disable Gated Timer mode
	//---------------------------------------------------------
	_T1MD			= 0;		// Enable Timer1 module
	/*
	// T1CON bits:
	bit 5-4 TCKPS<1:0>: Timer1 Input Clock Prescale Select bits
	11 = 1:256
	10 = 1:64
	01 = 1:8
	00 = 1:1
	*/
	T1CONbits.TCKPS		= 0b01;		// 1:8 prescaler, timer resolu-
									// tion: 125 nsec
									// Maximum interval ~8 msec
	//---------------------------------------------------------
	TMR1 				= 0; 		// Clear timer register
	PR1					= 999;		// 125 usec cycle
	//=========================================================
	// Configure Timer1 interrupts
	//---------------------------------------------------------							
	_T1IP		= _TMRIL;	// Set Timer1 interrupt priority
	_T1IF 		= 0 ; 		// Clear TMR1 interrupt flag
	_T1IE 		= 1; 		// Enable Timer1 interrupt
	//---------------------------------------------------------							
	T1CONbits.TON 		= 1; 		// Start Timer 1

	//****************************************************
	// Timer component uses CRC interrupt for asynchronous
	// callback operation; to avoid collision
	// with CRC, the module should be disabled!
	//****************************************************
	// Disable CRC module:
	CRCCON1		= 0;	// Stop CRC module
	// NOTE: While we are not really using CRC module features,
	// but only the CRC interrupt routine as a "software" in-
	// terrupt, for the MCU to "honor" CRC interrupt flag
	// (that is to actually trigger interrupt routine) the
	// corresponding module (CRC in this case) has to be
	// enabled in PMD.
	_CRCMD		= 0;	// Enable CRC module in PMD
								
	//=========================================================
	// Configure CRC interrupt
	//---------------------------------------------------------							
	_CRCIE 	= 0; 		// Disable CRC interrupt
	_CRCIF 	= 0; 		// Clear CRC interrupt flag
	_CRCIP	= 1;		// Set CRC interrupt priority to the
						// lowest interrupt level
	//---------------------------------------------------------							

	}
//************************************************************

