#include "System.h"
#include "MPL3115\MPL3115_Local.h"

//================================================================
void __attribute__((interrupt, no_auto_psv)) MPL_Interrupt(void)
	{
	//------------------------------------------------------------
	// Please note that MPL interrupt is configured to run at
	// least at or above I2C interrupt priority, so no I2C event
	// may take place before EXIT from this routine
	//------------------------------------------------------------
	MPL_IF = 0;		// Clear the MPL  interrupt flag or else
					// the CPU will keep vectoring back to the ISR
	//------------------------------------------------------------
	// Capture status of the Interrupt Line
	_MPL_PortLvl = MPL_INT_PORT;  
	//------------------------------------------------------------
    // Try to subscribe to I2C ASYNC processing
	//------------------------------------------------------------
	if (I2CRC_OK == I2CAsyncStart(&_MPLCallBack))
		{
		//////////////////////////////////////////////////////////////
		// Subscription successful
		//////////////////////////////////////////////////////////////
		_MPL_State		= 0;	// Zero out State Machine
		I2C_SEN			= 1;	// Initiate Start on SDA and SCL pins
								// NOTE: because of "subscription" I2C in-
								// terrupt will result in call to 
								// _MPLCallBack routine
		}
	}
//================================================================

//================================================================
void	_MPLCallBack()
	{
	//===============================================================
	// NOTE: This I2C interrupt call-back routine is geared specifi-
	//		 cally to supporting asynchronous data read operation for 
	//		 MPL3115 Altitude/Pressure sensor
	//===============================================================
	// General status checks - valid under all conditions
	//===============================================================
	if 	(
			I2C_ACKSTAT		// 1 = NACK received from slave
		||	I2C_BCL			// 1 = Master Bus Collision
		||	I2C_IWCOL		// 1 = Write Collision
		||	I2C_I2COV		// 1 = READ Overflow condition
		)
		{
		//-----------------------------------------------------------
		// Terminate current ASYNC session
		//-----------------------------------------------------------
		I2CAsyncStop();		// Un-subscribe from I2C and stop ASYNC
		return;
		}
	//===============================================================
	// Process conditions based upon the state of the State Machine
	//===============================================================
	switch (_MPL_State)
		{
		//=============================================================
		// Set MPL Register Address to Data (0xC0)
		//=============================================================
		case	0:		// Interrupt after initial SEN
			// Sending device address with WRITE cond.
			I2C_TRM_Reg	= _MPL_Addr & 0xFE;
			_MPL_State	= 1;		// Move state
			break;	
		//-----------------------------------------------------------
		case	1:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address	
			I2C_TRM_Reg	= 0x01;		// MPL3115 Data register address.
			_MPL_State	= 2;		// Move state
			break;
		//=============================================================
		// Transition to the Reading Data Mode
		//=============================================================
		case	2:		// Interrupt after register address
			// Slave send ACK (confirmed in General Checks);
			// Initiate Repeated Start condition
			I2C_RSEN	= 1;
			_MPL_State	= 3;		// Move state
			break;
		//-----------------------------------------------------------
		case	3:		// Interrupt after Repeated Start
			// Sending device address with READ cond.
			I2C_TRM_Reg	= _MPL_Addr | 0x01;
			_MPL_State	= 4;		// Move state
			break;
		//-----------------------------------------------------------
		case	4:		// Interrupt after Device Address with READ
			// Slave send ACK; we switch to READ
			I2C_I2COV 	= 0;		// Clear receive OVERFLOW bit, if any
			I2C_RCEN	= 1;		// Allow READ.
			_MPL_BufPos	= 0;		// Reset buffer position
			//----------------------------------------
			_MPL_State	= 5;		// Move state
			break;
		//=============================================================
		// Read and process data sample
		//=============================================================
		case	5:		// Interrupt after READing Data byte
			// Slave completed sending byte...
			// Retrieve and store data byte
			_MPL_Buffer[_MPL_BufPos] = I2C_RCV_Reg;	
			_MPL_BufPos++;				// Move buffer address pointer
			//---------------------------------------
			if (_MPL_BufPos < 5)
				// More bytes to read
				{
				// Generate ACK for the byte read
				I2C_ACKDT 	= 0;
				I2C_ACKEN 	= 1;
				//--------------
				_MPL_State	= 6;	// Move state
				}
			else
				// All 5 bytes are read
				{
				// Generate NACK for the last byte read
				I2C_ACKDT 	= 1;
				I2C_ACKEN 	= 1;
				//--------------
				_MPL_State	= 7;	// Move state
				}
			break;
		//-----------------------------------------
		case	6:		// Interrupt after ACK
			I2C_I2COV 	= 0;	// Clear receive OVERFLOW bit, if any
			I2C_RCEN	= 1;	// Allow READ.
			//----------------------------------------
			_MPL_State	= 5;	// Move state BACK to read next byte
			break;
		//=============================================================
		// After we consumed the Sample, we need to innitiate the new
		// OST cycle by reading the CtrlR1 and then writing it back
		// with OST bit set.
		//=============================================================
		case	7:		// Interrupt after NACK	- switch direction to
						// WRITE starting with "Repeated Start"
			// Initiate Repeated Start condition
			I2C_RSEN	= 1;
			_MPL_State	= 8;		// Move state
			break;
		//-----------------------------------------------------------
		case	8:		// Interrupt after RSEN
			// Sending device address with WRITE cond.
			I2C_TRM_Reg	= _MPL_Addr & 0xFE;
			_MPL_State	= 9;		// Move state
			break;	
		//-----------------------------------------------------------
		case	9:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address	
			I2C_TRM_Reg	= CtrlR1Addr;	// MPL3115 CtrlR1 address.
			_MPL_State	= 10;			// Move state
			break;
		//=============================================================
		// Transition to the Reading Data Mode
		//=============================================================
		case	10:		// Interrupt after sending register address
			// Slave send ACK (confirmed in General Checks);
			// Initiate Repeated Start condition
			I2C_RSEN	= 1;
			_MPL_State	= 11;		// Move state
			break;
		//-----------------------------------------------------------
		case	11:		// Interrupt after Repeated Start
			// Sending device address with READ cond.
			I2C_TRM_Reg	= _MPL_Addr | 0x01;
			_MPL_State	= 12;		// Move state
			break;
		//-----------------------------------------------------------
		case	12:		// Interrupt after Device Address with READ
			// Slave send ACK; we switch to READ
			I2C_I2COV 	= 0;		// Clear receive OVERFLOW bit, if any
			I2C_RCEN	= 1;		// Allow READ.
			_MPL_BufPos	= 0;		// Reset buffer position
			//----------------------------------------
			_MPL_State	= 13;		// Move state
			break;
		//=============================================================
		// Read CtrlR1
		//=============================================================
		case	13:		// Interrupt after READing Data byte
			// Slave completed sending byte... 
			_MPL_CtrlR1 = I2C_RCV_Reg;	// Retrieve and store data byte
			//---------------------------------------
			// Generate NACK for the last byte read
			I2C_ACKDT 		= 1;
			I2C_ACKEN 		= 1;
			//---------------------------------------
			_MPL_State	= 14;	// Move state
			break;
		//=============================================================
		// Write CtrlR1 with OST bit set
		//=============================================================
		case	14:		// Interrupt after ACK	- switch direction to
						// WRITE starting with "Repeated Start"
			// Initiate Repeated Start condition
			I2C_RSEN	= 1;
			_MPL_State	= 15;		// Move state
			break;
		//-----------------------------------------------------------
		case	15:		// Interrupt after RSEN
			// Sending device address with WRITE cond.
			I2C_TRM_Reg	= _MPL_Addr & 0xFE;
			_MPL_State	= 16;		// Move state
			break;
		//-----------------------------------------------------------
		case	16:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address
			I2C_TRM_Reg	= CtrlR1Addr;	// MPL3115 CtrlR1 address.
			_MPL_State	= 17;			// Move state
			break;
		//-----------------------------------------------------------
		case	17:		// Interrupt after CtrlR1 address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with new value for CtrlR1
			I2C_TRM_Reg	= _MPL_CtrlR1 | CtrlR1SetOST;
			_MPL_State	= 18;		// Move state
			break;	
		//-----------------------------------------------------------
		case	18:		// Interrupt after CtrlR1 write
			// Slave send ACK (confirmed in General Checks);
			//-----------------------------------------------------------
			// Terminate current ASYNC session
			//-----------------------------------------------------------
			I2CAsyncStop();		// Un-subscribe from I2C and stop ASYNC
			//-----------------------------------------------------------
			if (_MPL_PortLvl > 0)
				{
				//===============================================
				// Construct 20-bit ALT sample as integer
				//-----------------------------------------------
				long Alt = *((sbyte*)&_MPL_Buffer[0]);
				Alt = Alt << 8;
				Alt = Alt |  _MPL_Buffer[1];
				Alt = Alt << 8;
				Alt = Alt |  _MPL_Buffer[2];
				Alt = Alt >> 4;
				//-----------------------------------------------
				if (0 == _MPL_Ready || _MPL_Ready > 512)
					// First sample in sequence or we
					// need to start a new "sequence"
					// to preclude overflow of _MPL_Data
					//---------------------------------
					_MPL_Data = Alt;
				else
					// Subsequent sample in sequence: accumulate data
					// for subsequent averaging in retrieval routine.
					//---------------------------------
					_MPL_Data += Alt;
				//-----------------------------------------------
				_MPL_Ready++;		// _MPL_Ready > 0 -> Sample is ready!
				}
			_MPL_DataTS = TMRGetTS();
			//-----------------------------------------------------------
			break;	

		//=============================================================
		// Oops! something is terribly wrong with the State Machine...
		//=============================================================
		default:
			//-----------------------------------------------------------
			// Terminate current ASYNC session
			//-----------------------------------------------------------
			I2CAsyncStop();		// Un-subscribe from I2C and stop ASYNC
		}
	//===============================================================
	return;
	}
//================================================================

