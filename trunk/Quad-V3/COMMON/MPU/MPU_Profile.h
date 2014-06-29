//==================================================================
#ifndef MPU_PROFILE_H
#define	MPU_PROFILE_H

//==================================================================
// INTx Module definitions - please update depending on the module
// used in the current application.
//------------------------------------------------------------------
// For interrupt processing MPU6050 relies on the INT3 module of the
// PIC MCU.
//------------------------------------------------------------------
// INT3 interrupt bits
//------------------------------------------------------------------
// INT3 interrupt control bit
#define	MPU_IE			_INT3IE
// INT3 interrupt flag
#define	MPU_IF			_INT3IF
// INT3 Interrupt priority
#define	MPU_IP			_INT3IP
// INT3 Edge Detect Polarity Select bit
#define MPU_EP			_INT3EP
//------------------------------------------------------------------
// INT4 Interrupt routines
//------------------------------------------------------------------
#define MPU_Interrupt	_INT3Interrupt
//==================================================================





//==================================================================
// Helper function _MPUInitPinMap(void) implements mapping
// of INTx module pins using Peripheral Pin Select
//==================================================================
static inline void _MPUInitPinMap(void)
	{
	//--------------------------------------------------------
	// PIC24EP512GP806 INT3 pin map for this application
	//--------------------------------------------------------
	//	MPU-1/I2C1 INTx Sense Pin 	= RP(I)62/RC14
	//	MPU-2/I2C2 INTx Sense Pin 	= RP(I)43/RB11
	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure Sense pin
	//---------------------------------------------------------
	// NOTE: Selected pin (RP(I)43/RB11) is shared with ADC as
	//		 AN11; however Init() routine already put all
	//		 analog pins into Digital IO mode
	//---------------------------------------------------------
	// MPU-1
//	_TRISC14 = 1;	// Configure RC14 port for INPUT
//	_INT3R	 = 62; 	// (IN)  INTx mapped to pin RP(I)62/RC14
	// MPU-2
	_TRISB11 = 1;	// Configure RB11 port for INPUT
	_INT3R	 = 43; 	// (IN)  INTx mapped to pin RP(I)43/RB11
	//---------------------------------------------------------
	return;
	}
//==================================================================
#endif	/* MPU_PROFILE_H */

