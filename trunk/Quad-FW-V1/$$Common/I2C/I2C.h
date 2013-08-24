#include "System.h"

//=====================================================
#ifndef __I2C_H
#define __I2C_H
//=====================================================
#define	I2C_OK		0
#define I2C_WCOL	1
#define I2C_NACK	2
#define	I2C_TOUT	3
#define	I2C_OVFL	4
//--------------------
#define	I2C_NRDY	6		// I2C not initialized
#define	I2C_SBSY	8		// I2C is busy with SYNC
#define	I2C_ABSY	9		// I2C is busy with ASYNC
#define	I2C_BUSY   10		// I2C bus is busy?
//--------------------
#define I2C_RC_MAX 10		// Highest error code from I2C
//---------------------------------
#define	I2C_NACKRetry 50	// Retry count for NACK code
//-----------------------------------------------------
// Generic pointer to I2C Interrupt routine
//-----------------------------------------------------
typedef	void (*I2CCallBack)(void);
//============================================================
// Initialization routine
//============================================================
void	I2CInit(uint IL, uint Speed);	
		// Parameter (1<=IL<=7) defines the
		// priority of UART interrupt routine.
		//------------------------------------
		// Speed=0: baud rate set at 100 kHz,
		// any other value: 400 kHz
//============================================================
// General support function for integration with other modules
//============================================================
byte	I2CGetIL();
//============================================================
// Synchronous I2C API (visible externally) component
//============================================================
uint	I2CSyncRead(	byte	DevAddr, 
						byte	Register,
						byte*	Buffer,
						uint  	BufLen	);
//-----------------------------------------------------
uint	I2CSyncWrite(	byte 	DevAddr, 
						byte	Register,
						byte* 	Buffer,
						uint  	BuffLen );

//============================================================
// Asynchronous I2C API (visible externally) component
//============================================================
uint	I2CAsyncStart(I2CCallBack callBack);
//-----------------------------------------------------
void	I2CAsyncStop();
//-----------------------------------------------------
void	I2CRegisterInt(uint IntNum, uint IntEnFlag);
//============================================================

#endif



