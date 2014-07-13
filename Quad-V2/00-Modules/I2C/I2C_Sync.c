#include "I2C\I2C_Local.h"

//==================================================================
// Internal (local) components of Synchronous I2C interface
//==================================================================
void I2CIdle()
	{
    /* Wait until I2C Bus is Inactive */
	//----------------------------------
    while
		(
		I2C_SEN || I2C_PEN || I2C_RCEN || I2C_RSEN || I2C_ACKEN  || I2C_TRSTAT
		);
	return;	
	}
//==================================================================
void	I2CStart()
	{
	I2CIdle();
    I2C_SEN = 1;			// Initiate Start on SDA and SCL pins
	}
//==================================================================
void	I2CReStart()
	{
	I2CIdle();
    I2C_RSEN = 1;	// Initiate Repeated Start on SDA and SCL pins
	}
//==================================================================
void	I2CStop()
	{
	I2CIdle();
	I2C_PEN = 1;			// Initiate Stop on SDA and SCL pins
	}
//==================================================================
uint	I2CMasterWriteByte(byte data)
	{
	I2CIdle();					// Wait for bus to be idle
	while(I2C_TBF);				// Wait till transmit register is empty
	I2C_TRM_Reg = data;			// Put data byte into transmit register
	if(I2C_IWCOL)    			// Check for write collision
        return I2CRC_WCOL;		// Return error...
	while(I2C_TRSTAT);			// Wait until write cycle is complete
	I2CIdle();					// Ensure module is idle
	if ( I2C_ACKSTAT ) 			// Test for ACK condition received
		return I2CRC_NACK;		// NACK...
	//------------------------------------------------------------------
	return	I2CRC_OK;			// Byte successfully transferred
	}
//==================================================================
uint	I2CMasterReadByte(byte* data, uint Flag)
	{
	I2CIdle();					// Wait for bus to be idle
    I2C_RCEN = 1;				// Put module into READ mode
    while(I2C_RCEN);			// Wait until byte is received
	if (I2C_I2COV)				// Overflow?
		{
		I2C_I2COV = 0;			// Reset overflow condition
		return I2CRC_OVFL;		// return error...
		}
	while(!I2C_RBF);			// Wait for byte to be ready in receive
								// register - Excessive check, but...
	(*data) = I2C_RCV_Reg;		// return byte to caller
	//--------------------------------
	if(Flag == 0)              
		{
		// If last char, generate NACK sequence
		I2C_ACKDT = 1;
		I2C_ACKEN = 1;
		}
	else                         
		{
		// For other chars,generate ACK sequence
		I2C_ACKDT = 0;
		I2C_ACKEN = 1;
		}
	//--------------------------------
	I2CIdle();						// Ensure module is idle
									// ACK/NACK transmitted
	//------------------------------------------------------------------
	return	I2CRC_OK;				// Byte successfully transferred
	}
//==================================================================
