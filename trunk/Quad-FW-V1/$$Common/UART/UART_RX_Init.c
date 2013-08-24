#include "UART\UART_Local.h"

//************************************************************
void	UARTInitRX(int IL, int BaudRate)
	{
	//--------------------------------------------------------
	// PIC24HJ128GP204 UART pin map (for this application)
	//--------------------------------------------------------
	//	U2Rx 	= RP3/RB3
	//	U2RTS 	= RP2/RB2
	//--------------------------------------------------------
	// NOTE: RB2 and RB3 are multiplexed with AN4 and AN5 of ADC;
	// These pins should be put into digital mode prior to
	// be used by UART (please check ADCInit for possible con-
	// flicts!)
	_PCFG4	= 1;	// Release pin AN4 (RB2) for Digital I/O
	_PCFG5	= 1;	// Release pin AN5 (RB3) for Digital I/O
	//=========================================================
	
		
	//---------------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_UART_IL_RX	= IL;
	//---------------------------------------------------------
	// This initialization routine accepts BaudRate in multiples
	// of 2400 bps; Thus:
	// BaudRate =  1	=>   2400 bps
	// BaudRate =  2	=>   4800 bps
	// ...
	// BaudRate = 48	=> 115200 bps
	//------------------------------------------------------------
	// BaudRate =  0	=> Special case: Maximum Baud rate
	//------------------------------------------------------------
	// Acceptable values are: 1, 2, 3, 4, 6, 8, 16, 24, 48, and 0
	//---------------------------------------------------------
	// Baud Rate is calculated under the assumption that MCU
	// is operating at 40 MHz (Fcy = 40,000,000)
	//=========================================================
	//---------------------------------------------------------
	U2MODE			= 0;		// Disable UART2 for configuration
	// Default configuration sets UART into the:
	// "8-N-1" mode, IrDA disabled, UxCTS and UxRTS/BCLK pins 
	// controlled by port latches, Wake-up disabled, loopback
	// disabled, standard Baud rate generation.
	//---------------------------------------------------------
	// Please NOTE that the init program disables all PERIPHERAL
	// MODULES using PMDx registers. To continue configuring and
	// later enabling UART1 module we need to enable module in
	// PMDx
	//---------------------------------------------------------
	_U2MD	= 0;		// Enable UART2 module
	//---------------------------------------------------------
	
	//---------------------------------------------------------
	// Please NOTE that in the 16-bit series of MCUs UART pins
	// are not pre-defined, but instead are controlled through
	// REMAPPABLE PIN SELECT feature.
	//---------------------------------------------------------
	// Writing to RP control registers is protected by IOLOCK
	// bit in the OSCCON register. Please note that as part of
	// oscillator switch in the "Init" routine this bit was
	// cleared, which enables writing to these register at any
	// time.
	//---------------------------------------------------------
	// NOTE: Pins need to be mapped PRIOR to setting UxMODE.UEN
	//---------------------------------------------------------
	// Configure Transmitter's pins...
	//---------------------------------------------------------	
	// As we use UART1 ONLY to receive data, to "save" MCU pins 
	// we may map U2CTS to Vss and U2TX leave unmapped.
	//---------------------------------------------------------
	_U2CTSR 	= 0b11111; 	// (IN)  U2CTS tied to Vss
	//---------------------------------------------------------
	// Configure Receiver's pins...
	//---------------------------------------------------------
	_U2RXR 	= 3; 	// (IN)  U2Rx mapped to pin RP3/RB3
	//----------------------
	_RP2R 	= 5; 	// (OUT) U2RTS mapped to pin RP2/RB2
	//-------------------------------------------------------------------
	
	
	
	//---------------------------------------------------------
	/*	UXMODE: UARTX Mode Register
	-----------------------------------------------------------
	bit 15 UARTEN: UART Enable bit
			1 = UART is enabled. UART pins are controlled by 
				UART as defined by UEN<1:0> and UTXEN control bits.
			0 = UART is disabled. UART pins are controlled by
				corresponding PORT, LAT, and TRIS bits.
	bit 13 USIDL: Stop in Idle Mode bit
			1 = Discontinue operation when device enters Idle mode
			0 = Continue operation in Idle mode
	bit 12 IREN: IrDA Encoder and Decoder Enable bit
			1 = IrDA encoder and decoder enabled
			0 = IrDA encoder and decoder disabled
	bit 9-8 UEN<1:0>: UARTx Enable bits
			11 = UxTX, UxRX and BCLK pins are enabled and used; 
				 UxCTS pin controlled by port latches
			10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
			01 = UxTX, UxRX and UxRTS pins are enabled and used; 
				 UxCTS pin controlled by port latches
			00 = UxTX and UxRX pins are enabled and used; 
				 UxCTS and UxRTS/BCLK pins controlled by port latches
	bit 7 WAKE: Enable Wake-up on Start bit Detect During Sleep Mode bit
			1 = Wake-up enabled
			0 = Wake-up disabled
	bit 6 LPBACK: UART Loopback Mode Select bit
			1 = Enable Loopback mode
			0 = Loopback mode is disabled
	bit 5 ABAUD: Auto Baud Enable bit
			1 = Input to Capture module from UxRX pin
			0 = Input to Capture module from ICx pin
	bit 4 URXINV: Receive Polarity Inversion bit
			1 = UxRX Idle state is ‘0’
			0 = UxRX Idle state is ‘1’
	bit 3 BRGH: High Baud Rate Enable bit
			1 = BRG generates 4 clocks per bit period (4x baud clock, 
				High-Speed mode)
			0 = BRG generates 16 clocks per bit period (16x baud clock, 
				Standard mode)
	bit 2-1 PDSEL<1:0>: Parity and Data Selection bits
			11 = 9-bit data, no parity
			10 = 8-bit data, odd parity
			01 = 8-bit data, even parity
			00 = 8-bit data, no parity
	bit 0 STSEL: Stop Selection bit
			1 = 2 Stop bits
			0 = 1 Stop bit	
	*/	
	U2MODEbits.UEN	= 0b10;		// UxTX, UxRX, UxCTS and UxRTS 
								// pins are enabled and used -
								// the HW flow control mode	
	//---------------------------------------------------------


	//---------------------------------------------------------
	/*	UXSTA: UARTX Status and Control Register
	-----------------------------------------------------------
	bit 15, 13 UTXISEL: Transmission Interrupt Mode Selection bit
			11 = Reserved
			10 = Interrupt when a character is transferred to the 
				 Transmit Shift register and as result, the transmit 
				 buffer becomes empty
			01 = Interrupt when the last character is shifted out of
				 the Transmit Shift Register; all transmit operations
				 are completed
			00 = Interrupt when a character is transferred to the 
				 Transmit Shift register (this implies that there 
				 is at least one character open in the transmit buffer)
	bit 11 UTXBRK: Transmit Break bit
		1 = UxTX pin is driven low, regardless of transmitter state
		0 = UxTX pin operates normally
	bit 10 UTXEN: Transmit Enable bit
		1 = UART transmitter enabled, UxTX pin controlled by UART 
			(if UARTEN = 1) - NOTE: set only after UARTEN = 1
		0 = UART transmitter disabled, any pending transmission is
			aborted and buffer is reset. UxTX pin controlled by PORT.
	bit 9 UTXBF: Transmit Buffer Full Status bit (Read Only)
		1 = Transmit buffer is full
		0 = Transmit buffer is not full, 
			at least one more data word can be written
	bit 8 TRMT: Transmit Shift Register is Empty bit (Read Only)
		1 = Transmit shift register is empty and transmit buffer is 
			empty (the last transmission has completed)
		0 = Transmit shift register is not empty, a transmission is 
			in progress or queued in the transmit buffer
	bit 7-6 URXISEL<1:0>: Receive Interrupt Mode Selection bit
		11 =Interrupt flag bit is set when Receive Buffer is full 
			(i.e., has 4 data characters)
		10 =Interrupt flag bit is set when Receive Buffer is 3/4 full 
			(i.e., has 3 data characters)
		0x =Interrupt flag bit is set when a character is received
	bit 5 ADDEN: Address Character Detect (bit 8 of received data = 1)
		1 = Address Detect mode enabled. If 9-bit mode is not selected, 
			this control bit has no effect.
		0 = Address Detect mode disabled
	bit 4 RIDLE: Receiver Idle bit (Read Only)
		1 = Receiver is Idle
		0 = Data is being received
	bit 3 PERR: Parity Error Status bit (Read Only)
		1 = Parity error has been detected for the current character
		0 = Parity error has not been detected
	bit 2 FERR: Framing Error Status bit (Read Only)
		1 = Framing Error has been detected for the current character
		0 = Framing Error has not been detected
	bit 1 OERR: Receive Buffer Overrun Error Status bit (Read/Clear Only)
		1 = Receive buffer has overflowed
		0 = Receive buffer has not overflowed
	bit 0 URXDA: Receive Buffer Data Available bit (Read Only)
		1 = Receive buffer has data, at least one more character can be read
		0 = Receive buffer is empty
	*/
	//---------------------------------------------------------
	U2STA				= 0;	// Set all to defaults 
	// URXISEL<1:0>: Receive Interrupt Mode Selection bit
	//	0x =Interrupt flag bit is set when a character is received
	// RX interrupt on every byte received!
	//---------------------------------------------------------
	/*	UXBRG: UARTX Baud Rate Register
	-----------------------------------------------------------
	bit 15-0 BRG<15:0>: Baud Rate Divisor bits
	*/
	//---------------------------------------------------------
	switch (BaudRate)
		{
		//--------------------------------------------------------------
		// Special case: we set UART to high speed for PIC24-to-PIC24
		// communication. The U1BRG values correspond to following speeds:
		//	0 - 2,500,000
		//	1 - 1,250,000
		//  3 -   625,000
		//	4 -	  500,000
		//	9 -   250,000
		//---------------------------------------------------------------
		case  0:	U2BRG =   0;	break;		// please check table above
		//---------------------------------------------------------------
		case 48:	U2BRG =  21;	break;		// 115200 (113636, -1.36%)
		case 24:	U2BRG =  42;	break;		//  57600 ( 58140, 0.94%)
		case 16:	U2BRG =  64;	break;		//  38400 ( 38462, 0.16%)
		case  8:	U2BRG = 129;	break;		//  19200 ( 19231, 0.16%)
		case  6:	U2BRG = 173;	break;		//  14400 ( 14368, -0.22%)
		case  4:	U2BRG = 259;	break;		//   9600 (  9615, 0.16%)
		case  3:	U2BRG = 346;	break;		//   7200 (  7205, 0.07%)
		case  2:	U2BRG = 520;	break;		//   4800 (  4798, -0.04%)
		//-------------------------------
		case  1:
		default:	U2BRG = 1041;	break;		//   2400 (  2399, -0.04%)
		}
	//---------------------------------------------------------


	//---------------------------------------------------------
	_U2TXIE		= 0;		// Disable UART TX interrupt	
	_U2RXIE		= 0;		// Disable UART RX interrupt
	_U2EIE		= 0;		// Disable UART RX Error interrupt	
	//--------------------------------						
	_U2TXIF		= 0; 		// Clear UART TX interrupt flag
	_U2RXIF		= 0; 		// Clear UART RX interrupt flag
	_U2EIF		= 0;		// Clear UART RX Error interrupt flag
	//--------------------------------						
	_U2TXIP		= 0; 		// Setting U2TXIP = 0 effectively
									// disables TX interrupt.
	_U2RXIP	= _UART_IL_RX; 	// Set UART RX interrupt priority
	_U2EIP	= _UART_IL_RX; 	// Set UART RX Error interrupt priority 
									
	//---------------------------------------------------------
	// NOTE: Transmit Enable bit (UTXEN) is left at 0
	//---------------------------------------------------------

	//---------------------------------------------------------
	// UART module will be enabled in UARTRXStartAsyncRead routine
	//---------------------------------------------------------
	return;
	}

//************************************************************

