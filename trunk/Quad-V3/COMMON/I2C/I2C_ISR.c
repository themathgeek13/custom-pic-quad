#include "I2C\I2C_Local.h"



#ifdef _I2C_UseI2C1
//*******************************************************************
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C1Interrupt(void)
	{
	//---------------------------------------------------------------
	_MI2C1IF	= 0; 	// Clear   I2C Master interrupt flag
	//---------------------------------------------------------------
	I2C_CONBITS*	pCON	= (I2C_CONBITS*) (_I2C1_CB.pI2C_CON);
	I2C_STATBITS*	pSTAT	= (I2C_STATBITS*)(_I2C1_CB.pI2C_STAT);
	//---------------------------------------------------------------
	if (NULL == _I2C1_CB._I2C_CallBack)
		// There is no active Asynchronous subscribers - spurious interrupt
		{
		_MI2C1IE		= 0;	// Disable I2C Master interrupt
		pCON->PEN;
		return;
		}
	//===============================================================
	// Check for STOP condition on the bus
	//===============================================================
	if (1 == pSTAT->P)
		// STOP was issued by I2CAsyncStop(...) or as result of an error
		{
		//-----------------------------------------------------------
		// Check for Asynchronous queued requests
		//-----------------------------------------------------------
		int i;
		for (i = 0; i < I2CMaxAsyncRqst; i++)
			{
			if (_I2C1_CB._I2CRqstQueue[i].CallBack)
				{
				// Promote request from the queue to Active
				_I2C1_CB._I2C_CallBack		= _I2C1_CB._I2CRqstQueue[i].CallBack;
				_I2C1_CB._I2C_CallBackArg	= _I2C1_CB._I2CRqstQueue[i].CallBackArg;
				// Free up queue entry
				_I2C1_CB._I2CRqstQueue[i].CallBack		= NULL;
				_I2C1_CB._I2CRqstQueue[i].CallBackArg	= 0;
				//---------------------------------------------------
				// Initiate Start on I2C bus
				//---------------------------------------------------
				pCON->SEN = 1;
				// NOTE: because I2C bus is being allocated to the client,
				//		 from now until the asynchronous operation completes
				//		 I2C interrupts will be routed to client's callback
				//		 routine.
				//---------------------------------------------------
				return;
				}
			}
		//-----------------------------------------------------------
		// Current Asynchronous request completed and there is no
		// outstanding requests in the queue...
		//-----------------------------------------------------------
		_MI2C1IE		= 0;			// Disable I2C Master interrupt
		_I2C1_CB._I2C_CallBack		= NULL;		// clear Callback
		_I2C1_CB._I2C_CallBackArg	= 0;		// clear Callback Arg
		//-----------------------------------------------------------
		return;
		}
	//===============================================================
	// Check for any ERROR condition on the bus
	//===============================================================
	// Simple errors...
	//---------------------------------------------------------------
	if 	(	pSTAT->ACKSTAT		// 1 = NACK received from slave
		||	pSTAT->I2COV		// 1 = READ Overflow condition
		||	pSTAT->IWCOL		// 1 = Write Collision
//		||	pSTAT->BCL			// 1 = Master Bus Collision
		 )
		{
		//-----------------------------------------------------------
		// First, let's try to reset the bus...
		//-----------------------------------------------------------
		*(_I2C1_CB.pI2C_CON)	= 0;	// Disable I2C module..
		*(_I2C1_CB.pI2C_STAT)	= 0;	// Clear STATUS bits
		pCON->I2CEN				= 1;	// Re-enable I2C
		// Attempt to terminate current operation by initiating STOP
		I2CAsyncStop(pCON,	pSTAT);
		//-----------------------------------------------------------
		return;
		}
	//---------------------------------------------------------------
	// Bus collision...
	//---------------------------------------------------------------
	if 	(	pSTAT->BCL		)	// 1 = Master Bus Collision
		{
		//-----------------------------------------------------------
		// First, let's try to reset the bus...
		//-----------------------------------------------------------
		*(_I2C1_CB.pI2C_CON)	= 0;	// Disable I2C module..
		*(_I2C1_CB.pI2C_STAT)	= 0;	// Clear STATUS bits
		pCON->I2CEN				= 1;	// Re-enable I2C
		//-----------------------------------------------------------
		// Let's give it some time to recuperate...
		//-----------------------------------------------------------
		_MI2C1IE		= 0;			// Disable I2C Master interrupt
		_I2C1_CB._I2C_CallBack		= NULL;		// clear Callback
		_I2C1_CB._I2C_CallBackArg	= 0;		// clear Callback Arg
		//-----------------------------------------------------------
		pCON->SEN;
		//-----------------------------------------------------------
		return;
		}
	//===============================================================
	// Normal I2Cx interrupt with the active subscriber - pass
	// interrupt to respective subscriber.
	//===============================================================
	// Invoke callback function
	(*_I2C1_CB._I2C_CallBack)(	_I2C1_CB._I2C_CallBackArg,
								pCON,
								pSTAT,
								_I2C1_CB.pI2C_TRN,
								_I2C1_CB.pI2C_RCV);
	//---------------------------------------------------------------
	return;
	//===============================================================
	}
//*******************************************************************
#endif


#ifdef _I2C_UseI2C2
//*******************************************************************
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C2Interrupt(void)
	{
	//---------------------------------------------------------------
	_MI2C2IF	= 0; 	// Clear   I2C Master interrupt flag
	//---------------------------------------------------------------
	if (NULL == _I2C2_CB._I2C_CallBack)
		// There is no active Asynchronous subscribers - spurious interrupt
		{
		_MI2C2IE		= 0;	// Disable I2C Master interrupt
		return;
		}
	//---------------------------------------------------------------
	I2C_CONBITS*	pCON	= (I2C_CONBITS*) (_I2C2_CB.pI2C_CON);
	I2C_STATBITS*	pSTAT	= (I2C_STATBITS*)(_I2C2_CB.pI2C_STAT);
	//===============================================================
	// Check for STOP condition on the bus
	//===============================================================
	if (1 == pSTAT->P)
		// STOP was issued by I2CAsyncStop(...) or as result of an error
		{
		//-----------------------------------------------------------
		// Check for Asynchronous queued requests
		//-----------------------------------------------------------
		int i;
		for (i = 0; i < I2CMaxAsyncRqst; i++)
			{
			if (_I2C2_CB._I2CRqstQueue[i].CallBack)
				{
				// Promote request from the queue to Active
				_I2C2_CB._I2C_CallBack		= _I2C2_CB._I2CRqstQueue[i].CallBack;
				_I2C2_CB._I2C_CallBackArg	= _I2C2_CB._I2CRqstQueue[i].CallBackArg;
				// Free up queue entry
				_I2C2_CB._I2CRqstQueue[i].CallBack		= NULL;
				_I2C2_CB._I2CRqstQueue[i].CallBackArg	= 0;
				//---------------------------------------------------
				// Initiate Start on I2C bus
				//---------------------------------------------------
				pCON->SEN = 1;
				// NOTE: because I2C bus is being allocated to the client,
				//		 from now until the asynchronous operation completes
				//		 I2C interrupts will be routed to client's callback
				//		 routine.
				//---------------------------------------------------
				return;
				}
			}
		//-----------------------------------------------------------
		// Current Asynchronous request completed and there is no
		// outstanding requests in the queue...
		//-----------------------------------------------------------
		_MI2C2IE		= 0;			// Disable I2C Master interrupt
		_I2C2_CB._I2C_CallBack		= NULL;		// clear Callback
		_I2C2_CB._I2C_CallBackArg	= 0;		// clear Callback Arg
		//-----------------------------------------------------------
		return;
		}
	//===============================================================
	// Check for any ERROR condition on the bus
	//===============================================================
	if 	(
			pSTAT->ACKSTAT		// 1 = NACK received from slave
		||	pSTAT->BCL			// 1 = Master Bus Collision
		||	pSTAT->IWCOL		// 1 = Write Collision
		||	pSTAT->I2COV		// 1 = READ Overflow condition
		)
		{
		//-----------------------------------------------------------
		// Error: Terminate current ASYNC session
		// emulate I2CAsynStop(...)
		//-----------------------------------------------------------
		*(_I2C2_CB.pI2C_STAT)	= 0;	// clear STATUS bits
		pCON->PEN				= 1;	// Initiate Stop on I2C bus
		//-----------------------------------------------------------
		return;
		}
	//===============================================================
	// Normal I2Cx interrupt with the active subscriber - pass 
	// interrupt to respective subscriber.
	//===============================================================
	// Invoke callback function
	(*_I2C2_CB._I2C_CallBack)(	_I2C2_CB._I2C_CallBackArg,
								pCON,
								pSTAT,
								_I2C2_CB.pI2C_TRN,
								_I2C2_CB.pI2C_RCV);
	//---------------------------------------------------------------
	return;
	//===============================================================
	}
//*******************************************************************
#endif
