#include "I2C/I2C_Local.h"
#include "TMR/TMR.h"

//************************************************************
// Synchronous READ - I2C API (visible externally) component
//************************************************************
uint	I2CSyncRead(	byte 	DevAddr, 
						byte	Register,
						byte* 	Buffer,
						uint  	BufLen )
	{
	if (!_I2C_Init)		return I2CRC_NRDY;
	//=========================================================
	// Validate run-time conditions
	//---------------------------------------------------------
	uint	RC;
	BYTE	CPU_IPL;
	uint	RetryCount	= 0;

	//---------------------------------------------------------
	// Enter I2C (and related modules) CRITICAL SECTION
	//---------------------------------------------------------
Retry:
	RC	= I2CRC_OK;
	//------------------------------------
	SET_AND_SAVE_CPU_IPL(CPU_IPL, _I2C_IL);
		{
		if (_I2C_CallBack)		RC = I2CRC_ABSY;
		else	if (_I2C_SBSY)	RC = I2CRC_SBSY;
				else	if	(	I2C_SEN
							 || I2C_PEN
							 || I2C_RCEN
							 || I2C_RSEN
							 || I2C_ACKEN
							 || I2C_TRSTAT )
								// Bus is busy with something...?
								RC = I2CRC_BUSY;
						else
								//---------------------------------------------------------
								// Set Flag indicating Synchronous operation is in progress
								//---------------------------------------------------------
								_I2C_SBSY	= 1;	// Should be cleared at exit
		}  
	//---------------------------------------------------------
	// Leave I2C CRITICAL SECTION
	//---------------------------------------------------------
  	RESTORE_CPU_IPL(CPU_IPL);
	//=========================================================
	switch (RC)	
		{
		case	I2CRC_OK:
			break;		// Run-time conditions are OK
		//-------------------------------------------
		case	I2CRC_ABSY:
		case	I2CRC_SBSY:
		case	I2CRC_BUSY:
			// Situation could be helped by delay/retry
			if (RetryCount < I2C_BUSYRetry)
				{
				TMRDelayTicks(1);	// Small delay ~150 usec
				RetryCount++;
				goto Retry;					// Attempt retry
				}
			else;		// Fall through to "default"
		//-------------------------------------------
		default:
			return RC;	// Run-time conditions are not met
		}
	//=========================================================

	//---------------------------------------------------------
	// Event sequence to accomplish simple READ from the target
	// slave device in the MASTER mode:
	//	1. Assert a Start condition on SDAx and SCLx.
	//	2. Send the I2C device address byte to the slave with a
	//	   read indication ("1" in the LSB of address)
	//	3. Wait for and verify an Acknowledge from the slave.
	//	4. Assert receiving state (RCEN = 1).
	//	5. Receive byte and send ACK to the slave.
	//	6. Repeat steps 4 and 5 for every byte in a message, 
	//	   except the last - after receiving last byte send NACK.
	//	7. Generate a Stop condition on SDAx and SCLx.
	//---------------------------------------------------------
	// Prepare READ and WRITE forms of device address
	byte	i2cAddrW	= DevAddr & 0xFE;	// Set WRITE cond.
	byte	i2cAddrR	= DevAddr | 0x01;	// Set READ cond.
	//---------------------------------------------------------
	RC			= I2CRC_OK;
	//---------------------------------------------------------
	I2CStart();		// Signal START on SDA and SCL pins
	//---------------------------------------------------------
	// Send Device WRITE address
	//---------------------------------------------------------
	RC = I2CMasterWriteByte(i2cAddrW);
	if (RC != I2CRC_OK)	goto Finally;
	//---------------------------------------------------------
	// Send Register address (as data))
	//---------------------------------------------------------
	RC = I2CMasterWriteByte(Register);
	if (RC != I2CRC_OK)	goto Finally;
	//---------------------------------------------------------
	I2CReStart();	// Signal Repeated-START on SDA and SCL pins
	//---------------------------------------------------------
	// Send Device READ address
	//---------------------------------------------------------
	RC = I2CMasterWriteByte(i2cAddrR);
	if (RC != I2CRC_OK)	goto Finally;
	//---------------------------------------------------------
	// Receive data
	//---------------------------------------------------------
	_I2COV = 0;			// Clear receive OVERFLOW bit, if any
	//---------------------------------------------------------
	uint	BufPos;
	uint	BufCnt	= BufLen;
	//---------------------------------------------------------
	for (BufPos = 0; BufPos < BufLen; BufPos++)
		{
		BufCnt--;	// Used as a FLAG (BufCnt=0) to indicate last byte
		//---------------------------------------------------------
		RC = I2CMasterReadByte(Buffer, BufCnt);
		if (RC != I2CRC_OK)
			break;			// Error...
		Buffer++;
		}
	//---------------------------------------------------------
Finally:
	I2CStop();			// Signal STOP on SDA and SCL pins
	//---------------------------------------------------------
	_I2C_SBSY	= 0;	// Clear SYNC flag
	return RC;			// Return last Error Code...
	}
//************************************************************
