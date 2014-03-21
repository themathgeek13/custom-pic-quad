#include "UART\UART_RX_Local.h"

//==================================================================
byte				_UART_IL_RX	= 4; 	// Receiver
							// (UART) default interrupt level
//==================================================================
byte	const 		_UART_Start 	= 0x55; 
byte	const 		_UART_Stop  	= 0xAA; 

BOOL	volatile	_UART_Framed	= FALSE;
BOOL	volatile	_UART_BlockMode	= FALSE;

//==================================================================
// Receiver-specific variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Interface variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// _UART_RX_Async = 1 indicates that UART initiated Asynchronous Read
uint 	volatile	_UART_RX_Async	= 0; 
// Receiver statistics
ulong	volatile	_UART_RX_RecCnt	= 0; // Receive record count
ulong	volatile	_UART_RX_OvrCnt	= 0; // Receive frame overrun count
ulong	volatile	_UART_RX_InvCnt	= 0; // Receive invalid frame count
ulong	volatile	_UART_RX_ErrCnt	= 0; // Receive error count
//------------------------------------------------------------------
// Maximum length of legitimate data frame
uint	volatile	_UART_RX_Max_Frame_Len	= 0;
// _UART_RX_Ready = 1 indicates that UART loaded new frame
uint 	volatile	_UART_RX_Ready	= 0; // Obviously, Not READY
// Length of the received Frame (in Frame buffer)
uint	volatile	_UART_RX_Frame_Len	= 0;	// Empty...
// UART Receiver Frame buffer
byte 				_UART_RX_Frame[_UART_Buf_Max];
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// State management variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint				_UART_RX_StateControl[7][3]	=
						{
							{0, 1, 0},		// 0: Scan to first START
							{0, 2, 0},		// 1: Expecting second START
							{3, 3, 4},		// 2: Frame START identified
							{3, 3, 4},		// 3: Process frame data
							{5, 5, 6},		// 4: First STOP?
							{3, 3, 4},		// 5: Data byte after miscellaneous STOP
							{0, 1, 0}		// 6: Frame terminated - valid frame is reported here!
						};
uint	volatile	_UART_RX_CurrentState		= 0;	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Receiver Buffer and control variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UART Receive data buffer
byte 				_UART_RX_Buf[_UART_Buf_Max];
// Current position in Receive data buffer
uint	volatile	_UART_RX_Buf_Index	= 0;
//==================================================================

//===============================================================
// The following definitions apply only if _UART_Block_Read macro
// is defined in UART.h
//===============================================================
	#ifdef _UART_Block_Read
		//-----------------------------------------------------------
		WORD					volatile	_UART_BlockIndex 	= 0;
		//----------------------------------
		_UART_BlockBuffer_type				_UART_BlockArray[2];
		//-----------------------------------------------------------
	#endif
//===============================================================



