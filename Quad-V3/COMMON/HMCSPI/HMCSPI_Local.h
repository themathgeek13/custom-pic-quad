#include "HMCSPI\HMCSPI.h"
#include "HMCSPI\HMCSPI_Profile.h"

#include "TMR\TMR.h"

//==================================================================
#ifndef HMCSPI_LOCAL_H
#define	HMCSPI_LOCAL_H
//==================================================================
#define	AddrA		0x00
#define	AddrB		0x01
#define	AddrMode	0x02
#define	AddrStatus	0x09
#define	AddrID		0x0A
#define AddrData	0x03
#define	AddrTemp	0x31
//------------------------------------------------------------------
// Buffer data structure for communication with HMC 5983 over SPI
// in Enhanced Mode (using FIFO SPI Buffer feature)
//------------------------------------------------------------------
typedef union
	{
	byte	SPIBuf[_SPI_FIFO];
	// The following structure overlays the first byte
	// of the buffer, which represents Register address
	// and control bits (remember: Little Endian!)
	struct
		{
		/*	Register address, 6 bits*/
		unsigned	RegAddr:6;
		unsigned	MS:1;		// 1 = Autoincrement address
		unsigned	RW:1;		// Read/Write control bit
								// 0 - data is WRITTEN to the register
								// 1 - data is READ from the register
		byte		Data[_SPI_FIFO - 1];
		};
	} _HMC_Buffer_Template;
//==================================================================
extern uint				_HMC_Init;	// Not initialized
//------------------------------------------------------------------
extern byte				_HMC_IL; 	// SPI default interrupt level
//==================================================================

//==================================================================
// HMC Sensor data normalization values
//==================================================================
// MAG Sensitivity: 
extern	float			_HMC_Gain;
// MAG Hard Iron correction vector
extern	Vector			_HMC_HardIron;
// MAG Soft Iron correction matrix
extern 	Vector			_HMC_SoftIron_X;
extern 	Vector			_HMC_SoftIron_Y;
extern 	Vector			_HMC_SoftIron_Z;
//==================================================================

//==================================================================
// Raw MAG Data Sample - data length increased from int (native to
// sensor) to long to accommodate accumulation in the ISR routine
//==================================================================
typedef	struct
	{
	long		MX;
	long		MY;
	long		MZ;
	}	_HMCRawData;
//==================================================================
// Asynchronous read support
//==================================================================
extern volatile uint	_HMC_Async;	// Asynchronous read mode flag
//------------------------------------------------------------------
extern volatile	uint	_HMC_Ready;	// Flag indicating whether asynch-
									// ronous read data is ready
//------------------------------------------------------------------
extern  _HMCRawData		_HMC_Sample;// Asynchronous sample...
//==================================================================
#endif	/* HMCSPI_LOCAL_H */

#include "HMCSPI\HMCSPI_Inlines.h"
