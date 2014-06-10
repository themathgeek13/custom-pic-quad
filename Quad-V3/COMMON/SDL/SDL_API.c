#include "SDL\SDL_Local.h"

//************************************************************
void	SDLPostWhenReady(	byte * Data, 
							uint 	DataLen)
	{
	while (0 == _SDL_Ready); // Wait until READY
	//------------------------
	SDLPostIfReady(Data, DataLen);	
	}
//************************************************************
void	SDLPostIfReady(	byte * Data, 
							uint 	DataLen)
	{
	//========================================================
	if (0 == _SDL_Ready)
		return;					// UART is busy...
	//--------------------------------------------------------
	_SDL_Ready 	= 0;			// Acquire UART...
	//========================================================
	if (DataLen > _SDL_Buf_Max)
		DataLen	= _SDL_Buf_Max;	// Limit message to buffer size...
	//----------------------------------
	_SDL_Buf_Len	= DataLen;		
	_SDL_Buf_Index	= 0;
	//----------------------------------
	if (DataLen)
		{
		uint i;
		for ( i= 0; i < DataLen; i++)
			_SDL_Buf[i] = Data[i];
		}
	//----------------------------------
	// As we generate UART TX interrupts only when buffer
	// is empty and we set TX READY bit right after pushing
	// termination word (2 bytes) in responce to interrupt,
	// whenever UART is ready we have at least 2 slots in
	// the buffer...
	// Send "START" delimiter (double _SDL_Start)
	//----------------------------------
	UTXREG = _SDL_Start;
	asm ("nop"); 			// We need at least one cycle 
							// delay between writes to U1TXREG ...
	UTXREG = _SDL_Start;
	//----------------------------------
	UTXIE	= 0b1;			// Enable UART TX interrupt
	//----------------------------------
	return;
	}
//************************************************************




