#include "HMCMAG\HMCMAG_Local.h"
//*******************************************************

//================================================================
void __attribute__((interrupt, no_auto_psv)) _IC2Interrupt(void)
	{
	//------------------------------------------------------------
	// Please note that INT2 interrupt is configured to run at
	// least at or above I2C interrupt priority, so no I2C event
	// may take place before EXIT from this routine
	//------------------------------------------------------------
	HMC_IF = 0;		// Clear the ICx interrupt flag or else
					// the CPU will keep vectoring back to the ISR
	//------------------------------------------------------------
    // Try to subscribe to I2C ASYNC processing
	//------------------------------------------------------------
	if (I2CRC_OK == I2CAsyncStart(&_HMCCallBack))
		{
		//////////////////////////////////////////////////////////////
		// Subscription successful
		//////////////////////////////////////////////////////////////
		_HMC_State		= 0;	// Zero out State Machine
		I2C_SEN			= 1;	// Initiate Start on SDA and SCL pins
								// NOTE: because of "subscription" I2C in-
								// terrupt will result in call to 
								// _HMCCallBack routine
		}
	}
//================================================================

//================================================================
void	_HMCCallBack()
	{
	//===============================================================
	// NOTE: This I2C interrupt call-back routine is geared specifi-
	//		 cally to supporting asynchronous data read operation for 
	//		 HMC Magnetometer sensor
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
	switch (_HMC_State)
		{
		//=============================================================
		// Set HMC Register Address to Data (0x3B)
		//=============================================================
		case	0:		// Interrupt after initial SEN
			// Sending device address with WRITE cond.
			I2C_TRM_Reg	= _HMC_Addr & 0xFE;
			_HMC_State	= 1;		// Move state
			break;	
		//-----------------------------------------------------------
		case	1:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address
			I2C_TRM_Reg	= 0x03;		// HMC  Data register address.
			_HMC_State	= 2;		// Move state
			break;
		//=============================================================
		// Transition to the Reading Data Mode
		//=============================================================
		case	2:		// Interrupt after register address
			// Slave send ACK (confirmed in General Checks);
			// Initiate Repeated Start condition
			I2C_RSEN	= 1;
			_HMC_State	= 3;		// Move state
			break;
		//-----------------------------------------------------------
		case	3:		// Interrupt after Repeated Start
			// Sending device address with READ cond. 
			I2C_TRM_Reg	= _HMC_Addr | 0x01;
			_HMC_State	= 4;		// Move state
			break;
		//-----------------------------------------------------------
		case	4:		// Interrupt after Device Address with READ
			// Slave send ACK; we switch to READ
			I2C_I2COV 	= 0;		// Clear receive OVERFLOW bit, if any
			I2C_RCEN	= 1;		// Allow READ.
			_HMC_BufPos	= 0;		// Reset buffer position
			//----------------------------------------
			_HMC_State	= 5;		// Move state
			break;
		//=============================================================
		// Read and process data sample
		//=============================================================
		case	5:		// Interrupt after READing Data byte
			// Slave completed sending byte...
			// Retrieve and store data byte
			_HMC_Buffer[_HMC_BufPos] = I2C_RCV_Reg;
			_HMC_BufPos++;				// Move buffer address pointer
			//---------------------------------------
			if (_HMC_BufPos < 6)
				{
				// More bytes to read - generate ACK
				I2C_ACKDT 	= 0;
				I2C_ACKEN 	= 1;
				//----------------------
				_HMC_State	= 6;	// Move state
				}
			else
				{
				// All 7 bytes are read - terminate READ with NACK
				I2C_ACKDT 	= 1;
				I2C_ACKEN 	= 1;
				//----------------------
				_HMC_State	= 7;	// Move state
				}
			break;
		//-----------------------------------------
		case	6:		// Interrupt after ACK
			I2C_I2COV 	= 0;	// Clear receive OVERFLOW bit, if any
			I2C_RCEN	= 1;	// Allow READ.
			//----------------------------------------
			_HMC_State			= 5;	// Move state BACK to read next byte
			break;
		//-----------------------------------------
		case	7:		// Interrupt after NACK	- terminate cycle
						// and process retrieved sample
			//-----------------------------------------------------------
			// Terminate current ASYNC session
			//-----------------------------------------------------------
			I2CAsyncStop();		// Un-subscribe from I2C and stop ASYNC
			//-----------------------------------------------------------
			// "Unpack" data
			//-----------------------------------------------------------
			union
				{
				int		VInt;
				struct
					{
					byte	LSB;
					byte	MSB;
					};
				}	U;
			//-----------------------------------------------
			// Magnetometer
			//-----------------------------------------------
			// Please NOTE:
			// the six bytes returned represent values of X,
			// Z, and Y registers. As we use the right-handed
			// coordinate system with axis Z pointing down and
			// considering the orientation of the sensor on
			// the board, we make the following adjustments:
			//	Xres = -X;
			//	Zres = -Z;
			//	Yres =  Y;
			//-----------------------------------------------
			U.MSB	= _HMC_Buffer[0];
			U.LSB	= _HMC_Buffer[1];
			_HMC_Sensor.MX = -U.VInt;			//	Xres = -X;
			//-----------------------------------------------
			U.MSB	= _HMC_Buffer[2];
			U.LSB	= _HMC_Buffer[3];
			_HMC_Sensor.MZ = -U.VInt;			//	Zres = -Z;
			//-----------------------------------------------
			U.MSB	= _HMC_Buffer[4];
			U.LSB	= _HMC_Buffer[5];
			_HMC_Sensor.MY = U.VInt;			//	Yres =  Y;
			//-----------------------------------------------
			if (0 == _HMC_Ready)
				{
				//---------------------------------
				_HMC_Sample.MX		= _HMC_Sensor.MX;
				_HMC_Sample.MY		= _HMC_Sensor.MY;
				_HMC_Sample.MZ		= _HMC_Sensor.MZ;
				//---------------------------------
				}
			else
				{
				//---------------------------------
				_HMC_Sample.MX		+= _HMC_Sensor.MX;
				_HMC_Sample.MY		+= _HMC_Sensor.MY;
				_HMC_Sample.MZ		+= _HMC_Sensor.MZ;
				}
			//-----------------------------------------------
			++_HMC_Count;		// Increment sample count
			//-----------------------------------------------
			_HMC_Ready++;		// _HMC_Ready > 0 -> Sample is ready!
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


