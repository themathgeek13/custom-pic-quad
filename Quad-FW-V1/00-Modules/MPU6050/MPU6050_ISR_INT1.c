#include "System.h"
#include "MPU6050_Local.h"

//================================================================
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)
	{
	//------------------------------------------------------------
	// Please note that INT1 interrupt is configured to run at
	// least at or above I2C interrupt priority, so no I2C event
	// may take place before EXIT from this routine
	//------------------------------------------------------------
	_INT1IF = 0;	// Clear the INT1 interrupt flag or else
					// the CPU will keep vectoring back to the ISR
	//------------------------------------------------------------
    // Try to subscribe to I2C ASYNC processing
	//------------------------------------------------------------
	if (I2CRC_OK == I2CAsyncStart(&_MPUCallBack))
		{
		//////////////////////////////////////////////////////////////
		// Subscription successful
		//////////////////////////////////////////////////////////////
		_MPU_State		= 0;	// Zero out State Machine
		_SEN			= 1;	// Initiate Start on SDA and SCL pins
								// NOTE: because of "subscription" I2C in-
								// terrupt will result in call to 
								// _MPUCallBack routine
		}
	}
//================================================================

//================================================================
void	_MPUCallBack()
	{
	//===============================================================
	// NOTE: This I2C interrupt call-back routine is geared specifi-
	//		 cally to supporting asynchronous data read operation for 
	//		 MPU6050 Acc/Gyro sensor
	//---------------------------------------------------------------
	_MI2C1IF	= 0; 		// Clear   I2C(1) Master interrupt flag
	//===============================================================
	// General status checks - valid under all conditions
	//===============================================================
	if 	(
			_ACKSTAT		// 1 = NACK received from slave	
		||	_BCL			// 1 = Master Bus Collision
		||	_IWCOL			// 1 = Write Collision
		||	_I2COV			// 1 = READ Overflow condition
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
	switch (_MPU_State)
		{
		//=============================================================
		// Set MPU Register Address to Data (0x3B)
		//=============================================================
		case	0:		// Interrupt after initial SEN
			// Sending device address with WRITE cond.
			I2C1TRN		= _MPU_Addr & 0xFE;	
			_MPU_State	= 1;		// Move state
			break;	
		//-----------------------------------------------------------
		case	1:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address	
			I2C1TRN		= 0x3B;		// MPU6050 Data register address.
			_MPU_State	= 2;		// Move state
			break;
		//=============================================================
		// Transition to the Reading Data Mode
		//=============================================================
		case	2:		// Interrupt after register address
			// Slave send ACK (confirmed in General Checks);
			// Initiate Repeated Start condition
			_RSEN		= 1;
			_MPU_State	= 3;		// Move state
			break;
		//-----------------------------------------------------------
		case	3:		// Interrupt after Repeated Start
			// Sending device address with READ cond.
			I2C1TRN		= _MPU_Addr | 0x01;	
			_MPU_State	= 4;		// Move state
			break;
		//-----------------------------------------------------------
		case	4:		// Interrupt after Device Address with READ
			// Slave send ACK; we switch to READ
			_I2COV 		= 0;		// Clear receive OVERFLOW bit, if any
			_RCEN		= 1;		// Allow READ.
			_MPU_BufPos	= 0;		// Reset buffer position
			//----------------------------------------
			_MPU_State	= 5;		// Move state
			break;
		//=============================================================
		// Read and process data sample
		//=============================================================
		case	5:		// Interrupt after READing Data byte
			// Slave completed sending byte... 
			_MPU_Buffer[_MPU_BufPos] = I2C1RCV;	// Retrieve and store data byte
			_MPU_BufPos++;				// Move buffer address pointer
			//---------------------------------------
			if (_MPU_BufPos < 14)
				{
				// More bytes to read - generate ACK
				_ACKDT 		= 0;
				_ACKEN 		= 1;
				//----------------------
				_MPU_State	= 6;	// Move state
				}
			else
				{
				// All 14 bytes are read - terminate READ with NACK
				_ACKDT 		= 1;
				_ACKEN 		= 1;
				//----------------------
				_MPU_State	= 7;	// Move state
				}
			break;
		//-----------------------------------------
		case	6:		// Interrupt after ACK
			_I2COV 	= 0;	// Clear receive OVERFLOW bit, if any
			_RCEN	= 1;	// Allow READ.
			//----------------------------------------
			_MPU_State			= 5;	// Move state BACK to read next byte
			break;
		//-----------------------------------------
		case	7:		// Interrupt after NACK	- terminate cycle
						// and process retrieved sample
			//-----------------------------------------------------------
			// Terminate current ASYNC session
			//-----------------------------------------------------------
			I2CAsyncStop();		// Un-subscribe from I2C and stop ASYNC
			//-----------------------------------------------------------
			// Process and output data
			union
				{
				int				VInt;
				unsigned char	VByte[2];
				}	U;
			//===============================================
			// Due to orientation of the sensor on the board
			// in reference to orientation of the board in
			// the vehicle, direction of the axis need to change
			// to align right-handed coordinate system with
			// the vehicle
			//===============================================
			// Accelerometer:
			//-----------------------------------------------
			// 	Yveh	= -Xa
			//-----------------------------------------------
			U.VByte[1]		= _MPU_Buffer[0];
			U.VByte[0]		= _MPU_Buffer[1];
			_MPU_Sensor.AY 	= -U.VInt;
			//-----------------------------------------------
			// 	Xveh	= -Ya
			//-----------------------------------------------
			U.VByte[1]		= _MPU_Buffer[2];
			U.VByte[0]		= _MPU_Buffer[3];
			_MPU_Sensor.AX 	= -U.VInt;
			//-----------------------------------------------
			// 	Zveh = -Za
			//-----------------------------------------------
			U.VByte[1]		= _MPU_Buffer[4];
			U.VByte[0]		= _MPU_Buffer[5];
			_MPU_Sensor.AZ 	= -U.VInt;
			//-----------------------------------------------
			// Temperature
			//-----------------------------------------------
			U.VByte[1]		 = _MPU_Buffer[6];
			U.VByte[0]		 = _MPU_Buffer[7];
			_MPU_Sensor.Temp = U.VInt;
			//-----------------------------------------------
			// Gyroscopes
			//-----------------------------------------------
			// 	Yveh	= -Xa
			//-----------------------------------------------
			U.VByte[1]		= _MPU_Buffer[8];
			U.VByte[0]		= _MPU_Buffer[9];
			_MPU_Sensor.GY 	= -U.VInt;
			//-----------------------------------------------
			// 	Xveh	= -Ya
			//-----------------------------------------------
			U.VByte[1]		= _MPU_Buffer[10];
			U.VByte[0]		= _MPU_Buffer[11];
			_MPU_Sensor.GX 	= -U.VInt;
			//-----------------------------------------------
			// 	Zveh = -Za
			//-----------------------------------------------
			U.VByte[1]		= _MPU_Buffer[12];
			U.VByte[0]		= _MPU_Buffer[13];
			_MPU_Sensor.GZ 	= -U.VInt;
			//-----------------------------------------------
			++_MPU_Count;	// Account for the new sample...
			//-----------------------------------------------
			if (0 == _MPU_Ready)
				{
				// First sample in sequence
				// NOTE:	_MPU_Ready reverts to 0
				// 			after exhausting "uint"
				//			range.
				//---------------------------------
				_MPU_Sample.AX		= _MPU_Sensor.AX;
				_MPU_Sample.AY		= _MPU_Sensor.AY;
				_MPU_Sample.AZ		= _MPU_Sensor.AZ;
				//---------------------------------
				_MPU_Sample.Temp 	= _MPU_Sensor.Temp;
				//---------------------------------
				_MPU_Sample.GX		= _MPU_Sensor.GX;
				_MPU_Sample.GY		= _MPU_Sensor.GY;
				_MPU_Sample.GZ		= _MPU_Sensor.GZ;
				}
			else
				{
				// Subsequent sample in sequence: accumulate data
				// for subsequent averaging in retrieval routine.
				//---------------------------------
				_MPU_Sample.AX		+= _MPU_Sensor.AX;
				_MPU_Sample.AY		+= _MPU_Sensor.AY;
				_MPU_Sample.AZ		+= _MPU_Sensor.AZ;
				//---------------------------------
				_MPU_Sample.Temp 	+= _MPU_Sensor.Temp;
				//---------------------------------
				_MPU_Sample.GX		+= _MPU_Sensor.GX;
				_MPU_Sample.GY		+= _MPU_Sensor.GY;
				_MPU_Sample.GZ		+= _MPU_Sensor.GZ;
				}
			//-----------------------------------------------
			_MPU_Ready++;		// _MPU_Ready > 0 -> Sample is ready!
			//-----------------------------------------------------------
			
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

