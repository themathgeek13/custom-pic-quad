#include "I2C/I2C_Local.h"



//*******************************************************************
void __attribute__((__interrupt__,__no_auto_psv__)) I2C1Interrupt(void)
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
		// Rest Subscriber's Interrup Enable flags to requested values
		//-----------------------------------------------------------
		I2C_Sub1IE	= _I2C_Sub1;	// Re-set SUB1 interrupt
		I2C_Sub2IE	= _I2C_Sub2;	// Re-set SUB2 interrupt
		I2C_Sub3IE	= _I2C_Sub3;	// Re-set SUB3 interrupt
		I2C_Sub4IE	= _I2C_Sub4;	// Re-set SUB4 interrupt
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


//*******************************************************************
// We should never get here as we operate I2C in MASTER mode, but...
//*******************************************************************
void __attribute__((__interrupt__,__no_auto_psv__)) _SI2C1Interrupt (void)
	{
	//---------------------------------------------------------------
	I2C_SlaveIF	= 0; 		// Clear   I2C(1) Slave interrupt flag
	//---------------------------------------------------------------
	return;
	}
//*******************************************************************
