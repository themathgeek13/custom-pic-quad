#include "I2C\I2C_Local.h"

//==================================================================
// Variables shared (across I2C modules) - set in I2CInit
//==================================================================
byte	_I2C_IL			= 0; 	// I2C interrupt level 
uint	_I2C_Init		= 0;	// Init flag
uint	_I2C_BRG		= 0;	// Calculated BRG value
//==================================================================
// Control Blocks for I2C modules - initialized in I2CInit(...)
//------------------------------------------------------------------
#ifdef _I2C_UseI2C1
// Control Block for I2C1 Module
_I2C_CB		_I2C1_CB;
#endif
//------------------------------------------------------------------
#ifdef _I2C_UseI2C2
// Control Block for I2C2 Module
_I2C_CB		_I2C2_CB;
#endif
//==================================================================
