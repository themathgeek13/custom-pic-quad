#include "TMR\TMR.h"
#include "I2C\I2C.h"
//--------------------------------------
#include "MPU\MPU.h"
#include "MPU\MPU_Profile.h"
//==================================================================

//==================================================================
#ifndef __MPU_Local_H
#define __MPU_Local_H
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="MPU-6050 internal registers">
//------------------------------------------------------------------
// MPU-6050 internal registers' addresses
//==================================================================
// <editor-fold defaultstate="collapsed" desc="Self-Test registers">
#define MPU6050_SELF_TEST_X         0x0D   // R/W
#define MPU6050_SELF_TEST_Y         0x0E   // R/W
#define MPU6050_SELF_TEST_Z         0x0F   // R/W
#define MPU6050_SELF_TEST_A         0x10   // R/W
// </editor-fold>
//------------------------------------------------------------------
#define MPU6050_SMPLRT_DIV         0x19   // R/W
#define MPU6050_CONFIG             0x1A   // R/W
#define MPU6050_GYRO_CONFIG        0x1B   // R/W
#define MPU6050_ACCEL_CONFIG       0x1C   // R/W
#define MPU6050_FIFO_EN            0x23   // R/W
//------------------------------------------------------------------
// <editor-fold defaultstate="collapsed" desc="Master-Slave control">
#define MPU6050_I2C_MST_CTRL       0x24   // R/W
#define MPU6050_I2C_SLV0_ADDR      0x25   // R/W
#define MPU6050_I2C_SLV0_REG       0x26   // R/W
#define MPU6050_I2C_SLV0_CTRL      0x27   // R/W
#define MPU6050_I2C_SLV1_ADDR      0x28   // R/W
#define MPU6050_I2C_SLV1_REG       0x29   // R/W
#define MPU6050_I2C_SLV1_CTRL      0x2A   // R/W
#define MPU6050_I2C_SLV2_ADDR      0x2B   // R/W
#define MPU6050_I2C_SLV2_REG       0x2C   // R/W
#define MPU6050_I2C_SLV2_CTRL      0x2D   // R/W
#define MPU6050_I2C_SLV3_ADDR      0x2E   // R/W
#define MPU6050_I2C_SLV3_REG       0x2F   // R/W
#define MPU6050_I2C_SLV3_CTRL      0x30   // R/W
#define MPU6050_I2C_SLV4_ADDR      0x31   // R/W
#define MPU6050_I2C_SLV4_REG       0x32   // R/W
#define MPU6050_I2C_SLV4_DO        0x33   // R/W
#define MPU6050_I2C_SLV4_CTRL      0x34   // R/W
#define MPU6050_I2C_SLV4_DI        0x35   // R
#define MPU6050_I2C_MST_STATUS     0x36   // R
// </editor-fold>
//------------------------------------------------------------------
#define MPU6050_INT_PIN_CFG        0x37   // R/W
#define MPU6050_INT_ENABLE         0x38   // R/W
#define MPU6050_INT_STATUS         0x3A   // R
//------------------------------------------------------------------
// <editor-fold defaultstate="collapsed" desc="Sensor Data registers">
#define MPU6050_DATA_START		   0x3B   // R
#define MPU6050_ACCEL_XOUT_H       0x3B   // R
#define MPU6050_ACCEL_XOUT_L       0x3C   // R
#define MPU6050_ACCEL_YOUT_H       0x3D   // R
#define MPU6050_ACCEL_YOUT_L       0x3E   // R
#define MPU6050_ACCEL_ZOUT_H       0x3F   // R
#define MPU6050_ACCEL_ZOUT_L       0x40   // R
#define MPU6050_TEMP_OUT_H         0x41   // R
#define MPU6050_TEMP_OUT_L         0x42   // R
#define MPU6050_GYRO_XOUT_H        0x43   // R
#define MPU6050_GYRO_XOUT_L        0x44   // R
#define MPU6050_GYRO_YOUT_H        0x45   // R
#define MPU6050_GYRO_YOUT_L        0x46   // R
#define MPU6050_GYRO_ZOUT_H        0x47   // R
#define MPU6050_GYRO_ZOUT_L        0x48   // R
// </editor-fold>
//------------------------------------------------------------------
// <editor-fold defaultstate="collapsed" desc="External Sensor Data registers">
#define MPU6050_EXT_SENS_DATA_00   0x49   // R
#define MPU6050_EXT_SENS_DATA_01   0x4A   // R
#define MPU6050_EXT_SENS_DATA_02   0x4B   // R
#define MPU6050_EXT_SENS_DATA_03   0x4C   // R
#define MPU6050_EXT_SENS_DATA_04   0x4D   // R
#define MPU6050_EXT_SENS_DATA_05   0x4E   // R
#define MPU6050_EXT_SENS_DATA_06   0x4F   // R
#define MPU6050_EXT_SENS_DATA_07   0x50   // R
#define MPU6050_EXT_SENS_DATA_08   0x51   // R
#define MPU6050_EXT_SENS_DATA_09   0x52   // R
#define MPU6050_EXT_SENS_DATA_10   0x53   // R
#define MPU6050_EXT_SENS_DATA_11   0x54   // R
#define MPU6050_EXT_SENS_DATA_12   0x55   // R
#define MPU6050_EXT_SENS_DATA_13   0x56   // R
#define MPU6050_EXT_SENS_DATA_14   0x57   // R
#define MPU6050_EXT_SENS_DATA_15   0x58   // R
#define MPU6050_EXT_SENS_DATA_16   0x59   // R
#define MPU6050_EXT_SENS_DATA_17   0x5A   // R
#define MPU6050_EXT_SENS_DATA_18   0x5B   // R
#define MPU6050_EXT_SENS_DATA_19   0x5C   // R
#define MPU6050_EXT_SENS_DATA_20   0x5D   // R
#define MPU6050_EXT_SENS_DATA_21   0x5E   // R
#define MPU6050_EXT_SENS_DATA_22   0x5F   // R
#define MPU6050_EXT_SENS_DATA_23   0x60   // R
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="Master-Slave control">
#define MPU6050_I2C_SLV0_DO        0x63   // R/W
#define MPU6050_I2C_SLV1_DO        0x64   // R/W
#define MPU6050_I2C_SLV2_DO        0x65   // R/W
#define MPU6050_I2C_SLV3_DO        0x66   // R/W
#define MPU6050_I2C_MST_DELAY_CTRL 0x67   // R/W
// </editor-fold>
//------------------------------------------------------------------
#define MPU6050_SIGNAL_PATH_RESET  0x68   // R/W
#define MPU6050_USER_CTRL          0x6A   // R/W
#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_PWR_MGMT_2         0x6C   // R/W
//------------------------------------------------------------------
// <editor-fold defaultstate="collapsed" desc="FIFO Control">
//------------------------------------------------------------------
#define MPU6050_FIFO_COUNTH        0x72   // R/W
#define MPU6050_FIFO_COUNTL        0x73   // R/W
#define MPU6050_FIFO_R_W           0x74   // R/W
//------------------------------------------------------------------
// </editor-fold>
//------------------------------------------------------------------
#define MPU6050_WHO_AM_I           0x75   // R
//------------------------------------------------------------------
// <editor-fold defaultstate="collapsed" desc="Registers not defined in the Register Map document">
#define MPU6050_AUX_VDDIO          0x01   // R/W
#define MPU6050_FF_THR             0x1D   // R/W
#define MPU6050_FF_DUR             0x1E   // R/W
#define MPU6050_MOT_THR            0x1F   // R/W
#define MPU6050_MOT_DUR            0x20   // R/W
#define MPU6050_ZRMOT_THR          0x21   // R/W
#define MPU6050_ZRMOT_DUR          0x22   // R/W
#define MPU6050_MOT_DETECT_STATUS  0x61   // R
#define MPU6050_MOT_DETECT_CTRL    0x69   // R/W
// </editor-fold>
//------------------------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
// Variables shared (across MPU modules) - set in MPUInit
//==================================================================
extern byte	_MPU_IL	;		// MPU default interrupt level
extern uint	_MPU_Init;		// Init flag
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="Raw MPU Data Sample">
//------------------------------------------------------------------
// Raw MPU Data Sample - data length increased from int
// (native to sensor) to long to accommodate accumulation
// in the ISR routine
//------------------------------------------------------------------
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
	}	_MPURawData;
//------------------------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="MPU_CB - MPU Library control block">
//==================================================================
// Prototype for MPU Library control block
//==================================================================
typedef struct
	{
	//==============================================================
	byte		_MPU_IDCx;			// 1-based index of associated 
									// I2C bus
	byte		_MPU_Addr;			// Sensor address on I2C bus

	//==============================================================
	// <editor-fold defaultstate="collapsed" desc="Sensor data normalization values">
	//--------------------------------------------------------------
	// Sensor data normalization values
	//==============================================================
	// Temperature offset to bring the sample in reference to 0C
	int			_MPU_Temp_OffsetTo0;
	//--------------------------------------------------------------
	// Temp Sensitivity: Units per degree C
	//--------------------------------------------------------------
	float		_MPU_Temp_Sensitivity;
	//--------------------------------------------------------------
	// Gyro Sensitivity: Calculated based upon GS parameter of RESET
	// function (converted to rad/sec)
	//--------------------------------------------------------------
	float		_MPU_Gyro_Sensitivity;
	//--------------------------------------------------------------
	// Accl Sensitivity: Calculated based upon AS parameter of RESET
	//--------------------------------------------------------------
	float		_MPU_Accl_Sensitivity;
	//--------------------------------------------------------------
	// </editor-fold>
	//==============================================================

	//==============================================================
	// <editor-fold defaultstate="collapsed" desc="Temperature compensation parameters">
	//==============================================================
	// Gyro temperature/offset compensation to bring the sample in
	// reference to 0 deg/sec (per axis)
	//--------------------------------------------------------------
	float		_MPU_Gyro_BaseTemp;			// Measured
	//--------------------------------------------------------------
	float		_MPU_Gyro_XOffset;			// Calculated
	float		_MPU_Gyro_XSlope;			// Pre-defined
	//--------------------------------------------------------------
	float		_MPU_Gyro_YOffset;			// Calculated
	float		_MPU_Gyro_YSlope;			// Pre-defined
	//--------------------------------------------------------------
	float		_MPU_Gyro_ZOffset;			// Calculated
	float		_MPU_Gyro_ZSlope;			// Pre-defined
	//==============================================================
	// Accl temperature/offset compensation to bring the sample in
	// reference to 0 G (per axis)
	//==============================================================
	float		_MPU_Accl_BaseTemp;
	//--------------------------------------------------------------
	float		_MPU_Accl_XOffset;
	float		_MPU_Accl_XSlope;
	//--------------------------------------------------------------
	float		_MPU_Accl_YOffset;
	float		_MPU_Accl_YSlope;
	//--------------------------------------------------------------
	float		_MPU_Accl_ZOffset;	// Adjusted by IMU
	float		_MPU_Accl_ZSlope;
	//==============================================================
	// </editor-fold>
	//==============================================================

	//==============================================================
	// <editor-fold defaultstate="collapsed" desc="Asynchronous read control variables">
	//==============================================================
	// Asynchronous read control variables
	//==============================================================
	volatile	uint	_MPU_Async;		// Asynchronous operation flag
	volatile	uint	_MPU_Ready;		// Flag indicating whether asynch-
										// ronous read data is ready
	//--------------------------------------------------------------
	volatile	uint	_MPU_State;		// Step number in the asynchronous
										// read finite automata controller
	//--------------------------------------------------------------
	// Asynchronous READ buffer control
	//--------------------------------------------------------------
	volatile uint	_MPU_BufPos;		// Position in MPU read buffer
	volatile byte	_MPU_Buffer[14];	// MPU read buffer
	//--------------------------------------------------------------
	// Asynchronous READ intermediate data storage
	//--------------------------------------------------------------
	_MPURawData		_MPU_Sensor;
	//--------------------------------------------------------------
	// Asynchronous READ accumulated data storage
	//--------------------------------------------------------------
	_MPURawData		_MPU_Sample;// Asynchronous sample...
	//==============================================================
	// </editor-fold>
	//==============================================================
	} MPU_CB;
//------------------------------------------------------------------
#ifdef Use_MPU1
	extern	MPU_CB		MPU1_CB;
#endif
#ifdef Use_MPU2
	extern	MPU_CB		MPU2_CB;
#endif
//------------------------------------------------------------------
// Control Block Helper Functions
//==================================================================
static inline MPU_CB* MPUpCB(uint CB_ID)
	{
	switch (CB_ID)
		{
		case 1:
			#ifdef Use_MPU1
			return &MPU1_CB;
			#else
			return NULL;
			#endif
		case 2:
			#ifdef Use_MPU2
			return &MPU2_CB;
			#else
			return NULL;
			#endif
		default:
			return NULL;
		}
	}
//------------------------------------------------------------------
// </editor-fold>
//==================================================================

void	_MPUCallBack(uint			ClientParam,
					 I2C_CONBITS*	pCON,
					 I2C_STATBITS*	pSTAT,
					 vuint*			pTRN,
					 vuint*			pRCV);

//==================================================================

//==================================================================
// Synchronous helper functions used by other synchronous APIs
//==================================================================
// Synchronous READ (internal)
//------------------------------------------------------------------
uint	_MPURead(	MPU_CB*	pCB,
					byte 	Register,
					byte*	Buffer,
					uint  	BufLen	);
//------------------------------------------------------------------
// Synchronous WRITE (internal)
//------------------------------------------------------------------
uint	_MPUWrite(	MPU_CB*	pCB,
					byte	 Register,
					byte*	 Buffer,
					uint	 BufLen );
//------------------------------------------------------------------
// Synchronous Read Raw Sample (internal)
//------------------------------------------------------------------
uint	_MPUReadRawData(MPU_CB*	pCB,
						_MPURawData* pRawData);
//------------------------------------------------------------------
// Synchronous Gyro Calibration routine (internal)
//------------------------------------------------------------------
uint	_MPUCalibrateSync(MPU_CB*	pCB);
//==================================================================

//==================================================================
// Asynchronous helper functions used by other asynchronous APIs
//==================================================================
// Asynchronous Gyro Calibration routine (internal)
//------------------------------------------------------------------
uint	_MPUCalibrateAsync(MPU_CB*	pCB);
//==================================================================

#endif		// __MPU_Local_H
