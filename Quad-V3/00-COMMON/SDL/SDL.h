#include "System.h"

//=======================================================
#ifndef __SDL_H
#define __SDL_H
//=======================================================
// Serial Data Logger (SDL) uses UART to expose data
// messages. Each data message is exposed as a "frame"
// wrapped around with the two START (0x0505)and two
// STOP (0xAAAA) characters. Start and Stop characters
// are added automatically, so there is no need to add
// them to the data.
//------------------------------------------------------
// SDL can work with any available UART module and
// uses only TX part of the module.
//=======================================================

//=======================================================
// SDL_BAUD_RATE enumerator defines acceptable Baud rates
//=======================================================
// Acceptable PIC-to-PIC Baud rates are strongly dependent
// on the MCU clock speed. Rates below are defined under
// assumption that the MCU is operating at 64 MHz
// (Fcy = 64,000,000)
//=========================================================
typedef enum
	{
	//-----------------------
	// Standard Baud rates
	//-----------------------
	BAUD_2400,
	BAUD_4800,
	BAUD_7200,
	BAUD_9600,
	BAUD_14400,
	BAUD_19200,
	BAUD_38400,
	BAUD_57600,
	BAUD_115200,
	//-----------------------
	// PIC-to-PIC Baud rates
	//-----------------------
	BAUD_200K,
	BAUD_250K,
	BAUD_400K,
	BAUD_500K,
	BAUD_1M
	}	SDL_BAUD_RATE;
//=======================================================
void	SDLInit(uint IL, SDL_BAUD_RATE BaudRate);
			// Parameter (1<=IL<=7) defines the
			// priority of UART interrupt routine.

void	SDLPostIfReady(	byte* Data, 
							uint 	DataLen);

void	SDLPostWhenReady(	byte * Data, 
							uint 	DataLen);
//=======================================================
#endif



