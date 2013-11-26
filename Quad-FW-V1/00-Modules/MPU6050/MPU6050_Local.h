#include "TMR\TMR.h"
#include "I2C\I2C_Profile.h"

#include "MPU6050\MPU6050.h"

//==================================================================
#ifndef __MPU6050_Local_H
#define __MPU6050_Local_H
//==================================================================
extern volatile byte	_MPU_IL	; 	// MPU default interrupt level
extern volatile uint	_MPU_Init;	// Init flag
//==================================================================
extern const 	byte	_MPU_Addr;	// Sensor address on I2C bus
//==================================================================
extern volatile ulong	_MPU_Count;	// Sample count
//==================================================================
// Sensor data normalization values
//==================================================================
// Temperature offset to bring the sample in reference to 0C
extern const 	int			_MPU_Temp_OffsetTo0;
// Temp Sensitivity: Units per degree C
extern const 	float		_MPU_Temp_Sensitivity;
//==================================================================
// Gyro Sensitivity: Units per degree/sec (at 2000 deg/sec range)
extern const 	float		_MPU_Gyro_Sensitivity;
//------------------------------------------------------------------
// Gyro temperature/offset compensation to bring the sample in reference
// to 0 deg/sec (per axis)
//------------------------------------------------------------------
extern 	 		float		_MPU_Gyro_BaseTemp;	// Measured
//------------------------------------------------------------------
extern 	  		float		_MPU_Gyro_XOffset;	// Calculated
extern const  	float		_MPU_Gyro_XSlope;
//------------------------------------------------------------------
extern 	  		float		_MPU_Gyro_YOffset;	// Calculated
extern const  	float		_MPU_Gyro_YSlope;
//------------------------------------------------------------------
extern 	  		float		_MPU_Gyro_ZOffset;	// Calculated
extern const  	float		_MPU_Gyro_ZSlope;
//==================================================================
// Accl Sensitivity: G per units of LSB (at 2 G range)
extern const 	float		_MPU_Accl_Sensitivity;
// Accl temperature/offset compensation to bring the sample in reference
// to 0 G (per axis)
//------------------------------------------------------------------
extern const 	float		_MPU_Accl_BaseTemp; 
//------------------------------------------------------------------
extern const 	float		_MPU_Accl_XOffset;
extern const  	float		_MPU_Accl_XSlope;
//------------------------------------------------------------------
extern const 	float		_MPU_Accl_YOffset;
extern const  	float		_MPU_Accl_YSlope;
//------------------------------------------------------------------
extern const 	float		_MPU_Accl_ZOffset;
extern const  	float		_MPU_Accl_ZSlope;
//------------------------------------------------------------------


//-----------------------------------------------------
// Raw MPU Data Sample - data length increased from int
// (native to sensor) to long to accommodate accumulation
// in the ISR routine
//-----------------------------------------------------
typedef	struct
	{
	//-----------------------------------------------
	// Temperature
	//-----------------------------------------------
	long		Temp;
	//-----------------------------------------------
	// Accelerometer
	//-----------------------------------------------
	long		AX;
	long		AY;
	long		AZ;
	//-----------------------------------------------
	// Gyroscopes
	//-----------------------------------------------
	long		GX;
	long		GY;
	long		GZ;
	//-----------------------------------------------
	}	_MPURawData, *_pMPURawData;

//==================================================================
// Asynchronous read support
//==================================================================
extern volatile	uint	_MPU_Async;	// Asynchronous read in progress
									// flag
extern volatile	uint	_MPU_State;	// Step number in the asynchronous
									// read finite automata controller
//------------------------------------------------------------------
extern volatile	uint	_MPU_Ready;	// Flag indicating whether asynch-
									// ronous read data is ready
//------------------------------------------------------------------
// Asynchronous READ buffer control
//------------------------------------------------------------------
extern volatile uint	_MPU_BufPos;	// Position in MPU read buffer
extern 			byte	_MPU_Buffer[14];// MPU read buffer		
//------------------------------------------------------------------
// Asynchronous READ intermediate data storage
//------------------------------------------------------------------
extern  _MPURawData		_MPU_Sensor;
//------------------------------------------------------------------
// Asynchronous READ accumulated data storage
//------------------------------------------------------------------
extern  _MPURawData		_MPU_Sample;// Asynchronous sample...
//------------------------------------------------------------------
void	_MPUCallBack();
//==================================================================

//==================================================================
// Synchronous helper functions used by other synchronous APIs
//==================================================================
// Synchronous READ (internal)
//------------------------------------------------------------------
uint	_MPURead(	byte 	Register, 
					byte*	Buffer,
					uint  	BufLen	);
//------------------------------------------------------------------
// Synchronous WRITE (internal)
//------------------------------------------------------------------
uint	_MPUWrite(	byte	 Register, 
					byte*	 Buffer,
					uint	 BufLen );
//------------------------------------------------------------------
// Synchronous Read Raw Sample (internal)
//------------------------------------------------------------------
uint	_MPUReadRawData(_pMPURawData pRawData);
//==================================================================
#endif
