#ifndef I2C_PROFILE_H
#define	I2C_PROFILE_H
//==================================================================
// I2C Asynchronous Access Subscribers max count
//------------------------------------------------------------------
#define I2CSubscMax		4
//==================================================================

//==================================================================
#define	I2C_NACKRetry	50	// Retry count for NACK code
#define	I2C_BUSYRetry	50	// Retry count for BUSY code
//==================================================================
// I2C Master Interrupt routine
//------------------------------------------------------------------
#define	I2CInterrupt	_MI2C1Interrupt
// I2C Interrupt flag (Master)
#define I2C_IF			_MI2C1IF
// I2C Interrupr Enable flag (Master)
#define	I2C_IE			_MI2C1IE
// I2C Interrupr Priority (Master)
#define	I2C_IP			_MI2C1IP
//==================================================================
// I2C PMD (Peripheral Module Disable) flag
//------------------------------------------------------------------
#define	I2C_PMD			_I2C1MD
//==================================================================
// I2C Control register
//==================================================================
#define	I2C_CON			I2C1CON
//------------------------------------------------------------------
// I2C Control register bits
//------------------------------------------------------------------
#define I2C_SEN			I2C1CONbits.SEN
#define I2C_RSEN		I2C1CONbits.RSEN
#define I2C_PEN			I2C1CONbits.PEN
#define I2C_RCEN		I2C1CONbits.RCEN
#define I2C_ACKEN		I2C1CONbits.ACKEN
#define I2C_ACKDT		I2C1CONbits.ACKDT
#define I2C_STREN		I2C1CONbits.STREN
#define I2C_GCEN		I2C1CONbits.GCEN
#define I2C_SMEN		I2C1CONbits.SMEN
#define I2C_DISSLW		I2C1CONbits.DISSLW
#define I2C_A10M		I2C1CONbits.A10M
#define I2C_IPMIEN		I2C1CONbits.IPMIEN
#define I2C_SCLREL		I2C1CONbits.SCLREL
#define I2C_I2CSIDL		I2C1CONbits.I2CSIDL
#define I2C_I2CEN		I2C1CONbits.I2CEN
//==================================================================
// I2C Status register
//==================================================================
#define I2C_STAT		I2C1STAT
//------------------------------------------------------------------
// I2C Status register bits
//------------------------------------------------------------------
#define I2C_TBF			I2C1STATbits.TBF
#define I2C_RBF			I2C1STATbits.RBF
#define I2C_R_W			I2C1STATbits.R_W
#define I2C_S			I2C1STATbits.S
#define I2C_P			I2C1STATbits.P
#define I2C_D_A			I2C1STATbits.D_A
#define I2C_I2COV		I2C1STATbits.I2COV
#define I2C_IWCOL		I2C1STATbits.IWCOL
#define I2C_ADD10		I2C1STATbits.ADD10
#define I2C_GCSTAT		I2C1STATbits.GCSTAT
#define I2C_BCL			I2C1STATbits.BCL
#define I2C_TRSTAT		I2C1STATbits.TRSTAT
#define I2C_ACKSTAT		I2C1STATbits.ACKSTAT
//==================================================================
// I2C Transmit and Receive registers
//------------------------------------------------------------------
#define	I2C_TRM_Reg		I2C1TRN
#define	I2C_RCV_Reg		I2C1RCV
//==================================================================
// I2C Baud Rate Generator
//------------------------------------------------------------------
#define	I2C_BRG			I2C1BRG
//==================================================================
// Slave Mode configuration elements (just to disable them :) )
//==================================================================
#define I2C_MSK			I2C1MSK
#define I2C_ADD			I2C1ADD
//------------------------------------------------------------------
// I2C Slave Interrupt registers (NOTE: we use only Master mode)
//------------------------------------------------------------------
// I2C Interrupt flag (Slave)
#define I2C_SlaveIF		_SI2C1IF
// I2C Interrupr Enable flag (Slave)
#define	I2C_SlaveIE		_SI2C1IE
// I2C Interrupr Priority (Slave)
#define	I2C_SlaveIP		_SI2C1IP
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
	// I2C1 pins
	_ODCG2	= 1;
	_ODCG3	= 1;
	// I2C2 pins
//	_ODCF4	= 1;
//	_ODCF5	= 1;
	//---------------------------------------------------------
	return;
	}
//==================================================================
#endif	/* I2C_PROFILE_H */

