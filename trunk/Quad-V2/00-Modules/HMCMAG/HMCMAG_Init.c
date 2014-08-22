#include "HMCMAG\HMCMAG_Local.h"
//*******************************************************

//=============================================================
uint		HMCInit(byte ODR, byte Gain, byte DLPF)
	{
	// HMC module depends on I2C for communication with the 
	// sensor, so we need to make sure that I2C is initialized...
	byte	IL = I2CGetIL();
	if (0 == IL)
		return I2CRC_NRDY;	// I2C Module is not initialized
	//---------------------------------------------------------
	if (_HMC_Init)
		return	HMC_OK;		// Avoid repeated initialization...
	_HMC_Init	= 1;
	//---------------------------------------------------------
	_HMC_IL	= IL;
	//************************************************

	//---------------------------------------------------------
	// HMCMAG Module uses Input Capture facility to generate
	// interrupt on READY state for asynchronous data aquisition
	//---------------------------------------------------------
	HMC_ICCON	= 0;	// Disable ICx for configuration
	//---------------------------------------------------------
	// Please NOTE that the Init program disables all PERIPHERAL
	// MODULES using PMDx registers. To continue configuring and
	// later enabling Input Capture module we need to enable
	// module in PMDx
	//---------------------------------------------------------
	HMC_PMD		= 0;	// Enable ICx module in PMD
	//---------------------------------------------------------

	//---------------------------------------------------------
	// Map MCU pins used by Input Capture module through
	// REMAPPABLE PIN SELECT feature.
	//---------------------------------------------------------
	_HMCInitPinMap();

	//---------------------------------------------------------
	// Configure Interrupts
	//---------------------------------------------------------
	HMC_IE		= 0;			// Disable ICx interrupt
	HMC_IF		= 0; 			// Clear ICx interrupt flag
	HMC_IP		= _HMC_IL;		// Set ICx interrupt priority
	//---------------------------------------------------------
	// ICx interrupt enabled in MPLAsyncStart() routine
	//---------------------------------------------------------

	//---------------------------------------------------------
	// After configuration complete enable ICx module
	//---------------------------------------------------------
	// NOTE: For this application we do not capture the
	//		 actual timer value associated with the module,
	//		 so we do not care configuring timer associated
	//		 with ICx.
	//---------------------------------------------------------
	// NOTE: By setting HMC_ICCON = 0 we implicitly set ICI=0,
	//		 which implies that the ICx FIFO buffer overflow
	//		 will not stop generation of interrupts.
	//---------------------------------------------------------
	HMC_ICM	= 3; // Capture mode, interrupt on every rising edge
	//---------------------------------------------------------
	//*********************************************************
	// Now we should initialize the sensor...
	//*********************************************************
	return	HMCReset(ODR, Gain, DLPF);
	}
//=============================================================

//=============================================================
uint	HMCReset(byte ODR, byte Gain, byte DLPF)
	{
	if (!_HMC_Init)
		return HMC_NOTINIT;		// Not initialized...
	//-----------------------
	if (_HMC_Async)
		return HMC_ABSY;		// Asynchronous operation in progress...
	//=========================================================
	// Normalize input values
	//---------------------------------------------------------
	ODR	  &= 0x07;		// Only 3-bit value is allowed
	if (ODR > 6)
		ODR = 6;		// Maximum allowed data rate
	ODR  <<= 2;  		// Position ODR in bits 4-3-2 (0-based)
	//---------------------------------------------------------
	Gain	  &= 0x07;	// Only 3-bit value is allowed
	//---------------------------------------------------------
	DLPF	  &= 0x03;	// Only 2-bit value is allowed
	DLPF	 <<= 5;		// Position DLPF in bits 6-5 (0-based)
	//---------------------------------------------------------
	// Calculate sensitivity to bring measurements to mGs based
	// upon the Gain
	//---------------------------------------------------------
	switch (Gain)
		{
		case 0:
			_HMC_Sensitivity = 0.729927;		// +/- 0.88 Ga
			break;
		case 1:
			_HMC_Sensitivity = 0.917431;		// +/- 1.30 Ga
			break;
		case 2:
			_HMC_Sensitivity = 1.219512;		// +/- 1.90 Ga
			break;
		case 3:
			_HMC_Sensitivity = 1.515152;		// +/- 2.50 Ga
			break;
		case 4:
			_HMC_Sensitivity = 2.272727;		// +/- 4.00 Ga
			break;
		case 5:
			_HMC_Sensitivity = 2.564103;		// +/- 4.70 Ga
			break;
		case 6:
			_HMC_Sensitivity = 3.030303;		// +/- 5.60 Ga
			break;
		case 7:
			_HMC_Sensitivity = 4.347826;		// +/- 8.10 Ga
		default:
			_HMC_Sensitivity = 0.729927;		// Really should not be here...
			break;
		}
	//*********************************************************
	uint		RC		= 0;
	byte		RegA	= ODR | DLPF;	// Combine ODR and DLPF		
	byte		RegB	= Gain << 5;	// Position Gain in bits 7-6-5 (0-based)
	//--------------------------------------------------
	if ( (RC = HMCSetRegA(RegA)) )	// Set ODR, no bias
		return RC;							// Error...
	//--------------------------------------------------
	if ( (RC = HMCSetRegB(RegB)) )	// Set Gain
		return RC;							// Error...
	//--------------------------------------------------
	if ( (RC = HMCSetMode(0x00)) )	// Set Continuous mode
		return RC;							// Error...
	//*********************************************************
	// Now we may "warm-up" the sensor in the new configuration
	//---------------------------------------------------------
	_HMCRawData	RawData;
	//-----------------------------
	int 	i;
	//---------------------------------------------------------
	for (i = 0; i < 16; i++)
		{
		if ( (RC = _HMCReadRawData(&RawData)) )	
			return RC;							// Error...
		}
	//*********************************************************
	return HMC_OK;
	}

//***************************************************************





