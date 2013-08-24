#include "MPU6050\MPU6050_Local.h"
#include "I2C\I2C_Local.h"

//************************************************************
uint	MPUInit(byte RateDiv, byte DLPF)	
	{
	// MPU module depends on I2C for communication with the 
	// sensor, so we need to make sure that I2C is initialized...
	byte	IL = I2CGetIL();
	if (0 == IL)
		return I2C_NRDY;	// I2C Module is not initialized
	//---------------------------------------------------------
	if (_MPU_Init)
		return	MPU_OK;		// Avoid repeated initialization...
	_MPU_Init	= 1;
	//---------------------------------------------------------
	_MPU_IL	= IL;
	//---------------------------------------------------------
	// For INT1 we will use RP19/RC3 pin
	//---------------------------------------------------------
	_INT1IE	= 0;		// Disable INT1 Interrupt for configuration
	_INT1IF	= 0;		// Clear INT1 interrupt flag (if any)
	_INT1EP	= 0;		// Trigger INT1 on "raising edge"
	_INT1IP	= _MPU_IL;	// Set INT1 Interrupt Priority
	// Now we may configure RC3 as Input and map RP19 to INT1
	_TRISC3 = 1;	// Set RRC3 as Input;
	_INT1R	= 19;	// Map INT1 input to RP19;
	//---------------------------------------------------------
	// Some of the functions of this component depends on Timer,
	// so we need to make sure that the Timer is initialized...
	//---------------------------------------------------------
	TMRInitDefault();	// Hopefully timer is already initialized
						// so this statement will be just "NOP"
	//---------------------------------------------------------
	// Now we should initialize the sensor...
	//---------------------------------------------------------
	uint	RC	= MPUReset(RateDiv, DLPF);
	//---------------------------------------------------------
	return RC;
	}



