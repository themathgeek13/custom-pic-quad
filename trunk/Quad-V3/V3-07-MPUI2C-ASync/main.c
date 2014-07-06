#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "Init\Switches.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "SDL\SDL.h"
//---------------------------------
#include "MPU\MPU.h"

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
	//==================================================================
	BLIAsyncStart(50,50);
	TMRDelay(2000);
	BLIAsyncStop();
	//==================================================================
	if (_SW2)
		// Switch 2 is ON - Configuring MPU fo Alt. sensitivity
		RC = MPUInit(0, 3, MPU_GYRO_1000ds, MPU_ACC_4g);
							// Initialize motion Sensor
							// 1 kHz/(0+1) = 1000 Hz (1ms)
							// DLPF=3 => Bandwidth 44 Hz (delay: 4.9 msec)
	else
		// Switch 2 is OFF - Configuring MPU fo normal sensitivity
		RC = MPUInit(0, 3, MPU_GYRO_2000ds, MPU_ACC_2g);
							// Initialize motion Sensor
							// 1 kHz/(0+1) = 1000 Hz (1ms)
	if (RC)	BLIDeadStop("EG", 2);
	//*******************************************************************
	BLISignalOFF();


	//====================================================
	// Asynchronous interface
	//-----------------------------------------------------
	MPUData	Sample;
	if ( (RC = MPUAsyncStart(2)) )
		BLIDeadStop("SSS", 3);
	//-----------------------------------------------------
	while (TRUE)
		{
		Alarm = TMRSetAlarm(100);
		//------------------------------------
		if ( (RC = MPUAsyncReadWhenReady(2, &Sample)) )
			BLIDeadStop("SOS", 3);
		//------------------------
		BLISignalFlip();
		//-------------------------
		SDLPostIfReady((byte*)&Sample, sizeof(Sample));
		//-------------------------
		TMRWaitAlarm(Alarm);
		}

	//*******************************************************************
	return 0;
	}

