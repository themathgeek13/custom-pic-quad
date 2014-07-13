
#ifndef SR04PROFILE_H
#define	SR04PROFILE_H

#include "System.h"

//==================================================================
// IC Module definitions - please update depending on the module
// 						   used in the current application.
//------------------------------------------------------------------
// Definition for the pin that will be used by Input Capture module
// NOTE: Changes to this definition should be coordinated with the
//		 respective changes to the helper function responsible for
//		 mapping pin(s) to Input Capture module _SR04InitPinMap()
//------------------------------------------------------------------
#define ICPORT			_RB3
//------------------------------------------------------------------
// Input Capture Interrupt routines
//------------------------------------------------------------------
#define ICInterrupt		_IC7Interrupt
//------------------------------------------------------------------
// Input Capture Registers
//------------------------------------------------------------------
// Input Capture Control register
#define	ICCON			IC7CON
//------------------------------------------------------------------
// Input Capture Control bits/flags
//------------------------------------------------------------------
// Input Capture Mode Select bits
// ICM = 0 disables Input Capture module
// ICM = 1 - Capture mode, every edge (rising and falling)
// (ICI bits do not control interrupt generation for this mode)
//------------------------------------------------------------------
#define ICM				IC7CONbits.ICM

//------------------------------------------------------------------
// Input Capture interrupt bits
//------------------------------------------------------------------
// Input Capture interrupt control bit
#define	ICIE			_IC7IE
// Input Capture interrupt flag
#define	ICIF			_IC7IF
// Input Capture Interrupt priority
#define	ICIP			_IC7IP
//------------------------------------------------------------------

//------------------------------------------------------------------
// Peripheral Module Disable (PMD) register for selected
// Input Capture Module
//------------------------------------------------------------------
#define	ICMD			_IC7MD



//************************************************************
// Helper function _SR04InitPinMap(void) implements mapping
// of Input Capture module pins using Peripheral Pin Select
//************************************************************
static inline void _SR04InitPinMap(void)
	{
	//--------------------------------------------------------
	// PIC24HJ128GPxxx Input Capture pin map for this application
	//--------------------------------------------------------
	//	ICx Sense Pin 	= RP3/RB3
	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure Sense pin
	//---------------------------------------------------------
	// NOTE: Selected pin (RP3/RB3) is shared with ADC as AN5;
	//		 To use it for Input Capture module it should be
	//		 released from ADC for Digital IO
	//---------------------------------------------------------
	_PCFG5	= 1;	// Release AN5 (RP3/RB3) to Digital IO
	_TRISB3	= 1;	// Configure RB3 port for INPUT
	_IC7R	= 3; 	// (IN)  IC7 mapped to pin RP3/RB3
	//---------------------------------------------------------
	return;
	}


#endif	/* SR04PROFILE_H */

