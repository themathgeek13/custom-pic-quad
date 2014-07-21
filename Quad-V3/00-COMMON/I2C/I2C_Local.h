#include "I2C\I2C.h"
#include "I2C\I2C_Profile.h"

//==================================================================
#ifndef __I2C_Local_H
#define __I2C_Local_H
//==================================================================

//==================================================================
// Variables shared (across I2C modules) - set in I2CInit
//==================================================================
extern			byte	_I2C_IL;		// I2C interrupt level 
extern			uint	_I2C_Init;		// Init flag
extern			uint	_I2C_BRG;		// Calculated BRG value
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="_I2C_CB - I2C Library control block">
// Prototype for I2C Library Control Block
//------------------------------------------------------------------
typedef volatile struct
	{
	// ASYNC operation Flag	for the Module
	uint			_I2C_SBSY;		
	//------------------------------------------------------------
	// Address of the current I2C interrupt callback function
	// (corresponds to one of the active subscribers)
	I2CCallBack		_I2C_CallBack;
	// "Black-box" parameter for the callback function
	uint			_I2C_CallBackArg;
	//------------------------------------------------------------------
	// Array of I2C Asynchronous Access Subscribers to the Module
	//------------------------------------------------------------------
	I2CAsyncRqst		_I2CRqstQueue[I2CMaxAsyncRqst];
	//------------------------------------------------------------------
	// Addresses of I2C Control Registers for the Module
	//------------------------------------------------------------------
	vuint *	pI2C_CON;		// I2CxCON
	vuint *	pI2C_STAT;		// I2CxSTAT
	vuint *	pI2C_TRN;		// I2CxTRN
	vuint *	pI2C_RCV;		// I2CxRCV
	} _I2C_CB;
//==================================================================
// Control Blocks for I2C modules - initialized in I2CInit(...)
//------------------------------------------------------------------
#ifdef _I2C_UseI2C1
// Control Block for I2C1 Module
extern	_I2C_CB		_I2C1_CB;
#endif
//------------------------------------------------------------------
#ifdef _I2C_UseI2C2
// Control Block for I2C2 Module
extern	_I2C_CB		_I2C2_CB;
#endif
//==================================================================
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="Control Block Helper Functions">
//------------------------------------------------------------------
// Control Block Helper Functions
//==================================================================
static inline _I2C_CB* I2CpCB(uint CB_ID)
	{
	switch (CB_ID)
		{
		case 1:
			#ifdef _I2C_UseI2C1
			return &_I2C1_CB;
			#else
			return NULL;
			#endif
		case 2:
			#ifdef _I2C_UseI2C2
			return &_I2C2_CB;
			#else
			return NULL;
			#endif
		default:
			return NULL;
		}
	}
//------------------------------------------------------------------
static inline I2C_CONBITS*	I2CpCON(_I2C_CB* pCB)
	{ return (I2C_CONBITS*) (pCB->pI2C_CON); }
//------------------------------------------------------------------
static inline I2C_STATBITS*	I2CpSTAT(_I2C_CB* pCB)
	{ return (I2C_STATBITS*) (pCB->pI2C_STAT); }
//------------------------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
// <editor-fold defaultstate="collapsed" desc="I2Cx Helper Functions">
//------------------------------------------------------------------
// I2Cx Helper Functions
//==================================================================
static inline uint	I2CGetStatus(	_I2C_CB*		pCB,
									I2C_CONBITS*	pCON,
									I2C_STATBITS*	pSTAT)
	{
	if (pCB->_I2C_CallBack)	return I2CRC_ABSY;
	if (pCB->_I2C_SBSY)		return I2CRC_SBSY;
	if	(	pCON->SEN
		 || pCON->PEN
		 || pCON->RCEN
		 || pCON->RSEN
		 || pCON->ACKEN
		 || pSTAT->TRSTAT )
			// Bus is busy with something...?
			return I2CRC_BUSY;
	//-----------------------------
	return I2CRC_OK;
	}
//------------------------------------------------------------------
static inline void I2CSetIE(uint CB_ID, uint Value)
	{
	switch (CB_ID)
		{
		case 1:
			#ifdef _I2C_UseI2C1
				_MI2C1IE = Value;
			#endif
			break;
		case 2:
			#ifdef _I2C_UseI2C2
				_MI2C2IE = Value;
			#endif
			break;
		default:
			break;
		}
	}
//------------------------------------------------------------------
static inline void I2CSetIF(uint CB_ID, uint Value)
	{
	switch (CB_ID)
		{
		case 1:
			#ifdef _I2C_UseI2C1
				_MI2C1IF = Value;
			#endif
			break;
		case 2:
			#ifdef _I2C_UseI2C2
				_MI2C2IF = Value;
			#endif
			break;
		default:
			break;
		}
	}
//------------------------------------------------------------------
// </editor-fold>
//==================================================================

//==================================================================
// Internal (local) I2C Initialization routines
//==================================================================
#ifdef _I2C_UseI2C1
void	I2CInitI2C1();
#endif
#ifdef _I2C_UseI2C2
void	I2CInitI2C2();
#endif

//==================================================================
// Internal (local) components of Synchronous I2C interface
//==================================================================
void	I2CIdle(	_I2C_CB* pCB);
//------------------------------------------------------------------
void	I2CStart(	_I2C_CB* pCB);
void	I2CReStart(	_I2C_CB* pCB);
void	I2CStop(	_I2C_CB* pCB);
//------------------------------------------------------------------
uint	I2CMasterWriteByte(	_I2C_CB* pCB, byte data);
uint	I2CMasterReadByte(	_I2C_CB* pCB, byte* data, uint Flag);
//------------------------------------------------------------------

#endif



