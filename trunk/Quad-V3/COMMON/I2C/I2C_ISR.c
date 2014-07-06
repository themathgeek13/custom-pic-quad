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
	//===============================================================
	// Check for STOP condition on the bus
	//===============================================================
	if (1 == pSTAT->P)
		// STOP was issued by I2CAsyncStop(...) or as result of an error
		{
		//-----------------------------------------------------------
		_MI2C1IE		= 0;			// Disable I2C Master interrupt
		_I2C1_CB._I2C_CallBack	= 0;	// clear callback
		//-----------------------------------------------------------
		// Enable Subscribers' Interrup  flags
		//-----------------------------------------------------------
		int j;
		for (j = 0; j<I2CSubscMax; j++)
			{
			if (_I2C1_CB._I2CSubscr[j].SubscrIC)
				(*(_I2C1_CB._I2CSubscr[j].SubscrIC))(_I2C1_CB._I2CSubscr[j].ClientParam, 1);
			}
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
		*(_I2C1_CB.pI2C_STAT)	= 0;	// clear STATUS bits
		pCON->PEN				= 1;	// Initiate Stop on I2C bus
		//-----------------------------------------------------------
		return;
		}
	//===============================================================
	// Check for subscribers - if CallBack is active, pass interrupt
	// to respective subscriber.
	//===============================================================
	// Store callback pointer value locally to avoid "race condition"
	// with the following test
	//---------------------------------------------------------------
	I2CCallBack	 _callback	=	_I2C1_CB._I2C_CallBack;
	if (_callback)
		{
		// Invoke callback function
		(*_callback)(	_I2C1_CB._I2C_Param,
						1,		// Index of the current I2C module
						pCON,
						pSTAT,
						_I2C1_CB.pI2C_TRN,
						_I2C1_CB.pI2C_RCV);
		}
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
	I2C_CONBITS*	pCON	= (I2C_CONBITS*) (_I2C2_CB.pI2C_CON);
	I2C_STATBITS*	pSTAT	= (I2C_STATBITS*)(_I2C2_CB.pI2C_STAT);
	//===============================================================
	// Check for STOP condition on the bus
	//===============================================================
	if (1 == pSTAT->P)
		// STOP was issued by I2CAsyncStop(...) or as result of an error
		{
		//-----------------------------------------------------------
		_MI2C2IE		= 0;			// Disable I2C Master interrupt
		_I2C2_CB._I2C_CallBack	= 0;	// clear callback
		//-----------------------------------------------------------
		// Enable Subscribers' Interrup  flags
		//-----------------------------------------------------------
		int j;
		for (j = 0; j<I2CSubscMax; j++)
			{
			if (_I2C2_CB._I2CSubscr[j].SubscrIC)
				(*(_I2C2_CB._I2CSubscr[j].SubscrIC))(_I2C2_CB._I2CSubscr[j].ClientParam,1);
			}
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
	// Check for subscribers - if CallBack is active, pass interrupt
	// to respective subscriber.
	//===============================================================
	// Store callback pointer value locally to avoid "race condition"
	// with the following test
	//---------------------------------------------------------------
	I2CCallBack	 _callback	=	_I2C2_CB._I2C_CallBack;
	if (_callback)
		{
		// Invoke callback function
		(*_callback)(	_I2C2_CB._I2C_Param,
						2,		// Index of the current I2C module
						pCON,
						pSTAT,
						_I2C2_CB.pI2C_TRN,
						_I2C2_CB.pI2C_RCV);
		}
	//---------------------------------------------------------------
	return;
	//===============================================================
	}
//*******************************************************************
#endif
