#include "SDL\SDL_Local.h"

//==================================================================
byte				_SDL_IL_TX	= 4; 	// UART Transmitter
										// default interrupt level
//==================================================================
byte	const 		_SDL_Start = 0x55; 
byte	const 		_SDL_Stop  = 0xAA; 

// Transmitter-specific variables
//------------------------------------------------------------------
// _SDL_Ready = 1 indicates that UART is ready for TX operation
uint 	volatile	_SDL_Ready	= 1; // Obviously, READY
//------------------------------------------------------------------
// UART Transmit data buffer
byte 				_SDL_Buf[_SDL_Buf_Max];
// Length of the frame in Transmit data buffer	
uint	volatile	_SDL_Buf_Len	= 0;	// Empty...
// Current position in Transmit data buffer
uint	volatile	_SDL_Buf_Index	= 0;
//==================================================================




