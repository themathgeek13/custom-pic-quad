#ifndef HMCSPI_LOCAL_H
	#include "HMCSPI\HMCSPI_Local.h"
#endif

//==================================================================
#ifndef HMCSPI_INLINES_H
#define	HMCSPI_INLINES_H
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="static inline BOOL _HMC_AcquireBus()">
//------------------------------------------------------------------
// SPI Bus management routine
//------------------------------------------------------------------
static inline BOOL	_HMC_AcquireBus()
	{
	BOOL	RC				= FALSE;
	int		current_cpu_ipl;
	//==============================================
	// Enter HMC/I2C CRITICAL SECTION
	//----------------------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _HMC_IL);
	//----------------------------------------------
	// Validate SPI bus condition(s)
	if	(
		CS			==	0	// Target device is selected - operation is
		||					// in progress
		SPIBEC		>	0	// There are pending transfers in the buffer
		||
		SREMPTY		==	0	// Shift register is not empty
		||
		SRXEMPTY	==	0	// Receive FIFO is not empty
		)
		RC = FALSE;
	else
		{
		// Acquire the bus - Select Client device
		// (should be release after completion of I/O operation)
		CS_Start();
		RC = TRUE;
		}
	//----------------------------------------------
	// Leave HMC/I2C CRITICAL SECTION
	//==============================================
  	RESTORE_CPU_IPL(current_cpu_ipl);
	//==============================================
	return RC;
	}
//------------------------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="static inline HMC_RC	_HMC_ConvertStream(...)">
//------------------------------------------------------------------
// HMC Data stream conversion
//==================================================================
static inline HMC_RC	_HMC_ConvertStream(	byte* Data,
											int* X, int* Y, int* Z)
	{
	//-----------------------------------------
	// Structure to "Unpack" the data
	//-----------------------------------------
	union
		{
		int		VInt;
		// Little Endian representation of "int"
		struct
			{
			byte	LSB;
			byte	MSB;
			};
		}	U;
	//-----------------------------------------------
	// Please NOTE: the six bytes provided in the
	// Buffer represent values of X, Z, and Y registers
	// of the magnetometer. As we use the right-handed
	// coordinate system with axis Z pointing down and
	// considering the orientation of the sensor on
	// the board, we make the following adjustments:
	//	Xres = -X;
	//	Zres = -Z;
	//	Yres =  Y;
	//-----------------------------------------------
	// Check for overflow condition
	//-----------------------------------------------
	if	(
		0xF0 == Data[0]
		||
		0xF0 == Data[2]
		||
		0xF0 == Data[4]
		)
	  return HMC_OWFL;
	//-----------------------------------------------
	U.MSB	= Data[0];
	U.LSB	= Data[1];
	(*X) = -U.VInt;			//	Xres = -X;
	//-----------------------------------------------
	U.MSB	= Data[2];
	U.LSB	= Data[3];
	(*Z) = -U.VInt;			//	Zres = -Z;
	//-----------------------------------------------
	U.MSB	= Data[4];
	U.LSB	= Data[5];
	(*Y) = U.VInt;			//	Yres =  Y;
	//-----------------------------------------------
	return	HMC_OK;
	}
//------------------------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="static inline void _HMC_NormHMCData(...)">
//------------------------------------------------------------------
// HMC Data stream normalization for Hard and Soft Iron
//==================================================================
static inline void	_HMC_NormHMCData(Vector* MData)
	{
	//-----------------------------------------------
	// Apply Hard Iron adjustment
	//-----------------------------------------------
	VectorSub(MData, &_HMC_HardIron, MData);
	//-----------------------------------------------
	// Apply Soft Iron adjustment
	//-----------------------------------------------
	float MX	= VectorDotProduct(&_HMC_SoftIron_X, MData);
	float MY	= VectorDotProduct(&_HMC_SoftIron_Y, MData);
	float MZ	= VectorDotProduct(&_HMC_SoftIron_Z, MData);
	VectorSet	(MX, MY, MZ, MData);
	//-----------------------------------------------
	return;
	}
//------------------------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
#endif	/* HMCSPI_INLINES_H */

