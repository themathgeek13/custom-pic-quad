#include "HMCSPI\HMCSPI_Local.h"

//==================================================================
// SPI Synchronous Read/Write helper routines (forward declarations)
//------------------------------------------------------------------
HMC_RC		_HMC_RegRead(byte RAddr, byte* DataBuf, uint DataLen);
HMC_RC		_HMC_RegWrite(byte RAddr, byte* DataBuf, uint DataLen);
void		_HMC_IO(byte* Buffer, uint BufLen);
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="Single byte operations">
//-----------------------------------------------------
HMC_RC	HMC_ReadA(byte* A)
	{
	if (0 == _HMC_Init)
	  return HMC_NotInit;
	//-------------------------------------------
	return _HMC_RegRead(AddrA, A, 1);
	}
//-----------------------------------------------------
HMC_RC	HMC_ReadB(byte* B)
	{
	if (0 == _HMC_Init)
	  return HMC_NotInit;
	//-------------------------------------------
	return _HMC_RegRead(AddrB, B, 1);
	}
//-----------------------------------------------------
HMC_RC	HMC_ReadMode(byte* Mode)
	{
	if (0 == _HMC_Init)
	  return HMC_NotInit;
	//-------------------------------------------
	return _HMC_RegRead(AddrMode, Mode, 1);
	}
//-----------------------------------------------------
HMC_RC	HMC_ReadStatus(byte* Status)
	{
	if (0 == _HMC_Init)
	  return HMC_NotInit;
	//-------------------------------------------
	return _HMC_RegRead(AddrStatus, Status, 1);
	}
//-----------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="Multi-byte operations">
//-----------------------------------------------------
// Reads Configuration A and B and Mode registers
//-----------------------------------------------------
HMC_RC	HMC_ReadControl(byte* Config)
	{
	if (0 == _HMC_Init)
	  return HMC_NotInit;
	//-------------------------------------------
	return _HMC_RegRead (AddrA, Config, 3);
	}
//-----------------------------------------------------
// Reads Identification registers A, B, and C
//-----------------------------------------------------
HMC_RC	HMC_ReadID(byte* ID)
	{
	if (0 == _HMC_Init)
	  return HMC_NotInit;
	//-------------------------------------------
	return _HMC_RegRead (AddrID, ID, 3);
	}
//-----------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="HMC_RC	HMC_ReadRaw(int* X, int* Y, int* Z)">
HMC_RC	HMC_ReadRaw(int* X, int* Y, int* Z)
	{
	HMC_RC	RC;
	byte	Data[6];
	//-----------------------------------------
	// Wait for DRdy to go down and then up (new data sample)
	//-----------------------------------------
	while (1 == DRDY);	// wait for new....
	while (0 == DRDY);	// wait for ready...
	//-----------------------------------------
	// Data is ready - read data registers!
	//-----------------------------------------
	if (HMC_OK != (RC = _HMC_RegRead (AddrData, Data, 6)))
	  return RC;
	return	_HMC_ConvertStream(	Data, X, Y, Z);
	}
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="HMC_RC	HMC_ReadSample(HMCData* Sample)">
HMC_RC	HMC_ReadSample(HMCData* Sample)
	{
	HMC_RC	RC;
	int		X, Y, Z;
	//-----------------------------------------
	// Read next raw measurement
	//-----------------------------------------
	if (HMC_OK != (RC = HMC_ReadRaw(&X, &Y, &Z)))
	  return RC;
	//-----------------------------------------------
	// Obtain timestamp and normalize sensor data
	//-----------------------------------------------
	Sample->TS		= TMRGetTS();
	VectorSet(	_HMC_Gain * X, _HMC_Gain * Y, _HMC_Gain * Z,
				&Sample->M);
	//-----------------------------------------------
	_HMC_NormHMCData(&Sample->M);
	//-----------------------------------------------
	return	HMC_OK;
	}
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="HMC_RC	HMC_ReSet(byte ODR, byte Gain, byte DLPF)">
HMC_RC	HMC_ReSet(byte ODR, byte Gain, byte DLPF)
	{
	if (0 == _HMC_Init)
	  return HMC_NotInit;
	//-------------------------------------------
	HMC_RC	RC;
	//-------------------------------------------
	// Registers that we will be working with
	//-------------------------------------------
	struct
		{
		byte	A;
		byte	B;
		byte	Mode;
		}	Config;
	//-------------------------------------------
	// First, let's put device into the idle mode
	//-------------------------------------------
	Config.Mode	= 0x02;
	if (HMC_OK != (RC = _HMC_RegWrite(AddrMode, &Config.Mode, 1)))
		return RC;
	//=========================================================
	// Process ODR and DLPF
	//---------------------------------------------------------
	ODR		&= 0x07;	// Only 3-bit value is allowed
	ODR		<<= 2;  	// Position ODR in bits 4-3-2 (0-based)
	//---------------------------------------------------------
	DLPF	&= 0x03;	// Only 2-bit value is allowed
	DLPF	<<= 5;		// Position DLPF in bits 6-5 (0-based)
	//---------------------------------------------------------
	// Format configuration register A (we unconditionally
	// enable temperature sensor for automatic temperature com-
	// pensation, thus the 0x80 term)
	//---------------------------------------------------------
	Config.A = 0x80 + DLPF + ODR;
	//---------------------------------------------------------
	// Process Gain
	//---------------------------------------------------------
	Gain &= 0x07;		// Only 3-bit value is allowed
	//---------------------------------------------------------
	// Calculate weight to bring raw measurements to mGs based
	// upon the Gain
	//---------------------------------------------------------
	switch (Gain)
		{
		case 0:
			_HMC_Gain = 0.729927;		// +/- 0.88 Ga
			break;
		case 1:
			_HMC_Gain = 0.917431;		// +/- 1.30 Ga
			break;
		case 2:
			_HMC_Gain = 1.219512;		// +/- 1.90 Ga
			break;
		case 3:
			_HMC_Gain = 1.515152;		// +/- 2.50 Ga
			break;
		case 4:
			_HMC_Gain = 2.272727;		// +/- 4.00 Ga
			break;
		case 5:
			_HMC_Gain = 2.564103;		// +/- 4.70 Ga
			break;
		case 6:
			_HMC_Gain = 3.030303;		// +/- 5.60 Ga
			break;
		case 7:
			_HMC_Gain = 4.347826;		// +/- 8.10 Ga
		default:
			_HMC_Gain = 0.729927;		// Really should not be here...
			break;
		}
	//---------------------------------------------------------
	// Format configuration Register B
	//---------------------------------------------------------
	Config.B = (Gain << 5);
	//---------------------------------------------------------
	// Configure Mode for Continuous Measurement
	//---------------------------------------------------------
	Config.Mode	= 0x00;
	//---------------------------------------------------------
	// Configure device
	//---------------------------------------------------------
	if (HMC_OK != (RC = _HMC_RegWrite(AddrA, (byte*)&Config, 3)))
		return RC;
	//---------------------------------------------------------
	// After configuration has changed we need to read a few
	// measurements to let the device reconfigure its parameters
	//---------------------------------------------------------

//	return HMC_OK;


	HMCData		Sample;
	if (HMC_OK != (RC =  HMC_ReadSample(&Sample)))
		return RC;
	if (HMC_OK != (RC =  HMC_ReadSample(&Sample)))
		return RC;
	return  HMC_ReadSample(&Sample);
	}
// </editor-fold>
//==================================================================


//==================================================================
// SPI Synchronous Read/Write helper routines
//==================================================================
// <editor-fold defaultstate="collapsed" desc="HMC_RC _HMC_RegRead(byte RAddr, byte* DataBuf, uint DataLen)">
//------------------------------------------------------------------
// HMC SPI Register(s) Read routine for HMC 5983 Magnetometer
//==================================================================
HMC_RC		_HMC_RegRead(byte RAddr, byte* DataBuf, uint DataLen)
	{
	// Validate parameters
	if	(
		DataBuf		==	NULL
		||
		DataLen		<	1
		||
		DataLen		>	(_SPI_FIFO - 1)
		)
		return HMC_InvArg;
	//---------------------------------------------------
	_HMC_Buffer_Template		FIFO;
	uint						i;
	//---------------------------------------------------
	// Format I/O buffer
	//---------------------------------------------------
	// Clear buffer
	for (i = 0; i < _SPI_FIFO; i++)
		FIFO.SPIBuf[i] = 0;
	// Format Command byte
	FIFO.RegAddr	= RAddr;// Set initial register address
	FIFO.MS			= 1;	// Autoincrement register address
	FIFO.RW			= 1;	// Read value from register
	//---------------------------------------------------
	// Wait for bus to be free and acquire it
	//---------------------------------------------------
	while (_HMC_AcquireBus() == FALSE);
	//---------------------------------------------------
	// Perform I/O
	//---------------------------------------------------
	_HMC_IO(FIFO.SPIBuf, (DataLen+1));
	//---------------------------------------------------
	// Return data
	//---------------------------------------------------
	for (i = 0; i < DataLen; i++)
		DataBuf[i] = FIFO.Data[i];
	//---------------------------------------------------
	return HMC_OK;
	}
//-----------------------------------------------------
// </editor-fold>
//==================================================================
// <editor-fold defaultstate="collapsed" desc="HMC_RC _HMC_RegWrite(byte RAddr, byte* DataBuf, uint DataLen)">
//------------------------------------------------------------------
// HMC SPI Register(s) Write routine for HMC 5983 Magnetometer
//==================================================================
HMC_RC		_HMC_RegWrite(byte RAddr, byte* DataBuf, uint DataLen)
	{
	// Validate parameters
	if	(
		DataBuf		==	NULL
		||
		DataLen		<	1
		||
		DataLen		>	(_SPI_FIFO - 1)
		)
		return HMC_InvArg;
	//---------------------------------------------------
	_HMC_Buffer_Template		FIFO;
	uint						i;
	//---------------------------------------------------
	// Format I/O buffer
	//---------------------------------------------------
	// Clear buffer
	for (i = 0; i < _SPI_FIFO; i++)
		FIFO.SPIBuf[i] = 0;
	// Format Command byte
	FIFO.RegAddr	= RAddr;// Set initial register address
	FIFO.MS			= 1;	// Autoincrement register address
	FIFO.RW			= 0;	// Write value to register
	// Load buffer with data
	for (i = 0; i < DataLen; i++)
		FIFO.Data[i] = DataBuf[i];
	//---------------------------------------------------
	// Wait for bus to be free and acquire it
	//---------------------------------------------------
	while (_HMC_AcquireBus() == FALSE);
	//---------------------------------------------------
	// Perform I/O
	//---------------------------------------------------
	_HMC_IO(FIFO.SPIBuf, (DataLen+1));
	//---------------------------------------------------
	return HMC_OK;
	}
//-----------------------------------------------------
// </editor-fold>
//==================================================================
// <editor-fold defaultstate="collapsed" desc="void	_HMC_IO(byte* Buffer, uint BufLen)">
//------------------------------------------------------------------
// SPI Read/Write routines
//==================================================================
void		_HMC_IO(byte* Buffer, uint BufLen)
	{
	//---------------------------------------------------
	uint i;
	//---------------------------------------------------
	// Perform IO operation
	//---------------------------------------------------
	for (i = 0; i < BufLen; i++)
		SPIBUF = Buffer[i];	// Load FIFO from Buffer
	// Wait for transmission to end
	while (SPIBEC > 0);		// Wait for FIFO to clear
	while (SREMPTY == 0);	// Wait for Shift register to clear
	//---------------------------------------------------
	// Retrieve data from FIFO
	//---------------------------------------------------
	for (i = 0; i < BufLen; i++)
		{
		if (0 == SRXEMPTY)
			Buffer[i] = SPIBUF;	// Retrieve from FIFO
		}
	//---------------------------------------------------
	CS_Stop();				// Disselect client
	//---------------------------------------------------
	// CS_Stop() together with emptying the FIFO read
	// buffer effectively releases the SPI bus!
	// (Check _HMC_AcquireBus() routine)
	//---------------------------------------------------
	return;
	}
//-----------------------------------------------------
// </editor-fold>
//==================================================================
