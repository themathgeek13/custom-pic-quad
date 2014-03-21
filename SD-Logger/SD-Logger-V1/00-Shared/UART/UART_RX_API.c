#include "UART\UART_RX_Local.h"

//************************************************************
ulong UARTRXGetRecordCount(void)
	{return _UART_RX_RecCnt;}
//************************************************************


//************************************************************
void	UARTRXGetStat(pUARTRXStat RXStat)
	{
	uint current_cpu_ipl;
	//---------------------------------
	// Enter UART_RX CRITICAL SECTION
	//---------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _UART_IL_RX);  /* disable UART_RX interrupts */
	//--------------------------------------------------------
	RXStat->RecordCount			= _UART_RX_RecCnt;
	RXStat->FrameOverrunCount	= _UART_RX_OvrCnt;
	RXStat->InvalidFrameCount	= _UART_RX_InvCnt;
	RXStat->ErrorCount			= _UART_RX_ErrCnt;	
	//---------------------------------
	// Leave UART_RX CRITICAL SECTION
	//---------------------------------
  	RESTORE_CPU_IPL(current_cpu_ipl);
	//--------------------------
	}
//************************************************************


//************************************************************
BOOL	UARTRXStartAsyncRead(	uint MaxFrameSize, 
								BOOL Framed,
								BOOL BlockMode)
	{
	if (_UART_RX_Async)
		return	FALSE;	// Async Read mode is already established.
	//-------------------------------
	if (MaxFrameSize > _UART_Buf_Max)
		return FALSE;	// Specified frame size exceeds defined
						// frame buffer length
	//-------------------------------
#ifdef _UART_Block_Read
	//-------------------------------
	// Reset block control
	//-------------------------------
	_UART_BlockIndex			= 0;			// Select first block as "current"
	//-------------------------------
	_UART_BlockArray[0].IsFree 	= FALSE;		// Reserve first buffer
	_UART_BlockArray[0].Data.DataLen	= 0;
	memset(_UART_BlockArray[0].Data.Buffer, 0x00, 512);
	//-------------------------------
	_UART_BlockArray[1].IsFree 			= TRUE;			// Release second buffer
	_UART_BlockArray[1].Data.DataLen	= 0;
	memset(_UART_BlockArray[1].Data.Buffer, 0x00, 512);
	//-------------------------------
	_UART_BlockMode				= BlockMode;	// Both TRUE and FALSE are acceptable
	if (BlockMode)
		// To distinguish individual Frames in a block we have to store Frame
		// Start and Stop delimiters - force Framed mode
		Framed = TRUE;
#else
	if (BlockMode)
		return FALSE;			// Block mode requested without enabling block mode read
								// by defining macro _UART_Block_Read in UART_RX.h
#endif
	//-------------------------------
	// Store Frame Border save option
	//-------------------------------
	_UART_Framed	= Framed;
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
	URXIF		= 0; 		// Clear UART RX interrupt flag
	UREIF		= 0;		// Clear UART RX Error interrupt flag
	//-------------------------------
	// Enable Receiver module 
	//-------------------------------
	UARTEN		= 1;	
	//-------------------------------
	// Enable interrupts - Start Asynchronous read
	//-------------------------------
	UREIE			= 1;	// Enableable UART RX Error interrupt	
	URXIE			= 1;	// Enable UART RX interrupt
	//-------------------------------
	_UART_RX_Async	= 1;	// Indicate that Async Mode is on
	//-------------------------------
	return	TRUE;
	}
//************************************************************
void	UARTRXStopAsyncRead(void)
	{
	if (!_UART_RX_Async)
		return;		// Async Read mode is already suspended.
	//-------------------------------
	UARTEN		= 0;		// Disable UART Module
	//-------------------------------
	URXIE		= 0;		// Disable UART RX interrupt
	UREIE		= 0;		// Disable UART RX Error interrupt	
	//-------------------------------
	URXIF		= 0; 		// Clear UART RX interrupt flag
	UREIF		= 0;		// Clear UART RX Error interrupt flag
	//-------------------------------
	// Clear all error conditions
	//-------------------------------
	UPERR	= 0;
	UFERR	= 0;
	UOERR	= 0;
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
uint	UARTReadWhenNew	(	byte* 	Data, 
							uint 	DataLen)
	{
	if (!_UART_RX_Async)
		return 0;
	//--------------------
	if (_UART_BlockMode)
		return 0;		// Cannot call frame receive function
						// in block mode
	//--------------------
	if (DataLen < _UART_RX_Frame_Len)
		return 0;
	//----------------------------------------------
	// Wait for the new Block to be ready
	while (0 == _UART_RX_Ready); 
	//----------------------------------------------
	return UARTReadIfNew(Data, DataLen);
	}
//************************************************************
uint	UARTReadIfNew	(	byte*	Data, 
							uint 	DataLen)
	{
	if (!_UART_RX_Async)
		return 0;
	//--------------------
	if (DataLen < _UART_RX_Frame_Len)
		return 0;
	//--------------------
	if (_UART_BlockMode)
		return 0;		// Cannot call frame receive function
						// in block mode
	//--------------------
	if (0 == _UART_RX_Ready)
		return 0;		// No new frame data
	//--------------------------------------------------------
	DataLen = _UART_RX_Frame_Len;
	memcpy(Data, (void*)_UART_RX_Frame, DataLen);
	//--------------------------------------------------------
	// Release frame buffer back to UART_RX
	//--------------------------------------------------------
	_UART_RX_Ready = 0;		// This change is atomic!
	//--------------------------------------------------------
	return DataLen;
	}
//************************************************************




