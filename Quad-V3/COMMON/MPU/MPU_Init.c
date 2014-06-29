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
	MPU_IE	= 0;		// Disable INTx Interrupt for configuration
	MPU_IF	= 0;		// Clear INTx interrupt flag (if any)
	MPU_IP	= _MPU_IL;	// Set INTx Interrupt Priority
	MPU_EP	= 0;		// Trigger INTx on "raising edge"
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
	//---------------------------------------------------------
	// Now we should initialize the sensor...
	//---------------------------------------------------------
	uint	RC	= MPU_OK;
	RC = MPUReset(RateDiv, DLPF, GS, AS);
	//---------------------------------------------------------
	return RC;
	}



