#include "UART\UART_Local.h"

//************************************************************
ulong UARTRXGetRecordCount(void)
	{return _UART_RX_RecCnt;}
//************************************************************
void	UARTRXGetStat(pUARTRXStat RXStat)
	{
	RXStat->RecordCount			= _UART_RX_RecCnt;
	RXStat->FrameOverrunCount	= _UART_RX_OvrCnt;
	RXStat->ErrorCount			= _UART_RX_ErrCnt;	
	}
//************************************************************
void	UARTRXStartAsyncRead(uint MaxFrameSize)
	{
	if (_UART_RX_Async)
		return;		// Async Read mode is already established.
	//-------------------------------
	if (MaxFrameSize > _UART_Buf_Max)
		MaxFrameSize = _UART_Buf_Max;
	//-------------------------------
	// Reset statistics
	//-------------------------------
	_UART_RX_RecCnt	= 0; // Receive record count
	_UART_RX_OvrCnt	= 0; // Receive frame overrun count
	_UART_RX_ErrCnt	= 0; // Receive error count
	//-------------------------------
	// Reset output control
	//-------------------------------
	_UART_RX_Max_Frame_Len	= MaxFrameSize;
	_UART_RX_Ready			= 0; 	
	_UART_RX_Frame_Len		= 0;	// Empty...
	//-------------------------------
	// Reset State management
	//-------------------------------
	_UART_RX_CurrentState	= 0;	// Scan input to first START
	//------------------------------
	_UART_RX_Buf_Index		= 0;	// Reset index in Receive buffer
	//-------------------------------
	// Clear interrupt conditions
	//-------------------------------
	IFS1bits.U2RXIF		= 0; 		// Clear UART RX interrupt flag
	IFS4bits.U2EIF		= 0;		// Clear UART RX Error interrupt flag
	//-------------------------------
	// Enable Receiver module 
	//-------------------------------
	U2MODEbits.UARTEN	= 1;	
	//-------------------------------
	// Enable interrupts - Start Asynchronous read
	//-------------------------------
	IEC4bits.U2EIE		= 1;		// Enableable UART RX Error interrupt	
	IEC1bits.U2RXIE		= 1;		// Enable UART RX interrupt
	//-------------------------------
	_UART_RX_Async		= 1;		// Indicate that Async Mode is on
	//-------------------------------
	return;
	}
//************************************************************
void	UARTRXStopAsyncRead(void)
	{
	if (!_UART_RX_Async)
		return;		// Async Read mode is already suspended.
	//-------------------------------
	U2MODEbits.UARTEN	= 0;		// Disable UART Module
	//-------------------------------
	IEC1bits.U2RXIE		= 0;		// Disable UART RX interrupt
	IEC4bits.U2EIE		= 0;		// Disable UART RX Error interrupt	
	//-------------------------------
	IFS1bits.U2RXIF		= 0; 		// Clear UART RX interrupt flag
	IFS4bits.U2EIF		= 0;		// Clear UART RX Error interrupt flag
	//-------------------------------
	// Clear all error conditions
	//-------------------------------
	U2STAbits.PERR	= 0;
	U2STAbits.FERR	= 0;
	U2STAbits.OERR	= 0;
	//-------------------------------
	// Reset output control
	//-------------------------------
	_UART_RX_Max_Frame_Len	= 0;
	_UART_RX_Ready			= 0; 	// Discard current frame...
	_UART_RX_Frame_Len		= 0;	// Empty...
	//-------------------------------
	// Reset State management
	//-------------------------------
	_UART_RX_CurrentState	= 0;	// Scan input to first START
	_UART_RX_Buf_Index		= 0;	// Reset index in Receive buffer
	//-------------------------------
	_UART_RX_Async			= 0;	// Indicate that Async Mode is OFF
	//-------------------------------
	return;
	}
//************************************************************
int		UARTReadWhenNew	(	uchar * Data, 
							uint 	DataLen)
	{
	if (!_UART_RX_Async)
		return 0;
	//--------------------
	while (!_UART_RX_Ready); // Wait for the new frame to be read
	//--------------------
	return UARTReadIfNew(Data, DataLen);
	}
//************************************************************
int		UARTReadIfNew	(	uchar * Data, 
							uint 	DataLen)
	{
	if (!_UART_RX_Async)
		return 0;
	//--------------------
	if (!_UART_RX_Ready)
		return 0;
	//--------------------
	uint current_cpu_ipl;
	uint FrameLen = DataLen;
	uint i;
	//---------------------------------
	// Enter UARTRX CRITICAL SECTION
	//---------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _UART_IL_RX);  /* disable UART_RX interrupts */
	//--------------------------------------------------------
	if (FrameLen > _UART_RX_Frame_Len)
		FrameLen = _UART_RX_Frame_Len;
	for (i = 0; i < FrameLen; i++)
		Data[i] = _UART_RX_Frame[i];	
	//--------------------------------------------------------
	_UART_RX_Ready = 0;		// Frame consumed...
	//---------------------------------
	// Leave ADC CRITICAL SECTION
	//---------------------------------
  	RESTORE_CPU_IPL(current_cpu_ipl);
	//--------------------------
	return FrameLen;
	}
//************************************************************




