#include "HMCSPI\HMCSPI_Local.h"

//-------------------------------------------------------------
// Forward declaration of a helper function
//-------------------------------------------------------------
HMC_RC	_HMCAsyncRead(HMCData* Sample);
//-------------------------------------------------------------

//*************************************************************
// <editor-fold defaultstate="collapsed" desc="HMC_RC	HMC_AsyncStart()">
//-------------------------------------------------------------
HMC_RC	HMC_AsyncStart()
	{
	if (!_HMC_Init)
		return HMC_NotInit;		// Not initialized...
	//---------------------------------------------------------
	if (1 == _HMC_Async)
		return HMC_OK;			// Already started...
	//---------------------------------------------------------
	_HMC_Ready	= 0;		// Discard async sample (if any)
	_HMC_Async	= 1;		// Set Asynchronous READ flag
	//=========================================================
	// Start INTx module and enable INTx interrupts
	//---------------------------------------------------------
	HMC_IF	= 0;		// Clear the INTx interrupt flag
	HMC_IE	= 1;		// Enable INTx interrupt
	//---------------------------------------------------------
	// Next time HMC5983 raises DRDY line INTx will trigger
	// interrupt an initiate reading of the data.
	//=========================================================
	return HMC_OK;
	}
//-------------------------------------------------------------
// </editor-fold>
//*************************************************************
// <editor-fold defaultstate="collapsed" desc="HMC_RC	HMC_AsyncStop()">
//-------------------------------------------------------------
HMC_RC	HMC_AsyncStop()
	{
	if (!_HMC_Init)
		return HMC_NotInit;		// Not initialized...
	//---------------------------------------------------------
	if (0 == _HMC_Async)
		return HMC_OK;			// Async is not active...
	//=====================================================
	// Disable ASYNC driver
	//=====================================================
	// Stopt INTx module and disable INTx interrupts
	//---------------------------------------------------------
	HMC_IF	= 0;		// Clear the INTx interrupt flag
	HMC_IE	= 0;		// Disable INTx interrupt
	//=========================================================
	// Clear ASYNC flag
	//=========================================================
	_HMC_Async	= 0;		// Asynchronous read not active...
	//---------------------------------------------------------
	_HMC_Ready	= 0;		// Discard async sample
	//---------------------------------------------------------
	return HMC_OK;
	}
//-------------------------------------------------------------
// </editor-fold>
//*************************************************************
// <editor-fold defaultstate="collapsed" desc="HMC_RC	HMC_AsyncReadIfReady(HMCData* Sample)">
//-------------------------------------------------------------
HMC_RC	HMC_AsyncReadIfReady(HMCData* Sample)
	{
	if (0 == _HMC_Async)
		return HMC_NoAsync;		// Asynchronous read not active...
	//--------------------------------------------------
	if (0 == _HMC_Ready)
		return HMC_AsyncNotRdy;	// Async data is not ready yet
	//------------------------
	return _HMCAsyncRead(Sample);
	}
//-------------------------------------------------------------
// </editor-fold>
//*************************************************************
// <editor-fold defaultstate="collapsed" desc="HMC_RC	HMC_AsyncReadWhenReady(HMCData* Sample)">
//-------------------------------------------------------------
HMC_RC	HMC_AsyncReadWhenReady(HMCData* Sample)
	{
	if (0 == _HMC_Async)
		return HMC_NoAsync;		// Asynchronous read not active...
	//--------------------------------------------------
	while (0 == _HMC_Ready);	// Wait until READY
	//------------------------
	return _HMCAsyncRead(Sample);
	}
//-------------------------------------------------------------
// </editor-fold>
//*************************************************************

//*************************************************************
// <editor-fold defaultstate="collapsed" desc="HMC_RC _HMCAsyncRead(HMCData* Sample)">
//-------------------------------------------------------------
HMC_RC	_HMCAsyncRead(HMCData* Sample)
	{
	//----------------------------------------------
	uint			Ready_Cnt;
	_HMCRawData		RawData;
	//----------------------------------------------
	int current_cpu_ipl;
	//==============================================
	// Enter HMC/I2C CRITICAL SECTION
	//----------------------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _HMC_IL);  /* disable interrupts */
	//----------------------------------------------
	RawData.MX	= _HMC_Sample.MX;
	RawData.MY	= _HMC_Sample.MY;
	RawData.MZ	= _HMC_Sample.MZ;
	//-----------------------------------------------
	Ready_Cnt	= _HMC_Ready;
	//-----------------------------------------------
	_HMC_Ready = 0;		// Sample consumed...
	//----------------------------------------------
	// Leave HMC/I2C CRITICAL SECTION
	//==============================================
  	RESTORE_CPU_IPL(current_cpu_ipl);

	//==============================================
	// Adjust Sample Weight to account for multiple
	// samples (data averaging)
	//----------------------------------------------
	if (Ready_Cnt > 1)
		{
		float 	Weight = 1.0/(float)Ready_Cnt;
		VectorSet	(
					Weight * RawData.MX * _HMC_Gain,
					Weight * RawData.MY * _HMC_Gain,
					Weight * RawData.MZ * _HMC_Gain,
					&Sample->M
					);
		}
	else
		{
		VectorSet	(
							 RawData.MX * _HMC_Gain,
							 RawData.MY * _HMC_Gain,
							 RawData.MZ * _HMC_Gain,
					&Sample->M
					);
		}
	//-----------------------------------------------
	// Magnetic field - adjusted for Hard and Soft
	// Iron
	//-----------------------------------------------
	_HMC_NormHMCData(&Sample->M);
	//-----------------------------------------------
	// Set sample timestamp
	//----------------------------------------------
	Sample->TS	= TMRGetTS();
	//----------------------------------------------
	return HMC_OK; 			// The return code was OK
	}
//-------------------------------------------------------------
// </editor-fold>
//===============================================================
