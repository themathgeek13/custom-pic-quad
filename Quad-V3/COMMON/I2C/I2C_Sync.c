#include "I2C\I2C_Local.h"

//==================================================================
// Internal (local) components of Synchronous I2C interface
//==================================================================
void I2CIdle(_I2C_CB* pCB)
	{
	I2C_CONBITS*	pCON	= I2CpCON(pCB);
	I2C_STATBITS*	pSTAT	= I2CpSTAT(pCB);
    /* Wait until I2C Bus is Inactive */
	//----------------------------------
    while
		(
		pCON->SEN || pCON->PEN || pCON->RCEN || pCON->RSEN || pCON->ACKEN  || pSTAT->TRSTAT
		);
	return;	
	}
//==================================================================
void	I2CStart(_I2C_CB* pCB)
	{
	I2CIdle(pCB);				// Wait for bus to be Idle
	//-----------------------------------------------------
	I2CpCON(pCB)->SEN = 1;		// Initiate Start on SDA and SCL pins
	}
//==================================================================
void	I2CReStart(_I2C_CB* pCB)
	{
	I2CIdle(pCB);				// Wait for bus to be Idle
	//-----------------------------------------------------
	I2CpCON(pCB)->RSEN = 1;		// Initiate Repeated Start on SDA
								// and SCL pins
	}
//==================================================================
void	I2CStop(_I2C_CB* pCB)
	{
	I2CIdle(pCB);				// Wait for bus to be Idle
	//-----------------------------------------------------
	I2CpCON(pCB)->PEN = 1;		// Initiate Stop on SDA and SCL pins
	}
//==================================================================
uint	I2CMasterWriteByte(_I2C_CB* pCB, byte data)
	{
	I2CIdle(pCB);				// Wait for bus to be Idle
	//-----------------------------------------------------
	I2C_STATBITS*	pSTAT	= I2CpSTAT(pCB);
	//-----------------------------------------------------
	while(pSTAT->TBF);			// Wait till transmit register
								// is empty (available)
	//-----------------------------------------------------
	*(pCB->pI2C_STAT)	= 0;	// Reset Status byte
	//-----------------------------------------------------
	*(pCB->pI2C_TRN) = data;	// Put data byte into transmit register
	if(pSTAT->IWCOL)    		// Check for write collision
        return I2CRC_WCOL;		// Return error...
	while(pSTAT->TRSTAT);		// Wait until write cycle is complete
	//-----------------------------------------------------
	I2CIdle(pCB);				// Ensure module is idle
	//-----------------------------------------------------
	if ( pSTAT->ACKSTAT ) 		// Test for ACK condition received
		return I2CRC_NACK;		// NACK...
	//------------------------------------------------------------------
	return	I2CRC_OK;			// Byte successfully transferred
	}
//==================================================================
uint	I2CMasterReadByte(_I2C_CB* pCB, byte* data, uint Flag)
	{
	I2CIdle(pCB);				// Wait for bus to be Idle
	//-----------------------------------------------------
	I2C_CONBITS*	pCON	= I2CpCON(pCB);
	I2C_STATBITS*	pSTAT	= I2CpSTAT(pCB);
	//-----------------------------------------------------
	*(pCB->pI2C_STAT)	= 0;	// Reset Status byte
	//-----------------------------------------------------
    pCON->RCEN = 1;				// Put module into READ mode
    while(pCON->RCEN);			// Wait until byte is received
	if (pSTAT->I2COV)			// Overflow?
		{
		pSTAT->I2COV = 0;		// Reset overflow condition
		return I2CRC_OVFL;		// return error...
		}
	if (pSTAT->BCL)				// Bus collision?
		{
		pSTAT->BCL = 0;			// Reset bus collision condition
		return I2CRC_BCOL;		// return error...
		}
	while(!pSTAT->RBF);			// Wait for byte to be ready in receive
								// register - Excessive check, but...
	(*data) = *(pCB->pI2C_RCV);	// return byte to caller
	//--------------------------------
	// Set Acknowledge (ACK or NACK) code
	//--------------------------------
	if(Flag == 0)              
		// If last char, generate NACK sequence
		pCON->ACKDT = 1;
	else                         
		// For other chars,generate ACK sequence
		pCON->ACKDT = 0;
	//--------------------------------
	pCON->ACKEN = 1;			// Innitiate Acknowledge Sequence
	//--------------------------------
	I2CIdle(pCB);				// Ensure module is idle
								// ACK/NACK transmitted
	//------------------------------------------------------------------
	return	I2CRC_OK;			// Byte successfully transferred
	}
//==================================================================
