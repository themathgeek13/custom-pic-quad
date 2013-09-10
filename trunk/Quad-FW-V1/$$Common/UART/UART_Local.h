#include "UART\UART.h"


//==================================================================
#ifndef __UART_Local_H
#define __UART_Local_H
//==================================================================
#define _UART_Buf_Max 128
//------------------------------------------------------------------
extern uchar			_UART_IL_TX;
//==================================================================
extern uchar const 		_UART_Start;	
extern uchar const 		_UART_Stop;	
	
//==================================================================
// Transmitter-specific variables
//------------------------------------------------------------------
// _UART_TX_Ready = 1 indicates that UART is ready for TX operation
extern uint		volatile	_UART_TX_Ready;
//------------------------------------------------------------------
// UART Transmit data buffer
extern uchar 				_UART_TX_Buf[_UART_Buf_Max];
// Length of the frame in Transmit data buffer	
extern uint	 	volatile	_UART_TX_Buf_Len;
// Current position in Transmit data buffer
extern uint	 	volatile	_UART_TX_Buf_Index;
//==================================================================
#endif



