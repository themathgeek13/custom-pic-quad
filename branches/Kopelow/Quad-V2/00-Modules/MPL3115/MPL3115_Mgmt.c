#include "MPL3115/MPL3115_Local.h"


//-----------------------------------------------------
// Management functions (synchronous interface)
//-----------------------------------------------------
uint	MPLGetSTAT(byte*	 mplSTAT)

	{ return _MPLRead(0x00, mplSTAT, 1);	}
//-----------------------------------------------------
uint	MPLGetID(	byte*	 mplID)
	{ return _MPLRead(0x0C, mplID, 1); }
//-----------------------------------------------------
uint	MPLGetMODE(byte*	 mplMODE)
	{ return _MPLRead(0x11, mplMODE, 1); }
//-----------------------------------------------------
uint	MPLGetINTSrc(byte*	 mplINTSrc)
	{ return _MPLRead(0x12, mplINTSrc, 1); }
//-----------------------------------------------------
uint	MPLGetCTRL1(byte*	 mplCTRL)
	{ return _MPLRead(0x26, mplCTRL, 1); }
//-----------------------------------------------------
uint	MPLGetCTRL2(byte*	 mplCTRL)
	{ return _MPLRead(0x27, mplCTRL, 1); }
//-----------------------------------------------------
uint	MPLGetCTRL3(byte*	 mplCTRL)
	{ return _MPLRead(0x28, mplCTRL, 1); }
//-----------------------------------------------------
uint	MPLGetCTRL4(byte*	 mplCTRL)
	{ return _MPLRead(0x29, mplCTRL, 1); }
//-----------------------------------------------------
uint	MPLGetCTRL5(byte*	 mplCTRL)
	{ return _MPLRead(0x2A, mplCTRL, 1); }
//-----------------------------------------------------
float	MPLGetBase()
	{ return _MPL_BaseAlt; }
//-----------------------------------------------------



