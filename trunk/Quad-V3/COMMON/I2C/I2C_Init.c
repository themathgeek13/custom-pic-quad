#include "I2C\I2C_Local.h"

//************************************************************
void	I2CInit(uint IL, uint Speed)	
	// Parameter (1<=IL<=7) defines the
	// priority of I2C interrupt routine.
	//------------------------------------
	// Speed=0: baud rate set at 100 kHz,
	// any other value: 400 kHz
	{
	//---------------------------------------------------------
	if (_I2C_Init)
		return;			// Avoid repeated initialization...
	_I2C_Init	= 1;
	//---------------------------------------------------------
	if (IL < 1) IL = 1;
	if (IL > 7) IL = 7;
	_I2C_IL	= IL;
	//=========================================================
	//	Configure I2C pins for Open-Drain operation...
	//---------------------------------------------------------
	_I2CInitPinMap();
	//=========================================================
	//	Calculate common (across modules) Baud rate
	//---------------------------------------------------------
	// Baud Rate is calculated under the assumption that MCU
	// is operating at 64 MHz (Fcy = 64,000,000)
	//---------------------------------------------------------
	switch (Speed)
		{
		case 2:
			_I2C_BRG	= 56;		// 1MHz
			break;
		case 1:
			_I2C_BRG = 152;		// 400 kHz
			break;
		case 0:
		default:
			_I2C_BRG = 511;		// ~123 kHz - lowest I2C speed
								// achievable with Fcy = 64 MHz
			break;
		}
	//=========================================================
	// Initialize Control Block for I2C modules
	//---------------------------------------------------------
	int i;
	// <editor-fold defaultstate="collapsed" desc="Initialize _I2C1_CB">
	#ifdef _I2C_UseI2C1
	// Control Block for I2C1 Module
	_I2C1_CB._I2C_SBSY		= 0;		// Naturally, I2C is not busy :)
	_I2C1_CB._I2C_CallBack	= NULL;		// No active call-back
	//---------------------------------------------------------
	// Initialize I2C subscribers' structure
	//---------------------------------------------------------
	for (i = 0; i < I2CSubscMax; i++)
	{
		_I2C1_CB._I2CSubscr[i].CallBack = NULL;
		_I2C1_CB._I2CSubscr[i].SubscrIC = NULL;
	}
	//---------------------------------------------------------
	// Initialize references to I2C1 Control Registers
	//---------------------------------------------------------
	_I2C1_CB.pI2C_CON		= &I2C1CON;
	_I2C1_CB.pI2C_STAT		= &I2C1STAT;
	_I2C1_CB.pI2C_TRN		= &I2C1TRN;
	_I2C1_CB.pI2C_RCV		= &I2C1RCV;
	#endif
	// </editor-fold>
	//---------------------------------------------------------
	// <editor-fold defaultstate="collapsed" desc="Initialize _I2C2_CB">
	#ifdef _I2C_UseI2C2
	// Control Block for I2C2 Module
	_I2C2_CB._I2C_SBSY		= 0;		// Naturally, I2C is not busy :)
	_I2C2_CB._I2C_CallBack	= NULL;		// No active call-back
	//---------------------------------------------------------
	// Initialize I2C subscribers' structure
	//---------------------------------------------------------
	for (i = 0; i < I2CSubscMax; i++)
	{
		_I2C2_CB._I2CSubscr[i].CallBack = NULL;
		_I2C2_CB._I2CSubscr[i].SubscrIC = NULL;
	}
	//---------------------------------------------------------
	// Initialize references to I2C2 Control Registers
	//---------------------------------------------------------
	_I2C2_CB.pI2C_CON		= &I2C2CON;
	_I2C2_CB.pI2C_STAT		= &I2C2STAT;
	_I2C2_CB.pI2C_TRN		= &I2C2TRN;
	_I2C2_CB.pI2C_RCV		= &I2C2RCV;
	#endif
	// </editor-fold>
	//=========================================================
	// Initialize individual I2C modules
	//---------------------------------------------------------
	#ifdef _I2C_UseI2C1
	I2CInitI2C1();
	#endif
	//---------------------------------------------------------
	#ifdef _I2C_UseI2C2
	I2CInitI2C2();
	#endif
	//=========================================================
	}

	
	
	

//==================================================================
// Helper function - exposes _I2C_IL for I2C Subscribers
//------------------------------------------------------------------
byte	I2CGetIL()
	{ return _I2C_IL; }
//==================================================================


#ifdef _I2C_UseI2C1
void	I2CInitI2C1()
	{
	//=========================================================
	//	I2CxCON: I2C Status Register
	//---------------------------------------------------------
	I2C1CON			= 0;		// Disable I2C for configuration
	// NOTE: In the Global INIT routine all peripherals were disabled
	// 		 using PMD (Prepheral Module Disable) control register(s)
	//		 Prior to continuing initialization the module need to
	//		 be enabled
	_I2C1MD			= 0;	// I2C enabled in PMD
	//
	// Default configuration sets I2C into the:
	//
	// A10M		= 0:	I2CxADD register is a 7-bit slave address
	// GCEN		= 0: 	General call address disabled
	// STREN	= 0: 	Disable software or receive clock stretching
	// ACKDT	= 0: 	Send ACK during Acknowledge
	//---------------------------------------------------------
	//	I2CxSTAT: I2Cx STATUS Register
	//---------------------------------------------------------
	I2C1STAT		= 0;		// Reset all STATUS bits
	//---------------------------------------------------------
	//	I2CxMSK: I2Cx Slave Mode Address Mask Register
	//---------------------------------------------------------
	I2C1MSK		= 0;	// All address bits are unmasked
						// (full match required)
	//---------------------------------------------------------
	//	I2CxADD: I2Cx Slave Mode Address
	//---------------------------------------------------------
	I2C1ADD		= 0;
	//---------------------------------------------------------
	//	Set pre-calculated Baud rate
	//---------------------------------------------------------
	I2C1BRG	= _I2C_BRG;
	//=========================================================
	_MI2C1IE	= 0;	// Disable I2C Master interrupt
	_MI2C1IF	= 0; 	// Clear   I2C Master interrupt flag
		// The MI2CxIF interrupt is generated on completion of the
		// following master message events:
		//	• Start condition
		//	• Stop condition
		//	• Data transfer byte transmitted/received
		//	• Acknowledge transmit
		//	• Repeated Start
		//	• Detection of a bus collision event
	//---------------------------------------------------------
	_SI2C1IE	= 0;		// Disable I2C Slave interrupt
	_SI2C1IF	= 0; 		// Clear   I2C Slave interrupt flag
		// The SI2CxIF interrupt is generated on detection of a message
		// directed to the slave, including the	following events:
		// • Detection of a valid device address (including general call)
		// • Request to transmit data (ACK) or to stop data transmission (NACK)
		// • Reception of data
	//=========================================================
	_MI2C1IP	= _I2C_IL; 	// Set I2C Master interrupt priority
	_SI2C1IP	= 0;		// Set I2C Slave  interrupt priority
	//=========================================================
	// After configuration complete enable I2C(1) module
	//---------------------------------------------------------
	I2C1CONbits.I2CEN	= 1;	// Enables the I2Cx module and
								// configures the SDAx and SCLx
								// pins as serial port pins
	//=========================================================
	}
#endif

#ifdef _I2C_UseI2C2
void	I2CInitI2C2()
	{
	//=========================================================
	//	I2CxCON: I2C Status Register
	//---------------------------------------------------------
	I2C2CON			= 0;		// Disable I2C for configuration
	// NOTE: In the Global INIT routine all peripherals were disabled
	// 		 using PMD (Prepheral Module Disable) control register(s)
	//		 Prior to continuing initialization the module need to
	//		 be enabled
	_I2C2MD			= 0;	// I2C enabled in PMD
	//
	// Default configuration sets I2C into the:
	//
	// A10M		= 0:	I2CxADD register is a 7-bit slave address
	// GCEN		= 0: 	General call address disabled
	// STREN	= 0: 	Disable software or receive clock stretching
	// ACKDT	= 0: 	Send ACK during Acknowledge
	//---------------------------------------------------------
	//	I2CxSTAT: I2Cx STATUS Register
	//---------------------------------------------------------
	I2C2STAT		= 0;		// Reset all STATUS bits
	//---------------------------------------------------------
	//	I2CxMSK: I2Cx Slave Mode Address Mask Register
	//---------------------------------------------------------
	I2C2MSK		= 0;	// All address bits are unmasked
						// (full match required)
	//---------------------------------------------------------
	//	I2CxADD: I2Cx Slave Mode Address
	//---------------------------------------------------------
	I2C2ADD		= 0;
	//---------------------------------------------------------
	//	Set pre-calculated Baud rate
	//---------------------------------------------------------
	I2C2BRG	= _I2C_BRG;
	//=========================================================
	_MI2C2IE	= 0;	// Disable I2C Master interrupt
	_MI2C2IF	= 0; 	// Clear   I2C Master interrupt flag
		// The MI2CxIF interrupt is generated on completion of the
		// following master message events:
		//	• Start condition
		//	• Stop condition
		//	• Data transfer byte transmitted/received
		//	• Acknowledge transmit
		//	• Repeated Start
		//	• Detection of a bus collision event
	//---------------------------------------------------------
	_SI2C2IE	= 0;		// Disable I2C Slave interrupt
	_SI2C2IF	= 0; 		// Clear   I2C Slave interrupt flag
		// The SI2CxIF interrupt is generated on detection of a message
		// directed to the slave, including the	following events:
		// • Detection of a valid device address (including general call)
		// • Request to transmit data (ACK) or to stop data transmission (NACK)
		// • Reception of data
	//=========================================================
	_MI2C2IP	= _I2C_IL; 	// Set I2C Master interrupt priority
	_SI2C2IP	= 0;		// Set I2C Slave  interrupt priority
	//=========================================================
	// After configuration complete enable I2C(1) module
	//---------------------------------------------------------
	I2C2CONbits.I2CEN	= 1;	// Enables the I2Cx module and
								// configures the SDAx and SCLx
								// pins as serial port pins
	//=========================================================
	}
#endif

//************************************************************

