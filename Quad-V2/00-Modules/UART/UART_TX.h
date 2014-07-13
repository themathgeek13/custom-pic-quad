#include "System.h"

//=====================================================
#ifndef __UART_H
#define __UART_H
//=====================================================
// In this application we use UART1 module to transmit
// data and UART2 module to receive data. The reason
// to use 2 modules (versus transmit and receive logic
// on one module) is to allow for different Baud rates
// fro receiver and transmitter.
//----------------------------------------------------
// Transmitter: UART1
//----------------------------------------------------
void	UARTInitTX(uint IL, uint BaudRate);	
			// Parameter (1<=IL<=7) defines the
			// priority of UART1 interrupt routine.

void	UARTPostIfReady(	uchar* Data, 
							uint 	DataLen);

void	UARTPostWhenReady(	uchar * Data, 
							uint 	DataLen);
//=====================================================
#endif



