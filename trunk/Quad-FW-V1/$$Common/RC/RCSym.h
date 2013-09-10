//=====================================================
#ifndef __RCSym_H
#define __RCSym_H
//=====================================================

#include "RC\RCLocal.h"

//-----------------------------------------------------------
// RCSymLine Structure is used internally to represent
// entries in the Sample Array (see RCSymData)
//-----------------------------------------------------------
typedef struct 
	{
	char		Throttle;		
	//----------------------
	char		Roll;		
	char		Pitch;		
	char		Yaw;		
	} RCSymLine;

//************************************************************
// Definitions used internally for simulation
//************************************************************
// Simulation control values
//------------------------------------------------------------
extern 	ulong	_RCSymStart;			// Timestamp (in ms.)
										// of simulation start

void	RCSymArm();						// Simplified Remote
										// arming for simulation
										//----------------------
void	RCSymReset();					// Resets simulation sequence
										//----------------------
uint	RCSymReadWhenReady(pRCData	RCSample);
										//----------------------
uint	RCSymRead(pRCData RCSample);	// Reads data from the simulation
										// file if RCControl from the
										// receiver is 1

//**************************************************
// RCSetLNRate(...) applies linear rate
// to Roll-Pitch-Yaw controls and removes "low" zone
// on Yaw control to prevent "slow" rotation
//**************************************************
void static inline	RCSetSymRate(pRCData	RCSample)
	{
	if (fabsf(RCSample->Yaw) < 0.05)
		RCSample->Yaw  = 0.0;	// Eliminate jitter
	//---------------------------------------------
	RCSample->Roll 	= 0.600 * RCSample->Roll;
	RCSample->Pitch = 0.600 * RCSample->Pitch;
	RCSample->Yaw	= 0.600 * RCSample->Yaw;
	}
	
//------------------------------------------------------------
// Simulation data (defined in the RCSymData file):
//------------------------------------------------------------
extern const uint		_RCSymCount;	// Number of entries
										// in simulation file

extern const RCSymLine	_RCSymStream[];	

//=====================================================
#endif





