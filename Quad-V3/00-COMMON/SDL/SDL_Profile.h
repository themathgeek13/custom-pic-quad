#ifndef SDL_PROFILE_H
#define	SDL_PROFILE_H

//==================================================================
// Maximum length of a single UART message
//------------------------------------------------------------------
#define _SDL_Buf_Max 256
//------------------------------------------------------------------
// UART Module definitions - please update depending on the module
// 							 used in the current application.
//------------------------------------------------------------------
// UART Interrupt routines
//------------------------------------------------------------------
#define SDLInterrupt	_U1TXInterrupt
//------------------------------------------------------------------
// UART Registers
//------------------------------------------------------------------
// UART Mode register
#define	UMODE			U1MODE
// UART Status register
#define	USTA			U1STA
// UART Baud Rate Generator (BRG) register
#define	UBRG			U1BRG
// UART Write buffer register
#define UTXREG			U1TXREG
//------------------------------------------------------------------
// UART Mode bits/flags
//------------------------------------------------------------------
// UART Module Enable Operation bit
#define UARTEN			U1MODEbits.UARTEN
// UART Module enable flag bits
#define	UEN				U1MODEbits.UEN
// UART Module High Baud Rate Enable bit
#define	UBRGH			U1MODEbits.BRGH
//------------------------------------------------------------------
// UART Status bits/flags
//------------------------------------------------------------------
// UART Transmit Enable flag
#define UTXEN			U1STAbits.UTXEN
// UART Transmit Buffer Full Status flag (Read Only)
#define	UTXBF			U1STAbits.UTXBF
// UART Transmission Interrupt Mode Selection bits
#define UTXISEL0		U1STAbits.UTXISEL0
#define UTXISEL1		U1STAbits.UTXISEL1

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

//************************************************************
// Helper function _SDLInitPinMap(void) implements mapping
// of UART pins using Peripheral Pin Select
//------------------------------------------------------------
// NOTE: this function defines physical configuration -
//		 together with the definitions above this function
//		 need to be updated for adapting this code to a
//		 specific board.
//************************************************************
static inline void _SDLInitPinMap(void)
	{
	//=========================================================
	// PIC24EP512Pxxx UARTx (TX) pin map for this application
	//--------------------------------------------------------
	//	UxTX 	= RP99/RF3
	//	UxCTS 	= RPI41/RB9
	//--------------------------------------------------------
	// NOTE: RB9 is multiplexed with AN9 of ADC;
	// This pin should be put into digital mode prior to
	// be used by UART. However  "Init()" function puts all
	// analog pins into digital mode on the start.
	// NOTE: Please check ADCInit for possible conflicts!
	//=========================================================

	//=========================================================
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init()" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// Configure Transmitter's pins...
	//---------------------------------------------------------
	_TRISF3	= 0;	// Configure RF3 port for OUTPUT
	_RP99R 	= 1; 	// (OUT) pin RP99/RF3 mapped to U1TX
	//----------------------
	_TRISB9 = 1;	// Configure RB9 port for INPUT
	_U1CTSR = 41; 	// (IN)  U1CTS mapped to pin RPI41/RB9
	//---------------------------------------------------------
	// Configure Receiver's pins...
	//---------------------------------------------------------	
	// As we use UARTx ONLY to send data, to "save" MCU pins
	// we may map U1RX to Vss and U1RTS leave unmapped.
	//---------------------------------------------------------
	_U1RXR	= 0;	// U1RX tied to Vss
	//---------------------------------------------------------
	return;
	}


#endif	/* UART_TX_PROFILE_H */


