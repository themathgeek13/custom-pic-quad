#include "ADC/ADCLocal.h"

//==================================================================
uint			_ADCIL			= 4;	// ADC default interrupt level
//------------------------------------------------------------------
ulong  volatile	_ADCValue		= 0;	// Last ADC measurement
									// "0" indicates absence of a 
									// valid measurement
//------------------------------------------------------------------
ulong volatile	_ADCBuffer		= 0;	// Accumulator for samples
uint  volatile	_ADCSCnt		= 0;	// Sample count
//==================================================================
//	Run Variables (set in ADCGetCellCount())
//------------------------------------------------------------------
// These three values are represented in ADC counts:
uint 			_ADCCellCnt		= 0;	// Set in ADCInit()
uint 			_ADCBatMinV		= 0;	// Set in ADCInit()
uint 			_ADCBatRange	= 0;	// Set in ADCInit()
//------------------------------------------------------------------
// The following value represented in Volts:
float			_ADCBatNomV		= 0.0;	// Set in ADCInit()


//------------------------------------------------------------------
//	Constants
//------------------------------------------------------------------
uint  const		_ADCMinV		= 825;	// Minimum useful voltage for
										// 1-cell battery (3.2 V)
uint  const		_ADCRange		= 260;	// Useful discharge range for
										// 1-cell battery (1.0 V)
//------------------------------------------------------------------
float const		_ADCVRate		= 0.003872457;
									// Specific to the board:
									// Conversion rate to obtain
									// real voltage from ADC.
//==================================================================



