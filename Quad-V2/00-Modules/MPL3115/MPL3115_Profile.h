#include "I2C\I2C_Profile.h"
//==================================================================
#ifndef MPL3115_PROFILE_H
#define	MPL3115_PROFILE_H

//==================================================================
// For interrupt processing MPL3115 relies on the Input Capture
// module of the PIC MCU.
//------------------------------------------------------------------
// As MPL3115 uses I2C for communication, it has to be defined as a
// "Subscriber" in the I2C_Profile.h and reserve Subscriber ID (1-4)
//------------------------------------------------------------------
#define MPL_I2C_SubID	3
//------------------------------------------------------------------
// Input Capture interrupt bits
// (should match subscriber definition in I2C_Profile.h)
//------------------------------------------------------------------
// Input Capture interrupt control bit
#define	MPL_IE			_IC1IE
// Input Capture interrupt flag
#define	MPL_IF			_IC1IF
// Input Capture Interrupt priority
#define	MPL_IP			_IC1IP
//------------------------------------------------------------------
// Peripheral Module Disable (PMD) register for selected
// Input Capture Module
//------------------------------------------------------------------
#define	MPL_PMD			_IC1MD
//------------------------------------------------------------------

//==================================================================
// IC Module definitions - please update depending on the module
// 						   used in the current application.
//------------------------------------------------------------------
// Definition for the pin that will be used by Input Capture module
// NOTE: Changes to this definition should be coordinated with the
//		 respective changes to the helper function responsible for
//		 mapping pin(s) to Input Capture module _MPLInitPinMap()
//------------------------------------------------------------------
#define MPL_INT_PORT	_RB2
//------------------------------------------------------------------
// Input Capture Interrupt routines
//------------------------------------------------------------------
#define MPL_Interrupt	_IC1Interrupt
//------------------------------------------------------------------
// Input Capture Registers
//------------------------------------------------------------------
// Input Capture Control register
#define	MPL_ICCON		IC1CON
//------------------------------------------------------------------
// Input Capture Control bits/flags
//------------------------------------------------------------------
// Input Capture Mode Select bits
// ICM = 0 disables Input Capture module
// ICM = 1 - Capture mode, every edge (rising and falling)
// (ICI bits do not control interrupt generation for this mode)
//------------------------------------------------------------------
#define MPL_ICM			IC1CONbits.ICM
//==================================================================


//==================================================================
// Helper function _MPLInitPinMap(void) implements mapping
// of Input Capture module pins using Peripheral Pin Select
//==================================================================
static inline void _MPLInitPinMap(void)
	{
	//--------------------------------------------------------
	// PIC24HJ128GPxxx Input Capture pin map for this application
	//--------------------------------------------------------
	//	ICx Sense Pin 	= RP2/RB2
	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure Sense pin
	//---------------------------------------------------------
	// NOTE: Selected pin (RP2/RB2) is shared with ADC as AN4;
	//		 To use it for Input Capture module it should be
	//		 released from ADC for Digital IO
	//---------------------------------------------------------
	_PCFG4	= 1;	// Release AN4 (RP2/RB2) to Digital IO
	_TRISB2	= 1;	// Configure RB2 port for INPUT
	_IC1R	= 2; 	// (IN)  IC1 mapped to pin RP2/RB2
	//---------------------------------------------------------
	return;
	}
//==================================================================

#endif	/* MPL3115_PROFILE_H */

