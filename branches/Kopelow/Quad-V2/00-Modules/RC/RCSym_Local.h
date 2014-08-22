#include "RC/RCSym.h"
#include "RC/RCLocal.h"

//=====================================================
#ifndef RCSYM_LOCAL_H
#define	RCSYM_LOCAL_H
//=====================================================

//************************************************************
// Definitions used internally for simulation
//************************************************************
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
//------------------------------------------------------------
// Simulation control values
//------------------------------------------------------------
extern 	ulong			_RCSymStart;	// Timestamp (in ms.)
										// of simulation start
//------------------------------------------------------------
// Simulation data (defined in the RCSymData file):
//------------------------------------------------------------
extern const uint		_RCSymCount;	// Number of entries
										// in simulation file

extern const RCSymLine	_RCSymStream[];

//************************************************************
// RCSymReset function - resets simulation sequence
//************************************************************
static inline void	RCSymReset()
	{
	//--------------------------------------
	// Reinitialize simulation sequence
	//--------------------------------------
	_RCSymStart			= TMRGetRTC();
	//-----------------------------------------------
	return;
	}
//************************************************************

//=====================================================
#endif	/* RCSYM_LOCAL_H */

