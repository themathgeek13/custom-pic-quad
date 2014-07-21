#include "System.h"
#include "MPL\MPL_Local.h"

//================================================================
void __attribute__((interrupt, no_auto_psv)) MPL_Interrupt(void)
	{
	//------------------------------------------------------------
	// Please note that MPL interrupt (INTx) is configured to run
	// at least at or above I2C interrupt priority, so no I2C
	// event may take place before EXIT from this routine
	//------------------------------------------------------------
	MPL_IF = 0;		// Clear the MPL  interrupt flag or else
					// the CPU will keep vectoring back to the ISR
	//------------------------------------------------------------
	// Capture status of the Interrupt Line
	// (interrupt may come from Timer)
	_MPL_PortLvl = MPL_INT_PORT;
	//------------------------------------------------------------------
	// I2C Asynchronous READ subscription data
	//------------------------------------------------------------------
	I2CAsyncRqst	MPLRqst = {&_MPLCallBack, NULL};
	//------------------------------------------------------------
    // Try to innitiate I2C ASYNC processing for MPL
	//------------------------------------------------------------
	if (	I2CRC_OK == I2CAsyncStart(MPL_I2Cx, &MPLRqst)	)
		{
		//////////////////////////////////////////////////////////////
		// Bus acqusition in ASYNC mode is successful!
		//////////////////////////////////////////////////////////////
		_MPL_State		= 0;	// Zero out State Machine
		// NOTE: because of successful bus acqusition I2C interrupt
		//		 will be routed to _MPLCallBack routine
		}
	}
//================================================================

//================================================================
void	_MPLCallBack(uint			ClientParam,
					 I2C_CONBITS*	pCON,
					 I2C_STATBITS*	pSTAT,
					 vuint*			pTRN,
					 vuint*			pRCV)
	{
	//===============================================================
	// NOTE: This I2C interrupt call-back routine is geared specifi-
	//		 cally to supporting asynchronous data read operation for 
	//		 MPL3115 Altitude/Pressure sensor
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
			*(pTRN)	= MPL_Addr & 0xFE;
			_MPL_State	= 1;		// Move state
			return;
		//-----------------------------------------------------------
		case	1:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address	
			*(pTRN)		= 0x01;		// MPL3115 Data register address.
			_MPL_State	= 2;		// Move state
			return;
		//=============================================================
		// Transition to the Reading Data Mode
		//=============================================================
		case	2:		// Interrupt after register address
			// Slave send ACK (confirmed in General Checks);
			// Initiate Repeated Start condition
			pCON->RSEN	= 1;
			_MPL_State	= 3;		// Move state
			return;
		//-----------------------------------------------------------
		case	3:		// Interrupt after Repeated Start
			// Sending device address with READ cond.
			*(pTRN)		= MPL_Addr | 0x01;
			_MPL_State	= 4;		// Move state
			return;
		//-----------------------------------------------------------
		case	4:		// Interrupt after Device Address with READ
			// Slave send ACK; we switch to READ
			pSTAT->I2COV	= 0;		// Clear receive OVERFLOW bit, if any
			pCON->RCEN		= 1;		// Allow READ.
			_MPL_BufPos		= 0;		// Reset buffer position
			//----------------------------------------
			_MPL_State	= 5;		// Move state
			return;
		//=============================================================
		// Read and process data sample
		//=============================================================
		case	5:		// Interrupt after READing Data byte
			// Slave completed sending byte...
			// Retrieve and store data byte
			_MPL_Buffer[_MPL_BufPos] = *(pRCV);
			_MPL_BufPos++;				// Move buffer address pointer
			//---------------------------------------
			if (_MPL_BufPos < 5)		// While we do not use Temp
										// from the sensor, we still
										// have to read it... (last 2 bytes)
				// More bytes to read
				{
				// Generate ACK for the byte read
				pCON->ACKDT	= 0;
				//--------------
				_MPL_State	= 6;	// Move state
				}
			else
				// All 5 bytes are read
				{
				// Generate NACK for the last byte read
				pCON->ACKDT	= 1;
				//--------------
				_MPL_State	= 7;	// Move state
				}
			pCON->ACKEN = 1;		// Innitiate acknowledgement
			return;
		//-----------------------------------------
		case	6:		// Interrupt after ACK
			pSTAT->I2COV 	= 0;	// Clear receive OVERFLOW bit, if any
			pCON->RCEN		= 1;	// Allow READ.
			//----------------------------------------
			_MPL_State	= 5;	// Move state BACK to read next byte
			return;
		//=============================================================
		// After we consumed the Sample, we need to innitiate the new
		// OST cycle by reading the CtrlR1 and then writing it back
		// with OST bit set.
		//=============================================================
		case	7:		// Interrupt after NACK	- switch direction to
						// WRITE starting with "Repeated Start"
			// Initiate Repeated Start condition
			pCON->RSEN	= 1;
			_MPL_State	= 8;		// Move state
			return;
		//-----------------------------------------------------------
		case	8:		// Interrupt after RSEN
			// Sending device address with WRITE cond.
			*(pTRN)		= MPL_Addr & 0xFE;
			_MPL_State	= 9;		// Move state
			return;
		//-----------------------------------------------------------
		case	9:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address	
			*(pTRN)		= CtrlR1Addr;	// MPL3115 CtrlR1 address.
			_MPL_State	= 10;			// Move state
			return;
		//=============================================================
		// Transition to the Reading Data Mode
		//=============================================================
		case	10:		// Interrupt after sending register address
			// Slave send ACK (confirmed in General Checks);
			// Initiate Repeated Start condition
			pCON->RSEN	= 1;
			_MPL_State	= 11;		// Move state
			return;
		//-----------------------------------------------------------
		case	11:		// Interrupt after Repeated Start
			// Sending device address with READ cond.
			*(pTRN)		= MPL_Addr | 0x01;
			_MPL_State	= 12;		// Move state
			return;
		//-----------------------------------------------------------
		case	12:		// Interrupt after Device Address with READ
			// Slave send ACK; we switch to READ
			pSTAT->I2COV		= 0;		// Clear receive OVERFLOW bit, if any
			pCON->RCEN			= 1;		// Allow READ.
			//----------------------------------------
			_MPL_State	= 13;		// Move state
			return;
		//=============================================================
		// Read CtrlR1
		//=============================================================
		case	13:		// Interrupt after READing Data byte
			// Slave completed sending byte... 
			_MPL_CtrlR1 = *(pRCV);	// Retrieve and store data byte
			//---------------------------------------
			// Generate NACK for the last byte read
			pCON->ACKDT 	= 1;
			pCON->ACKEN 	= 1;
			//---------------------------------------
			_MPL_State	= 14;	// Move state
			return;
		//=============================================================
		// Write CtrlR1 with OST bit set
		//=============================================================
		case	14:		// Interrupt after ACK	- switch direction to
						// WRITE starting with "Repeated Start"
			// Initiate Repeated Start condition
			pCON->RSEN	= 1;
			_MPL_State	= 15;		// Move state
			return;
		//-----------------------------------------------------------
		case	15:		// Interrupt after RSEN
			// Sending device address with WRITE cond.
			*(pTRN)		= MPL_Addr & 0xFE;
			_MPL_State	= 16;		// Move state
			return;
		//-----------------------------------------------------------
		case	16:		// Interrupt after device address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with register address
			*(pTRN)		= CtrlR1Addr;	// MPL3115 CtrlR1 address.
			_MPL_State	= 17;			// Move state
			return;
		//-----------------------------------------------------------
		case	17:		// Interrupt after CtrlR1 address
			// Slave send ACK (confirmed in General Checks);
			// We proceed with new value for CtrlR1
			*(pTRN)		= _MPL_CtrlR1 | CtrlR1SetOST;
			_MPL_State	= 18;		// Move state
			return;
		//-----------------------------------------------------------
		case	18:		// Interrupt after CtrlR1 write
			// Slave send ACK (confirmed in General Checks);
			//-----------------------------------------------------------
			// Terminate current ASYNC session
			//-----------------------------------------------------------
			I2CAsyncStop( pCON, pSTAT);	// Stop I2C ASYNC processing
			//-----------------------------------------------------------
			if (_MPL_PortLvl > 0) // Data read was in responce to DRDY
				{
				//=======================================================
				// Construct 20-bit ALT sample as integer
				//-------------------------------------------------------
				long Alt = *((sbyte*)&_MPL_Buffer[0]);
				Alt = Alt << 8;
				Alt = Alt |  _MPL_Buffer[1];
				Alt = Alt << 8;
				Alt = Alt |  _MPL_Buffer[2];
				Alt = Alt >> 4;
				//-------------------------------------------------------
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
				//-------------------------------------------------------
				_MPL_Ready++;		// _MPL_Ready > 0 -> Sample is ready!
				//-------------------------------------------------------
				}
			_MPL_DataTS = TMRGetTS();
			//-----------------------------------------------------------
			return;

		//=============================================================
		// Oops! something is terribly wrong with the State Machine...
		//=============================================================
		default:
			//-----------------------------------------------------------
			// Terminate current ASYNC session
			//-----------------------------------------------------------
			I2CAsyncStop( pCON, pSTAT);	// Stop I2C ASYNC processing
			return;
		}
	//===============================================================
	}
//================================================================

