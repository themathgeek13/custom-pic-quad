#include "SDL\SDL_Local.h"

//************************************************************
void	SDLInit(uint IL, SDL_BAUD_RATE BaudRate)
	{
	//---------------------------------------------------------
	// NOTE: For transmit-only UART modules (like the SDL) it
	//		 is beneficial to use High Baud Rate mode (4 clocks
	//		 per bit) to approximate serial communication speed
	//		 with greater precision.
	//---------------------------------------------------------

	//---------------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_SDL_IL_TX	= IL;
	//---------------------------------------------------------
	UMODE			= 0;		// Disable UARTx for configuration
	// Default configuration sets UART into the:
	// "8-N-1" mode, IrDA disabled, UxCTS and UxRTS/BCLK pins 
	// controlled by port latches, Wake-up disabled, loopback
	// disabled, standard Baud rate generation.
	//---------------------------------------------------------
	// Please NOTE that the init program disables all PERIPHERAL
	// MODULES using PMDx registers. To continue configuring and
	// later enabling UARTx module we need to enable module in
	// PMDx
	//---------------------------------------------------------
	UPMD	= 0;		// Enable UARTx module
	//---------------------------------------------------------
	
	//---------------------------------------------------------
	// Map MCU pins used by UART module through
	// REMAPPABLE PIN SELECT feature.
	//---------------------------------------------------------
	// NOTE: Pins need to be mapped PRIOR to setting UxMODE.UEN
	//---------------------------------------------------------
	 _SDLInitPinMap();
	
	
	
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
	bit 11 RTSMD: Mode Selection for UxRTS Pin bit
			1 = UxRTS pin in Simplex mode
			0 = UxRTS pin in Flow Control mode
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
	UBRGH	= 0b1;	// Enable UART High Baud Rate (4 clocks per bit)
	UEN		= 0b10;	// UxTX, UxRX, UxCTS and UxRTS pins are
					// enabled and used - the HW flow control mode	
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
	USTA				= 0;	// Set all to defaults 
	// UTXISEL = 10	Interrupt when a character is transferred to the 
	//				Transmit Shift register and as result, the transmit 
	//				buffer becomes empty
	UTXISEL1	= 0b1;	// Generate interrupt when 
	UTXISEL0	= 0b0;	// buffer is EMPTY

	//---------------------------------------------------------
	/*	UXBRG: UARTX Baud Rate Register
	-----------------------------------------------------------
	bit 15-0 BRG<15:0>: Baud Rate Divisor bits
	*/
	//---------------------------------------------------------
	switch (BaudRate)
		{
		//--------------------------------------------------------------
		// PIC-to-PIC rates
		//--------------------------------------------------------------
		case BAUD_1M:		UBRG =   15;	break;
		case BAUD_500K:		UBRG =   31;	break;
		case BAUD_400K:		UBRG =   39;	break;
		case BAUD_250K:		UBRG =   63;	break;
		case BAUD_200K:		UBRG =   79;	break;
		//--------------------------------------------------------------
		// Standard rates
		//--------------------------------------------------------------
		case BAUD_115200:	UBRG =  138;	break;
		case BAUD_57600:	UBRG =  277;	break;
		case BAUD_38400:	UBRG =  416;	break;
		case BAUD_19200:	UBRG =  832;	break;
		case BAUD_14400:	UBRG = 1110;	break;
		case BAUD_9600:		UBRG = 1666;	break;
		case BAUD_7200:		UBRG = 2221;	break;
		case BAUD_4800:		UBRG = 3332;	break;
		case BAUD_2400:		UBRG = 6666;	break;
		//-------------------------------
		default:			UBRG = 6666;	break;
		}
	//---------------------------------------------------------


	//---------------------------------------------------------
	UTXIE		= 0;			// Disable UART TX interrupt	
	URXIE		= 0;			// Disable UART RX interrupt	
	//--------------------------------						
	UTXIF		= 0; 			// Clear UART TX interrupt flag
	URXIF		= 0; 			// Clear UART RX interrupt flag
	//--------------------------------						
	UTXIP		= _SDL_IL_TX; 	// Set UART TX interrupt priority
	URXIP		= 0; 			// Set UART RX interrupt priority
								// Setting U1RXIP = 0 effectively
								// disables RX interrupt.
	//---------------------------------------------------------
	// After configuration complete enable UART module	
	//---------------------------------------------------------
	UARTEN		= 1;
	//---------------------------------------------------------
	// Now we may enable UARTx Transmit function after safety
	// delay in one cycle.	
	//---------------------------------------------------------
	Nop();
	UTXEN		= 1;
	}

//************************************************************

