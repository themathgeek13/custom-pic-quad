#include "I2C\I2C_Local.h"



//*******************************************************************
void __attribute__((__interrupt__,__no_auto_psv__)) I2CInterrupt(void)
	{
	//---------------------------------------------------------------
	I2C_IF	= 0; 		// Clear   I2C Master interrupt flag
	//---------------------------------------------------------------
	if (1 == I2C_P)
		// STOP was issued by I2CAsyncStop()
		{
		//-----------------------------------------------------------
		I2C_IE			= 0;	// Disable I2C Master interrupt
		_I2C_CallBack	= 0;	// clear callback
		//-----------------------------------------------------------
		// Enable Subscribers' Interrup  flags
		//-----------------------------------------------------------
		int j;
		for (j = 0; j<I2CSubscMax; j++)
			{
			if (_I2CSubscr[j].SubscrIC)
				(*(_I2CSubscr[j].SubscrIC))(1);
			}
		//-----------------------------------------------------------
		return;
		}
	//---------------------------------------------------------------
	// Check for subscribers - if CallBack is active, pass interrupt
	// to respective subscriber.
	//---------------------------------------------------------------
	// Store callback pointer value locally to avoid "race condition"
	// with the following test
	//---------------------------------------------------------------
	I2CCallBack	 _callback	=	_I2C_CallBack;	
	if (_callback)
		{
		// Invoke callback function
		(*_callback)();
		}
	//---------------------------------------------------------------
	return;
	}
//*******************************************************************

