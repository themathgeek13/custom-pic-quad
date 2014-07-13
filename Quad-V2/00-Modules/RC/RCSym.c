#include "RC\RCSym_Local.h"

//#include "RC\RCSymData_VibroTest.h"
#include "RC\RCSymData_BalanceHard.h"
//#include "RC\RCSymData_BalanceTest.h"
//#include "RC\RCSymData_MB_Ramp.h"
//#include "RC\RCSymData_MB_Soft.h"
//#include "RC\RCSymData_MB_Hard.h"
//#include "RC\RCSymData_YawTest.h"

//************************************************************
// Simulation control values and access routines
//------------------------------------------------------------
// Timestamp (in ms.) of simulation start
ulong		_RCSymStart				= 0; 

	
//************************************************************
// RCSymArm function - enforces simplified "arming" of the
// remote  - waiting for RC.Control to go LOW and then HIGH
//************************************************************
void	RCSymArm()
	{
	RCData		Capture;
	// Simplified ARMing - waiting for RC.Control to go from
	// low to high
	//========================================================
RetryLow:
	RCReadWhenReady(&Capture);		// Read actual NEW sample

	if (0 == RCIsLinked())			// If we loose connection we need
		goto RetryLow;				// to start again...

	if (1 == Capture.Control)
		goto RetryLow;
	//--------------------------------------	
RetryHigh:
	RCReadWhenReady(&Capture);		// Read actual NEW sample

	if (0 == RCIsLinked())			// If we loose connection we need
		goto RetryLow;				// to start again...

	if (0 == Capture.Control)
		goto RetryHigh;
	//--------------------------------------	
	// Reinitialize simulation sequence
	//--------------------------------------	
	RCSymReset();
	//-----------------------------------------------
	return;
	}
//************************************************************



//************************************************************
// Same as RCSymRead(...) function, but will block untill
// the new reading is available from receiver.
//************************************************************
uint	RCSymReadWhenReady(RCData*	RCSample)
	{
	while(0 == _RCSampleReady);	// Wait for new reading from receiver
	//===========================================================
	return RCSymRead(RCSample);
	}


//************************************************************
// RCSymRead(..) function - reads data from the simulation
// file if RCControl from the receiver is 1
//************************************************************
uint	RCSymRead(RCData*	RCSample)
	{
	if(0 == _RCSampleReady)	
		return 0;		// There is no new samples from
						// real receiver - RCSample structure
						// is not updated!
	//---------------------------------------------------
	// Read sample from Receiver
	//---------------------------------------------------
	uint RC = RCRead(RCSample);
	//---------------------------------------------------
	if (0 == RCSample->Control)
		{
		//--------------------------------------
		// Reset output data
		//--------------------------------------
		RCSample->Throttle	= 0.0;
		//------------------------
		RCSample->Roll		= 0.0;
		RCSample->Pitch		= 0.0;
		RCSample->Yaw		= 0.0;
		//--------------------------------------	
		// Reinitialize simulation sequence
		//--------------------------------------	
		RCSymReset();
		//--------------------------------------	
		return RC;
		}
	//---------------------------------------------------
	ulong SymDet =	(TMRGetRTC() - _RCSymStart) / 20; 	// Number of 20-ms slots
												// since simulation start
	//---------------------------------------------------
	if (SymDet < _RCSymCount)
		{
		uint SymIdx = (uint)SymDet;
		//--------------------------------------	
		// Perform simulation step 
		//--------------------------------------
		RCSample->Throttle	= ((float)_RCSymStream[SymIdx].Throttle)	*0.01;
		//--------------------
		RCSample->Roll		= ((float)_RCSymStream[SymIdx].Roll)		*0.01;
		RCSample->Pitch		= ((float)_RCSymStream[SymIdx].Pitch)		*0.01;
		RCSample->Yaw		= ((float)_RCSymStream[SymIdx].Yaw)			*0.01;
		//--------------------------------------
		RCSample->Control	= 1;
		}
	else
		// Simulation sequence exhausted!
		{
		//--------------------------------------
		// Reset output data
		//--------------------------------------
		RCSample->Throttle	= 0.0;
		//------------------------
		RCSample->Roll		= 0.0;
		RCSample->Pitch		= 0.0;
		RCSample->Yaw		= 0.0;
		//--------------------------------------
		// Force RC Control to 0
		//--------------------------------------
		RCSample->Control	= 0;
		}
	//---------------------------------------------------
	return RC;
	}	

								





