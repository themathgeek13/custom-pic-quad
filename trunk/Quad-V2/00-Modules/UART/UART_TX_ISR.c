#include "UART\UART_TX_Local.h"


//************************************************************
void __attribute__((__interrupt__,__no_auto_psv__)) UTXInterrupt(void)
	{
	if (_UART_TX_Buf_Len > 0)
		{
		while ( (_UART_TX_Buf_Len > 0) && (0 == UTXBF) )
			{
			// We still have data to transfer...
			UTXREG = _UART_TX_Buf[_UART_TX_Buf_Index];
			//----------------------------------
			_UART_TX_Buf_Index++;	// Adjust index to next character
			_UART_TX_Buf_Len--;	// Adjust counter of bytes in buffer
			}
		}
	else
		{
		//----------------------------------
		// As we generate UART TX interrupts only when buffer
		// is empty, when we enter interrupt routine we have 4 
		// slots in the buffer...
		// Send "STOP" delimiter (double _UART_Stop)
		//----------------------------------
		UTXREG = _UART_Stop;
		asm ("nop"); // We need at least one cycle delay between writes to U1TXREG ...
		UTXREG = _UART_Stop;
		//----------------------------------
		// Nothing more to transmit...
		UTXIE				= 0;	// Disable UART TX interrupt
		_UART_TX_Ready		= 1;	// Indicate readiness for next
									// message.
		}
	//-------------------------------------------------
	UTXIF		= 0; 		// Clear UART TX interrupt flag
	//-------------------------------------------------
	return;
	}
//************************************************************







