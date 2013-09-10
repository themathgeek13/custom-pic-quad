#include "RC\RCLocal.h"
#include "TMR\TMR.h"

//**************************************************
// RCArm function - enforces "arming" of the remote.
// The THROTTLE should go above 75% and then below
// 10% of the total range.
//**************************************************
void	RCArm()
	{
	//--------------------------
	RCData	Capture;
	//--------------------------
WaitForThrottleHigh:
	// Get NEW reading from receiver
	RCReadWhenReady(&Capture);		
	if (Capture.Throttle < 0.75f)	// 75% of the Max Throttle of 1.0	
		goto WaitForThrottleHigh;
	//========================================================================

WaitForThrottleLow:
	// Get NEW reading from receiver
	RCReadWhenReady(&Capture);	
	if (0 == RCIsLinked())			// If we loose connection we need
		goto WaitForThrottleHigh;	// to start again...
	
	if (Capture.Throttle > 0.1f)	// 10% of the Max Throttle of 1.0
		goto WaitForThrottleLow;
	//========================================================================
	return;
	}
//************************************************************


//************************************************************
// Returns Connection Status
// 1 - Connection to transmitter is maintained
// 0 - Connection to transmitter is lost
//************************************************************
uint	RCIsLinked()
	{
	return _RCConnActive;
	}

//**************************************************
// Same as RCRead(...) function, but will block untill
// the new reading is available from receiver.
//**************************************************
uint	RCReadWhenReady(RCData*	RCSample)
	{
	while(!_RCSampleReady);	// Wait for new reading from receiver
	//===========================================================
	return RCRead(RCSample);
	}

//************************************************************
// RCRead function - reads normalized sample from RC recv.
// If connection to receiver is lost, the signal is slowly
// moved to the "default" values...
//--------------------------------------------------
// Return value indicates whether a new sample ob-
// tained from the receiver.
//--------------------------------------------------
// NOTE: Output data structure updated ONLY if a new
//       sample is available!
//============================================================
// Local static variable assisting in filtering out potential
// sporadic drops in Control signal 
//============================================================
uint	_RCControlCount		= 0;
//************************************************************
uint	RCRead(RCData*	RCSample)
	{
	if (0 == _RCSampleReady)	
		return 0;		// New Sample is not ready yet!
						// RCSample structure left "as-is"
	//----------------------
	RCRawData	RCRawSample;
	char 		saved_ipl;     
                  
	//================================================================
	// Enter Critical Section: RC interrupt is blocked
	//================================================================
	SET_AND_SAVE_CPU_IPL(saved_ipl,_RCIL);
	//================================================================
	if ( _RCSampleTimed )				// Current "sample" was
										// triggered by timer!
		{
		//------------------------------------------------------------
		// Sample is "stale" - probably we lost connection to transmit-
		// ter - let's slowly "degrade" control values
		//------------------------------------------------------------
		_RCRawSample.Ch1 = (29 * _RCRawSample.Ch1) >> 5;	// Roll
		_RCRawSample.Ch2 = (29 * _RCRawSample.Ch2) >> 5;	// Pitch
		_RCRawSample.Ch4 = (29 * _RCRawSample.Ch4) >> 5;	// Yaw
		//----------------------------------------------
		// To facilitate "safe landing" Throttle signal
		// deteriorates much slower...
		_RCRawSample.Ch3 = (126 * _RCRawSample.Ch3) >> 7;	// Throttle
		//----------------------------------------------
		if (_RCRawSample.Ch3 > 200)
			_RCRawSample.Ch5 = 1;	// To avoid immediate cut-off binary
									// control signal maintained at 1
									// while Throttle "degrades"
		else
			_RCRawSample.Ch5 = 0;	// Finally force "cut-off"...
		//------------------------------------------------------------
		// Reset "stale" flag
		//------------------------------------------------------------
		_RCSampleTimed = 0;
		}
	//----------------------------------------------------------------
	// Consume current sample
	//----------------------------------------------------------------
	RCRawSample.Ch1		= _RCRawSample.Ch1;
	RCRawSample.Ch2		= _RCRawSample.Ch2;
	RCRawSample.Ch3		= _RCRawSample.Ch3;
	RCRawSample.Ch4		= _RCRawSample.Ch4;
	RCRawSample.Ch5		= _RCRawSample.Ch5;
	//----------------------------------------------------------------
	_RCSampleReady	= 0;				// Sample is consumed...
	//================================================================
	// Leave Critical Section
	//================================================================
	RESTORE_CPU_IPL(saved_ipl);
	//================================================================

	//================================================================
	RCSample->Throttle	=  ((float)RCRawSample.Ch3) * _RCPlusRange;
	if (fabsf(RCSample->Throttle) < 0.01) RCSample->Throttle = 0.0;
	//-------------------
	RCSample->Roll		=  ((float)RCRawSample.Ch1) * _RCPlusMinusRange;
	//-------------------
			// When the stick goes forward receiver reading is increasing;
			// However to comply with our IMU axis orientation moving stick
			// forward (nose - down) should result in NEGATIVE pitch, so we
			// need to reverse the Pitch value:
	RCSample->Pitch		= -((float)RCRawSample.Ch2) * _RCPlusMinusRange;
	//-------------------
	RCSample->Yaw		=  ((float)RCRawSample.Ch4) * _RCPlusMinusRange;
	//----------------------------------------------------------------
	// Filtering out potential sporadic drops in Control signal
	//----------------------------------------------------------------
	RCSample->Control	= 1; 	// Default "safe" setting
	//----------------------
	if (RCRawSample.Ch5 > 0)
		// Reset counter of "low" samples
		_RCControlCount = _RCControlMin;
	else
		// Change Control value based upon the minimum number of times
		// in a row it appears to be 0		
		{
		if (_RCControlCount > 0)
			_RCControlCount--;
		else
			// "Safe" counter exhausted - setting Control to 0
			RCSample->Control	= 0;
		}
	//----------------------------------------------------------------
	return 1;	// RCSample updated with new sample 
	}
//************************************************************





