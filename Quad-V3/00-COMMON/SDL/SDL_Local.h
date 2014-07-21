#include "SDL\SDL.h"
#include "SDL\SDL_Profile.h"


//==================================================================
#ifndef __SDL_Local_H
#define __SDL_Local_H
//==================================================================
extern byte			_SDL_IL_TX;
//==================================================================
extern byte const 	_SDL_Start;	
extern byte const 	_SDL_Stop;	
	
//==================================================================
// Transmitter-specific variables
//------------------------------------------------------------------
// _SDL_Ready = 1 indicates that UART is ready for TX operation
extern uint		volatile	_SDL_Ready;
//------------------------------------------------------------------
// UART Transmit data buffer
extern byte 				_SDL_Buf[_SDL_Buf_Max];
// Length of the frame in Transmit data buffer	
extern uint	 	volatile	_SDL_Buf_Len;
// Current position in Transmit data buffer
extern uint	 	volatile	_SDL_Buf_Index;
//==================================================================
#endif



