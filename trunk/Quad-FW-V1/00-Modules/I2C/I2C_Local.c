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
volatile uint	_I2C_Int1		= 0;	// Ext Int1 control
volatile uint	_I2C_Int2		= 0;	// Ext Int2 control
//==================================================================
byte	I2CGetIL()
	{
	return _I2C_IL;
	}
//==================================================================
