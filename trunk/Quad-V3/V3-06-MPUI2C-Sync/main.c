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
	I2CInit(5, 1);	// First param: IL = 5 (interrupt request priority
					// Second param: I2C speed
					// 0 - lowest (123 kHz at Fcy = 64MHz)
					// 1 - 200 kHz - MPU-6050 stable
					// 2 - 400 kHz
					// 3 - 1 MHz
	//-------------------------------------------------------------------
	uint			RC			= 0;
	ulong			Alarm		= 0;
	//==================================================================
	BLIAsyncStart(100,100);
	TMRDelay(2000);
	BLIAsyncStop();
	//==================================================================
	BLIAsyncStart(50,50);
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
	BLIAsyncStop();
	//*******************************************************************
	BLISignalOFF();

	//====================================================
//	byte			mpuID;
//	byte			mpuDLPF;
//	byte			mpuINT;
//	byte			mpuPWRM1;
//	//---------------------------
//	RC = MPUReadID(2, &mpuID);
//	RC = MPUGetPWRM1(2, &mpuPWRM1);
//	RC = MPUGetDLPF(2, &mpuDLPF);
//	RC = MPUGetINT(2, &mpuINT);
	//-----------------------------------------------------

	//====================================================
	// Synchronous interface
	//-----------------------------------------------------
	struct
		{
		MPUData	Sample1;
		MPUData	Sample2;
		} MPU;
	//-----------------------------------------------------
	while (TRUE)
		{
		Alarm = TMRSetAlarm(500);
		//------------------------------------
		if ( (RC = MPUReadSample(1, &MPU.Sample1)) )
			BLIDeadStop("SOS", 3);
		//------------------------
		if ( (RC = MPUReadSample(2, &MPU.Sample2)) )
			BLIDeadStop("SOS", 3);
		//------------------------------------
		BLISignalFlip();
		//-------------------------
		SDLPostIfReady((byte*)&MPU, sizeof(MPU));
		//-------------------------
		TMRWaitAlarm(Alarm);
		}

	//*******************************************************************
	return 0;
	}

