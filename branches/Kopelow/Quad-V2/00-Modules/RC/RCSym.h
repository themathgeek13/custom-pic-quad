#include "System.h"

#include "RC.h"
//=====================================================
#ifndef __RCSym_H
#define __RCSym_H
//=====================================================
// Simplified ARMing for simulation
void	RCSymArm();						
//-----------------------------------------------------
// The following 2 function read simulated data file if
// RCControl from the receiver is 1
//-----------------------------------------------------
// Blocking call - provides new simulated sample when
// the true update obtained from receiver
uint	RCSymReadWhenReady(RCData*	RCSample);
//-----------------------------------------------------
// Non-blocking call - returns immediately sample from
// the simulated sequence based upon the time from the
// start of the simulation
uint	RCSymRead(RCData* RCSample);	

//=====================================================
#endif		// __RCSym_H //





