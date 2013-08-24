#include "UART\UART_RX.h"
#include "UART\UART_RX_Profile.h"

#include "string.h"

//==================================================================
#ifndef __UART_RX_Local_H
#define __UART_RX_Local_H
//==================================================================
extern byte			_UART_IL_RX;
//==================================================================
extern byte const 		_UART_Start;	
extern byte const 		_UART_Stop;	

extern BOOL	volatile	_UART_Framed;
extern BOOL	volatile	_UART_BlockMode;

//==================================================================
// Receiver-specific variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Interface variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// _UART_RX_Async = 1 indicates that UART initiated Asynchronous Read
extern uint 	volatile	_UART_RX_Async; 
// Receiver statistics
extern ulong	volatile	_UART_RX_RecCnt;
extern ulong	volatile	_UART_RX_InvCnt;
extern ulong	volatile	_UART_RX_OvrCnt;
extern ulong	volatile	_UART_RX_ErrCnt;
//------------------------------------------------------------------
// Maximum length of legitimate data frame
extern uint		volatile	_UART_RX_Max_Frame_Len;
// _UART_RX_Ready = 1 indicates that UART loaded new frame
extern uint 	volatile	_UART_RX_Ready;
// Length of the received Frame (in Frame buffer)
extern uint		volatile	_UART_RX_Frame_Len;
// UART Receiver Frame buffer
extern byte 				_UART_RX_Frame[_UART_Buf_Max];
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// State management variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern uint				_UART_RX_StateControl[7][3];
extern uint	volatile	_UART_RX_CurrentState;	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Receiver Buffer and control variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UART Receive data buffer
extern byte 				_UART_RX_Buf[_UART_Buf_Max];
// Current position in Receive data buffer
extern uint		volatile	_UART_RX_Buf_Index;
//===============================================================
// The following definitions apply only if _UART_Block_Read macro
// is defined in UART.h
//===============================================================
	#ifdef _UART_Block_Read
	//-----------------------------------------------------------
	typedef struct
		{
		BOOL			volatile	IsFree;
		UARTDataBlock				Data;	
		}	__attribute__ ((packed))
			_UART_BlockBuffer_type;
	//-----------------------------------------------------------
	extern WORD						volatile	_UART_BlockIndex;
	//----------------------------------
	extern _UART_BlockBuffer_type				_UART_BlockArray[2];
	//-----------------------------------------------------------
		
	#endif
//===============================================================
#endif



