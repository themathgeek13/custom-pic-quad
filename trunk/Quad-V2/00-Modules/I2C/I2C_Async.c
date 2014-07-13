#include "I2C\I2C_Local.h"

//============================================================
// Asynchronous I2C API (visible externally) component
//============================================================
uint	I2CAsyncStart(I2CCallBack callBack)
	{
	//=========================================================
	// Validate run-time conditions
	//---------------------------------------------------------
	if (!_I2C_Init)		return I2CRC_NRDY;
	//=========================================================
	uint	RC		= I2CRC_OK;
	BYTE	CPU_IPL;
	//---------------------------------------------------------
	// Enter I2C (and related modules) CRITICAL SECTION
	//---------------------------------------------------------
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
							// We can subscribe for I2C Async notification(s)
							{
							I2C_IF		= 0; 	// Clear  I2C Master interrupt flag
							//---------------------------------------------------------
							// Set Flag indicating Asynchronous operation is in progress
							//---------------------------------------------------------
							_I2C_CallBack	= callBack;
							//////////////////////////////////////////////////////////
							//--------------------------------------------------------
							I2C_IE		= 1;	// Enable I2C Master interrupt
							//--------------------------------------------------------
							// Disable subscribers' interrupts
							I2C_Sub1IE	= 0;
							I2C_Sub2IE	= 0;
							I2C_Sub3IE	= 0;
							I2C_Sub4IE	= 0;
							}
		}  
	//---------------------------------------------------------
	// Leave I2C CRITICAL SECTION
	//---------------------------------------------------------
  	RESTORE_CPU_IPL(CPU_IPL);
	//=========================================================
	return RC;		
	}
//============================================================
void	I2CAsyncStop()
	{
	//--------------------------------------------------------
	// NOTE: Should be called only from I2C interrupt routine
	//       or its extension procedure
	//--------------------------------------------------------
	I2C_STAT		= 0;	// clear STATUS bits
	I2C_PEN 		= 1;	// Initiate Stop on SDA and SCL pins
	//--------------------------------------------------------
	// NOTE: callback reference will be cleared in Interrupt
	//		 routine after "STOP" processed
	//--------------------------------------------------------
	return;
	}
//============================================================

//============================================================
void	I2CRegisterSubscr(uint SubNum)
	{
	//--------------------------------------------------------
	switch (SubNum)
		{
		case 1:
			_I2C_Sub1 = I2C_Sub1IE = 1;
			break;
		case 2:
			_I2C_Sub2 = I2C_Sub2IE = 1;
			break;
		case 3:
			_I2C_Sub3 = I2C_Sub3IE = 1;
			break;
		case 4:
			_I2C_Sub4 = I2C_Sub4IE = 1;
			break;
		default:
			;
		}
	//--------------------------------------------------------
	return;
	}
//============================================================

//============================================================
void	I2CDeRegisterSubscr(uint SubNum)
	{
	//--------------------------------------------------------
	switch (SubNum)
		{
		case 1:
			_I2C_Sub1 = I2C_Sub1IE = 0;
			break;
		case 2:
			_I2C_Sub2 = I2C_Sub2IE = 0;
			break;
		case 3:
			_I2C_Sub3 = I2C_Sub3IE = 0;
			break;
		case 4:
			_I2C_Sub4 = I2C_Sub4IE = 0;
			break;
		default:
			;
		}
	//--------------------------------------------------------
	return;
	}
//============================================================





