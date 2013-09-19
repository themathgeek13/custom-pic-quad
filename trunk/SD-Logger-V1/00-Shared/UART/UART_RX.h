#include "System.h"

//===============================================================
#ifndef __UART_RX_H
#define __UART_RX_H
//===============================================================
// In this application we use UART module to receive data. 
//---------------------------------------------------------------
// Receiver: UART
//----------------------------------------------------
typedef struct
	{
	ulong	RecordCount;
	ulong	FrameOverrunCount;
	ulong	InvalidFrameCount;
	ulong	ErrorCount;
	}	UARTRXStat, *pUARTRXStat;
//----------------------------------------------------
void	UARTInitRX(int IL, int BaudRate);	
			// Parameter (1<=IL<=7) defines the
			// priority of UART interrupt routine.

ulong 	UARTRXGetRecordCount(void);
void	UARTRXGetStat(pUARTRXStat RXStat);

BOOL	UARTRXStartAsyncRead(	uint MaxFrameSize, 
								BOOL Framed,
								BOOL BlockMode);
void	UARTRXStopAsyncRead(void);

uint	UARTReadWhenNew	(	byte* 	Data, 
							uint 	DataLen);

uint	UARTReadIfNew	(	byte* 	Data, 
							uint 	DataLen);
//==================================================================
// The following define macro (if defined) enables block receives - 
// messages are being "streamed" in chunks of 512 bytes to facilitate
// block write operations.
// NOTE: Enabling this feature consumes ~1 KB of RAM.
// NOTE: Messages are streamed together with the frame delimiters
//==================================================================
#define	_UART_Block_Read
//===============================================================
// The following definitions apply only if _UART_Block_Read macro
// is defined above.
//===============================================================
#ifdef _UART_Block_Read
	typedef struct
		{
		WORD	volatile	DataLen;
		byte				Buffer[512];	
		}	UARTDataBlock;
	//-----------------------------------------------------------
	// Blocking call to retrieve the bext 512 bytes block of data
	// from the UART receiver; if the returned length of the data in
	// the block is less than full block length of 512, this is the
	// last block of a file.
	UARTDataBlock*	UARTReadBlock();
	//-----------------------------------------------------------
	// Frees up the buffer that was returned by the call to
	// UARTReadBlock(...); should be called after the block data
	// stored onto the disk.
	void			UARTFreeBlock(UARTDataBlock* pData);
	//-----------------------------------------------------------
#endif
//===============================================================
#endif



