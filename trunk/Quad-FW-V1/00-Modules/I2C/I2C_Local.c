#include "I2C\I2C_Local.h"

//==================================================================
volatile byte	_I2C_IL			= 0; 	// I2C interrupt level (set in I2CInit)
volatile uint	_I2C_Init		= 0;	// Init flag
//------------------------------------------------------------------
volatile uint	_I2C_SBSY		= 0;	// SYNC operation Flag
//------------------------------------------------------------------
volatile I2CCallBack
		 		_I2C_CallBack	= 0;	// CallBack function pointer
										// (ASYNC operation Flag))
//------------------------------------------------------------------
// I2C Asynchronous Access Subscribers
//------------------------------------------------------------------
volatile uint	_I2C_Sub1		= 0;	// Sub1 Interrupt control
volatile uint	_I2C_Sub2		= 0;	// Sub2 Interrupt control
volatile uint	_I2C_Sub3		= 0;	// Sub3 Interrupt control
volatile uint	_I2C_Sub4		= 0;	// Sub4 Interrupt control
// For each real asynchronous subscriber we should provide #defines
// in the I2C_Profile.h for Interrupt flag and Interrupt enable flag.
// However by-default (in the absence of subscribers) both of these
// flags will point to "_I2C_SubDummy" just to allow the code to
// compile successfully.
volatile uint	_I2C_SubDummy	= 0;
//==================================================================
byte	I2CGetIL()
	{
	return _I2C_IL;
	}
//==================================================================
