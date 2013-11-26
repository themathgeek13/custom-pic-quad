#include "HMCMAG\HMCMAG_Local.h"
//*******************************************************

//-------------------------------------------------------
// HMC Asynchronous Read operation is closely linked with
// the operation of the I2C module, thus we need to bring
// in the definition of some internal data structures.
//-------------------------------------------------------


// Forward declaration...
uint	_HMCAsyncRead(HMCSample* pSample);

//*************************************************************
uint		HMCAsyncStart()
	{
	if (!_HMC_Init)
		return HMC_NOTINIT;		// Not initialized...
	//---------------------------------------------------------							
	if (1 == _HMC_Async)
		return HMC_OK;			// Already started...
	//---------------------------------------------------------
	_HMC_Async	= 1;		// Set Asynchronous READ flag
	//=========================================================
	// Enable INT2 interrupts
	//---------------------------------------------------------							
	_INT2IF = 0;			// Clear the INT2 interrupt flag
	I2CRegisterSubscr(2);	// Enable INT2 interrupt and re-
							// gister with I2C module- when 
							// HMC magnetometer has sample,
							// the interrupt will be triggered
	//=========================================================
	return HMC_OK;
	}
//*************************************************************


//*************************************************************
uint	HMCAsyncStop()
	{
	if (!_HMC_Init)
		return HMC_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	if (0 == _HMC_Async)
		return HMC_OK;			// Async is not active...
	//=====================================================
	// Disable ASYNC driver - INT2
	//=====================================================
	I2CDeRegisterSubscr(2);	// Disable and deregister
							// INT2 interrupt
	_INT2IF = 0;			// Clear the INT2 interrupt flag
	//=========================================================
	// Clear ASYNC flag
	//=========================================================
	_HMC_Async	= 0;		// Asynchronous read not active...
	//---------------------------------------------------------
	_HMC_Ready	= 0;		// Discard async sample
	//---------------------------------------------------------
	return HMC_OK;			
	}
//*************************************************************


//*************************************************************
uint	HMCAsyncRead(HMCSample* pSample)
	{
	if (0 == _HMC_Async)
		return HMC_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	return _HMCAsyncRead(pSample);
	}
//*************************************************************

//*************************************************************
uint	HMCAsyncReadIfReady(HMCSample* pSample)
	{
	if (0 == _HMC_Async)
		return HMC_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	if (0 == _HMC_Ready)
		return HMC_NRDY;
	//------------------------
	return _HMCAsyncRead(pSample);
	}
//*************************************************************

//*************************************************************
uint	HMCAsyncReadWhenReady(HMCSample* pSample)
	{
	if (0 == _HMC_Async)
		return HMC_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	while (0 == _HMC_Ready);		// Wait until READY
	//------------------------
	return _HMCAsyncRead(pSample);
	}
//*************************************************************

//*************************************************************
uint	_HMCAsyncRead(HMCSample* pSample)
	{
	//----------------------------------------------
	uint		Ready_Cnt;
	_HMCRawData	RawData;
	//----------------------------------------------
	int current_cpu_ipl;
	//==============================================
	// Enter HMC/I2C CRITICAL SECTION
	//----------------------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _HMC_IL);  /* disable interrupts */
	//----------------------------------------------
	pSample->Count	= _HMC_Count;
	//-----------------------------------------------
	RawData.MX	= _HMC_Sample.MX;
	RawData.MY	= _HMC_Sample.MY;
	RawData.MZ	= _HMC_Sample.MZ;
	//-----------------------------------------------
	Ready_Cnt		= _HMC_Ready;
	//-----------------------------------------------
	_HMC_Ready = 0;		// Sample consumed...
	//----------------------------------------------
	// Leave HMC/I2C CRITICAL SECTION
	//==============================================
  	RESTORE_CPU_IPL(current_cpu_ipl);

	//==============================================
	// Adjust Sample Weight to account for multiple samples
	//----------------------------------------------
	float 	Weight;
	if (Ready_Cnt > 1)
		Weight = 1.0/(float)Ready_Cnt;
	else
		Weight = 1.0;
	//-----------------------------------------------
	// Magnetic field - adjusted for sensitivity
	// and Hard Iron
	//-----------------------------------------------
	VectorSet	(
				Weight * RawData.MX * _HMC_Sensitivity - _HMC_HardIron.X,
				Weight * RawData.MY * _HMC_Sensitivity - _HMC_HardIron.Y,
				Weight * RawData.MZ * _HMC_Sensitivity - _HMC_HardIron.Z,
				&pSample->M
				);
	//-----------------------------------------------
	// Adjustment for Soft Iron - Multiplication of 
	// soft iron adjustment matrix by magnetic vector
	// written by resulting vector components. 
	//-----------------------------------------------
	float MX	= VectorDotProduct(&_HMC_SoftIron_X, &pSample->M);
	float MY	= VectorDotProduct(&_HMC_SoftIron_Y, &pSample->M);
	float MZ	= VectorDotProduct(&_HMC_SoftIron_Z, &pSample->M);
	VectorSet	(MX, MY, MZ, &pSample->M);
	//-----------------------------------------------
	// Set sample timestamp
	//----------------------------------------------
	pSample->TS	= TMRGetTS();
	//----------------------------------------------
	return HMC_OK; 			// The return code was OK	
	}
//===============================================================




