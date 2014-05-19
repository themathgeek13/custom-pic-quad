#include "MPU6050\MPU6050_Local.h"

//==================================================================
volatile byte		_MPU_IL		= 0; 	// MPU (INT1) interrupt level
volatile uint		_MPU_Init	= 0;	// Init flag
//==================================================================

// MPU6050 device address (assuming pin AD0 = 0):
const	byte		_MPU_Addr		= 0xD0; 	// 1101000-R/W
// NOTE: The address above is the "write" address - LSB is set to 0;
//		 The LSB will be set to "1" (changing address to 0xD1) in
//		 the I2C write routine.
//==================================================================
volatile ulong		_MPU_Count;			// Sample count
//==================================================================
// Sensor data normalization values
//==================================================================
// Temperature offset to bring the sample in reference to 0C
const 	int			_MPU_Temp_OffsetTo0		= -12421;
// Temp Sensitivity: Degree C per unit of LSB
const 	float		_MPU_Temp_Sensitivity	= 0.00294117647;
//==================================================================
// Gyro Sensitivity: Rad/sec per unit of LSB (at 2000 deg/sec range)
const 	float		_MPU_Gyro_Sensitivity	= 0.001064225153655;
//------------------------------------------------------------------
// Gyro temperature/offset compensation to bring the sample in reference
// to 0 deg/sec (per axis)
//------------------------------------------------------------------
	 	float		_MPU_Gyro_BaseTemp		=  0.0;		// Measured
//------------------------------------------------------------------
	  	float		_MPU_Gyro_XOffset		=  0.0;		// Calculated
const  	float		_MPU_Gyro_XSlope		= -0.79;
//------------------------------------------------------------------
	  	float		_MPU_Gyro_YOffset		=  0.0;		// Calculated
const  	float		_MPU_Gyro_YSlope		=  1.20;
//------------------------------------------------------------------
	  	float		_MPU_Gyro_ZOffset		=  0.0;		// Calculated
const  	float		_MPU_Gyro_ZSlope		= -0.0964; 
//==================================================================
// Accl Sensitivity: G per unit of LSB (at 2 G range)
const 	float		_MPU_Accl_Sensitivity	= 0.00006103515625;
// Accl temperature/offset compensation to bring the sample in reference
// to 0 G (per axis)
//------------------------------------------------------------------
const 	float		_MPU_Accl_BaseTemp		=   25.0; 
//------------------------------------------------------------------
const 	float		_MPU_Accl_XOffset		=  -37.20; 
const  	float		_MPU_Accl_XSlope		=   -6.54;
//------------------------------------------------------------------
const 	float		_MPU_Accl_YOffset		=  -72.00; 
const  	float		_MPU_Accl_YSlope		=    9.47; 
//------------------------------------------------------------------
	 	float		_MPU_Accl_ZOffset		=  2131.00;
const  	float		_MPU_Accl_ZSlope		=   126.42; 
//------------------------------------------------------------------

//==================================================================
// Asynchronous read support
//==================================================================
volatile uint		_MPU_Async;			// Asynchronous read in progress
										// flag
volatile uint		_MPU_State	= 0;	// Step number in the asynchronous
										// read finite automata controller
//------------------------------------------------------------------
volatile uint		_MPU_Ready	= 0;	// Flag indicating whether asynch-
										// ronous read data is ready
//------------------------------------------------------------------
// Asynchronous READ buffer control
//------------------------------------------------------------------
volatile uint		_MPU_BufPos	= 0;	// Position in MPU read buffer
		 byte		_MPU_Buffer[14];	// MPU read buffer		
//------------------------------------------------------------------
// Asynchronous READ intermediate data storage
//------------------------------------------------------------------
_MPURawData			_MPU_Sample;		// Asynchronous sample...
//------------------------------------------------------------------
_MPURawData			_MPU_Sensor;		// Sensor data
//==================================================================

