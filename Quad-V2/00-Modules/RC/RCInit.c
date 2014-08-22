#include "RC/RCLocal.h"
#include "TMR/TMR.h"


//************************************************************
// RCInit function initializes IC Module.
//************************************************************
// The Radio Control module uses Timer3 to avoid blocking if
// connection to transmitter is lost (or receiver is not con-
// nected to the board).
//------------------------------------------------------------
// RCInit() function besides initializing Change Notification
// also initializes Timer3 module for the requested frequency.
// Please Do Not Change Timer3 settings to avoid breaking
// RC operation.
//-----------------------------------------------------
void	RCInit(int IL)
	{
	// Validate requested Interrup Level value
	//----------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_RCIL	= IL;
	//----------------------------------------------------

	//************************************************
	// RC group of functions depend on timer providing
	// timestamps for interval measurement, thus we
	// make sure that timers are intitialized.
	//************************************************
	TMRInitDefault();

	//-----------------------------------------------------
	// Set respective pins as INPUT (should have been set
	// as INPUT on RESET, nevertheless...)
	//-----------------------------------------------------
	_TRISC7		= 1;		// Ch1
	_TRISC8		= 1;		// Ch2
	_TRISC9		= 1;		// Ch3
	_TRISB10	= 1;		// Ch4
	_TRISB11	= 1;		// Ch5
	//-----------------------------------------------------
	// Enable Weak Pull-Up on receiver pins (to allow ope-
	// ration when receiver is not plugged in)
	//-----------------------------------------------------
	_CN17PUE	= 1;		// Ch1
	_CN20PUE	= 1;		// Ch2
	_CN19PUE	= 1;		// Ch3
	_CN16PUE	= 1;		// Ch4
	_CN15PUE	= 1;		// Ch5
	//-----------------------------------------------------

	//-----------------------------------------------------
	// Disable all individual change notifications
	//-----------------------------------------------------
	CNEN1	= 0;
	CNEN2	= 0;

	//-----------------------------------------------------
	// Set general CN interrupt control
	//-----------------------------------------------------
	_CNIF 		= 0; 		// Reset CN interrupt request
	_CNIP 		= _RCIL;	// Set CN interrupt priority
	_CNIE 		= 1; 		// Enable CN interrupts

	//=========================================================
	// The Receiver Control module uses Timer3
	//---------------------------------------------------------
	// Stop/Disable Timer3; reset all flags
	//---------------------------------------------------------
	T3CON		= 0;
	// Enable Timer3 if disabled through PMD
	_T3MD		= 0;	// Timer3 module enabled
	// Set Timer3 prescaler to 1:64 (tick = 1.6 usec)
	T3CONbits.TCKPS	= 0b10;
	//---------------------------------------------------------							
	// Configure Timer2 interrupt priority
	//---------------------------------------------------------							
	_T3IF 	= 0 ; 				// Clear TMR3 interrupt flag
	_T3IP	= _RCIL;			// Set the same priority as for CN
								// interrupts.
	_T3IE 	= 1 ;   			// Enable TMR3 CPU interrupt
	PR3		= _RC_Tmr_Count;	// Set Timer3 rolover threshold
								// (RC "safety" interval)
	//=========================================================

	//=========================================================
	// Reset control automaton
	//-----------------------------------------------------
	_RCState		= 0;	
	_CN17IE			= 1;	// Enable CN interrupt on Ch1 (CN17/RC7)
							// Hopefully CN interrupt will happen
							// before the Timer3 interrupt :)	
	//-----------------------------------------------------
	// Start Safety Margin timer
	//-----------------------------------------------------
	TMR3			= 0;	// Re-set Timer3 counter
	_T3IF 			= 0 ; 	// Clear TMR3 interrupt flag
	T3CONbits.TON 	= 1; 	// Start Timer3 - counting 25 msec;
	//---------------------------						
	return;
	}
//************************************************************






