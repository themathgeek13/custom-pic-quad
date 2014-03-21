//==================================================================
#ifndef __UART_RX_Profile_H
#define __UART_RX_Profile_H
//==================================================================
// Maximum length of a single UART message
//------------------------------------------------------------------
#define _UART_Buf_Max 256
//------------------------------------------------------------------
// UART Module definitions - please update depending on the module
// 							 used in the current application.
//------------------------------------------------------------------
// UART Interrupt routines
//------------------------------------------------------------------
#define UErrInterrupt	_U1ErrInterrupt
#define URXInterrupt	_U1RXInterrupt
//------------------------------------------------------------------
// UART Registers
//------------------------------------------------------------------
// UART Mode register
#define	UMODE			U1MODE
// UART Status register
#define	USTA			U1STA
// UART Baud Rate Generator (BRG) register
#define	UBRG			U1BRG
// UART Read buffer register
#define URXREG			U1RXREG
//------------------------------------------------------------------
// UART Module enable flag bits
#define	UEN				U1MODEbits.UEN
// UART Module Enable Operation bit
#define UARTEN			U1MODEbits.UARTEN
// UART Receive Buffer Data Available flag (Read Only)
#define	URXDA			U1STAbits.URXDA
//------------------------------------------------------------------
// UART interrupt bits
//------------------------------------------------------------------
// UART TX interrupt control bit	
#define	UTXIE			_U1TXIE
// UART RX interrupt control bit
#define	URXIE			_U1RXIE	
// UART RX Error interrupt control bit
#define	UREIE			_U1EIE	
//--------------------------------
// UART TX interrupt flag						
#define	UTXIF			_U1TXIF	
// UART RX interrupt flag
#define	URXIF			_U1RXIF	
// UART RX Error interrupt flag
#define	UREIF			_U1EIF	
//--------------------------------	
// UART TX Interrupt priority					
#define	UTXIP			_U1TXIP
// UART RX interrupt priority
#define	URXIP			_U1RXIP
// UART RX Error interrupt priority 
#define	UREIP			_U1EIP
//------------------------------------------------------------------
// UART Error flags
//------------------------------------------------------------------
//  Parity Error Status bit (Read Only)	
#define	UPERR			U1STAbits.PERR
//  Framing Error Status bit (Read Only)	
#define	UFERR			U1STAbits.FERR
//  Receiver Overrun Error Status bit (Read Only)	
#define	UOERR			U1STAbits.OERR

//------------------------------------------------------------------
// Peripheral Module Disable (PMD) register for selected UART Module
//------------------------------------------------------------------
#define	UPMD			_U1MD


//------------------------------------------------------------------
// Please NOTE that in the 16-bit series of MCUs UART pins are not
// pre-defined, but instead are controlled through REMAPPABLE PIN
// SELECT (RPS) feature.
//------------------------------------------------------------------
// PIC24HJ128GP202/4 UART pin map (for this application)
//------------------------------------------------------------------
//	UART Receive pin 	= RP7/RB7
//	UART RTS pin	 	= RP6/RB6
//------------------------------------------------------------------
// UART Function Register for mapping input pins:
// UART1 Receive 		_U1RXR 
// UART1 Clear To Send 	_U1CTSR
// UART2 Receive 		_U2RXR
// UART2 Clear To Send 	_U2CTSR
//------------------------------------------------------------------
// UART Receive function register to map (input) pin
#define U_RPS_RX		_U1RXR
// Receiver pin number (RP-number)
#define RXpin			7
//------------------------------------------------------------------
// Peripheral ID numbers to map to (output) pins
//	U1TX 	00011 - RPn tied to UART1 Transmit
//	U1RTS 	00100 - RPn tied to UART1 Ready To Send
//	U2TX 	00101 - RPn tied to UART2 Transmit
//	U2RTS 	00110 - RPn tied to UART2 Ready To Send
//------------------------------------------------------------------
// RPS Register to map RTS (output) pin
#define RTSpin			_RP6R
// RTS function ID for Selected UART module
#define U_RPS_RTSid		4
//==================================================================
#endif


