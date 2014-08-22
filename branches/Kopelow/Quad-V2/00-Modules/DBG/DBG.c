#include "DBG/DBG.h"

//************************************************************
void	DBGInit()
	{
	//*******************************************************************
	// Debugger interface uses pins AN4/RB2 and AN5/RB3 for communicating
	// debug signals, so they need to be released for digital I/O
	//-------------------------------------------------------------------
	_PCFG4	= 1;	// Release pin AN4/RB2   for Digital I/O
	_PCFG5	= 1;	// Release pin AN5/RB3   for Digital I/O
	//-------------------------------------------------------------------
	// Now let's configure these pins for Digital Output and set them to 0
	//-------------------------------------------------------------------
	// Configure RB2 as OUTPUT
	_TRISB2		= 0;
	_LATB2		= 0;	// Reset port
	//--------------------------------
	// Configure RB3 as OUTPUT
	_TRISB3		= 0;
	_LATB3		= 0;	// Reset port
	//-------------------------------------------------------------------
	return;
	}
//************************************************************






