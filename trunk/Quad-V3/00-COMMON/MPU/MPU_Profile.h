//==================================================================
#ifndef MPU_PROFILE_H
#define	MPU_PROFILE_H
//==================================================================
// The following two #define statements identify MPU-6050 modules
// that will be used in this application; if a particular module is
// not used, please comment out respective #define statement
//==================================================================
#define	Use_MPU1
#define	Use_MPU2
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="Association of MPU sensors with I2C modules and MPU sensors' addresses">
//==================================================================
// MPU1 connected to I2C bus 1
//------------------------------------------------------------------
#ifdef Use_MPU1
	#define MPU1_IDCx		1
	#define MPU1_Addr		0xD0		// 1101000-R/W ADO=0
//	#define MPU1_Addr		0xD2	 	// 1101001-R/W ADO=1
#endif
//------------------------------------------------------------------
// MPU2 connected to I2C bus 2
//------------------------------------------------------------------
#ifdef Use_MPU2
	#define MPU2_IDCx		2
	#define MPU2_Addr		0xD0		// 1101000-R/W ADO=0
//	#define MPU2_Addr		0xD2	 	// 1101001-R/W ADO=1
#endif
//==================================================================
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="Interrupt Routines and related definitions">
//==================================================================
// Each of the MPU-6050 modules need to be associated with one of
// the INTx Modules - please update definitions below depending on
// the allocation of external interrup modules INTx to respective
// MPU-6050 sensors used in the current application.
//------------------------------------------------------------------
// First sensor...
//------------------------------------------------------------------
// INT2 module of the PIC MCU allocated to sensor 1
//------------------------------------------------------------------
#ifdef Use_MPU1
	//--------------------------------------------------------------
	// INTx interrupt bits
	//--------------------------------------------------------------
	// INTx interrupt control bit
	#define	MPU1_IE			_INT2IE
	// INTx interrupt flag
	#define	MPU1_IF			_INT2IF
	// INTx Interrupt priority
	#define	MPU1_IP			_INT2IP
	// INTx Edge Detect Polarity Select bit
	#define MPU1_EP			_INT2EP
	//--------------------------------------------------------------
	// INTx Interrupt routines
	//--------------------------------------------------------------
	#define MPU1_Interrupt	_INT2Interrupt
	//--------------------------------------------------------------
#endif
//------------------------------------------------------------------
// Second sensor...
//------------------------------------------------------------------
// INT3 module of the PIC MCU allocated to sensor 2
//------------------------------------------------------------------
#ifdef Use_MPU2
	//--------------------------------------------------------------
	// INTx interrupt bits
	//--------------------------------------------------------------
	// INTx interrupt control bit
	#define	MPU2_IE			_INT3IE
	// INTx interrupt flag
	#define	MPU2_IF			_INT3IF
	// INTx Interrupt priority
	#define	MPU2_IP			_INT3IP
	// INTx Edge Detect Polarity Select bit
	#define MPU2_EP			_INT3EP
	//--------------------------------------------------------------
	// INTx Interrupt routines
	//--------------------------------------------------------------
	#define MPU2_Interrupt	_INT3Interrupt
	//--------------------------------------------------------------
#endif
//==================================================================
// Interrupt Control Helper Functions
//==================================================================
static inline void MPUSetIF(uint CB_ID, uint IF)
	{
	switch (CB_ID)
		{
		case 1:
			#ifdef Use_MPU1
			MPU1_IF = IF;
			#endif
			break;
		case 2:
			#ifdef Use_MPU2
			MPU2_IF = IF;
			#endif
			break;
		default:
			break;
		}
	return;
	}
//------------------------------------------------------------------
static inline void MPUSetIE(uint CB_ID, uint IE)
	{
	switch (CB_ID)
		{
		case 1:
			#ifdef Use_MPU1
			MPU1_IE = IE;
			#endif
			break;
		case 2:
			#ifdef Use_MPU2
			MPU2_IE = IE;
			#endif
			break;
		default:
			break;
		}
	return;
	}
//==================================================================
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="_MPUInitPinMap(void)">
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
	// MPU1
	//---------------------------------------------------------
	#ifdef Use_MPU1
		_TRISC14 = 1;	// Configure RC14 port for INPUT
		_INT2R	 = 62; 	// (IN)  INTx mapped to pin RP(I)62/RC14
	#endif
	//---------------------------------------------------------
	// MPU2
	//---------------------------------------------------------
	#ifdef Use_MPU2
		_TRISB11 = 1;	// Configure RB11 port for INPUT
		_INT3R	 = 43; 	// (IN)  INTx mapped to pin RP(I)43/RB11
	#endif
	//---------------------------------------------------------
	return;
	}
//==================================================================
// </editor-fold>
//==================================================================
#endif	/* MPU_PROFILE_H */

