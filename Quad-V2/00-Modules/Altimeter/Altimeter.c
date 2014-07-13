#include "Altimeter\AltimeterLocal.h"
#include "DEF\DEF.h"

AltmData	AltmLocal;
//-------------------------------
ulong		AccLastTS	= 0;	// Timestamp of the last ACC Sample
float		AccSUM		= 0.0;	// Sum of Acc-Z measurements since AccLastTS
uint		AccCount	= 0;	// Count of Acc-Z neasurements since AccLastTS
//-------------------------------
#ifndef __SR04_Use__
uint		FlightFlag	= 0;	// Indicator whether the take-off took place
#endif

#define		__Use_DEF__

#ifdef		__Use_DEF__
DEF			DEF_MPL_AltFlt;
DEF			DEF_MPL_VvertFlt;
#endif

// <editor-fold defaultstate="collapsed" desc="AltimeterInit(int IL)">
uint	AltimeterInit(int IL)
	{
	//==================================================================
	#ifdef __MPL_Use__
	//------------------------------------------------------------------
	// Initialize MPL3115 Altimeter
	//------------------------------------------------------------------
	// OSR = 3 => Average over 2^3=  8 samples, update rate about 38 Hz
	//			  Sample-to-sample dev +/- 3 m
	// OSR = 4 => Average over 2^4= 16 samples, update rate about 20 Hz
	// OSR = 5 => Average over 2^5= 32 samples, update rate about 10 Hz
	// OSR = 6 => Average over 2^6= 64 samples, update rate about  6 Hz
	// OSR = 7 => Average over 2^7=128 samples, update rate about  3 Hz
	//------------------------------------------------------------------
	byte	OSR	= 3;
	//------------------------------------------------------------------
	if ( MPLInit (OSR) )
		BLIDeadStop ("EB", 2);
	#endif
	//==================================================================
	#ifdef __SR04_Use__
	//--------------------------------------------------------------
	// Initialize Ultrasonic Altimeter
	//--------------------------------------------------------------
	SR04Init (IL);		// Initialize SR04 with IPL = IL
	#endif
	//==================================================================
	return 0;
	}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="AltimeterReset()">
uint	AltimeterReset()
	{
	////////////////////////////////////////////////////////////////////
	#ifdef __MPL_Use__
	//==================================================================
	// Start MPL3115 Altimeter in Asynchronous mode
	//--------------------------------------------------------------
	MPLAsyncStart();	// Start as soon as possible for warm-up
	//--------------------------------------------------------------
	#endif
	////////////////////////////////////////////////////////////////////
	#ifdef __SR04_Use__
	//--------------------------------------------------------------
	// Calibrate Ground level for Ultrasonic Altimeter
	//--------------------------------------------------------------
	if (SR04ResetBase())
		// Altimeter calibration failed
		BLIDeadStop("CU", 2);	// Failure...
	//--------------------------------------------------------------
	// Read first Sample
	//--------------------------------------------------------------
	SR04ReadWhenReady(&AltmLocal.SR04Sample);
	//==================================================================
	#endif
	////////////////////////////////////////////////////////////////////
	#ifdef __MPL_Use__
	//==================================================================
	// Calibrate ground level for MPL3115 Altimeter
	//--------------------------------------------------------------
	if (MPLSetGround() != MPL_OK) 
		// Altimeter calibration failed
		BLIDeadStop("CB", 2);	// Failure...
	//--------------------------------------------------------------
	// Read first Sample
	//--------------------------------------------------------------
	MPLAsyncReadWhenReady(&AltmLocal.MPLSample);
	AltmLocal.MPLAltSmthd	= 0.0;	// RESET happens on the ground, so
									// Altitude should be 0 :)
	AltmLocal.MPLBase		= MPLGetBase();
	//==================================================================
	#endif
	////////////////////////////////////////////////////////////////////
	AltmLocal.AccAvg	= 0.0;
	AltmLocal.AccDeltaV	= 0.0;
	AltmLocal.MPLDeltaV	= 0.0;
	//==================================================================
	// Reset local (to the module) variables
	//------------------------------------------------------------------
	AccLastTS	= 0;
	AccSUM		= 0.0;
	AccCount	= 0;
	//------------------------------------------------------------------
	#ifdef		__Use_DEF__
	DEFFilterInit(71.0, 5.0, &DEF_MPL_AltFlt);		// Altitude filter
	DEFFilterInit( 6.0, 3.0, &DEF_MPL_VvertFlt);	// Vertical speed filter
	#endif
	//==================================================================
	return 0;
	}
// </editor-fold>

uint	AltimeterGetAltData(ulong		AccTS,
							Vector*		ACC,
							AltmData*	AltResult)
	{
	uint	RC	= 0;	// Pre-set to "no MPL update"
	//==================================================================
	#ifdef __SR04_Use__
	//-----------------------------------------------
	// Altitude From Ultrasonic sensor
	//-----------------------------------------------
	if (SR04Read(&AltmLocal.SR04Sample) > 0)
		{
		// Obtained next altitude reading from US sensor.
		// We may do some filtering here ...
		}
	#endif
	//==================================================================

	//==================================================================
	// Accumulate vertical acceleration for calculating average
	//------------------------------------------------------------------
	if (0 == AccLastTS)
		AccLastTS = AccTS;
	else
		{
		// Transform Gravity vector to Earth frame
		Vector	GE;
		DCMToEarth(	ACC, &GE);
		//------------------------------------------------
		// Factor out Earth Gravity and reverse sign to
		// make "up" positive
		// Also convert units of "G" to meters per second
		AccSUM	+= -(1.0 + GE.Z);
		AccCount++;
		}
	//==================================================================

	//==================================================================
	#ifdef __MPL_Use__
	//-----------------------------------------------
	// Altitude from Barometric sensor
	//-----------------------------------------------
	MPLData		MPLSample;
	//-----------------------------------------------
	if (MPL_OK == MPLAsyncRead(&MPLSample))
		{
		// New Barometric Altimeter measurement obtained...
		RC = 1;		// Indicate that update was received
		//------------------------------------------------
		// <editor-fold defaultstate="collapsed" desc="Perform measurement weighted smooting">
		//------------------------------------------------
		// Calculate average vertical acceleration during
		// sample interval and change in vertical speed
		//------------------------------------------------
		if (AccCount > 0)
			{
			// Calculate average of ACC-Z measurements
			AltmLocal.AccAvg = 9.81 * AccSUM	/ (float) (AccCount);
			}
		else
			AltmLocal.AccAvg = 0.0;
		//-------------------------
		AltmLocal.AccDeltaV	 = AltmLocal.AccAvg * (AccTS - AccLastTS) * TMRGetTSRate();
		//------------------------------------------------
		// Smoothing MPL altitude measurements
		//------------------------------------------------
		#ifdef __Use_DEF__
		float MPLAltSmthd = DEFFilterApply(	MPLSample.Alt,
											MPLSample.TS,
											&DEF_MPL_AltFlt);
		#else
		float MPLAltSmthd = MPLSample.Alt;	// No filtering
		#endif
		// </editor-fold>
		//------------------------------------------------

		//------------------------------------------------
		// Now calculate vertical speed from MPL
		//------------------------------------------------
		// Temporary variables used for speed/altitude calculation.
		float dT	= (MPLSample.TS - AltmLocal.MPLSample.TS) * TMRGetTSRate();
		float newV	= (MPLAltSmthd - AltmLocal.MPLAltSmthd) / dT;
		#ifdef __Use_DEF__
		newV = DEFFilterApply(	newV,
								MPLSample.TS,
								&DEF_MPL_VvertFlt);
		#endif
		AltmLocal.MPLDeltaV	= newV - AltmLocal.MPLSpeed;
		//------------------------------------------------
		// Update reporting values
		//------------------------------------------------
		AltmLocal.MPLSample.TS	= MPLSample.TS;
		AltmLocal.MPLSample.Alt = MPLSample.Alt;
		AltmLocal.MPLAltSmthd	= MPLAltSmthd;
		AltmLocal.MPLSpeed		= newV;
		//------------------------------------------------
		#ifdef __SR04_Use__
		// Can trust US Altimeter (for now) only to 0.75 m :(
		if (AltmLocal.SR04Sample.Altitude < 0.75)
			// We have VALID measurement from US Sensor
			// We may use this actual measurement with a very low weight
			MPLAdjustGround(AltmLocal.MPLSample.Alt, AltmLocal.SR04Sample.Altitude);
		#endif
		//------------------------------------------------
		AltmLocal.MPLBase		= MPLGetBase();
		//---------------------------------------------------------
		// Reset ACC-related local variables for the next cycle
		//---------------------------------------------------------
		AccLastTS	= AccTS;
		AccSUM		= 0.0;
		AccCount	= 0;
		}
	else
		{
		// <editor-fold defaultstate="collapsed" desc="Leftovers from previous thoughts">
		//==================================================================
		// Now we generate adjustmentbased upon data from the accellerometer
		//------------------------------------------------------------------
		//		if (0 == AccLastTS)
		//			AccLastTS = AccTS;
		//		else
		//			{
		//			// Transform Gravity vector to Earth frame
		//			Vector	GE;
		//			DCMToEarth(	ACC, &GE);
		//			//------------------------------------------------
		//			// Factor out Earth Gravity and reverse sign to
		//			// make "up" positive
		//			// Also convert units of "G" to meters per second
		//			AccSUM	+= -(1.0 + GE.Z) * 9.81;
		//			AccCount++;
		//			//------------------------------------------------
		//			// Calculate ACC-based speed/altitude adjustment
		//			//------------------------------------------------
		//			dT	= (AccTS - AccLastTS) * TMRGetTSRate();
		//			// Cerify calculation conditions
		//			if (dT > 0.0 && AccCount > 0)
		//				{
		//				// Calculate average of ACC-Z measurements
		//				AltmLocal.VertAcc = AccSUM	/ (float)(AccCount);
		//				//------------------------------------------------
		//				dV		= AltmLocal.VertAcc * dT;
		//				dAlt	= (AltmLocal.MPLSpeed + dV/2.0) * dT;
		//				//---------------------------------------------------------
		//				AltmLocal.VertSpeed = AltmLocal.MPLSpeed + dV;
		//				AltmLocal.VertPos	+= dAlt;
		//				}
		//==================================================================
		// </editor-fold>
		}
	#endif
	//==================================================================

	//==================================================================
	int i;
	for (i = 0; i < sizeof(AltmLocal); i++)
		((BYTE*)AltResult)[i] = ((BYTE*)&AltmLocal)[i];
	//==================================================================
	return RC;
	}
// </editor-fold>