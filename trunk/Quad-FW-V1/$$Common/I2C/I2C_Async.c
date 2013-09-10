#include "I2C\I2C_Local.h"

//============================================================
// Asynchronous I2C API (visible externally) component
//============================================================
uint	I2CAsyncStart(I2CCallBack callBack)
	{
	if (!_I2C_Init)		return I2C_NRDY;
	//=========================================================
	// Validate run-time conditions
	//---------------------------------------------------------
	uint	RC	= I2C_OK;
	int		CPU_IPL;
	//---------------------------------------------------------
	// Enter I2C (and related modules) CRITICAL SECTION
	//---------------------------------------------------------
	SET_AND_SAVE_CPU_IPL(CPU_IPL, _I2C_IL);
		{
		if (_I2C_CallBack)		RC = I2C_ABSY;
		else	if (_I2C_SBSY)	RC = I2C_SBSY;
				else	if	( _SEN || _PEN || _RCEN || _RSEN || _ACKEN || _TRSTAT )
								// Bus is busy with something...?
								RC = I2C_BUSY;
						else
							// We can subscribe for I2C Async notification(s)
							{
							_MI2C1IF		= 0; 	// Clear   I2C(1) Master interrupt flag
							//---------------------------------------------------------
							// Set Flag indicating Asynchronous operation is in progress
							//---------------------------------------------------------
							_I2C_CallBack	= callBack;
							//////////////////////////////////////////////////////////
							//--------------------------------------------------------
							_MI2C1IE		= 1;	// Enable I2C(1) Master interrupt	
							//--------------------------------------------------------
							_INT1IE	= 0;	// Disable INT1 interrupt
							_INT2IE	= 0;	// Disable INT2 interrupt
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
	I2CSTAT			= 0;	// clear STATUS bits
	_PEN 			= 1;	// Initiate Stop on SDA and SCL pins
	//--------------------------------------------------------
	// NOTE: callback reference will be cleared in Interrupt
	//		 routine after "STOP" processed
	//--------------------------------------------------------
	return;
	}
//============================================================

//============================================================
void	I2CRegisterInt(uint IntNum, uint IntEnFlag)
	{
	//--------------------------------------------------------
	switch (IntNum)
		{
		case 1:
			_I2C_Int1 	= IntEnFlag;
			_INT1IE		= _I2C_Int1;
			break;
		case 2:
			_I2C_Int2 	= IntEnFlag;
			_INT2IE		= _I2C_Int2;
			break;
		default:
			;
		}
	//--------------------------------------------------------
	return;
	}
//============================================================





