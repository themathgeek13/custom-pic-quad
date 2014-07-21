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
#define	I2CRC_ISID 11		// Invalid Subscription ID provided
//--------------------
#define I2CRC_MAX  10		// Highest error code from I2C
//============================================================
// I2C Subscriber interface
//============================================================
// Generic pointer to I2C Interrupt routine
//------------------------------------------------------------
typedef	void (*I2CCallBack)(void);
//------------------------------------------------------------
// Generic pointer to I2C Subscriber interrupt control routine
//------------------------------------------------------------
typedef	void (*I2CSubscrIC)(uint);
//------------------------------------------------------------
// I2C Subscription data structure
//------------------------------------------------------------
typedef	struct
	{
	I2CCallBack		CallBack;
	I2CSubscrIC		SubscrIC;
	} I2CSubscr;
//============================================================
// Initialization routine
//============================================================
void	I2CInit(uint IL, uint Speed);	
		// Parameter (1<=IL<=7) defines the
		// priority of UART interrupt routine.
		//------------------------------------
		// Speed:
		// 0 - baud rate set at 100 kHz,
		// 1 - baud rate set at 400 kHz,
		// 2 - baud rate set at   1 MHz
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
uint	I2CAsyncStart(uint SubscrID);
//-----------------------------------------------------
void	I2CAsyncStop();
//-----------------------------------------------------
uint	I2CRegisterSubscr(I2CSubscr* Subscr);
// Upon successful registration return SubscrID,
// otherwise - NULL
//-----------------------------------------------------
uint	I2CDeRegisterSubscr(uint SubscrID);
//============================================================

#endif



