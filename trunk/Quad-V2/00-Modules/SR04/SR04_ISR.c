#include "SR04\SR04_Local.h"

#include "TMR\TMR.h"

//************************************************************
// SR04-related Interrupt Routines
//************************************************************
void __attribute__((__interrupt__, __no_auto_psv__)) ICInterrupt(void)
	{
	//-------------
	ICIF 	= 0; 	// Reset ICx interrupt request
	//=========================================================
	// Obtain timestamp for this interrupt
	//---------------------------------------------------------
	ulong	TS	= TMRGetTS();
	//---------------------------------------------------------
	// Process interrupt based upon the captured edge
	//---------------------------------------------------------
	if (ICPORT)
		{
		// Rising edge - start of the measurement cycle -
		// just save the timestamp...
		_SR04Start	= TS;
		//=====================================================
		}
	else
		// Falling edge - if conditions are right, calculate
		// and save duration of the sound travel (in ticks)
		{
		if (0 != _SR04Start) // The rising edge was captured
			{
			ulong	SampleInt	= TS - _SR04Start;
			// Is this a valid measurement - duration < 25 msec
			// (asuming primary interval timer is "ticking" at 0.2 usec)
			if (SampleInt > 125000)	// Invalid: SampleInt > 25 msec
				SampleInt = 125000;	// Force to valid range
			//-------------------------------------------------
			if (0 == _SR04Ready || _SR04Ready > 16383)
				// Either no sample or too many samples
				{
				_SR04Sum = SampleInt;
				_SR04Ready = 1;
				}
			else
				{
				_SR04Sum += SampleInt;
				_SR04Ready++;
				}
			//-------------------------------------------------
			// Reset to wait for rising edge
			_SR04Start = 0;
			// Capture TS of the most recent measurement
			// (required for Speed calculation)
			_SR04RecentTS = TS;
			}
		//-----------------------------------------------------
		}
	return;
	}
//*************************************************************

