#include "ADC\ADCLocal.h"

//************************************************************
void	ADCInit(uint IL)
	{
	//---------------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_ADCIL	= IL;
	//=========================================================
	// NOTE:	In this application we have only one input to
	//			measure, so we do not need to use DMA.
	//=========================================================
	//	AD1CON1 control register
	//---------------------------------------------------------
	AD1CON1				= 0;		// Disable ADC1, allow reconfiguration
									// ... unsigned integer format ...
	//----------------------	
	AD1CON1bits.ADSIDL	= 1;		// Discontinue operation in IDLE mode
	AD1CON1bits.AD12B	= 1;		// 12-bit mode selected
	AD1CON1bits.SSRC	= 0b111;	// Internal counter ends sampling and
									// starts conversion (auto-convert)
	AD1CON1bits.ASAM	= 1;		// Sampling begins immediately after last
									// conversion. SAMP bit is auto-set.
	//---------------------------------------------------------

	//=========================================================
	//	AD1CON2 control register
	//---------------------------------------------------------
	AD1CON2				= 0;	// ... Avdd	/ Avss
								// Do NOT scan inputs...
								// Use only Ch0
								// Interrupt after every conversion
	//---------------------------------------------------------

	//=========================================================
	//	AD1CON3 control register
	//---------------------------------------------------------
	// The minimum Tad = 117.6 ns; at this Tad the Tsamp = 3*Tad.
	// Thus the 12-bit conversion will take (3+14)*Tad = 1999.2 ns,
	// which corresponds to nominal speed of 500 kSample/sec.
	//---------------------------------------------------------
	// With the Tcy = 25 ns (at 40 mHz), the minimum acceptable
	// Tad will be 125 ns (5*Tcy) with Tsamp = 3*Tad. The maximum
	// conversion speed under these conditions will be:
	// Tconv = (3+14)*Tad = 17*125 = 2,125 ns, which corresponds
	// to the maximum conversion rate of 470.6 kSample/sec.
	//-----------------------------------------------------------
	// Because the sample caps eventually loses charge, conversion
	// rates below 10 kHz may affect linearity performance, 
	// especially at elevated temperatures.
	//-----------------------------------------------------------
	// We are not in a hurrfy with ADC measurements in this app-
	// lication (battery voltage does not drop "that fast"), so we
	// will set relatively slow conversion rate with the maximum
	// sampling time to account for rather large analog source 
	// impedance (~8kOhm) versus recommended 200 Ohm for the fastest
	// conversion rate.
	// Thus we will settle on the following values:
	// Tad   = 100*Tcy  =  2.5 us (ADCS = 99)
	// Tsamp =  26*Tad  = 65.0 us (SAMC = 25)
	// Tconv = (26+14)*Tad = 40*2.5 = 100 us.
	//---------------------------------------------------------


	AD1CON3				= 0;
	AD1CON3bits.ADRC	= 0;	// Clock derived from system clock
	AD1CON3bits.SAMC	= 25;	// Tsamp = (25+1) * Tad
	AD1CON3bits.ADCS	= 99;	// Tad 	 = (99+1) * Tcy = 2.5 us
								
	//---------------------------------------------------------

	//=========================================================
	//	ADxCON4: ADCx Control Register 4
	//---------------------------------------------------------
	AD1CON4				= 0;	// We are not using DMA...
	//---------------------------------------------------------
		
	
	//=========================================================
	//	AD1CHS123: ADC1 Input Channel 1, 2, 3 Select Register
	//---------------------------------------------------------
	AD1CHS123		= 0;	// For 12-bit ADC we use only Ch. 0
	//---------------------------------------------------------


	//=========================================================
	//	AD1CHS0: ADC1 Input Channel 0 Select Register
	//---------------------------------------------------------
	AD1CHS0				= 0;	// We will be using only MUX-A
								// Channel 0 negative input is Vref
	AD1CHS0bits.CH0SA	= 11;	// Channel 0 positive input is AN11
	//---------------------------------------------------------

	//=========================================================
	//	AD1PCFGL: ADC1 Port Configuration Register Low
	//=========================================================
	// Please NOTE: In this program we use only AN11 for ADC to
	// measure the voltage (through divider) of the battery; 
	// the rest of the ANALOG pins may be released for digital I/O
	//---------------------------------------------------------
	_PCFG11		= 0;	// AN11/RB13 in analog mode 
	_TRISB13	= 1;	// Indicates "INPUT" on the pin;
						// should be set by-default at RESET, but...
							
	_PCFG0	= 1;	// Release pin AN0/RA0   for Digital I/O
	_PCFG1	= 1;	// Release pin AN1/RA1 	 for Digital I/O
	_PCFG2	= 1;	// Release pin AN2/RB0   for Digital I/O	- PGED1
	_PCFG3	= 1;	// Release pin AN3/RB1   for Digital I/O	- PGEC1
	_PCFG4	= 1;	// Release pin AN4/RB2   for Digital I/O
	_PCFG5	= 1;	// Release pin AN5/RB3   for Digital I/O
	_PCFG6	= 1;	// Release pin AN6/RC0   for Digital I/O
	_PCFG7	= 1;	// Release pin AN7/RC1   for Digital I/O
	_PCFG8	= 1;	// Release pin AN8/RC2   for Digital I/O
	_PCFG9	= 1;	// Release pin AN9/RB15  for Digital I/O
	_PCFG10	= 1;	// Release pin AN10/RB14 for Digital I/O
	_PCFG12	= 1;	// Release pin AN12/RB12 for Digital I/O


	//=========================================================
	//	AD1CSSL: ADC1 Input Scan Select Register Low
	//---------------------------------------------------------
	AD1CSSL				= 0;	// Disselect all pins from scan
	//---------------------------------------------------------

	//=========================================================
	// Configure ADC interrupts
	//---------------------------------------------------------							
	IFS0bits.AD1IF 		= 0 ; 		// Clear ADC interrupt flag
	IEC0bits.AD1IE 		= 0 ;   	// Disable ADC CPU interrupt

	IPC3bits.AD1IP 	= _ADCIL;   	// Set ADC interrupt priority

								
	// After configuration complete enable ADC module
	//=========================================================
	AD1CON1bits.ADON	= 1;	
	IEC0bits.AD1IE 		= 1 ;   	// Enable ADC CPU interrupt


	//=========================================================
	// Now we may set up run parameter for current battery
	//=========================================================
	while ( 0 == _ADCValue );		// Wait for first sample...
	//---------------------------------------------------------
	if (_ADCValue > 2208)					// V > 8.55v
		_ADCCellCnt = 3;					// 3-cell
	else	if (_ADCValue > 1472)			// V > 5.70v
				_ADCCellCnt = 2;			// 2-cell...
			else	
				_ADCCellCnt = 1;			
	//--------------------------------------
	_ADCBatMinV		= _ADCMinV  * _ADCCellCnt;
	_ADCBatRange	= _ADCRange * _ADCCellCnt;

	//=========================================================
	return;
	}

//************************************************************

