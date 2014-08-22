#include "MPL3115/MPL3115_Local.h"
#include "I2C/I2C_Local.h"

#include <math.h>

//************************************************************
uint	MPLInit(byte OSR)
	{
	//************************************************
	// MPL module depends on I2C for communication with the 
	// sensor, so we need to make sure that I2C is initialized...
	//************************************************
	byte	IL = I2CGetIL();
	if (0 == IL)
		return I2CRC_NRDY;	// I2C Module is not initialized
	//---------------------------------------------------------
	if (_MPL_Init)
		return	MPL_OK;		// Avoid repeated initialization...
	_MPL_Init	= 1;
	//---------------------------------------------------------
	_MPL_IL	= IL;
	//************************************************

	//************************************************
	// MPL group of functions depend on timer providing
	// timestamps for interval measurement, thus we
	// make sure that timer is intitialized.
	//************************************************
	TMRInitDefault();

	//---------------------------------------------------------
	// MPL Module uses Input Capture facility to generate
	// interrupt on READY state for asynchronous data aquisition
	//---------------------------------------------------------
	MPL_ICCON	= 0;	// Disable ICx for configuration
	//---------------------------------------------------------
	// Please NOTE that the Init program disables all PERIPHERAL
	// MODULES using PMDx registers. To continue configuring and
	// later enabling Input Capture module we need to enable
	// module in PMDx
	//---------------------------------------------------------
	MPL_PMD		= 0;	// Enable ICx module
	//---------------------------------------------------------

	//---------------------------------------------------------
	// Map MCU pins used by Input Capture module through
	// REMAPPABLE PIN SELECT feature.
	//---------------------------------------------------------
	 _MPLInitPinMap();

	//---------------------------------------------------------
	// Configure Interrupts
	//---------------------------------------------------------
	MPL_IE		= 0;			// Disable ICx interrupt
	MPL_IF		= 0; 			// Clear ICx interrupt flag
	MPL_IP		= _MPL_IL;		// Set ICx interrupt priority
	//---------------------------------------------------------
	// ICx interrupt enabled in MPLAsyncStart() routine
	//---------------------------------------------------------

	//---------------------------------------------------------
	// After configuration complete enable ICx module
	//---------------------------------------------------------
	// NOTE: For this application we do not capture the
	//		 actual timer value associated with the module,
	//		 so we do not care configuring timer associated
	//		 with ICx.
	//---------------------------------------------------------
	// NOTE: By setting MPL_ICCON = 0 we implicitly set ICI=0,
	//		 which implies that the ICx FIFO buffer overflow
	//		 will not stop generation of interrupts.
	//---------------------------------------------------------
	MPL_ICM	= 3; // Capture mode, interrupt on every rising edge
	//---------------------------------------------------------

	//---------------------------------------------------------
	// Now we should initialize the sensor...
	//---------------------------------------------------------
	uint	RC	= MPL_OK;
	//---------------------------------------------------------
	if (MPL_OK != (RC = MPLReset(OSR)))
	  return RC;
	//---------------------------------------------------------
	return RC;
	}

//=============================================================
uint	MPLReset(byte OSR)
	{
	if (!_MPL_Init)
		return MPL_NOTINIT;		// Not initialized...
	//*********************************************************
	uint		RC		= MPL_OK;
	//*********************************************************
	if (_MPL_Async)
		{
		// Asynchronous operation in progress...
		// Let's try to stop it for RESET
		if (MPL_OK != (RC = MPLAsyncStop()))
		  return RC;	// Failure... Not likely :)
		}
	//************************************************
	// Validate OSR - acceptable values are from 0
	// for no oversampling to 7 for 2^7=128 over-
	// sampling ratio
	//************************************************
	if (OSR > 7) OSR = 7;

	//*********************************************************
	byte		CtrlR1;
	byte		OSR_Ctrl = OSR << 3;
	//---------------------------------------------------------
	// First, let's put MPL into STANDBY mode
	//---------------------------------------------------------
	// Read current value
	RC = _MPLRead(CtrlR1Addr, &CtrlR1, 1);
	if (RC) return RC;	// Failure...
	// Clear SBYB bit
	CtrlR1 &= 0xFE;
	// Apply new configuration
	RC	= _MPLWrite(CtrlR1Addr, &CtrlR1, 1);
	if (RC) return RC;	// Failure...
	// Wait until STANDBY completes
	CtrlR1 = 0xFF;		// Dummy value
	while (CtrlR1 & 0x01)
		{
		TMRDelay(1);	// 1 msec delay...
		RC = _MPLRead(CtrlR1Addr, &CtrlR1, 1);
		if (RC) return RC;	// Failure...
		}
	//---------------------------------------------------------
	// Second, let's RESET MPL by initiating RESET
	// NOTE: RESET also disables FIFO
	//---------------------------------------------------------
	CtrlR1 = 0x04;		// Set RESET bit
	// Innitiate RESET
	// NOTE: REST also resets I2C bus, so we expect NACK
	RC	= _MPLWrite(CtrlR1Addr, &CtrlR1, 1);
	if (RC != I2CRC_NACK) return RC;	// Failure...
	// Wait until RESET completes
	CtrlR1 = 0xFF;		// Dummy value
	while (0x00 != CtrlR1)
		{
		TMRDelay(1);	// 1 msec delay...
		RC = _MPLRead(CtrlR1Addr, &CtrlR1, 1);
		if (RC) return RC;	// Failure...
		}
	//---------------------------------------------------------
	// Now that MPL is in STANDBY after RESET, we may
	// configure other control registers
	//---------------------------------------------------------
	// Let's configure Event Flag Generation
	//---------------------------------------------------------
	byte	PT_DATA_CFG		= 0x07;	// DRDY = PDEFE = TDEFE = 1
	RC	= _MPLWrite(0x13, &PT_DATA_CFG, 1);
	if (RC) return RC;	// Failure...
	//---------------------------------------------------------
	// After RESET CtrlR2 = 0x00 - no need to change
	//---------------------------------------------------------
	// Interrupt Control Register
	byte	CtrlR3	= 0x22;		// Int1, Int2 - active HIGH
								// Push/Pull (vs. Open Drain)
	RC	= _MPLWrite(0x28, &CtrlR3, 1);
	if (RC) return RC;	// Failure...
	//---------------------------------------------------------
	// Interrupt Enable Register
	byte	CtrlR4	= 0x83;		// Only DRDY + PCHG + TCHG
	RC	= _MPLWrite(0x29, &CtrlR4, 1);
	if (RC) return RC;	// Failure...
	//---------------------------------------------------------
	// Interrupt Routing Register
	byte	CtrlR5	= 0x83;		// DRDY + PCHG + TCHG on Int1 pin
	RC	= _MPLWrite(0x2A, &CtrlR5, 1);
	if (RC) return RC;	// Failure...
	//---------------------------------------------------------
	// Finally we may configure sensor for Altimeter mode with
	// specified OSR and set OST to start the cycle
	//---------------------------------------------------------
	CtrlR1 = 0x80 | OSR_Ctrl | CtrlR1SetOST;	// Alt + OSR + OST
	// Write new configuration value
	RC = _MPLWrite(CtrlR1Addr, &CtrlR1, 1);
	if (RC) return RC;	// Failure...
	//*********************************************************

	//*********************************************************
	// Before we conclude RESET we need to calculate value of
	// MAX interval between consequitive data samples based on
	// the new OSR value
	//*********************************************************
	_MPL_MaxInt = (ulong)((powf(2.0, (float)(OSR))*0.003 + 0.004)/TMRGetTSRate());

	//*********************************************************
	// To conclude RESET we need to implement single READ
	// operation
	//*********************************************************
	MPLData	Sample;
	return MPLReadSample(&Sample);
	}
//=============================================================

//=============================================================
uint	MPLSetGround()
	{
	if (0 == _MPL_Init)
		return MPL_NOTINIT;		// Not initialized...
	//=========================================================
	// Local Variables
	//---------------------------------------------------------
	MPLData	SampleData;
	float		Ground		= 0.0;
	//---------------------------------------------------------
	uint			RC		= MPL_OK;	// Pre-set to Success
	//=========================================================

	//=========================================================
	// Reset  Ground offset...
	//---------------------------------------------------------
	// Clear accumulated pipeline
	if (_MPL_Async)
		{
		// Asynchronous operation in progress...
		if ( MPL_OK != (RC = MPLAsyncReadWhenReady(&SampleData)) )
			return RC;				// Error...
		}
	// Reset Base offset
	_MPL_BaseAlt	= 0.0;
	//---------------------------------------------------------
	// To collect average for Ground altitudewe would like to
	// sample MPL for 5 seconds
	//---------------------------------------------------------
	ulong	Alarm = TMRSetAlarm(1000);	// Set Alarm time 1 sec
										// into the future
	long	SampleCount	= 0;			// Number of samples collected
	//---------------------------------------------------------
	do
		{
		if (_MPL_Async)
			// Asynchronous operation in progress...
			RC = MPLAsyncReadWhenReady(&SampleData);
		else
			// Use Synchronous access
			RC = MPLReadSample(&SampleData);
		//-----------------------------------------
		// Check for error
		//-----------------------------------------
		if ( MPL_OK != RC )
			return RC;				// Error...
		//--------------------------------------
		// Sample obtained successfully
		//--------------------------------------
		Ground += SampleData.Alt;	// Accumulate Alt value
		SampleCount++;				// Increase count
		}
	while ( FALSE == TMRTestAlarm(Alarm) );
	//---------------------------------------------------------
	// Let's set the Ground level as the average of SampleCount
	// samples with rounding to sensor precision + 1
	//---------------------------------------------------------
	_MPL_BaseAlt	=  floorf((Ground / ((float)SampleCount)) * 32.0 + 0.5)/32.0;
	//*********************************************************
	return MPL_OK;
	}

//=============================================================
uint	MPLAdjustGround(float Altitude, float Target)
	{
	if (0 == _MPL_Init)
		return MPL_NOTINIT;		// Not initialized...
	//=========================================================
	// Gradually adjust Ground offset...
	//---------------------------------------------------------
	// "Weigt" should be some prime number different from
	// parameter "smooting" weight in Altimeter module
	//---------------------------------------------------------
	// 131 - expect slow changes
	// 179 - even slower (for OSR = 3)
	// 257 - even slower (for OSR = 3)
	_MPL_BaseAlt = _MPL_BaseAlt + (Altitude - Target) / 257.0;
	//---------------------------------------------------------
	// Let's round the Ground level offset to sensor precision + 1
	//---------------------------------------------------------
//	_MPL_BaseAlt	=  floorf(_MPL_BaseAlt * 32.0 + 0.5)/32.0;
	//*********************************************************
	return MPL_OK;
	}


