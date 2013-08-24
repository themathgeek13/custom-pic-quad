#include "I2C\I2C_Local.h"

//==================================================================
// Internal (local) components of Synchronous I2C interface
//==================================================================
void I2CIdle()
	{
    /* Wait until I2C Bus is Inactive */
	//----------------------------------
    while	( _SEN || _PEN || _RCEN || _RSEN || _ACKEN || _TRSTAT );
	return;	
	}
//==================================================================
void	I2CStart()
	{
	I2CIdle();
    _SEN = 1;	// Initiate Start on SDA and SCL pins
	}
//==================================================================
void	I2CReStart()
	{
	I2CIdle();
    _RSEN = 1;	// Initiate Repeated Start on SDA and SCL pins
	}
//==================================================================
void	I2CStop()
	{
	I2CIdle();
	_PEN = 1;	// Initiate Stop on SDA and SCL pins
	}
//==================================================================
uint	I2CMasterWriteByte(byte data)
	{
	I2CIdle();					// Wait for bus to be idle
	while(_TBF);				// Wait till I2C1TRN register is empty
	I2CTRN = data;				// Put data byte into transmit register
	if(_IWCOL)    				// Check for write collision 
        return I2C_WCOL;		// Return error...
	while(_TRSTAT);				// Wait until write cycle is complete 
	I2CIdle();					// Ensure module is idle
	if ( _ACKSTAT ) 			// Test for ACK condition received
		return I2C_NACK;		// NACK...
	//------------------------------------------------------------------
	return	I2C_OK;				// Byte successfully transferred	
	}
//==================================================================
uint	I2CMasterReadByte(byte* data, uint Flag)
	{
	I2CIdle();					// Wait for bus to be idle
    _RCEN = 1;					// Put module into READ mode
    while(_RCEN);				// Wait until byte is received
	if (_I2COV)					// Overflow?
		{
		_I2COV = 0;				// Reset overflow condition
		return I2C_OVFL;		// return error...
		}
	while(!_RBF);				// Wait for byte to be ready in I2C1RCV
								// Excessive check, but...
	(*data) = I2CRCV;			// return byte to caller 
	//--------------------------------
	if(Flag == 0)              
		{
		// If last char, generate NACK sequence
		_ACKDT = 1;
		_ACKEN = 1;
		}
	else                         
		{
		// For other chars,generate ACK sequence
		_ACKDT = 0;
		_ACKEN = 1;
		}
	//--------------------------------
	I2CIdle();						// Ensure module is idle
									// ACK/NACK transmitted
	//------------------------------------------------------------------
	return	I2C_OK;				// Byte successfully transferred	
	}
//==================================================================
