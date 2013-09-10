#include "System.h"

#include "RC\RC.h"
#include "DCM\DCM.h"
#include "MCM\MCM.h"

//=====================================================
#ifndef __QCM_H
#define __QCM_H
//=====================================================

float	QCMBatteryMgmt();

void	QCMPerformStep(RCData* RC, DCMData* IMU, MCMData* MC);

//=====================================================

//************************************************************
// Working assumptions:
//************************************************************
// Our Body and Earth reference frames represent right-handed
// coordinate system with X axis pointing forward, Y axis - 
// along the right wing, and Z axis - down.
//
// With this orientation of the axis:
//
//	Roll:		  -Pi <=  Roll   <=  +Pi
//	Roll value is "positive" when board banks to the right
//							
//	Pitch:		-Pi/2 <=  Pitch  <= +Pi/2
//	Pitch value is "positive" when the board points up
//
//	Yaw:		  -Pi <=   Yaw   <=  +Pi
//	Yaw value is positive if the board is turned right (clockwise)
//
//	Azimuth:	    0 <= Azimuth <=  2Pi
//	Azimuth increases when the board is turned clockwize from the
//	North direction
//
//------------------------------------------------------------
// IMU data provided from the IMU board is represented in the
// same coordinate system.
//************************************************************
// Front and Back props rotate platform counter-clockwise
// (negative rotation around Z axis), Left and Right -
// clockwise (positive rotation around Z axis).
//************************************************************

//=====================================================
#endif

