#include "UART\UART_RX_Local.h"


//************************************************************************
// UART Receive Error Interrupt routine
//------------------------------------------------------------------------
void __attribute__((__interrupt__,__no_auto_psv__)) UErrInterrupt(void)
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
	UPERR	= 0;
	UFERR	= 0;
	UOERR	= 0;
	//---------------------------------------------------------------
	_UART_RX_ErrCnt++;	// Increment error count
	//---------------------------------------------------------------
	UREIF	= 0;		// Clear UART RX Error interrupt flag
	//---------------------------------------------------------------
	return;
	}
//************************************************************************


//************************************************************************
// UART Receive Interrupt helper function
//------------------------------------------------------------------------
void static inline _UART_RX_SaveByte(byte	Byte)
	{
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
	}


//************************************************************************
// UART Receive Interrupt routine
//------------------------------------------------------------------------
void __attribute__((__interrupt__,__no_auto_psv__)) URXInterrupt(void)
	{
	while (URXDA)
		{
		byte	Byte	= URXREG;		// Read received byte
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
				if (_UART_Framed)
					{
					// Frame borders requested by caller
					_UART_RX_SaveByte(_UART_Start);	// Store ignored START
					_UART_RX_SaveByte(_UART_Start);	// Store ignored START					
					}
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	3:		// 3: Data byte received
				_UART_RX_SaveByte(Byte);		// Store data byte
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	4:		// 4: Potential "STOP"?
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	5:		// 5: Data after miscellaneous "STOP"
				_UART_RX_SaveByte(_UART_Stop); // Store skipped STOP
				_UART_RX_SaveByte(Byte);		// Store data byte
				//--------------------------------------------------	
				break;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			case	6:		// 6: Frame terminated; submit frame
				if (_UART_Framed)
					{
					// Frame borders requested by caller
					_UART_RX_SaveByte(_UART_Stop);	// Store ignored STOP
					_UART_RX_SaveByte(_UART_Stop);	// Store ignored STOP					
					}
			
				if (_UART_RX_Buf_Index <= _UART_RX_Max_Frame_Len)
					{
					if (_UART_RX_Buf_Index)
						{
						// Valid frame...
						++_UART_RX_RecCnt;		// Increment record counter
						// Let's store size of the current frame
						_UART_RX_Frame_Len	= _UART_RX_Buf_Index;
						//-------------------------------------------------------------
						// Decide on frame disposition based upon the ASYNC Mode -
						// Block or Frame
						//-------------------------------------------------------------
						if (_UART_BlockMode)
							{
							// Block Mode
							//---------------------------------------------------------
							#ifdef _UART_Block_Read
							//---------------------------------------------------------
							if 	(	_UART_RX_Frame_Len > 4			// Not the "last" frame
								&&									// ...and fits in the current buffer
									_UART_BlockArray[_UART_BlockIndex].Data.DataLen + _UART_RX_Frame_Len < 512 
								)
								{
								// Store Frame in the current buffer
								memcpy( &_UART_BlockArray[_UART_BlockIndex].Data.Buffer[_UART_BlockArray[_UART_BlockIndex].Data.DataLen],
										_UART_RX_Buf, _UART_RX_Frame_Len);
								_UART_BlockArray[_UART_BlockIndex].Data.DataLen += _UART_RX_Frame_Len;
								}
							else
								{
								// Either the last frame in the file or frame exceeds
								// available space in the current buffer; In either 
								// case we need to acquire next buffer - if free
								//-----------------------------------------------------
								// Calculate index of the next buffer - as we have only
								// 2 buffers (0 and 1) - "exclusive OR" works nicely
								WORD	nextBlocIndex 	= _UART_BlockIndex ^ 0x0001; 
								WORD 	Chunk 			= 0;
								//-----------------------------------------------------
								if (_UART_BlockArray[nextBlocIndex].IsFree)
									// We can proceed ONLY if the next buffer is free;
									// otherwise current frame got dropped...
									{
									// Acquire the buffer
									_UART_BlockArray[nextBlocIndex].IsFree	= FALSE; 
									//----------------------------------------------
									if (_UART_RX_Frame_Len <= 4)
										// Last frame of a file
										_UART_RX_Frame_Len = 0;
									else
										{
										//----------------------------------------------
										// Leftover space in the current buffer
										Chunk = 512 - _UART_BlockArray[_UART_BlockIndex].Data.DataLen;	
										// Fill-in the rest of the buffer
										memcpy( &_UART_BlockArray[_UART_BlockIndex].Data.Buffer[_UART_BlockArray[_UART_BlockIndex].Data.DataLen],
												_UART_RX_Buf, Chunk);
										_UART_BlockArray[_UART_BlockIndex].Data.DataLen = 512;	// Current block is filled in
										// Update left-over length of the frame
										_UART_RX_Frame_Len -= Chunk;
										}
									//----------------------------------------------
									// Release filled-in buffer to application									
									//----------------------------------------------
									_UART_RX_Ready = (uint)&_UART_BlockArray[_UART_BlockIndex].Data;
									//----------------------------------------------
									// Switch to the new buffer
									//----------------------------------------------
									_UART_BlockIndex	= nextBlocIndex;
									_UART_BlockArray[_UART_BlockIndex].Data.DataLen = _UART_RX_Frame_Len;
									//----------------------------------
									if (_UART_RX_Frame_Len)
										memcpy(  _UART_BlockArray[_UART_BlockIndex].Data.Buffer,
												&_UART_RX_Buf[Chunk], _UART_RX_Frame_Len);	
									//----------------------------------------------
									}
								else
									// Otherwise received frame is skipped
									_UART_RX_OvrCnt++;
								}
							#endif
							}
						else
							{
							// Frame Mode
							//---------------------------------------------------------
							if (0 == _UART_RX_Ready)
								{
								// Output frame buffer is available
								memcpy(_UART_RX_Frame, _UART_RX_Buf, _UART_RX_Frame_Len);
								//--------------------------------------
								_UART_RX_Ready = 1;
								//---------------------------------------------------------
								}
							else
								// Otherwise received frame is skipped
								_UART_RX_OvrCnt++;
							}
						}
					else;	// Ignore empty frames...
					}
				else
					_UART_RX_InvCnt++;		// Increment count of invalid frames
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
	URXIF		= 0; 		// Clear UART RX interrupt flag
	//-------------------------------------------------
	return ;
	}
//************************************************************************




