#include "System.h"
//*****************************************************
#include "I2C\I2C_Profile.h"
//==================================================================
#ifndef HMCMAG_PROFILE_H
#define	HMCMAG_PROFILE_H

//==================================================================
// For interrupt processing HMC5883 relies on the Input Capture
// module of the PIC MCU.
//------------------------------------------------------------------
// As HMC5883 uses I2C for communication, it has to be defined as a
// "Subscriber" in the I2C_Profile.h and reserve Subscriber ID (1-4)
//------------------------------------------------------------------
#define HMC_I2C_SubID	2
//------------------------------------------------------------------
// Input Capture interrupt bits
// (should match subscriber definition in I2C_Profile.h)
//------------------------------------------------------------------
// Input Capture interrupt control bit
#define	HMC_IE			_IC2IE
// Input Capture interrupt flag
#define	HMC_IF			_IC2IF
// Input Capture Interrupt priority
#define	HMC_IP			_IC2IP
//------------------------------------------------------------------
// Peripheral Module Disable (PMD) register for selected
// Input Capture Module
//------------------------------------------------------------------
#define	HMC_PMD			_IC2MD
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
// Input Capture Interrupt routines
//------------------------------------------------------------------
#define HMC_Interrupt	_IC2Interrupt
//------------------------------------------------------------------
// Input Capture Registers
//------------------------------------------------------------------
// Input Capture Control register
#define	HMC_ICCON		IC2CON
//------------------------------------------------------------------
// Input Capture Control bits/flags
//------------------------------------------------------------------
// Input Capture Mode Select bits
// ICM = 0 disables Input Capture module
// ICM = 1 - Capture mode, every edge (rising and falling)
// (ICI bits do not control interrupt generation for this mode)
//------------------------------------------------------------------
#define HMC_ICM			IC2CONbits.ICM
//==================================================================


//==================================================================
// Helper function _HMCInitPinMap(void) implements mapping
// of Input Capture module pins using Peripheral Pin Select
//==================================================================
static inline void _HMCInitPinMap(void)
	{
	//--------------------------------------------------------
	// PIC24HJ128GPxxx Input Capture pin map for this application
	//--------------------------------------------------------
	//	ICx Sense Pin 	= RP2/RC4
	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure Interrupt pin
	//---------------------------------------------------------
	_TRISC4 = 1;		// Set RC4 as Input;
	_IC2R	= 20;		// Map IC2 input to RP20;
	//---------------------------------------------------------

	return;
	}
//==================================================================

#endif	/* HMCMAG_PROFILE_H */

