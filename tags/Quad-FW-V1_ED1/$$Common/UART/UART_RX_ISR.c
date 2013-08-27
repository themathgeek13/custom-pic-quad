#include "UART\UART_Local.h"


//************************************************************************
// UART2 Receive Error Interrupt routine
//------------------------------------------------------------------------
void __attribute__((__interrupt__,__no_auto_psv__)) _U2ErrInterrupt(void)
	{
	// On error we ignore current frame and reset state automaton
	_UART_RX_CurrentState	= 0;	// Reset automaton: Scan input to first START
	//------------------------------
	_UART_RX_Buf_Index		= 0;	// Reset index in Receive buffer
	//---------------------------------------------------------------
	// Clear all error conditions
	//---------------------------------------------------------------
	/*
	bit 3 PERR: Parity Error Status bit (Read Only)
		1 = Parity error has been detected for the current character
		0 = Parity error has not been detected
	bit 2 FERR: Framing Error Status bit (Read Only)
		1 = Framing Error has been detected for the current character
		0 = Framing Error has not been detected
	bit 1 OERR: Receive Buffer Overrun Error Status bit (Read/Clear Only)
		1 = Receive buffer has overflowed
		0 = Receive buffer has not overflowed
	*/
	U2STAbits.PERR	= 0;
	U2STAbits.FERR	= 0;
	U2STAbits.OERR	= 0;
	//---------------------------------------------------------------
	_UART_RX_ErrCnt++;			// Increment error count
	//---------------------------------------------------------------
	IFS4bits.U2EIF		= 0;	// Clear UART RX Error interrupt flag
	//---------------------------------------------------------------
	return;
	}
//************************************************************************


//************************************************************************
// UART2 Receive Interrupt routine
//------------------------------------------------------------------------
void __attribute__((__interrupt__,__no_auto_psv__)) _U2RXInterrupt(void)
	{
	while (U2STAbits.URXDA)
		{
		uchar	Byte	= U2RXREG;		// Read received byte
		uint	Code	= 0;			// 0 - Data byte
										// 1 - Start code
										// 2 - Stop code
		if (_UART_Start == Byte)	
			Code = 1;
		else if (_UART_Stop == Byte)
				Code = 2;
		//---------------------------
		// Advance state
		//---------------------------
		_UART_RX_CurrentState	= _UART_RX_StateControl[_UART_RX_CurrentState][Code];
		//--------------------------------
		// Perform Action on received byte
		//--------------------------------
		switch (_UART_RX_CurrentState)
			{
			//-------------------------------------------------------------
			case	0:		// 0: Scan to Start - No action...
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	1:		// 1: First Start byte during scan, wait for second...
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	2:		// 2: Second Start byte during scan, ready for frame data...
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	3:		// 3: Data byte received
				if (_UART_RX_Buf_Index < _UART_RX_Max_Frame_Len)
					{
					_UART_RX_Buf[_UART_RX_Buf_Index]	= Byte;
					_UART_RX_Buf_Index++;
					}
				else
					// Set _UART_RX_Buf_Index just above _UART_RX_Max_Frame_Len
					// to indicate frame overrun;
					// Ignore data bytes beyond _UART_RX_Max_Frame_Len
					_UART_RX_Buf_Index = _UART_RX_Max_Frame_Len + 1;	
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	4:		// 4: Potential "STOP"?
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	5:		// 5: Data after miscellaneous "STOP"
				if (_UART_RX_Buf_Index < _UART_RX_Max_Frame_Len)
					{
					_UART_RX_Buf[_UART_RX_Buf_Index]	= _UART_Stop;	// Store skipped STOP
					_UART_RX_Buf_Index++;
					}
				else
					// Set _UART_RX_Buf_Index just above _UART_RX_Max_Frame_Len
					// to indicate frame overrun;
					// Ignore data bytes beyond _UART_RX_Max_Frame_Len
					_UART_RX_Buf_Index = _UART_RX_Max_Frame_Len + 1;
				//--------------------------------------------------	
				if (_UART_RX_Buf_Index < _UART_RX_Max_Frame_Len)
					{
					_UART_RX_Buf[_UART_RX_Buf_Index]	= Byte;			// Store data byte
					_UART_RX_Buf_Index++;
					}
				else
					// Set _UART_RX_Buf_Index just above _UART_RX_Max_Frame_Len
					// to indicate frame overrun;
					// Ignore data bytes beyond _UART_RX_Max_Frame_Len
					_UART_RX_Buf_Index = _UART_RX_Max_Frame_Len + 1;	
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	6:		// 6: Frame terminated; submit frame
				if (_UART_RX_Buf_Index <= _UART_RX_Max_Frame_Len)
					{
					if (_UART_RX_Buf_Index)
						{
						// Valid frame...
						++_UART_RX_RecCnt;		// Increment record counter
						//--------------------------------------
						for (_UART_RX_Frame_Len	= 0; _UART_RX_Frame_Len < _UART_RX_Buf_Index; _UART_RX_Frame_Len++)
							_UART_RX_Frame[_UART_RX_Frame_Len] = _UART_RX_Buf[_UART_RX_Frame_Len];
						//--------------------------------------
						_UART_RX_Ready = 1;
						}
					else;	// Ignore empty frames...
					}
				else
					_UART_RX_OvrCnt++;		// Increment count of frame overruns
				//----------------------------------
				// Reset receiver
				//----------------------------------
				_UART_RX_CurrentState	= 0;	// Reset automaton: Scan input to first START
				//------------------------------
				_UART_RX_Buf_Index		= 0;	// Reset index in Receive buffer
				break;
			//-------------------------------------------------------------
			}
		//--------------------------
		}
	//-------------------------------------------------
	IFS1bits.U2RXIF		= 0; 		// Clear UART RX interrupt flag
	//-------------------------------------------------
	return ;
	}
//************************************************************************




