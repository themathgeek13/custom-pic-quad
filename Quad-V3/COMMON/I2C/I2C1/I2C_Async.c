#include "I2C\I2C_Local.h"

//============================================================
// Asynchronous I2C API (visible externally) component
//============================================================
// <editor-fold defaultstate="collapsed" desc="uint	I2CAsyncStart(uint SubscrID)">
uint	I2CAsyncStart(uint SubscrID)
	{
	//=========================================================
	// Validate run-time conditions
	//---------------------------------------------------------
	if (!_I2C_Init)		return I2CRC_NRDY;
	//=========================================================
	int		i, j;
	//---------------------------------------------------------
	uint	RC		= I2CRC_OK;
	BYTE	CPU_IPL;
	//---------------------------------------------------------
	// Enter I2C (and related modules) CRITICAL SECTION
	//---------------------------------------------------------
	SET_AND_SAVE_CPU_IPL(CPU_IPL, _I2C_IL);
		if (_I2C_CallBack)		{RC = I2CRC_ABSY; goto Finally;}
		if (_I2C_SBSY)			{RC = I2CRC_SBSY; goto Finally;}
		if	(	I2C_SEN
			 || I2C_PEN
			 || I2C_RCEN
			 || I2C_RSEN
			 || I2C_ACKEN
			 || I2C_TRSTAT )
				// Bus is busy with something...?
								{RC = I2CRC_BUSY; goto Finally;}
		//------------------------------------------------------------
		// We can attempt to subscribe for I2C Async notification(s)
		//---------------------------------------------------------
		// First, let's validate SubscrID parameter
		//---------------------------------------------------------
		for (i = 0; i<I2CSubscMax; i++)
			{
			if ((uint)&_I2CSubscr[i] == SubscrID)
				{
				// Subscription ID validated, proceed with activating
				// Async notification
				//--------------------------------------------
				I2C_IF		= 0; 	// Clear  I2C Master interrupt flag
				//---------------------------------------------------------
				// Set Flag indicating Asynchronous operation is in progress
				//---------------------------------------------------------
				_I2C_CallBack	= _I2CSubscr[i].CallBack;
				//////////////////////////////////////////////////////////
				//--------------------------------------------------------
				// Disable subscribers' interrupts
				for (j = 0; j<I2CSubscMax; j++)
					{
					if (_I2CSubscr[j].SubscrIC)
						(*(_I2CSubscr[j].SubscrIC))(0);
					}
				//--------------------------------------------------------
				I2C_IE		= 1;	// Enable I2C Master interrupt
				//--------------------------------------------------------
				goto Finally;
				}
			}
	//---------------------------------------------------------
	// SubscrID does not point to valid Subscription!
	//---------------------------------------------------------
	RC = I2CRC_ISID;
	//---------------------------------------------------------
	// Leave I2C CRITICAL SECTION
	//---------------------------------------------------------
Finally:
  	RESTORE_CPU_IPL(CPU_IPL);
	//=========================================================
	return RC;		
	}
// </editor-fold>
//============================================================
// <editor-fold defaultstate="collapsed" desc="void	I2CAsyncStop()">
void	I2CAsyncStop()
	{
	//--------------------------------------------------------
	// NOTE: Should be called only from I2C interrupt routine
	//       or its extension procedure
	//--------------------------------------------------------
	I2C_STAT		= 0;	// clear STATUS bits
	I2C_PEN 		= 1;	// Initiate Stop on SDA and SCL pins
	//--------------------------------------------------------
	// NOTE: callback reference will be cleared in Interrupt
	//		 routine after "STOP" processed
	//--------------------------------------------------------
	return;
	}
// </editor-fold>
//============================================================
// <editor-fold defaultstate="collapsed" desc="uint	I2CRegisterSubscr(I2CSubscr* Subscr, uint* SubscrID)">
uint	I2CRegisterSubscr(I2CSubscr* Subscr)
	{
	int i;
	//--------------------------------------------------------
	// Check for existing subscription....
	//--------------------------------------------------------
	for (i = 0; i < I2CSubscMax; i++)
		{
		if (_I2CSubscr[i].CallBack == Subscr->CallBack
			&&
			_I2CSubscr[i].SubscrIC == Subscr->SubscrIC)
			{
			// Enable Client's interrupt line
			(*(Subscr->SubscrIC))(1);
			//--------------------------------------------
			// Already registered - return subscription
			// address as "black box" SubscrID
			return (uint) & _I2CSubscr[i];
			}
		}
	//--------------------------------------------------------
	// Attempt to add new subscription....
	//--------------------------------------------------------
	for (i = 0; i < I2CSubscMax; i++)
		{
		if ( NULL == _I2CSubscr[i].CallBack
			&&
			NULL == _I2CSubscr[i].SubscrIC)
			{
			// Found emp-ty slot - "subscribe" and return
			// subscription address as "black box" SubscrID
			_I2CSubscr[i].CallBack = Subscr->CallBack;
			_I2CSubscr[i].SubscrIC = Subscr->SubscrIC;
			//--------------------------------------------
			// Enable Client's interrupt line
			(*(Subscr->SubscrIC))(1);
			//--------------------------------------------
			// Return subscription address as "black box"
			// SubscrID
			return (uint) & _I2CSubscr[i];
			}
		}
	//--------------------------------------------------------
	// Registration unsuccessful...
	//--------------------------------------------------------
	return NULL;
	}
// </editor-fold>
//============================================================
// <editor-fold defaultstate="collapsed" desc="uint	I2CDeRegisterSubscr(uint SubscrID)">
uint	I2CDeRegisterSubscr(uint SubscrID)
	{
	int i;
	//--------------------------------------------------------
	// Check for existing subscription....
	//--------------------------------------------------------
	for (i = 0; i<I2CSubscMax; i++)
		{
		if ((uint)&_I2CSubscr[i] == SubscrID)
			{
			// Subscription ID validated
			//--------------------------------------------
			// Disable Client's interrupt line
			(*(_I2CSubscr[i].SubscrIC))(0);
			// Release respective slot
			//--------------------------------------------
			_I2CSubscr[i].CallBack = NULL;
			_I2CSubscr[i].SubscrIC = NULL;
			//--------------------------------------------
			return I2CRC_OK;
			}
		}
	//--------------------------------------------------------
	return I2CRC_ISID;
	}
// </editor-fold>
//============================================================





