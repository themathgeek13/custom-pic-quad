#include <string.h>

#include "UART\UART_Local.h"

//************************************************************
void	UARTPostWhenReady(	uchar * Data, 
							uint 	DataLen)
	{
	while (0 == _UART_TX_Ready); // Wait until READY
	//------------------------
	UARTPostIfReady(Data, DataLen);	
	}
//************************************************************
void	UARTPostIfReady(	uchar * Data, 
							uint 	DataLen)
	{
	//========================================================
	if (0 == _UART_TX_Ready)
		return;						// UART is busy...
	//--------------------------------------------------------
	_UART_TX_Ready 	= 0;			// Acquire UART...
	//========================================================
	if (DataLen > _UART_Buf_Max)
		DataLen	= _UART_Buf_Max;	// Limit message to buffer size...
	//----------------------------------
	_UART_TX_Buf_Len	= DataLen;		
	_UART_TX_Buf_Index	= 0;
	//----------------------------------
	if (DataLen);
		memcpy(_UART_TX_Buf, Data, DataLen); 
	//----------------------------------
	// As we generate UART TX interrupts only when buffer
	// is empty and we set TX READY bit right after pushing
	// termination word (2 bytes) in responce to interrupt,
	// whenever UART is ready we have at least 2 slots in
	// the buffer...
	// Send "START" delimiter (double _UART_Start)
	//----------------------------------
	U1TXREG = _UART_Start;
	asm ("nop"); 			// We need at least one cycle 
							// delay between writes to U1TXREG ...
	U1TXREG = _UART_Start;
	//----------------------------------
	IEC0bits.U1TXIE	= 0b1;			// Enable UART TX interrupt
	//----------------------------------
	return;
	}
//************************************************************




