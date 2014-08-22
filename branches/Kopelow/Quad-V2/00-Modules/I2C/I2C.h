#include "System.h"

//=====================================================
#ifndef __I2C_H
#define __I2C_H
//=====================================================
#define	I2CRC_OK	0
#define I2CRC_WCOL	1
#define I2CRC_NACK	2
#define	I2CRC_TOUT	3
#define	I2CRC_OVFL	4
//--------------------
#define	I2CRC_NRDY	6		// I2C not initialized
#define	I2CRC_SBSY	8		// I2C is busy with SYNC
#define	I2CRC_ABSY	9		// I2C is busy with ASYNC
#define	I2CRC_BUSY 10		// I2C bus is busy?
//--------------------
#define I2CRC_MAX  10		// Highest error code from I2C
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
void	I2CRegisterSubscr(uint SubNum);
void	I2CDeRegisterSubscr(uint SubNum);
//============================================================

#endif



