#ifndef I2C_PROFILE_H
#define	I2C_PROFILE_H
//==================================================================
// The following two #define statements identify which I2C modules
// will be used in this application; if a particular module is not
// used, please comment out respective #define statement
//==================================================================
#define	_I2C_UseI2C1
#define	_I2C_UseI2C2
//==================================================================

//==================================================================
// Definitions shared across I2C modules
//------------------------------------------------------------------
// I2C Asynchronous Access Subscribers max count
//------------------------------------------------------------------
#define I2CMaxAsyncRqst		1
//==================================================================

//==================================================================
// Helper function _I2CInitPinMap(void) implements configuration
// (and mapping, if needed) of Control pins
//==================================================================
static inline void _I2CInitPinMap(void)
	{
	//=========================================================
	// On PIC24EPxxxGP806 I2C1 (primary) pins are SCL1 -> RG2
	// and SDA1 -> RG3 and I2C2 pins are  SCL2 -> RF5 and
	// SDA2 -> RF4
	// Prior to using I2C these ports need to be configured
	// for Open-Drain operation...
	//---------------------------------------------------------
	// NOTE: Selection of Primary or Alternative I2C pins
	//		 implemented in Init() routine through _FPOR
	//---------------------------------------------------------
	#ifdef _I2C_UseI2C1
		// I2C1 pins
		_ODCG2	= 1;
		_ODCG3	= 1;
	#endif
	//---------------------------------------------------------
	#ifdef _I2C_UseI2C2
		// I2C2 pins
		_ODCF4	= 1;
		_ODCF5	= 1;
	#endif
	//---------------------------------------------------------
	return;
	}
//==================================================================
#endif	/* I2C_PROFILE_H */

