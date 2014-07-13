#include "System.h"
//------------------------------------------------------------------

#ifndef __ALTIMETER_H
#define	__ALTIMETER_H
//---------------------------------
#include "DCM\DCM.h"
//---------------------------------
// Header for optional HW components
//---------------------------------
#ifdef __MPL_Use__
	#include "MPL3115\MPL3115.h"
#endif
#ifdef __SR04_Use__
	#include "SR04\SR04.h"
#endif


//==================================================================
// AltmData - results of Altitude calculation
//==================================================================
typedef struct
	{
	//--------------------------------------------------------------
	// Altitude components - contrary to the axis orientation for
	// IMU, for altitude measurements we assume that z-axis is
	// pointing "up"
	//--------------------------------------------------------------
	float	AccAvg;
	float	AccDeltaV;
	float	MPLDeltaV;
	//-----------------------------
	#ifdef __MPL_Use__
	//-----------------------------------------------
	// Altitude from Barometric sensor
	//-----------------------------------------------
	MPLData		MPLSample;
	//----------------------
	float		MPLAltSmthd;
	float		MPLSpeed;
	//----------------------
	float		MPLBase;
	//----------------------
	#endif
	//-----------------------------------------------
	#ifdef __SR04_Use__
	//-----------------------------------------------
	// Altitude From Ultrasonic sensor
	//-----------------------------------------------
	SR04Data	SR04Sample;
	//----------------------
	#endif
	//-----------------------------------------------
	}	AltmData;
//=============================================================

uint	AltimeterInit(int IL);

uint	AltimeterReset();

uint	AltimeterGetAltData(ulong		AccTS,
							Vector*		ACC,
							AltmData*	AltResult);

#endif	/* __ALTIMETER_H */

