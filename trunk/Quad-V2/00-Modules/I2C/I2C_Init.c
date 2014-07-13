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
	//---------------------------------------------------------

	//=========================================================
	//	On PIC24HJ128GP2xx ASDA1 -> RB5 and ASCL1 -> RB6
	//	Prior to using I2C1 these ports need to be configured
	//	for Open-Drain operation...
	//---------------------------------------------------------
	// NOTE: Selection of Primary or Alternative I2C pins
	//		 implemented in Init() routine through _FPOR
	//---------------------------------------------------------
	_ODCB5	= 1;
	_ODCB6	= 1;

	//=========================================================
	//	I2CCON: I2C Status Register
	//---------------------------------------------------------
	I2C_CON			= 0;		// Disable I2C for configuration
	// NOTE: In the Global INIT routine all peripherals were disabled
	// 		 using PMD (Prepheral Module Disable) control register(s)
	//		 Prior to continuing initialization the module need to
	//		 be enabled
	I2C_PMD			= 0;	// I2C enabled in PMD
	//
	// Default configuration sets I2C into the:
	//
	// A10M		= 0:	I2CxADD register is a 7-bit slave address 
	// GCEN		= 0: 	General call address disabled
	// STREN	= 0: 	Disable software or receive clock stretching
	// ACKDT	= 0: 	Send ACK during Acknowledge
	//---------------------------------------------------------
	/*
	bit 4 ACKEN: Acknowledge Sequence Enable bit (I2C Master mode receive operation)
			1 = Initiate Acknowledge sequence on SDAx and SCLx pins and transmit ACKDT
				data bit (hardware clear at end of master Acknowledge sequence)
			0 = Acknowledge sequence not in progress
	bit 3 RCEN: Receive Enable bit (I2C Master mode)
			1 = Enables Receive mode for I2C (hardware clear at end of eighth bit 
				of master receive data byte)
			0 = Receive sequence not in progress
	bit 2 PEN: Stop Condition Enable bit (I2C Master mode)
			1 = Initiate Stop condition on SDAx and SCLx pins (hardware clear at end 
				of master Stop sequence)
			0 = Stop condition not in progress
	bit 1 RSEN: Repeated Start Condition Enable bit (I2C Master mode)
			1 = Initiate Repeated Start condition on SDAx and SCLx pins (hardware 
				clear at end of master Repeated Start sequence)
			0 = Repeated Start condition not in progress
	bit 0 SEN: Start Condition Enable bit (I2C Master mode)
			1 = Initiate Start condition on SDAx and SCLx pins (hardware clear at end 
				of master Start sequence)
			0 = Start condition not in progress
	*/
	
	//---------------------------------------------------------
	/*	I2C1STAT: I2Cx Status Register
	-----------------------------------------------------------
	bit 15	ACKSTAT: Acknowledge Status bit
				Hardware set or clear at end of Slave or Master Acknowledge.
				1 = NACK received from slave
				0 = ACK received from slave
	bit 14 	TRSTAT: Transmit Status bit (I2C Master mode transmit operation)
				Hardware set at beginning of master transmission;
				hardware clear at end of slave Acknowledge.
				1 = Master transmit is in progress (8 bits + ACK)
				0 = Master transmit is not in progress
	bit 10	BCL: Master Bus Collision Detect bit
				Hardware set at detection of bus collision.
				1 = A bus collision has been detected during a master operation
				0 = No collision
	bit 9 	GCSTAT: General Call Status bit
				Hardware set when address matches general call address; 
				hardware clear at Stop detection.
				1 = General call address was received
				0 = General call address was not received
	bit 8 	ADD10: 10-Bit Address Status bit
				Hardware set at match of 2nd byte of matched 10-bit address; 
				hardware clear at Stop detection.
				1 = 10-bit address was matched
				0 = 10-bit address was not matched
	bit 7 	IWCOL: Write Collision Detect bit
				Hardware set at occurrence of write to I2CxTRN register while busy 
				(cleared by software).
				1 = An attempt to write the I2CxTRN register failed because the I2C module is busy
				0 = No collision
	bit 6	I2COV: Receive Overflow Flag bit
				Hardware set at attempt to transfer I2CxRSR register to I2CxRCV register 
				(cleared by software).
				1 = A byte was received while the I2CxRCV register is still holding the previous byte
				0 = No overflow
	bit 5 	D/A: Data/Address bit (I2C Slave mode)
				Hardware clear at device address match; hardware set by reception of slave 
				byte or is set after the transmission is complete and the TBF flag is cleared.
				1 = Indicates that the last byte received was data
				0 = Indicates that the last byte received was a device address
	bit 4 	P: Stop bit
				Hardware set or clear when Start, Repeated Start or Stop detected.
				1 = Indicates that a Stop bit has been detected last
				0 = Stop bit was not detected last
	bit 3 	S: Start bit
				Hardware set or clear when Start, Repeated Start or Stop detected.
				1 = Indicates that a Start (or Repeated Start) bit has been detected last
				0 = Start bit was not detected last
	bit 2 	R/W: Read/Write Information bit (when operating as I2C slave)
				Hardware set or clear after reception of I2C device address byte.
				1 = Read: data transfer is output from slave
				0 = Write: data transfer is input to slave
	bit 1 	RBF: Receive Buffer Full Status bit
				Hardware set when the I2CxRCV register is written with received byte; 
				hardware clear when software reads the I2CxRCV register.
				1 = Receive complete; I2CxRCV register is full
				0 = Receive not complete; I2CxRCV register is empty
	bit 0 	TBF: Transmit Buffer Full Status bit
				Hardware set when software writes to I2CxTRN register; 
				hardware clear at completion of data transmission.
				1 = Transmit in progress; I2CxTRN register is full
				0 = Transmit complete; I2CxTRN register is empty
	*/	
	I2C_STAT		= 0;		// Reset all STATUS bits
	//---------------------------------------------------------


	//---------------------------------------------------------
	//	I2CxMSK: I2Cx Slave Mode Address Mask Register
	//---------------------------------------------------------
	I2C_MSK		= 0;	// All address bits are unmasked
						// (full match required)

	//---------------------------------------------------------
	//	I2CxADD: I2Cx Slave Mode Address 
	//---------------------------------------------------------
	I2C_ADD		= 0;

	//---------------------------------------------------------
	//	I2CxBRG: I2Cx Baud Rate Register
	//---------------------------------------------------------
	// Baud Rate is calculated under the assumption that MCU
	// is operating at 40 MHz (Fcy = 40,000,000)
	//---------------------------------------------------------
	if (0 == Speed)
		I2C_BRG	= 395;		// 100 kHz
	else
		I2C_BRG	= 95;		// 400 kHz
	//---------------------------------------------------------


	//=========================================================
	I2C_IE	= 0;		// Disable I2C Master interrupt
	I2C_IF	= 0; 		// Clear   I2C Master interrupt flag
		// The MI2CxIF interrupt is generated on completion of the
		// following master message events:
		//	• Start condition
		//	• Stop condition
		//	• Data transfer byte transmitted/received
		//	• Acknowledge transmit
		//	• Repeated Start
		//	• Detection of a bus collision event
	//---------------------------------------------------------
	I2C_SlaveIE	= 0;		// Disable I2C Slave interrupt
	I2C_SlaveIF	= 0; 		// Clear   I2C Slave interrupt flag
		// The SI2CxIF interrupt is generated on detection of a message
		// directed to the slave, including the	following events:
		// • Detection of a valid device address (including general call)
		// • Request to transmit data (ACK) or to stop data transmission (NACK)
		// • Reception of data	
	//=========================================================
	I2C_IP		= _I2C_IL; 	// Set I2C Master interrupt priority
	I2C_SlaveIP	= 0;		// Set I2C Slave  interrupt priority
	//=========================================================
	// After configuration complete enable I2C(1) module	
	//---------------------------------------------------------
	I2C_I2CEN	= 1;		// Enables the I2Cx module and configures
							// the SDAx and SCLx pins as serial port pins
	//=========================================================
	}

//************************************************************

