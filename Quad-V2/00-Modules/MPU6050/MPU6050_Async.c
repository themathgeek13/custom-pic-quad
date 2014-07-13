#include "MPU6050\MPU6050_Local.h"

//-------------------------------------------------------
// MPU6050 Asynchronous Read operation is closely linked with
// the operation of the I2C module, thus we need to bring
// in the definition of some internal data structures.
//-------------------------------------------------------

// Forward declaration...
uint	_MPUAsyncRead(MPUData* pSample);

//*************************************************************
uint		MPUAsyncStart()
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	if (1 == _MPU_Async)
		return MPU_OK;			// Already started...
	//---------------------------------------------------------
	_MPU_Async	= 1;		// Set Asynchronous READ flag
	//=========================================================
	// Enable INT1 interrupts
	//---------------------------------------------------------							
	_INT1IF = 0;			// Clear the INT1 interrupt flag
	I2CRegisterSubscr(1);	// Enable INT1 interrupt and re-
							// gister with I2C module- when 
							// MPU6050 has sample, the 
							// interrupt will be triggered
	//=========================================================
	return MPU_OK;
	}
//*************************************************************


//*************************************************************
uint	MPUAsyncStop()
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//---------------------------------------------------------
	if (0 == _MPU_Async)
		return MPU_OK;			// Async is not active...
	//=====================================================
	// Disable ASYNC driver - INT1
	//=====================================================
	I2CDeRegisterSubscr(1);	// Disable and deregister
							// INT1 interrupt
	_INT1IF = 0;			// Clear the INT1 interrupt flag
	//=========================================================
	// Clear ASYNC flag
	//=========================================================
	_MPU_Async	= 0;		// Asynchronous read not active...
	//---------------------------------------------------------
	_MPU_Ready	= 0;		// Discard async sample
	//---------------------------------------------------------
	return MPU_OK;			
	}
//*************************************************************


//*************************************************************
uint	MPUAsyncRead(MPUData* pSample)
	{
	if (0 == _MPU_Async)
		return MPU_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	return _MPUAsyncRead(pSample);
	}
//*************************************************************

//*************************************************************
uint	MPUAsyncReadIfReady(MPUData* pSample)
	{
	if (0 == _MPU_Async)
		return MPU_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	if (0 == _MPU_Ready)
		return MPU_NRDY;
	//--------------------------------------------------
	return _MPUAsyncRead(pSample);
	}
//*************************************************************

//*************************************************************
uint	MPUAsyncReadWhenReady(MPUData* pSample)
	{
	if (0 == _MPU_Async)
		return MPU_NACT;			// Asynchronous read not active...
	//--------------------------------------------------
	while (0 == _MPU_Ready); 		// Wait until READY
	//------------------------
	return _MPUAsyncRead(pSample);
	}
//*************************************************************

//*************************************************************
uint	_MPUAsyncRead(MPUData* pSample)
	{
	//----------------------------------------------
	uint		Ready_Cnt;
	_MPURawData RawData;
	//----------------------------------------------
	int 		current_cpu_ipl;
	//----------------------------------------------

	//==============================================
	// Enter MPU/I2C CRITICAL SECTION
	//----------------------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _MPU_IL);  /* disable interrupts */
	//-----------------------------------------------
	pSample->Count	= _MPU_Count;
	//---------------------------------
	RawData.Temp 	= _MPU_Sample.Temp;
	//---------------------------------
	RawData.AX		= _MPU_Sample.AX;
	RawData.AY		= _MPU_Sample.AY;
	RawData.AZ		= _MPU_Sample.AZ;
	//---------------------------------
	RawData.GX		= _MPU_Sample.GX;
	RawData.GY		= _MPU_Sample.GY;
	RawData.GZ		= _MPU_Sample.GZ;
	//-----------------------------------------------
	Ready_Cnt		= _MPU_Ready;
	//-----------------------------------------------
	_MPU_Ready 		= 0;		// Sample consumed...
	//----------------------------------------------
	// Leave MPU/I2C CRITICAL SECTION
	//==============================================
  	RESTORE_CPU_IPL(current_cpu_ipl);

	//==============================================
	// Set sample timestamp
	//----------------------------------------------
	pSample->TS	= TMRGetTS();
	//==============================================
	float	TDev;
	//----------------------------------------------
	// Adjust Sample Weight to account for multiple samples
	//----------------------------------------------
	float 	Weight;
	if (Ready_Cnt > 1)
		Weight = 1.0/(float)Ready_Cnt;
	else
		Weight = 1.0;
	//----------------------------------------------
	// Process collected sample
	//----------------------------------------------
	// Temperature (C) (will be used in subsequent
	// temperature compensation calculation)
	//-----------------------------------------------
	pSample->Temp = (Weight * RawData.Temp - _MPU_Temp_OffsetTo0) * _MPU_Temp_Sensitivity;
	//-----------------------------------------------
	// Acceleration (G)
	//-----------------------------------------------
	TDev	= pSample->Temp - _MPU_Accl_BaseTemp;
	//-----------------------------------------------
	VectorSet	(
				(Weight * RawData.AX - (_MPU_Accl_XOffset + _MPU_Accl_XSlope*TDev)) * _MPU_Accl_Sensitivity,
				(Weight * RawData.AY - (_MPU_Accl_YOffset + _MPU_Accl_YSlope*TDev)) * _MPU_Accl_Sensitivity,
				(Weight * RawData.AZ - (_MPU_Accl_ZOffset + _MPU_Accl_ZSlope*TDev)) * _MPU_Accl_Sensitivity,
				&pSample->A
				);
	//-----------------------------------------------
	// Gyroscopes (Rad/sec)
	//-----------------------------------------------
	TDev	= pSample->Temp - _MPU_Gyro_BaseTemp;
	//-----------------------------------------------
	VectorSet	(
				(Weight * RawData.GX - (_MPU_Gyro_XOffset + _MPU_Gyro_XSlope*TDev)) * _MPU_Gyro_Sensitivity,
				(Weight * RawData.GY - (_MPU_Gyro_YOffset + _MPU_Gyro_YSlope*TDev)) * _MPU_Gyro_Sensitivity,
				(Weight * RawData.GZ - (_MPU_Gyro_ZOffset + _MPU_Gyro_ZSlope*TDev)) * _MPU_Gyro_Sensitivity,
				&pSample->G
				);
	//-----------------------------------------------
	return MPU_OK; 			// The return code was OK	
	}
//*************************************************************

//*************************************************************
uint	MPUAsyncAdjustAccZBase(float Incl)
	{
	if (0 == _MPU_Async)
		return MPU_NACT;	// Asynchronous read not active...
	//--------------------------------------------------
	TMRDelay(2000); 		// Wait 2,000 msec (2 second) to
							// accumulate in the buffer enough
							// samples for for solid averaging
	//----------------------------------------------
	uint		Ready_Cnt;
	_MPURawData RawData;
	//----------------------------------------------
	int 		current_cpu_ipl;
	//----------------------------------------------

	//==============================================
	// Enter MPU/I2C CRITICAL SECTION
	//----------------------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _MPU_IL);  /* disable interrupts */
	//-----------------------------------------------
	RawData.Temp 	= _MPU_Sample.Temp;
	//---------------------------------
	RawData.AX		= _MPU_Sample.AX;
	RawData.AY		= _MPU_Sample.AY;
	RawData.AZ		= _MPU_Sample.AZ;
	//---------------------------------
	RawData.GX		= _MPU_Sample.GX;
	RawData.GY		= _MPU_Sample.GY;
	RawData.GZ		= _MPU_Sample.GZ;
	//-----------------------------------------------
	Ready_Cnt		= _MPU_Ready;
	//-----------------------------------------------
	_MPU_Ready 		= 0;		// Sample consumed...
	//----------------------------------------------
	// Leave MPU/I2C CRITICAL SECTION
	//==============================================
  	RESTORE_CPU_IPL(current_cpu_ipl);

	//==============================================
	// Adjust Sample Weight to account for multiple samples
	//----------------------------------------------
	float 	Weight;
	if (Ready_Cnt > 1)
		Weight = 1.0/(float)Ready_Cnt;
	else
		Weight = 1.0;
	//----------------------------------------------
	// Process collected sample
	//----------------------------------------------
	// Temperature (C) (will be used in subsequent
	// temperature compensation calculation)
	//-----------------------------------------------
	float	Temp = (Weight * RawData.Temp - _MPU_Temp_OffsetTo0) * _MPU_Temp_Sensitivity;
	//-----------------------------------------------
	// Acceleration (G)
	//-----------------------------------------------
	float	TDev	= Temp - _MPU_Accl_BaseTemp;
	//-----------------------------------------------
//	AccZBase = (Weight * RawData.AZ - _MPU_Accl_ZOffset - _MPU_Accl_ZSlope*TDev) * _MPU_Accl_Sensitivity;

	// NOTE: Incl is the cosine of the angle between Earth gravity 
	// ( -1G given given Z-axis orientation to be "down"), thus
	// Expected AccZ => -Incl; AccZ should appear on the right side
	// with the "-" sign and as two "-" becomes "+" we can use Incl
	// directly in the formula below
	_MPU_Accl_ZOffset  = Incl/_MPU_Accl_Sensitivity + Weight * RawData.AZ - _MPU_Accl_ZSlope*TDev;

	//-----------------------------------------------
	return MPU_OK; 			// The return code was OK	
	}
//*************************************************************

//=============================================================
uint	_MPUCalibrateAsync()
	{
	if (!_MPU_Init)
		return MPU_NOTINIT;		// Not initialized...
	//-----------------------
	if (0 == _MPU_Async)
		return MPU_NACT;		// Asynchronous read not active...

	//=========================================================
	// Local Variables
	//---------------------------------------------------------
	ulong Alarm	= TMRSetAlarm(2000);	// Set Alarm time 2 sec
										// into the future.
	//---------------------------------------------------------
	uint		Ready_Cnt;
	_MPURawData RawData;
	//----------------------------------------------
	int 		current_cpu_ipl;
	//=========================================================

	//=========================================================
	// Reset  Gyro offsets...
	//---------------------------------------------------------
	_MPU_Gyro_XOffset		= 0;
	_MPU_Gyro_YOffset		= 0;
	_MPU_Gyro_ZOffset		= 0;
	//---------------------------------------------------------
	// To collect averages we would like to "watch" MPU for at
	// least 2 seconds; number of samples will be variable
	// depending on the value of RateDiv
	//---------------------------------------------------------
	TMRWaitAlarm(Alarm);
	//---------------------------------------------------------

	//=========================================================
	// Enter MPU/I2C CRITICAL SECTION
	//---------------------------------------------------------
  	SET_AND_SAVE_CPU_IPL(current_cpu_ipl, _MPU_IL);  /* disable interrupts */
	//---------------------------------------------------------
	RawData.Temp 	= _MPU_Sample.Temp;
	//---------------------------------
	RawData.AX		= _MPU_Sample.AX;
	RawData.AY		= _MPU_Sample.AY;
	RawData.AZ		= _MPU_Sample.AZ;
	//---------------------------------
	RawData.GX		= _MPU_Sample.GX;
	RawData.GY		= _MPU_Sample.GY;
	RawData.GZ		= _MPU_Sample.GZ;
	//---------------------------------------------------------
	Ready_Cnt		= _MPU_Ready;
	//---------------------------------------------------------
	_MPU_Ready 		= 0;		// Sample consumed...
	//---------------------------------------------------------
	// Leave MPU/I2C CRITICAL SECTION
	//=========================================================
  	RESTORE_CPU_IPL(current_cpu_ipl);
	//=========================================================

	//=========================================================
	// Adjust Sample Weight to account for multiple samples
	//---------------------------------------------------------
	float 	Weight;
	if (Ready_Cnt > 1)
		Weight = 1.0/(float)Ready_Cnt;
	else
		Weight = 1.0;
	//=========================================================

	//=========================================================
	// Process collected sample
	//---------------------------------------------------------
	// Gyro offset is calculated in LSB units
	//---------------------------------------
	_MPU_Gyro_XOffset	= (float)RawData.GX * Weight;
	_MPU_Gyro_YOffset	= (float)RawData.GY * Weight;
	_MPU_Gyro_ZOffset	= (float)RawData.GZ * Weight;
	//---------------------------------------
	// Base temperature converted to degrees C
	//---------------------------------------
	_MPU_Gyro_BaseTemp	= ((float)RawData.Temp * Weight - _MPU_Temp_OffsetTo0)
						  * _MPU_Temp_Sensitivity;
	//*********************************************************
	return MPU_OK;
	}



