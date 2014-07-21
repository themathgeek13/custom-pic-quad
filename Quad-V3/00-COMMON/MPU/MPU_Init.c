#include "MPU\MPU_Local.h"
#include "I2C\I2C_Local.h"

//************************************************************
uint	MPUInit(byte RateDiv, byte DLPF,
				MPU_FS_SEL GS, MPU_AFS_SEL AS)
	{
	// MPU module depends on I2C for communication with the 
	// sensor, so we need to make sure that I2C is initialized...
	byte	IL = I2CGetIL();
	if (0 == IL)
		return I2CRC_NRDY;	// I2C Module is not initialized
	//---------------------------------------------------------
	if (_MPU_Init)
		return	MPU_OK;		// Avoid repeated initialization...
	_MPU_Init	= 1;
	//---------------------------------------------------------
	_MPU_IL	= IL;
	//---------------------------------------------------------
	// Configure INTx module associated with MPU 
	//---------------------------------------------------------
	#ifdef Use_MPU1
		MPU1_IE	= 0;		// Disable INTx Interrupt for configuration
		MPU1_IF	= 0;		// Clear INTx interrupt flag (if any)
		MPU1_IP	= _MPU_IL;	// Set INTx Interrupt Priority
		MPU1_EP	= 0;		// Trigger INTx on "raising edge"
	#endif
	#ifdef Use_MPU2
		MPU2_IE	= 0;		// Disable INTx Interrupt for configuration
		MPU2_IF	= 0;		// Clear INTx interrupt flag (if any)
		MPU2_IP	= _MPU_IL;	// Set INTx Interrupt Priority
		MPU2_EP	= 0;		// Trigger INTx on "raising edge"
	#endif

	//---------------------------------------------------------
	// Now we may configure pin associated with selected INTx
	//---------------------------------------------------------
	_MPUInitPinMap();
	//---------------------------------------------------------
	// Some of the functions of this component depends on Timer,
	// so we need to make sure that the Timer is initialized...
	//---------------------------------------------------------
	TMRInitDefault();	// Hopefully timer is already initialized
						// so this statement will be just "NOP"

	//=========================================================
	// <editor-fold defaultstate="collapsed" desc="Initialize MPUx_CB - MPU Library control block(s)">
	//=========================================================
	#ifdef Use_MPU1
		//-----------------------------------------------------
		// Values defined in MPU_Profile.h
		//-----------------------------------------------------
		MPU1_CB._MPU_Addr = MPU1_Addr;
		MPU1_CB._MPU_IDCx = MPU1_IDCx;
		//-----------------------------------------------------
		// Temperature offset to bring the sample to 0C
		MPU1_CB._MPU_Temp_OffsetTo0		= -12421;
		// Temp Sensitivity: Degree C per unit of LSB
		MPU1_CB._MPU_Temp_Sensitivity	= 0.00294117647;
		MPU1_CB._MPU_Gyro_Sensitivity	= 0.0;
		MPU1_CB._MPU_Accl_Sensitivity	= 0.0;
		//=====================================================
		// Gyro temperature/offset compensation
		//-----------------------------------------------------
		MPU1_CB._MPU_Gyro_BaseTemp		= 0.0;		// Measured
		//-----------------------------------------------------
		MPU1_CB._MPU_Gyro_XOffset		= 0.0;		// Calculated
		MPU1_CB._MPU_Gyro_XSlope		= 0.0;		//-0.79;	// Pre-defined
		//-----------------------------------------------------
		MPU1_CB._MPU_Gyro_YOffset		=  0.0;		// Calculated
		MPU1_CB._MPU_Gyro_YSlope		=  0.0;		//1.20;	// Pre-defined
		//-----------------------------------------------------
		MPU1_CB._MPU_Gyro_ZOffset		=  0.0;		// Calculated
		MPU1_CB._MPU_Gyro_ZSlope		= 0.0;		//-0.0964;	// Pre-defined
		//=====================================================
		// Accl temperature/offset compensation
		//=====================================================
		MPU1_CB._MPU_Accl_BaseTemp		=   25.0;
		//-----------------------------------------------------
		MPU1_CB._MPU_Accl_XOffset		=  0.0;		//-37.20;
		MPU1_CB._MPU_Accl_XSlope		=  0.0;		// -6.54;
		//-----------------------------------------------------
		MPU1_CB._MPU_Accl_YOffset		=  0.0;		//-72.00;
		MPU1_CB._MPU_Accl_YSlope		=  0.0;		//  9.47;
		//-----------------------------------------------------
		MPU1_CB._MPU_Accl_ZOffset		=  0.0;		//2131.00;
		MPU1_CB._MPU_Accl_ZSlope		=  0.0;		// 126.42;
		//=====================================================
		// Asynchronous read support
		//=====================================================
		MPU1_CB._MPU_Async	= 0;	// Asynchronous operation flag
		MPU1_CB._MPU_Ready	= 0;	// Flag indicating whether asynch-
									// ronous read data is ready
		//-----------------------------------------------------
		MPU1_CB._MPU_State	= 0;	// Step number in the asynchronous
									// read finite automata controller
		//-----------------------------------------------------
		// Asynchronous READ buffer control
		//-----------------------------------------------------
		MPU1_CB._MPU_BufPos	= 0;	// Position in MPU read buffer
		//=====================================================
	#endif
	#ifdef Use_MPU2
		//-----------------------------------------------------
		// Values defined in MPU_Profile.h
		//-----------------------------------------------------
		MPU2_CB._MPU_Addr = MPU2_Addr;
		MPU2_CB._MPU_IDCx = MPU2_IDCx;
		//-----------------------------------------------------
		// Temperature offset to bring the sample to 0C
		MPU2_CB._MPU_Temp_OffsetTo0		= -12421;
		// Temp Sensitivity: Degree C per unit of LSB
		MPU2_CB._MPU_Temp_Sensitivity	= 0.00294117647;
		MPU2_CB._MPU_Gyro_Sensitivity	= 0.0;
		MPU2_CB._MPU_Accl_Sensitivity	= 0.0;
		//=====================================================
		// Gyro temperature/offset compensation
		//-----------------------------------------------------
		MPU2_CB._MPU_Gyro_BaseTemp		= 0.0;		// Measured
		//-----------------------------------------------------
		MPU2_CB._MPU_Gyro_XOffset		= 0.0;		// Calculated
		MPU2_CB._MPU_Gyro_XSlope		= 0.0;		//-0.79;	// Pre-defined
		//-----------------------------------------------------
		MPU2_CB._MPU_Gyro_YOffset		=  0.0;		// Calculated
		MPU2_CB._MPU_Gyro_YSlope		=  0.0;		// 1.20;	// Pre-defined
		//-----------------------------------------------------
		MPU2_CB._MPU_Gyro_ZOffset		=  0.0;		// Calculated
		MPU2_CB._MPU_Gyro_ZSlope		=  0.0;		//-0.0964;	// Pre-defined
		//=====================================================
		// Accl temperature/offset compensation
		//=====================================================
		MPU2_CB._MPU_Accl_BaseTemp		=   25.0;
		//-----------------------------------------------------
		MPU2_CB._MPU_Accl_XOffset		=  0.0;		//-37.20;
		MPU2_CB._MPU_Accl_XSlope		=  0.0;		// -6.54;
		//-----------------------------------------------------
		MPU2_CB._MPU_Accl_YOffset		=  0.0;		//-72.00;
		MPU2_CB._MPU_Accl_YSlope		=  0.0;		//  9.47;
		//-----------------------------------------------------
		MPU2_CB._MPU_Accl_ZOffset		=  0.0;		//2131.00;
		MPU2_CB._MPU_Accl_ZSlope		=  0.0;		// 126.42;
		//=====================================================
		// Asynchronous read support
		//=====================================================
		MPU2_CB._MPU_Async	= 0;	// Asynchronous operation flag
		MPU2_CB._MPU_Ready	= 0;	// Flag indicating whether asynch-
									// ronous read data is ready
		//-----------------------------------------------------
		MPU2_CB._MPU_State	= 0;	// Step number in the asynchronous
									// read finite automata controller
		//-----------------------------------------------------
		// Asynchronous READ buffer control
		//-----------------------------------------------------
		MPU2_CB._MPU_BufPos	= 0;	// Position in MPU read buffer
		//=====================================================
	#endif
	//---------------------------------------------------------
	// </editor-fold>
	//=========================================================
	
	//---------------------------------------------------------
	// Now we should initialize the sensor...
	//---------------------------------------------------------
	uint	RC	= MPU_OK;
	#ifdef Use_MPU1
	if (MPU_OK != (RC = MPUReset(1, RateDiv, DLPF, GS, AS)))
		return RC;
	#endif
	#ifdef Use_MPU2
	if (MPU_OK != (RC = MPUReset(2, RateDiv, DLPF, GS, AS)))
		return RC;
	#endif

	//---------------------------------------------------------
	return RC;
	}



