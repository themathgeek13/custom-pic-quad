#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "Init\Switches.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "SDL\SDL.h"
//---------------------------------
#include "MPU\MPU.h"	// MPU-6050 - gyroscope/accelerometer
#include "MPL\MPL.h"	// MPL-3115A2 - barometric altimeter

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
	// Switch 2 controls the I2C Bus speed
	//-------------------------------------------------------------------
	// First param: IL = 5 (interrupt request priority
	//-------------------------------------------------------------------
	// Second param: I2C speed
	// 0 - lowest (123 kHz at Fcy = 64MHz)
	// 1 - 200 kHz - MPU-6050 stable
	// 2 - 400 kHz
	// 3 - 1 MHz
	//-------------------------------------------------------------------
	if (_SW1)
		// Switch 2 is ON - Configuring I2C at 1 MHz
		I2CInit(5, 3);
	else
		// Switch 2 is OFF - Configuring I2C at 400 kHz
		I2CInit(5, 2);
	//*******************************************************************
	uint			RC			= 0;
	ulong			Alarm		= 0;
	//==================================================================
	BLIAsyncStart(50,50);
	TMRDelay(5000);
	BLIAsyncStop();
	//==================================================================
	// Initialize MPU-6050
	//------------------------------------------------------------------
	if (_SW2)
		// Switch 2 is ON - Configuring MPU fo Alt. sensitivity
		RC = MPUInit(0, 1, MPU_GYRO_1000ds, MPU_ACC_4g);
							// Initialize motion Sensor
							// 1 kHz/(0+1) = 1000 Hz (1ms)
							// DLPF = 3 => Bandwidth 44 Hz (delay: 4.9 msec)
	else
		// Switch 2 is OFF - Configuring MPU fo normal sensitivity
		RC = MPUInit(0, 1, MPU_GYRO_2000ds, MPU_ACC_2g);
							// Initialize motion Sensor
							// 1 kHz/(0+1) = 1000 Hz (1ms)
							// DLPF = 1 => Bandwidth 184 Hz (delay: 2.0 msec)
	if (RC)	BLIDeadStop("EG", 2);
	//-------------------------------------------------------------------
	// Initialize MPL3115 Altimeter
	//------------------------------------------------------------------
	// OSR = 3 => Average over 2^3=  8 samples, update rate about 38 Hz
	//			  Sample-to-sample dev +/- 3 m
	// OSR = 4 => Average over 2^4= 16 samples, update rate about 20 Hz
	// OSR = 5 => Average over 2^5= 32 samples, update rate about 10 Hz
	// OSR = 6 => Average over 2^6= 64 samples, update rate about  6 Hz
	// OSR = 7 => Average over 2^7=128 samples, update rate about  3 Hz
	//------------------------------------------------------------------
	byte	OSR	= 3;
	//------------------------------------------------------------------
	if ( MPLInit (OSR) )
		BLIDeadStop ("EB", 2);
	//*******************************************************************
	struct
		{
		MPUData		MPUSample1;
		MPUData		MPUSample2;
		MPLData		MPLSample;
		} SensorData;
	//=====================================================
	// Initialize Asynchronous mode
	//-----------------------------------------------------
	if ( (RC = MPUAsyncStart(1)) )
		BLIDeadStop("S1", 2);
	//------------------------------
	if ( (RC = MPUAsyncStart(2)) )
		BLIDeadStop("S2", 2);
	//-----------------------------------------------------
	if ( (RC = MPLAsyncStart()) )
		BLIDeadStop("S3", 2);
	//=====================================================
	// Main Loop
	//-----------------------------------------------------
	BLISignalOFF();
	while (TRUE)
		{
		Alarm = TMRSetAlarm(1000);
		//-----------------------------------------------------
		if ( (RC = MPUAsyncReadWhenReady(1, &SensorData.MPUSample1)) )
			BLIDeadStop("SOS", 3);
		//--------------------------
		if ( (RC = MPUAsyncReadWhenReady(2, &SensorData.MPUSample2)) )
			BLIDeadStop("SOS", 3);
		if (MPL_OK != MPLAsyncReadWhenReady(&SensorData.MPLSample))
			BLIDeadStop("SOS", 3);
		//-----------------------------------------------------
		BLISignalFlip();
		//-------------------------
		SDLPostIfReady((byte*)&SensorData, sizeof(SensorData));
		//-------------------------
		TMRWaitAlarm(Alarm);
		}

	//*******************************************************************
	return 0;
	}

