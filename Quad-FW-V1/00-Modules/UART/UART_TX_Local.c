#include "UART\UART_TX_Local.h"

//==================================================================
uchar				_UART_IL_TX	= 4; 	// UART Transmitter
										// default interrupt level
//==================================================================
uchar	const 		_UART_Start = 0x55; 
uchar	const 		_UART_Stop  = 0xAA; 

// Transmitter-specific variables
//------------------------------------------------------------------
// _UART_TX_Ready = 1 indicates that UART is ready for TX operation
uint 	volatile	_UART_TX_Ready	= 1; // Obviously, READY
//------------------------------------------------------------------
// UART Transmit data buffer
uchar 				_UART_TX_Buf[_UART_Buf_Max];
// Length of the frame in Transmit data buffer	
uint	volatile	_UART_TX_Buf_Len	= 0;	// Empty...
// Current position in Transmit data buffer
uint	volatile	_UART_TX_Buf_Index	= 0;
//==================================================================




