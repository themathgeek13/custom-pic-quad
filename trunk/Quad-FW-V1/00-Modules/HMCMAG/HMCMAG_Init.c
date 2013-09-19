#ifdef MAG_Use
//*************************************************************

#include "HMCMAG\HMCMAG_Local.h"
//=============================================================
uint		HMCInit(byte ODR, byte Gain, byte DLPF)
	{
	// HMC module depends on I2C for communication with the 
	// sensor, so we need to make sure that I2C is initialized...
	byte	IL = I2CGetIL();
	if (0 == IL)
		return I2C_NRDY;	// I2C Module is not initialized
	//---------------------------------------------------------
	if (_HMC_Init)
		return	HMC_OK;		// Avoid repeated initialization...
	_HMC_Init	= 1;
	//---------------------------------------------------------
	_HMC_IL	= IL;
	//---------------------------------------------------------
	// For INT2 we will use RP20/RC4 pin
	//---------------------------------------------------------
	_INT2IE	= 0;		// Disable INT2 Interrupt for configuration
	_INT2IF	= 0;		// Clear INT2 interrupt flag (if any)
	_INT2EP	= 0;		// Trigger INT2 on "raising edge"
	_INT2IP	= _HMC_IL;	// Set INT2 Interrupt Priority
	// Now we may configure RB4 as Input and map RP4 to INT2
	_TRISC4 = 1;		// Set RC4 as Input;
	_INT2R	= 20;		// Map INT2 input to RP20;
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
	return 0;
	}

//***************************************************************
#endif /* MAG_Use */





