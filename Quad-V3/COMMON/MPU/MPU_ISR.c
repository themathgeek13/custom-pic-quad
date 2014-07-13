#include "System.h"
#include "MPU\MPU_Local.h"

//================================================================
#ifdef Use_MPU1
void __attribute__((interrupt, no_auto_psv)) MPU1_Interrupt(void)
	{
	//------------------------------------------------------------
	// Please note that INTx interrupt is configured to run at
	// least at or above I2C interrupt priority, so no I2C event
	// may take place before EXIT from this routine
	//------------------------------------------------------------
	MPU1_IF = 0;	// Clear the INTx interrupt flag or else
					// the CPU will keep vectoring back to the ISR
	//------------------------------------------------------------------
	// I2C Asynchronous READ subscription data
	//------------------------------------------------------------------
	I2CAsyncRqst	MPURqst = {&_MPUCallBack, 1};
	//------------------------------------------------------------
    // Try to innitiate to I2C ASYNC processing for MPU
	//------------------------------------------------------------
	if (	I2CRC_OK == I2CAsyncStart(MPU1_IDCx, &MPURqst)	)
		{
		//////////////////////////////////////////////////////////////
		// Bus acqusition in ASYNC mode is successful!
		//////////////////////////////////////////////////////////////
		MPU1_CB._MPU_State		= 0;	// Zero out State Machine
		// NOTE: because of successful bus acqusition I2C interrupt 
		//		 will be routed to _MPUCallBack routine
		}
	}
#endif
//================================================================

//================================================================
#ifdef Use_MPU2
void __attribute__((interrupt, no_auto_psv)) MPU2_Interrupt(void)
	{
	//------------------------------------------------------------
	// Please note that INTx interrupt is configured to run at
	// least at or above I2C interrupt priority, so no I2C event
	// may take place before EXIT from this routine
	//------------------------------------------------------------
	MPU2_IF = 0;	// Clear the INTx interrupt flag or else the
					// CPU will keep vectoring back to the ISR
	//------------------------------------------------------------------
	// I2C Asynchronous READ subscription data
	//------------------------------------------------------------------
	I2CAsyncRqst	MPURqst = {&_MPUCallBack, 2};
	//------------------------------------------------------------
    // Try to innitiate to I2C ASYNC processing for MPU
	//------------------------------------------------------------
	if (	I2CRC_OK == I2CAsyncStart(MPU2_IDCx, &MPURqst)	)
		{
		//////////////////////////////////////////////////////////////
		// Bus acqusition in ASYNC mode is successful!
		//////////////////////////////////////////////////////////////
		MPU2_CB._MPU_State		= 0;	// Zero out State Machine
		// NOTE: because of successful bus acqusition I2C interrupt 
		//		 will be routed to _MPUCallBack routine
		}
	}
#endif
//================================================================

//================================================================
void	_MPUCallBack(uint			ClientParam,
					 I2C_CONBITS*	pCON,
					 I2C_STATBITS*	pSTAT,
					 vuint*			pTRN,
					 vuint*			pRCV)
	{
	MPU_CB*		pCB = MPUpCB(ClientParam);
	if (NULL == pCB)
		// Should never ever happen, but...
		{
		I2CAsyncStop( pCON, pSTAT);
		return;
		}
	//===============================================================
	// NOTE: This I2C interrupt call-back routine is geared specifi-
	//		 cally to supporting asynchronous data read operation for 
	//		 MPU6050 Acc/Gyro sensor
	//===============================================================
	// Process conditions based upon the state of the State Machine
	//===============================================================
	switch (pCB->_MPU_State)
		{
		//=============================================================
		// Set MPU Register Address to Data (0x3B)
		//=============================================================
		case	0:		// Interrupt after initial SEN
			// Sending device address with WRITE cond.
			*(pTRN)			= pCB->_MPU_Addr & 0xFE;
			pCB->_MPU_State	= 1;		// Move state
			break;	
		//-----------------------------------------------------------
		case	1:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address	
			*(pTRN)			= 0x3B;		// MPU6050 Data register address.
			pCB->_MPU_State	= 2;		// Move state
			break;
		//=============================================================
		// Transition to the Reading Data Mode
		//=============================================================
		case	2:		// Interrupt after register address
			// Slave send ACK (confirmed in General Checks);
			// Initiate Repeated Start condition
			pCON->RSEN		= 1;
			pCB->_MPU_State	= 3;		// Move state
			break;
		//-----------------------------------------------------------
		case	3:		// Interrupt after Repeated Start
			// Sending device address with READ cond.
			*(pTRN)			= pCB->_MPU_Addr | 0x01;
			pCB->_MPU_State	= 4;		// Move state
			break;
		//-----------------------------------------------------------
		case	4:		// Interrupt after Device Address with READ
			// Slave send ACK; we switch to READ
			pSTAT->I2COV		= 0;		// Clear receive OVERFLOW bit, if any
			pCON->RCEN			= 1;		// Allow READ.
			pCB->_MPU_BufPos	= 0;		// Reset buffer position
			//----------------------------------------
			pCB->_MPU_State		= 5;		// Move state
			break;
		//=============================================================
		// Read and process data sample
		//=============================================================
		case	5:		// Interrupt after READing Data byte
			// Slave completed sending byte... 
			pCB->_MPU_Buffer[pCB->_MPU_BufPos] = *(pRCV);
										// Retrieve and store data byte
			pCB->_MPU_BufPos++;			// Move buffer address pointer
			//---------------------------------------
			if (pCB->_MPU_BufPos < 14)
				{
				// More bytes to read - generate ACK
				pCON->ACKDT		= 0;
				//----------------------
				pCB->_MPU_State	= 6;	// Move state
				}
			else
				{
				// All 14 bytes are read - terminate READ with NACK
				pCON->ACKDT		= 1;
				//----------------------
				pCB->_MPU_State	= 7;	// Move state
				}
			pCON->ACKEN = 1;		// Innitiate acknowledgement
			break;
		//-----------------------------------------
		case	6:		// Interrupt after ACK
			pSTAT->I2COV	= 0;	// Clear receive OVERFLOW bit, if any
			pCON->RCEN		= 1;	// Allow READ.
			//----------------------------------------
			pCB->_MPU_State	= 5;	// Move state BACK to read next byte
			break;
		//-----------------------------------------
		case	7:		// Interrupt after NACK	- terminate cycle
						// and process retrieved sample
			//-----------------------------------------------------------
			// Terminate current ASYNC session
			//-----------------------------------------------------------
			I2CAsyncStop( pCON, pSTAT);	// Stop I2C ASYNC processing
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
			// 	Yveh	= Xa
			//-----------------------------------------------
			U.VByte[1]			= pCB->_MPU_Buffer[0];
			U.VByte[0]			= pCB->_MPU_Buffer[1];
			pCB->_MPU_Sensor.AY =  U.VInt;
			//-----------------------------------------------
			// 	Xveh	=  Ya
			//-----------------------------------------------
			U.VByte[1]			= pCB->_MPU_Buffer[2];
			U.VByte[0]			= pCB->_MPU_Buffer[3];
			pCB->_MPU_Sensor.AX =  U.VInt;
			//-----------------------------------------------
			// 	Zveh = -Za
			//-----------------------------------------------
			U.VByte[1]			= pCB->_MPU_Buffer[4];
			U.VByte[0]			= pCB->_MPU_Buffer[5];
			pCB->_MPU_Sensor.AZ = -U.VInt;
			//-----------------------------------------------
			// Temperature
			//-----------------------------------------------
			U.VByte[1]				= pCB->_MPU_Buffer[6];
			U.VByte[0]				= pCB->_MPU_Buffer[7];
			pCB->_MPU_Sensor.Temp	= U.VInt;
			//-----------------------------------------------
			// Gyroscopes
			//-----------------------------------------------
			// 	Yveh	=  Xa
			//-----------------------------------------------
			U.VByte[1]			= pCB->_MPU_Buffer[8];
			U.VByte[0]			= pCB->_MPU_Buffer[9];
			pCB->_MPU_Sensor.GY =  U.VInt;
			//-----------------------------------------------
			// 	Xveh	=  Ya
			//-----------------------------------------------
			U.VByte[1]			= pCB->_MPU_Buffer[10];
			U.VByte[0]			= pCB->_MPU_Buffer[11];
			pCB->_MPU_Sensor.GX =  U.VInt;
			//-----------------------------------------------
			// 	Zveh = -Za
			//-----------------------------------------------
			U.VByte[1]			= pCB->_MPU_Buffer[12];
			U.VByte[0]			= pCB->_MPU_Buffer[13];
			pCB->_MPU_Sensor.GZ = -U.VInt;
			//-----------------------------------------------
			if (0 == pCB->_MPU_Ready)
				{
				// First sample in sequence
				// NOTE:	_MPU_Ready reverts to 0
				// 			after exhausting "uint"
				//			range.
				//---------------------------------
				pCB->_MPU_Sample.AX		= pCB->_MPU_Sensor.AX;
				pCB->_MPU_Sample.AY		= pCB->_MPU_Sensor.AY;
				pCB->_MPU_Sample.AZ		= pCB->_MPU_Sensor.AZ;
				//---------------------------------
				pCB->_MPU_Sample.Temp 	= pCB->_MPU_Sensor.Temp;
				//---------------------------------
				pCB->_MPU_Sample.GX		= pCB->_MPU_Sensor.GX;
				pCB->_MPU_Sample.GY		= pCB->_MPU_Sensor.GY;
				pCB->_MPU_Sample.GZ		= pCB->_MPU_Sensor.GZ;
				}
			else
				{
				// Subsequent sample in sequence: accumulate data
				// for subsequent averaging in retrieval routine.
				//---------------------------------
				pCB->_MPU_Sample.AX		+= pCB->_MPU_Sensor.AX;
				pCB->_MPU_Sample.AY		+= pCB->_MPU_Sensor.AY;
				pCB->_MPU_Sample.AZ		+= pCB->_MPU_Sensor.AZ;
				//---------------------------------
				pCB->_MPU_Sample.Temp 	+= pCB->_MPU_Sensor.Temp;
				//---------------------------------
				pCB->_MPU_Sample.GX		+= pCB->_MPU_Sensor.GX;
				pCB->_MPU_Sample.GY		+= pCB->_MPU_Sensor.GY;
				pCB->_MPU_Sample.GZ		+= pCB->_MPU_Sensor.GZ;
				}
			//-----------------------------------------------
			pCB->_MPU_Ready++;	// _MPU_Ready > 0 -> Sample is ready!
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
			I2CAsyncStop( pCON, pSTAT);	// Stop I2C ASYNC processing
		}
	//===============================================================
	return;
	}
//================================================================

