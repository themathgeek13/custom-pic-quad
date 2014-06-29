//==================================================================
#ifndef __MPL_PROFILE_H
#define	__MPL_PROFILE_H

//==================================================================
// INTx Module definitions - please update depending on the module
// used in the current application.
//------------------------------------------------------------------
// For interrupt processing MPL3115 relies on the INT4 module of the
// PIC MCU.
//------------------------------------------------------------------
// INT4 interrupt bits
//------------------------------------------------------------------
// INT4 interrupt control bit
#define	MPL_IE			_INT4IE
// INT4 interrupt flag
#define	MPL_IF			_INT4IF
// INT4 Interrupt priority
#define	MPL_IP			_INT4IP
// INT4 Edge Detect Polarity Select bit
#define MPL_EP			_INT4EP
//------------------------------------------------------------------
// INT4 Interrupt routines
//------------------------------------------------------------------
#define MPL_Interrupt	_INT4Interrupt
//==================================================================

//==================================================================
// Definition for the pin that will be used by INT4 module
// NOTE: Changes to this definition should be coordinated with the
//		 respective changes to the helper function responsible for
//		 mapping pin(s) to Input Capture module _MPLInitPinMap()
//------------------------------------------------------------------
#define MPL_INT_PORT	_RB10
//==================================================================


//==================================================================
// Helper function _MPLInitPinMap(void) implements mapping
// of INTx module pins using Peripheral Pin Select
//==================================================================
static inline void _MPLInitPinMap(void)
	{
	//--------------------------------------------------------
	// PIC24EP512GP806 INT4 pin map for this application
	//--------------------------------------------------------
	//	INT4 Sense Pin 	= RP(I)42/RB10
	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure Sense pin
	//---------------------------------------------------------
	// NOTE: Selected pin (RP(I)42/RB10) is shared with ADC as
	//		 AN10; however Init() routine already put all
	//		 analog pins into Digital IO mode
	//---------------------------------------------------------
	_TRISB10 = 1;	// Configure RB10 port for INPUT
	_INT4R	 = 42; 	// (IN)  INT4 mapped to pin RP(I)42/RB10
	//---------------------------------------------------------
	return;
	}
//==================================================================

#endif	/* __MPL_PROFILE_H */

