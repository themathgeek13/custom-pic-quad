#include "HMCSPI\HMCSPI_Local.h"

//************************************************************
// ICx Interrupt Routines (Data Ready trigger from HMC)
//************************************************************
void __attribute__((__interrupt__, __no_auto_psv__)) ICInterrupt(void)
	{
	//---------------------------------------------------
	_HMC_Buffer_Template		FIFO;
	uint						i;
	//---------------------------------------------------------
	IC_IF 	= 0; 	// Reset ICx interrupt request
	// Clear capture buffer (and ignore its contents)
	while (ICBNE)
	    i = ICBUF;
	//=========================================================
	// We have captured RISING edge - HMC has measurement!
	//---------------------------------------------------------
	if (FALSE == _HMC_AcquireBus())
		return;	// SPI Bus is busy, hopefully next time...
	//=========================================================
	// Bus is successfully acquired, we may start SPI read
	// operation. However, first, we need to format I/O buffer
	//---------------------------------------------------------
	// Clear buffer
	for (i = 0; i < _SPI_FIFO; i++)
		FIFO.SPIBuf[i] = 0;
	// Format Command byte
	FIFO.RegAddr	= AddrData;	// Set initial register address
	FIFO.MS			= 1;		// Autoincrement register address
	FIFO.RW			= 1;		// Read value from register
	//---------------------------------------------------------
	// Initialize IO operation
	//---------------------------------------------------------
	SPI_IF	= 0;	// Reset SPI interrupt request (if any)
	SPI_IE	= 1;	// Enable interrupts (to capture end of
					// transission)
	// Load FIFO buffer
	for (i = 0; i < 7; i++)			// Address + 6 data bytes
		SPIBUF = FIFO.SPIBuf[i];	// Load SPI FIFO from Buffer
	//---------------------------------------------------------
	// Received data will be processed in the SPI Interrupt
	//---------------------------------------------------------
	return;
	}

//************************************************************
// ICx Interrupt Routines (Data Ready trigger from HMC)
//************************************************************
void __attribute__((__interrupt__, __no_auto_psv__)) SPIInterrupt(void)
	{
	SPI_IF	= 0;	// Reset SPI interrupt request
	SPI_IE	= 0;	// Disable SPI interrupts
	//---------------------------------------------------------
	_HMC_Buffer_Template		FIFO;
	uint						i;
	//=========================================================
	// We have captured end of SPI I/O operation and may now
	// retrieve from FIFO sensor data
	//---------------------------------------------------------
	// Clear buffer
	for (i = 0; i < _SPI_FIFO; i++)
		FIFO.SPIBuf[i] = 0;
	// Retrieve data from FIFO
	for (i = 0; i < 7; i++)		// Address + 6 data bytes
		{
		if (0 == SRXEMPTY)
			FIFO.SPIBuf[i] = SPIBUF;	// Retrieve from FIFO
		}
	//---------------------------------------------------------
	CS_Stop();				// Disselect client
	//---------------------------------------------------------
	// CS_Stop() together with emptying the FIFO read
	// buffer effectively releases the SPI bus!
	// (Check _HMC_AcquireBus() routine)
	//---------------------------------------------------------
	int		X, Y, Z;
	// Obtain measurement values from captured HMC data stream
	HMC_RC	RC = _HMC_ConvertStream(FIFO.Data, &X, &Y, &Z);
	if (HMC_OK != RC)
		return;		// Measurement verflow... Maybe next time :)
	//---------------------------------------------------------
	// Accumulate measurements for subsequent averaging
	//---------------------------------------------------------
	if (0 == _HMC_Ready)
		{
		//---------------------------------
		// First measurement in a series
		//---------------------------------
		_HMC_Sample.MX		= X;
		_HMC_Sample.MY		= Y;
		_HMC_Sample.MZ		= Z;
		//---------------------------------
		}
	else
		{
		//---------------------------------
		// Subsequent measurement
		//---------------------------------
		_HMC_Sample.MX		+= X;
		_HMC_Sample.MY		+= Y;
		_HMC_Sample.MZ		+= Z;
		}
	//---------------------------------------------------------
	_HMC_Ready++;		// _HMC_Ready > 0 -> Sample is ready!
	//---------------------------------------------------------
	// NOTE: Measurement values are up to 12 bits; MX, MY, and
	//		 MZ are defined as "long"; _HMC_Ready is defined
	//		 as "uint", so it will "roll over" to 0 after
	//		 65,536 unread samples.
	//---------------------------------------------------------
	return;
	}
