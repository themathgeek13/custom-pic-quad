#include "HMCMAG\HMCMAG_Local.h"
//*******************************************************
#ifdef __MAG_Use__
//*******************************************************


//-----------------------------------------------------
// HMC Management functions
//-----------------------------------------------------
uint		HMCReadID(	byte*	 Buffer,
						uint	 BufLen )
	{
	if (BufLen > 3)
		BufLen	= 3;	// HMC ID is 3 bytes long
	//-------------------------------------------
	return 	_HMCRead(0xA, Buffer, BufLen);
	}
//-----------------------------------------------------
uint		HMCReadStatus(	byte*	 Buffer)
	{
	return 	_HMCRead(0x9, Buffer, 1);
	}
//-----------------------------------------------------
uint		HMCGetMode(		byte*	 Mode)
	{
	return 	_HMCRead(0x2, Mode, 1);
	}
uint		HMCSetMode(		byte	 Mode)
	{
	return 	_HMCWrite(0x2, &Mode, 1);
	}
//-----------------------------------------------------
uint		HMCGetRegA(	byte*	 RegA)
	{
	return 	_HMCRead(0x0, RegA, 1);
	}
uint		HMCSetRegA(	byte	 RegA)
	{
	return 	_HMCWrite(0x0, &RegA, 1);
	}
//-----------------------------------------------------
uint		HMCGetRegB(	byte*	 RegB)
	{
	return 	_HMCRead(0x1, RegB, 1);
	}
uint		HMCSetRegB( byte	 RegB)
	{
	return 	_HMCWrite(0x1, &RegB, 1);
	}
//-----------------------------------------------------


//***************************************************************
#endif /* __MAG_Use__ */
