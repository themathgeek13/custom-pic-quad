#include "I2C\I2C_Local.h"

//============================================================
// Asynchronous I2C API (visible externally) component
//============================================================
// <editor-fold defaultstate="collapsed" desc="uint	I2CAsyncStart(uint SubscrID)">
uint	I2CAsyncStart(uint I2Cx, I2CAsyncRqst* Rqst)
	{
	if (!_I2C_Init)		return I2CRC_NRDY;
	//=========================================================
	// Obtain references to proper Control Blocks and registers
	//---------------------------------------------------------
	_I2C_CB*		pCB;
	if ( NULL == (pCB = I2CpCB(I2Cx)) )		return I2CRC_NOTA;
	//---------------------------------------------------------
	I2C_CONBITS*	pCON	= I2CpCON(pCB);
	I2C_STATBITS*	pSTAT	= I2CpSTAT(pCB);
	//=========================================================
	// Validate run-time conditions
	//---------------------------------------------------------
	int		i;
	//---------------------------------------------------------
	uint	RC		= I2CRC_OK;
	BYTE	CPU_IPL;
	//---------------------------------------------------------
	// Enter I2C (and related modules) CRITICAL SECTION
	//---------------------------------------------------------
	SET_AND_SAVE_CPU_IPL(CPU_IPL, _I2C_IL);
		{
		//-----------------------------------------------------------
		// New request...
		//-----------------------------------------------------------
		if (pCB->_I2C_CallBack)
			// There is an active request being processed -
			// several checks need to be implemented...
			{
			//------------------------------------------------------------
			// First, check whether this request already active
			//---------------------------------------------------------
			if (	pCB->_I2C_CallBack		== Rqst->CallBack
				&&	pCB->_I2C_CallBackArg	== Rqst->CallBackArg )
				{
				// Duplicate request...
				RC = I2CRC_RQSTA;
				goto Finally;
				}
			//-------------------------------------------------------
			// Second, check whether this request already queued
			//-------------------------------------------------------
			for (i = 0; i < I2CMaxAsyncRqst; i++)
				{
				if (	pCB->_I2CRqstQueue[i].CallBack		== Rqst->CallBack
					 &&
						pCB->_I2CRqstQueue[i].CallBackArg	== Rqst->CallBackArg )
					{
					// Request is already in the queue...
					RC = I2CRC_OK;
					goto Finally;
					}
				}
			//-------------------------------------------------------
			// Third, try to add this request to the queue
			//-------------------------------------------------------
			for (i = 0; i < I2CMaxAsyncRqst; i++)
				{
				if (	NULL == pCB->_I2CRqstQueue[i].CallBack )
					{
					// Free slot found! Add request to the queue
					pCB->_I2CRqstQueue[i].CallBack		= Rqst->CallBack;
					pCB->_I2CRqstQueue[i].CallBackArg	= Rqst->CallBackArg;
					//-------------------------------------------
					RC = I2CRC_OK;
					goto Finally;
					}
				}
			// No free slots available in the queue...
			RC = I2CRC_QFULL;
			goto Finally;
			}
		else
			// No Active Asynchronous requests now - let's try
			// to innitiate a new Asynchronous request
			{
			// Frist, let's check bus condition
			if (0 == pSTAT->P)
				{
				// Bus is not idle as the last status is not "Stop"
				RC = I2CRC_BUSY;	// // Bus is busy...
				goto Finally;
				}
			//--------------------------------------------
			// Bus condition validated, proceed with activating
			// Async operation
			//---------------------------------------------------------
			// Store in the I2C Library control block address of the
			// callback function of the current bus owner and
			// respective callback parameter.
			//---------------------------------------------------------
			pCB->_I2C_CallBack		= Rqst->CallBack;
			// NOTE: non-NULL value of pCB->_I2C_CallBack field
			//		 also serves as a FLAG indicating that bus is
			//		 busy and tested for in I2CGetStatus(...) routine
			pCB->_I2C_CallBackArg	= Rqst->CallBackArg;
			//--------------------------------------------------------
			I2CSetIF(I2Cx, 0); 	// Clear  I2C Master interrupt flag
			I2CSetIE(I2Cx, 1);	// Enable I2C Master interrupt
			//--------------------------------------------------------
			// Initiate Start on I2C bus
			pCON->SEN = 1;
			// NOTE: because I2C bus is being allocated to the client,
			//		 from now until the asynchronous operation completes
			//		 I2C interrupts will be routed to client's callback
			//		 routine.
			RC = I2CRC_OK;
			goto Finally;
			}
		}
Finally:
	//---------------------------------------------------------
	// Leave I2C CRITICAL SECTION
	//---------------------------------------------------------
  	RESTORE_CPU_IPL(CPU_IPL);
	//=========================================================
	return RC;		
	}
// </editor-fold>
//============================================================





