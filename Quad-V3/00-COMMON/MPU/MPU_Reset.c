#include "MPU\MPU_Local.h"


//=============================================================
uint	MPUReset(uint MPUx, byte RateDiv, byte DLPF,
				 MPU_FS_SEL GS, MPU_AFS_SEL AS)
{
	if (0 == _MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (pCB->_MPU_Async)
		return MPU_ABSY;		// Asynchronous operation in progress...
	//*********************************************************
	uint		RC;	
	byte		RegValue;
	ulong		Alarm;
	//*********************************************************
	// First, for consistency, let's RESET MPU - all regs are
	// set to 0x00, except the Reg6B=0x40 (sleep)
	//---------------------------------------------------------
	RC	= MPUSetByte(MPUx, MPU6050_PWR_MGMT_1, 0x80);
	if (RC) return RC;	// Failure...
	// RESET bit is set to 0 by HW at the end of RESET
	// Wait until RESET completes
	Alarm	= TMRSetAlarm(10);	// 10 msec should be enough for reset
	do 
		{
		TMRDelayTicks(1);	// Short Delay
		//--------------------------------
		RC = MPUGetByte(MPUx, MPU6050_PWR_MGMT_1, &RegValue);
		if (RC) return RC;	// Failure...
		//--------------------------------
		if (TMRCheckAlarm(Alarm))	// Time expired without MPU completing RESET
			return MPU_FAIL;
		}
	while (0x40 != RegValue);
	//---------------------------------------------------------
	// Second, we have to take MPU out of "sleep" and configure
	// to use PLL with Z axis (fastest!) gyroscope reference
	//---------------------------------------------------------
	RC	= MPUSetByte(MPUx, MPU6050_PWR_MGMT_1, 0x03);
	if (RC) return RC;	// Failure...
	// Verify PWR_MGMT_1
	RC = MPUGetByte(MPUx, MPU6050_PWR_MGMT_1, &RegValue);
	if (RC) return RC;	// Failure...
	if (0x03 != RegValue) return MPU_FAIL; // Initialization failed
	//---------------------------------------------------------
	// Third, we have to take ALL sensors out of STANDBY
	// Should be by-default after RESET, but...
	//---------------------------------------------------------
	RC	= MPUSetByte(MPUx, MPU6050_PWR_MGMT_2, 0x00);
	if (RC) return RC;	// Failure...
	// Verify PWR_MGMT_2
	RC = MPUGetByte(MPUx, MPU6050_PWR_MGMT_2, &RegValue);
	if (RC) return RC;	// Failure...
	if (0x00 != RegValue) return MPU_FAIL; // Initialization failed

	//=========================================================
	// Now we may proceed configuring Gyro and Accelerometer
	//=========================================================
	// Digital low-pass filter: when DLPF = 0 - disabled,
	// when DLPF = 1...6 - enabled, DLPF = 7 - reserved
	// (DLPF occupies the lowest 3 bits of the register)
	if (DLPF > 6)	DLPF = 6;	// Highest allowed value
	if (DLPF < 1)	DLPF = 1;	// Lowest allowed value (to keep
								// Gyro and Acc rates in sync)
	RC	= MPUSetByte(MPUx, MPU6050_CONFIG, DLPF);
	if (RC) return RC;	// Failure...
	// Verify written value
	RC = MPUGetByte(MPUx, MPU6050_CONFIG, &RegValue);
	if (RC) return RC;	// Failure...
	if (DLPF != RegValue) return MPU_FAIL; // Initialization failed
	//=========================================================
	// Sample Rate = Gyroscope Output Rate / (1 + RateDiv) where
	// Gyroscope Output Rate = 1kHz when the DLPF is enabled
	// ( 1 <= DLPF <= 6)
	RC	= MPUSetByte(MPUx, MPU6050_SMPLRT_DIV, RateDiv);
	if (RC) return RC;	// Failure...
	// Verify written value
	RC = MPUGetByte(MPUx, MPU6050_SMPLRT_DIV, &RegValue);
	if (RC) return RC;	// Failure...
	if (RateDiv != RegValue) return MPU_FAIL; // Initialization failed
	//=========================================================
	// Gyro configuration:
	// XG_ST (selft-test)		0
	// YG_ST (selft-test)		0
	// ZG_ST (selft-test)		0
	// FS_SEL[1:0]
	//					00	-  250 deg/sec
	//					01	-  500 deg/sec
	//					10	- 1000 deg/sec
	//					11	- 2000 deg/sec
	// Reserver [2:0]			000
	switch (GS)
		{
		case 	MPU_GYRO_250ds:
			pCB->_MPU_Gyro_Sensitivity = 0.00013323124;
			RegValue = 0x00;
			break;
		case 	MPU_GYRO_500ds:
			pCB->_MPU_Gyro_Sensitivity = 0.00026646248;
			RegValue = 0x01;
			break;
		case 	MPU_GYRO_1000ds:
			pCB->_MPU_Gyro_Sensitivity = 0.00053211257;
			RegValue = 0x02;
			break;
		case 	MPU_GYRO_2000ds:
		default:
			pCB->_MPU_Gyro_Sensitivity = 0.0010642251;
			RegValue = 0x03;
			break;
		}
	RegValue *= 8;	// Place sensitivity bits into proper position
	RC	= MPUSetByte(MPUx, MPU6050_GYRO_CONFIG, RegValue);
	if (RC) return RC;	// Failure...
	//=========================================================
	// ACC configuration:
	// XA_ST (selft-test)		0
	// YA_ST (selft-test)		0
	// ZA_ST (selft-test)		0
	// AFS_SEL[1:0]
	//					00	-  2g
	//					01	-  4g
	//					10	-  8g
	//					11	- 16g
	// Reserver [2:0]			000
	switch (AS)
		{
		case 	MPU_ACC_2g:
			pCB->_MPU_Accl_Sensitivity = 0.000061035156;
			RegValue = 0x00;
			break;
		case 	MPU_ACC_4g:
			pCB->_MPU_Accl_Sensitivity = 0.00012207031;
			RegValue = 0x01;
			break;
		case 	MPU_ACC_8g:
			pCB->_MPU_Accl_Sensitivity = 0.00024414062;
			RegValue = 0x02;
			break;
		case 	MPU_ACC_16g:
		default:
			pCB->_MPU_Accl_Sensitivity = 0.00048828125;
			RegValue = 0x03;
			break;
		}
	RegValue *= 8;	// Place sensitivity bits into proper position
	RC	= MPUSetByte(MPUx, MPU6050_ACCEL_CONFIG, RegValue);
	if (RC) return RC;	// Failure...
	//---------------------------------------------------------
	// Now that sensors are configured, we may proceed to
	// DISABLE FIFO and I2C Master, and RESET sensors'
	// Signal Path and respective registers
	//---------------------------------------------------------
	RC	= MPUSetByte(MPUx, MPU6050_USER_CTRL, 0x01);
	if (RC) return RC;	// Failure...
	// Sensors' RESET bits are returned to 0 by HW at the end of
	// RESET - let's wait until RESET completes
	// Wait until RESET completes
	Alarm	= TMRSetAlarm(10);	// 10 msec should be enough for reset
	do
		{
		TMRDelayTicks(1);	// Short Delay
		//--------------------------------
		RC = MPUGetByte(MPUx, MPU6050_USER_CTRL, &RegValue);
		if (RC) return RC;	// Failure...
		//--------------------------------
		if (TMRCheckAlarm(Alarm))	// Time expired without MPU completing RESET
			return MPU_FAIL;
		}
	while (0x00 != RegValue);

	//=========================================================
	// Now we may proceed with configuring interrupts
	//=========================================================
	// Interrupt control register
	//---------------------------------------------
	// INT Active High		(0)
	// INT push-pull		(0)
	// INT pulse 50 usec	(0)
	// Any READ clears INT	(1)
	//---------------------
	// FSYNC disabled [3:2]	(0)
	//---------------------
	// I2C_BYPAS_EN			(0)
	// CLKOUT diabled		(0)
	//---------------------------------------------
	RC	= MPUSetByte(MPUx, MPU6050_INT_PIN_CFG, 0x10);
	if (RC) return RC;	// Failure...
	//=========================================================
	// Enable interrupts: Only DATA_RDY_EN
	RC	= MPUSetByte(MPUx, MPU6050_INT_ENABLE, 0x01);
	if (RC) return RC;	// Failure...
	//=========================================================
	//Clear READY status (if any) by reading STATUS register
	RC	= MPUGetByte(MPUx, MPU6050_INT_STATUS, &RegValue);
	if (RC) return RC;	// Failure...
	//*********************************************************
	return MPU_OK;
	}
//=============================================================

//=============================================================
uint	MPUCalibrate(uint MPUx)
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	MPU_CB*		pCB = MPUpCB(MPUx);
	if (NULL == pCB)	return MPU_NOTA;	// Should never happened!
	//------------------------------------------------------------------
	if (pCB->_MPU_Async)
		return _MPUCalibrateAsync(pCB);
	else
		return _MPUCalibrateSync(pCB);
	//-----------------------
	}




