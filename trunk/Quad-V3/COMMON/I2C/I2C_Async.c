#include "I2C\I2C_Local.h"

//============================================================
// Asynchronous I2C API (visible externally) component
//============================================================
// <editor-fold defaultstate="collapsed" desc="uint	I2CAsyncStart(uint SubscrID)">
uint	I2CAsyncStart(uint	I2Cx, uint SubscrID)
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
	int		i, j;
	//---------------------------------------------------------
	uint	RC		= I2CRC_OK;
	BYTE	CPU_IPL;
	//---------------------------------------------------------
	// Enter I2C (and related modules) CRITICAL SECTION
	//---------------------------------------------------------
	SET_AND_SAVE_CPU_IPL(CPU_IPL, _I2C_IL);
		{
		if (I2CRC_OK != (RC=I2CGetStatus(pCB, pCON, pSTAT)))
			goto Finally;
		//------------------------------------------------------------
		// We can attempt to subscribe for I2C Async notification(s)
		//---------------------------------------------------------
		// First, let's validate SubscrID parameter
		//---------------------------------------------------------
		for (i = 0; i<I2CSubscMax; i++)
			{
			if ((uint)&(pCB->_I2CSubscr[i]) == SubscrID)
				{
				// Subscription ID validated, proceed with activating
				// Async notification
				//--------------------------------------------
				I2CSetIF(I2Cx, 0); 	// Clear  I2C Master interrupt flag
				//---------------------------------------------------------
				// Store in the I2C Library control block address of the
				// callback function of the current bus owner and
				// respective callback parameter.
				//---------------------------------------------------------
				pCB->_I2C_CallBack	= pCB->_I2CSubscr[i].CallBack;
				// NOTE: non-NULL value of pCB->_I2C_CallBack field
				//		 also serves as a FLAG indicating that bus is
				//		 busy and tested for in I2CGetStatus(...) routine
				pCB->_I2C_Param		= pCB->_I2CSubscr[i].ClientParam;
				//////////////////////////////////////////////////////////
				//--------------------------------------------------------
				// Disable subscribers' interrupts
				for (j = 0; j<I2CSubscMax; j++)
					{
					if (pCB->_I2CSubscr[j].SubscrIC)
						(*(pCB->_I2CSubscr[j].SubscrIC))(pCB->_I2CSubscr[j].ClientParam,0);
					}
				//--------------------------------------------------------
				I2CSetIE(I2Cx, 1);	// Enable I2C Master interrupt
				//--------------------------------------------------------
				// Initiate Start on I2C bus
				pCON->SEN = 1;
				// NOTE: because I2C bus is being allocated to the client,
				//		 from now until the asynchronous operation completes
				//		 I2C interrupts will be routed to client's callback
				//		 routine.
				goto Finally;
				}
			}
		
		//---------------------------------------------------------
		// SubscrID does not point to valid Subscription!
		//---------------------------------------------------------
		RC = I2CRC_ISID;
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
// <editor-fold defaultstate="collapsed" desc="void	I2CAsyncStop()">
void	I2CAsyncStop(uint I2Cx)
	{
	//--------------------------------------------------------
	// NOTE: Should be called only from I2C interrupt routine
	//       or its extension procedure
	//--------------------------------------------------------
	//=========================================================
	// Obtain references to proper Control Blocks and registers
	//---------------------------------------------------------
	_I2C_CB*		pCB;
	if ( NULL == (pCB = I2CpCB(I2Cx)) )		return;
	//---------------------------------------------------------
	I2C_CONBITS*	pCON	= I2CpCON(pCB);
	//=========================================================
	*(pCB->pI2C_STAT)	= 0;	// clear STATUS bits
	pCON->PEN			= 1;	// Initiate Stop on I2C bus
	//--------------------------------------------------------
	// NOTE: callback reference will be cleared in Interrupt
	//		 routine after "STOP" processed
	//--------------------------------------------------------
	return;
	}
// </editor-fold>
//============================================================
// <editor-fold defaultstate="collapsed" desc="uint	I2CRegisterSubscr(I2CSubscr* Subscr, uint* SubscrID)">
uint	I2CRegisterSubscr(uint I2Cx, I2CSubscr* Subscr)
	{
	int i;
	//=========================================================
	// Obtain references to proper Control Blocks
	//---------------------------------------------------------
	_I2C_CB*		pCB;
	if ( NULL == (pCB = I2CpCB(I2Cx)) )		return NULL;
	//--------------------------------------------------------
	// Check for existing subscription....
	//--------------------------------------------------------
	for (i = 0; i < I2CSubscMax; i++)
		{
		if (pCB->_I2CSubscr[i].CallBack == Subscr->CallBack
			&&
			pCB->_I2CSubscr[i].SubscrIC == Subscr->SubscrIC)
			{
			// Enable Client's interrupt line
			(*(Subscr->SubscrIC))(Subscr->ClientParam, 1);
			//--------------------------------------------
			// Already registered - return subscription
			// address as "black box" SubscrID
			return (uint) &(pCB->_I2CSubscr[i]);
			}
		}
	//--------------------------------------------------------
	// Attempt to add new subscription....
	//--------------------------------------------------------
	for (i = 0; i < I2CSubscMax; i++)
		{
		if ( NULL == pCB->_I2CSubscr[i].CallBack
			&&
			NULL == pCB->_I2CSubscr[i].SubscrIC)
			{
			// Found emp-ty slot - "subscribe" and return
			// subscription address as "black box" SubscrID
			pCB->_I2CSubscr[i].ClientParam	= Subscr->ClientParam;
			pCB->_I2CSubscr[i].CallBack		= Subscr->CallBack;
			pCB->_I2CSubscr[i].SubscrIC		= Subscr->SubscrIC;
			//--------------------------------------------
			// Enable Client's interrupt line
			(*(Subscr->SubscrIC))(Subscr->ClientParam, 1);
			//--------------------------------------------
			// Return subscription address as "black box"
			// SubscrID
			return (uint) &(pCB->_I2CSubscr[i]);
			}
		}
	//--------------------------------------------------------
	// Registration unsuccessful...
	//--------------------------------------------------------
	return NULL;
	}
// </editor-fold>
//============================================================
// <editor-fold defaultstate="collapsed" desc="uint	I2CDeRegisterSubscr(uint SubscrID)">
uint	I2CDeRegisterSubscr(uint I2Cx, uint SubscrID)
	{
	int i;
	//=========================================================
	// Obtain references to proper Control Blocks
	//---------------------------------------------------------
	_I2C_CB*		pCB;
	if ( NULL == (pCB = I2CpCB(I2Cx)) )		return I2CRC_NOTA;
	//--------------------------------------------------------
	// Check for existing subscription....
	//--------------------------------------------------------
	for (i = 0; i<I2CSubscMax; i++)
		{
		if ((uint)&(pCB->_I2CSubscr[i]) == SubscrID)
			{
			// Subscription ID validated
			//--------------------------------------------
			// Disable Client's interrupt line
			(*(pCB->_I2CSubscr[i].SubscrIC))(pCB->_I2CSubscr[i].ClientParam, 0);
			// Release respective slot
			//--------------------------------------------
			pCB->_I2CSubscr[i].ClientParam	= NULL;
			pCB->_I2CSubscr[i].CallBack		= NULL;
			pCB->_I2CSubscr[i].SubscrIC		= NULL;
			//--------------------------------------------
			return I2CRC_OK;
			}
		}
	//--------------------------------------------------------
	return I2CRC_ISID;
	}
// </editor-fold>
//============================================================





