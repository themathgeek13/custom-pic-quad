#include "I2C/I2C.h"
#include "I2C/I2C_Profile.h"

//==================================================================
#ifndef __I2C_Local_H
#define __I2C_Local_H
//==================================================================
// I2C Interrupt Level
//------------------------------------------------------------------
extern volatile byte			_I2C_IL;
extern volatile uint			_I2C_Init;
//==================================================================
extern volatile uint			_I2C_SBSY;	// ASYNC operation Flag
//------------------------------------------------------------------
extern volatile	I2CCallBack		_I2C_CallBack;
//------------------------------------------------------------------
// I2C Asynchronous Access Subscribers
//------------------------------------------------------------------
extern volatile uint			_I2C_Sub1;
extern volatile uint			_I2C_Sub2;
extern volatile uint			_I2C_Sub3;
extern volatile uint			_I2C_Sub4;
// Interrupt control placeholder for I2C subscribers
extern volatile uint			_I2C_SubDummy;
//==================================================================
// Internal (local) components of Synchronous I2C interface
//==================================================================
void	I2CIdle();
//------------------------------------------------------------------
void	I2CStart();
void	I2CReStart();
void	I2CStop();
//------------------------------------------------------------------
uint	I2CMasterWriteByte(byte data);
uint	I2CMasterReadByte(byte* data, uint Flag);
//------------------------------------------------------------------

#endif



