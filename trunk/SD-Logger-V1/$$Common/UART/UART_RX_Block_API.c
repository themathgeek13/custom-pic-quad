#include "UART\UART_RX_Local.h"

//===============================================================
// The following definitions apply only if _UART_Block_Read macro
// is defined above.
//===============================================================
#ifdef _UART_Block_Read
//***************************************************************
// Blocking call to retrieve the bext 512 bytes block of data
// from the UART receiver; if the returned length of the data in
// the block is less than full block length of 512, this is the
// last block of a file.
UARTDataBlock*	UARTReadBlock()
	{
	if (!_UART_RX_Async)
		return NULL;		// Applicable ONLY in ASYNC mode
	//--------------------
	if (!_UART_BlockMode)
		return NULL;		// Applicable ONLY in block mode
	//----------------------------------------------
	// Wait for the new Block to be ready
	while (0 == _UART_RX_Ready); 
	//----------------------------------------------
	UARTDataBlock*	DataBlock = (UARTDataBlock*)_UART_RX_Ready;
	// Indicate that current block consumed
	_UART_RX_Ready = 0;		// This is an atomic operation!
	//----------------------------------------------
	return DataBlock;
	}
//***************************************************************



//***************************************************************
// Frees up the buffer that was returned by the call to
// UARTReadBlock(...); should be called after the block data
// stored onto the disk.
void	UARTFreeBlock(UARTDataBlock* pData)
	{
	if (!_UART_BlockMode)
		return;		// Applicable ONLY in block mode
	//----------------------------------------------
	_UART_BlockBuffer_type* pBlockBuffer =
		(_UART_BlockBuffer_type*)(((byte*)pData) - sizeof(BOOL));
	//----------------------------------------------
	pBlockBuffer->Data.DataLen	= 0;
	memset(pBlockBuffer->Data.Buffer, 0x00, 512);
	//----------------------------------------------
	// Release the Buffer back to the pool...
	//----------------------------------------------
	pBlockBuffer->IsFree 	= TRUE;		// This is atomic operation!
	return;
	}
//***************************************************************
#endif
//===============================================================





