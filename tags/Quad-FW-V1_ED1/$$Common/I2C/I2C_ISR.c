#include "I2C\I2C_Local.h"



//*******************************************************************
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C1Interrupt(void)
	{
	//---------------------------------------------------------------
	_MI2C1IF	= 0; 		// Clear   I2C(1) Master interrupt flag
	//---------------------------------------------------------------
	if (1 == _P)
		// STOP was issued by I2CAsyncStop()
		{
		//----------------------------------------
		_MI2C1IE= 0;			// Disable I2C(1)
								// Master interrupt
		_I2C_CallBack	= 0;	// clear callback
		//----------------------------------------
		_INT1IE	= _I2C_Int1;	// Re-set INT1 interrupt
		_INT2IE	= _I2C_Int2;	// Re-set INT2 interrupt
		//----------------------------------------
		return;
		}
	//----------------------------------------------
	// Store callback pointer value locally to avoid
	// "race condition" with the following test
	//----------------------------------------------
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
void __attribute__((__interrupt__,__no_auto_psv__)) _SI2C1Interrupt (void)
	{
	//---------------------------------------------------------------
	_SI2C1IF	= 0; 		// Clear   I2C(1) Slave interrupt flag
	//---------------------------------------------------------------
	return;
	}
//*******************************************************************
