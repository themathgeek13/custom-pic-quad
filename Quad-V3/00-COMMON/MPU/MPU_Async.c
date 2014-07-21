#include "MPU\MPU_Local.h"

//-------------------------------------------------------
// MPU6050 Asynchronous Read operation is closely linked with
// the operation of the I2C module, thus we need to bring
// in the definition of some internal data structures.
//-------------------------------------------------------

// Forward declaration...
uint	_MPUAsyncRead(MPU_CB* pCB, MPUData* pSample);

//*************************************************************
uint		MPUAsyncStart(uint MPUx)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (pCB->_MPU_Async)
		return MPU_OK;			// Already started...
	//------------------------------------------------------------------
	pCB->_MPU_Async	= 1;		// Set indicator that MPU6050 
								// is in Asynchronous mode
	pCB->_MPU_Ready	= 0;		// Discard async sample, if any
	//=========================================================
	MPUSetIF(MPUx, 0);			// Clear the interrupt flag
	MPUSetIE(MPUx, 1);			// Enable interrupt processing
								// When MPL6050 has sample, the
								// interrupt will be triggered
	//=========================================================
	return MPU_OK;
	}
//*************************************************************


//*************************************************************
uint	MPUAsyncStop(uint MPUx)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (0 == pCB->_MPU_Async)
		return MPU_OK;			// Async is not active...
	//=========================================================
	pCB->_MPU_Async	= 0;		// Clear MPU-6050 Asynchronous
								// mode indicator
	pCB->_MPU_Ready	= 0;		// Discard async sample, if any
	//---------------------------------------------------------
	MPUSetIE(MPUx, 1);			// Disable interrupt processing
	MPUSetIF(MPUx, 0);			// Clear the interrupt flag
	//---------------------------------------------------------
	return MPU_OK;			
	}
//*************************************************************


//*************************************************************
uint	MPUAsyncRead(uint MPUx, MPUData* pSample)
	{
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (0 == pCB->_MPU_Async)
		return MPU_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	return _MPUAsyncRead(pCB, pSample);
	}
//*************************************************************

//*************************************************************
uint	MPUAsyncReadIfReady(uint MPUx, MPUData* pSample)
	{
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (0 == pCB->_MPU_Async)
		return MPU_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	if (0 == pCB->_MPU_Ready)
		return MPU_NRDY;
	//--------------------------------------------------
	return _MPUAsyncRead(pCB, pSample);
	}
//*************************************************************

//*************************************************************
uint	MPUAsyncReadWhenReady(uint MPUx, MPUData* pSample)
	{
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (0 == pCB->_MPU_Async)
		return MPU_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	while (0 == pCB->_MPU_Ready); 		// Wait until READY
	//------------------------
	return _MPUAsyncRead(pCB, pSample);
	}
//*************************************************************

//*************************************************************
uint	_MPUAsyncRead(MPU_CB* pCB, MPUData* pSample)
	{
	//----------------------------------------------
	uint		Ready_Cnt;
	_MPURawData RawData;
	//----------------------------------------------
	int 		current_cpu_ipl;
	//----------------------------------------------

	//==============================================
	// Enter MPU/I2C CRITICAL SECTION
	//----------------------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _MPU_IL);  /* disable interrupts */
	//---------------------------------
	RawData.Temp 	= pCB->_MPU_Sample.Temp;
	//---------------------------------
	RawData.AX		= pCB->_MPU_Sample.AX;
	RawData.AY		= pCB->_MPU_Sample.AY;
	RawData.AZ		= pCB->_MPU_Sample.AZ;
	//---------------------------------
	RawData.GX		= pCB->_MPU_Sample.GX;
	RawData.GY		= pCB->_MPU_Sample.GY;
	RawData.GZ		= pCB->_MPU_Sample.GZ;
	//-----------------------------------------------
	Ready_Cnt		= pCB->_MPU_Ready;
	//-----------------------------------------------
	pCB->_MPU_Ready = 0;		// Sample consumed...
	//----------------------------------------------
	// Leave MPU/I2C CRITICAL SECTION
	//==============================================
  	RESTORE_CPU_IPL(current_cpu_ipl);

	//==============================================
	// Set sample timestamp
	//----------------------------------------------
	pSample->TS	= TMRGetTS();
	//==============================================
	float	TDev;
	//----------------------------------------------
	// Adjust Sample Weight to account for multiple samples
	//----------------------------------------------
	float 	Weight;
	if (Ready_Cnt > 1)
		Weight = 1.0/(float)Ready_Cnt;
	else
		Weight = 1.0;
	//----------------------------------------------
	// Process collected sample
	//----------------------------------------------
	// Temperature (C) (will be used in subsequent
	// temperature compensation calculation)
	//-----------------------------------------------
	pSample->Temp = (Weight * RawData.Temp - pCB->_MPU_Temp_OffsetTo0) * pCB->_MPU_Temp_Sensitivity;
	//-----------------------------------------------
	// Acceleration (G)
	//-----------------------------------------------
	TDev	= pSample->Temp - pCB->_MPU_Accl_BaseTemp;
	//-----------------------------------------------
	VectorSet	(
				(Weight * RawData.AX - (pCB->_MPU_Accl_XOffset + pCB->_MPU_Accl_XSlope*TDev)) * pCB->_MPU_Accl_Sensitivity,
				(Weight * RawData.AY - (pCB->_MPU_Accl_YOffset + pCB->_MPU_Accl_YSlope*TDev)) * pCB->_MPU_Accl_Sensitivity,
				(Weight * RawData.AZ - (pCB->_MPU_Accl_ZOffset + pCB->_MPU_Accl_ZSlope*TDev)) * pCB->_MPU_Accl_Sensitivity,
				&pSample->A
				);
	//-----------------------------------------------
	// Gyroscopes (Rad/sec)
	//-----------------------------------------------
	TDev	= pSample->Temp - pCB->_MPU_Gyro_BaseTemp;
	//-----------------------------------------------
	VectorSet	(
				(Weight * RawData.GX - (pCB->_MPU_Gyro_XOffset + pCB->_MPU_Gyro_XSlope*TDev)) * pCB->_MPU_Gyro_Sensitivity,
				(Weight * RawData.GY - (pCB->_MPU_Gyro_YOffset + pCB->_MPU_Gyro_YSlope*TDev)) * pCB->_MPU_Gyro_Sensitivity,
				(Weight * RawData.GZ - (pCB->_MPU_Gyro_ZOffset + pCB->_MPU_Gyro_ZSlope*TDev)) * pCB->_MPU_Gyro_Sensitivity,
				&pSample->G
				);
	//-----------------------------------------------
	return MPU_OK; 			// The return code was OK	
	}
//*************************************************************


//=============================================================
uint	_MPUCalibrateAsync(MPU_CB*	pCB)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//------------------------------------------------------------------
	if (0 == pCB->_MPU_Async)
		return MPU_NACT;			// Asynchronous read not active...
	//=========================================================
	// Local Variables
	//---------------------------------------------------------
	uint		Ready_Cnt;
	MPUData		Sample;
	_MPURawData RawData;
	//----------------------------------------------
	int 		current_cpu_ipl;
	//=========================================================

	//=========================================================
	// Reset  Gyro offsets...
	//---------------------------------------------------------
	pCB->_MPU_Gyro_XOffset		= 0;
	pCB->_MPU_Gyro_YOffset		= 0;
	pCB->_MPU_Gyro_ZOffset		= 0;
	//---------------------------------------------------------
	// Consume current sample to clean the buffer
	//---------------------------------------------------------
	_MPUAsyncRead(pCB, &Sample);
	//---------------------------------------------------------
	// To collect averages we would like to "watch" MPU for at
	// least 2 seconds; number of samples will be variable
	// depending on the value of RateDiv
	//---------------------------------------------------------
	TMRDelay(2000);
	//---------------------------------------------------------

	//=========================================================
	// Enter MPU/I2C CRITICAL SECTION
	//---------------------------------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _MPU_IL);  // disable interrupts
	//---------------------------------------------------------
	RawData.Temp 	= pCB->_MPU_Sample.Temp;
	//---------------------------------
	RawData.AX		= pCB->_MPU_Sample.AX;
	RawData.AY		= pCB->_MPU_Sample.AY;
	RawData.AZ		= pCB->_MPU_Sample.AZ;
	//---------------------------------
	RawData.GX		= pCB->_MPU_Sample.GX;
	RawData.GY		= pCB->_MPU_Sample.GY;
	RawData.GZ		= pCB->_MPU_Sample.GZ;
	//---------------------------------------------------------
	Ready_Cnt		= pCB->_MPU_Ready;
	//---------------------------------------------------------
	pCB->_MPU_Ready 		= 0;		// Sample consumed...
	//---------------------------------------------------------
	// Leave MPU/I2C CRITICAL SECTION
	//=========================================================
  	RESTORE_CPU_IPL(current_cpu_ipl);
	//=========================================================

	//=========================================================
	// Adjust Sample Weight to account for multiple samples
	//---------------------------------------------------------
	float 	Weight;
	if (Ready_Cnt > 1)
		Weight = 1.0/(float)Ready_Cnt;
	else
		Weight = 1.0;
	//=========================================================

	//=========================================================
	// Process collected sample
	//---------------------------------------------------------
	// Gyro offset is calculated in LSB units
	//---------------------------------------
	pCB->_MPU_Gyro_XOffset	= (float)RawData.GX * Weight;
	pCB->_MPU_Gyro_YOffset	= (float)RawData.GY * Weight;
	pCB->_MPU_Gyro_ZOffset	= (float)RawData.GZ * Weight;
	//---------------------------------------
	// Base temperature converted to degrees C
	//---------------------------------------
	pCB->_MPU_Gyro_BaseTemp	= ((float)RawData.Temp * Weight - pCB->_MPU_Temp_OffsetTo0)
						  * pCB->_MPU_Temp_Sensitivity;
	//*********************************************************
	return MPU_OK;
	}



