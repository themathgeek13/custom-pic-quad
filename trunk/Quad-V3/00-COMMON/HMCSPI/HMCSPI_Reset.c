#include "HMCSPI\HMCSPI_Local.h"

//==================================================================
// <editor-fold defaultstate="collapsed" desc="HMC_RC	HMC_ReSet(byte ODR, byte Gain, byte DLPF)">
HMC_RC	HMC_ReSet(byte ODR, byte Gain, byte DLPF)
	//--------------------------------------------------------------
	// HMC_Reset(...) Parameters explanations
	//--------------------------------------------------------------
	// <editor-fold defaultstate="collapsed" desc="Output Data Rate (ODR">
	//------------------------------------------------------
	// Typical Data Output Rate (Hz) for various ODR values
	//------------------------------------------------------
	//		ODR =	0:		  0.75
	//		ODR =	2:		  1.5
	//		ODR =	2:		  3
	//		ODR =	3:		  7.5
	//		ODR =	4:		 15		(Default)
	//		ODR =	5:		 30
	//		ODR =	6:		 75
	//		ODR =	7:		220		(fastest)
	// </editor-fold>
	//--------------------------------------------------------------
	// <editor-fold defaultstate="collapsed" desc="Sensor Field Range (Gain)">
	//------------------------------------------------------
	// Recommended sensor field range (Ga) for various Gains
	//------------------------------------------------------
	//		Gain =	0:		0.9
	//		Gain =	1:		1.3
	//		Gain =	2:		1.9
	//		Gain =	3:		2.5
	//		Gain =	4:		4.0
	//		Gain =	5:		4.7
	//		Gain =	6:		5.6
	//		Gain =	7:		8.1
	//------------------------------------------------------
	// </editor-fold>
	//--------------------------------------------------------------
	// <editor-fold defaultstate="collapsed" desc="Low-pass filtering (DLPF)">
	//------------------------------------------------------
	// Low-pass filtering achieved through sample averaging.
	// Averaging does not affect effective ODR, so I assume
	// that wit averaging enabled each successive reported
	// sample is an average of the new measurement with "n"
	// previous measurements - something like a FIR filter.
	//------------------------------------------------------
	// DLPF = 0 => 1-average	
	// DLPF = 1 => 2-average
	// DLPF = 2 => 4-average
	// DLPF = 3 => 8-average
	//------------------------------------------------------
	// </editor-fold>
	//--------------------------------------------------------------
	{
	if (0 == _HMC_Init)
	  return HMC_NotInit;
	//-------------------------------------------
	HMC_RC	RC;
	//-------------------------------------------
	// Registers that we will be working with
	//-------------------------------------------
	struct
		{
		byte	A;
		byte	B;
		byte	Mode;
		}	Config;
	//-------------------------------------------
	// First, let's put device into the idle mode
	//-------------------------------------------
	Config.Mode	= 0x02;
	if (HMC_OK != (RC = _HMC_RegWrite(AddrMode, &Config.Mode, 1)))
		return RC;
	//=========================================================
	// Process ODR and DLPF
	//---------------------------------------------------------
	ODR		&= 0x07;	// Only 3-bit value is allowed
	ODR		<<= 2;  	// Position ODR in bits 4-3-2 (0-based)
	//---------------------------------------------------------
	DLPF	&= 0x03;	// Only 2-bit value is allowed
	DLPF	<<= 5;		// Position DLPF in bits 6-5 (0-based)
	//---------------------------------------------------------
	// Format configuration register A (we unconditionally
	// enable temperature sensor for automatic temperature com-
	// pensation, thus the 0x80 term)
	//---------------------------------------------------------
	Config.A = 0x80 + DLPF + ODR;
	//---------------------------------------------------------
	// Process Gain
	//---------------------------------------------------------
	Gain &= 0x07;		// Only 3-bit value is allowed
	//---------------------------------------------------------
	// Calculate weight to bring raw measurements to mGs based
	// upon the Gain
	//---------------------------------------------------------
	switch (Gain)
		{
		case 0:
			_HMC_Gain = 0.729927;		// +/- 0.88 Ga
			break;
		case 1:
			_HMC_Gain = 0.917431;		// +/- 1.30 Ga
			break;
		case 2:
			_HMC_Gain = 1.219512;		// +/- 1.90 Ga
			break;
		case 3:
			_HMC_Gain = 1.515152;		// +/- 2.50 Ga
			break;
		case 4:
			_HMC_Gain = 2.272727;		// +/- 4.00 Ga
			break;
		case 5:
			_HMC_Gain = 2.564103;		// +/- 4.70 Ga
			break;
		case 6:
			_HMC_Gain = 3.030303;		// +/- 5.60 Ga
			break;
		case 7:
		default:						// Really should not be here...
			_HMC_Gain = 4.347826;		// +/- 8.10 Ga
			break;
		}
	//---------------------------------------------------------
	// Format configuration Register B
	//---------------------------------------------------------
	Config.B = (Gain << 5);	// Position Gain in bits 7-5 (0-based)
							// Bits 4-0 are reserved and should be 0
	//---------------------------------------------------------
	// Configure Mode for Continuous Measurement
	//---------------------------------------------------------
	Config.Mode	= 0x00;
	//---------------------------------------------------------
	// Configure device
	//---------------------------------------------------------
	if (HMC_OK != (RC = _HMC_RegWrite(AddrA, (byte*)&Config, 3)))
		return RC;
	//---------------------------------------------------------
	// After configuration has changed we need to read a few
	// measurements to let the device reconfigure its parameters
	//---------------------------------------------------------
	HMCData		Sample;
	if (HMC_OK != (RC =  HMC_ReadSample(&Sample)))
		return RC;
	if (HMC_OK != (RC =  HMC_ReadSample(&Sample)))
		return RC;
	return  HMC_ReadSample(&Sample);
	}
// </editor-fold>
//==================================================================
