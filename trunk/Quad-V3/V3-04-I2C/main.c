#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "Init\Switches.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "SDL\SDL.h"
//---------------------------------
#include "MPU\MPU.h"
#include "MPU\MPU_Local.h"

int main(void)
	{

	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
	// Switch 1 controls the Serial Data Logger (SDL) communication speed
	//-------------------------------------------------------------------
	if (_SW1)
		// Switch 1 is ON - Configuring SDL for PIC-to-PIC
		// high-speed communication at 1 MBaud
		SDLInit(3, BAUD_1M);
	else
		// Switch 1 is OFF - Configuring SDL for ZigBEE
		// wireless communication at 115.2 KBaud
		SDLInit(3, BAUD_115200);
	//*******************************************************************
	I2CInit(5, 1);
	//-------------------------------------------------------------------
	uint			RC			= 0;
	ulong			Alarm		= 0;
	MPUData			MPUSample;
	byte			mpuID;
	byte			mpuDLPF;
	byte			mpuINT;
	byte			mpuPWRM1;
	//==================================================================
	BLIAsyncStart(100,100);
	TMRDelay(2000);
	BLIAsyncStop();
	//==================================================================
	BLIAsyncStart(50,50);
	if ( MPUInit(0, 3, MPU_GYRO_2000ds, MPU_ACC_2g) )
							// Initialize motion Sensor
							// 1 kHz/(0+1) = 1000 Hz (1ms)
							// DLPF=3 => Bandwidth 44 Hz (delay: 4.9 msec)
		BLIDeadStop("EG", 2);
	BLIAsyncStop();
	//*******************************************************************
	BLISignalOFF();
	RC = MPUReadID(	 &mpuID);
	RC = MPUGetPWRM1(&mpuPWRM1);
	RC = MPUGetDLPF( &mpuDLPF);
	RC = MPUGetINT(	 &mpuINT);
	//-----------------------------------------------------

	//====================================================
	// Synchronous interface
	//-----------------------------------------------------
	_MPURawData	RawData;
	//-----------------------------------------------------
	while (TRUE)
		{
		Alarm = TMRSetAlarm(100);
		//------------------------------------
		if ( (RC = _MPUReadRawData(&RawData)) )
			BLIDeadStop("SOS", 3);
		//------------------------
		BLISignalFlip();
		//-------------------------
		SDLPostIfReady((byte*)&MPUSample, sizeof(MPUSample));
		//-------------------------
		TMRWaitAlarm(Alarm);
		}

	//*******************************************************************
	return 0;
	}

