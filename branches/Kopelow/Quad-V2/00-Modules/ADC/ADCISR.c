#include "ADC/ADCLocal.h"


//************************************************************
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
	{
	//---------------------------------------------------
	// To avoid buffer overrun, stop ADC
	//---------------------------------------------------
	AD1CON1bits.ADON		= 0;
	//---------------------------------------------------
	// Retrieve sample
	//---------------------------------------------------
	_ADCBuffer	+= ADC1BUF0;	// Add current sample to buffer
	_ADCSCnt++;					// Increment sample count in
								// buffer
	//---------------------------------------------------
	if (_ADCSCnt >= 128)		// 128 samples in buffer
		{
		//----------------------------------------------
		// Calculate new value as average of accumulated
		// samples.
		//----------------------------------------------
		ulong	NewValue = (_ADCBuffer + 64) >> 7;
		//----------------------------------------------
		// Given the configured ADC rate of 10 KHz, the
		// first update to ADCValue takes 12.8 msec with
		// every subsequent update taking 6.4 msec
		//----------------------------------------------
		if (0 == _ADCValue)
			{
			// First ADC sample - take "as-is"
			//------------------------------------------------
			// Add 64 and divide by 128 - average with rounding
			_ADCValue 	= NewValue;
			}
		else
			{
			// Subsequent samples - apply IIR filtering:
			// FilteredValue = (15*FilteredValue + NewValue)/16
			//------------------------------------------------
			_ADCValue	= (_ADCValue * 15 + NewValue) >> 4;
			}
		//--------------------------------------------------------
		_ADCSCnt	= 64;		// Half of the series consumed
								// Buffer halved (with rounding)
		_ADCBuffer	= (_ADCBuffer + 1) >> 1;
		}
	//---------------------------------------------------
	IFS0bits.AD1IF 		= 0 ; 		// Clear ADC interrupt flag
	AD1CON1bits.ADON	= 1;		// Re-start ADC
	}
//************************************************************




