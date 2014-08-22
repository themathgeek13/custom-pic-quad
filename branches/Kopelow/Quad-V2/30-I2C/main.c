#include "System.h"
//---------------------------------
#include "Init/Init.h"
#include "TMR/TMR.h"
#include "BLI/BLI.h"
#include "I2C/I2C.h"
#include "I2C/I2C_Local.h"
#include "UART/UART_TX.h"
//---------------------------------
#include "MPU6050/MPU6050.h"
#include "HMCMAG/HMCMAG.h"
#include "MPL3115/MPL3115.h"
//---------------------------------

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
        //--------------------------
	BLIInit();			// Initialize Signal interface
	I2CInit(5, 1);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at
	// BaudRate =   48	=>   115,200 bps	- ZigBEE
	//--------------------------------------
	// BaudRate =  100	=>   250,000 bps
	// BaudRate =  200	=>   500,000 bps
	// BaudRate =  250	=>   625,000 bps
	// BaudRate =  350	=>   833,333 bps	- SD Logger, FTDI cable
	// BaudRate =  500	=> 1,250,000 bps
	// BaudRate = 1000	=> 2,500,000 bps
	//*******************************************************************

	if ( MPUInit(0, 3) )	// Initialize motion Sensor
							// 1 kHz/(0+1) = 1000 Hz (1ms)
							// DLPF=3 => Bandwidth 44 Hz (delay: 4.9 msec)
		BLIDeadStop("EG", 2);
	//--------------------------
        #ifdef __HMC_Use__
        if (HMCInit(6, 1, 0))	// Initialize magnetic Sensor
							// ODR  = 6 (max, 75 Hz),
							// Gain = 1 (1.3 Gs)
							// DLPF = 0 (no averaging)
		BLIDeadStop("EM", 2);
        #endif
	//--------------------------
        #ifdef __MPL_Use__
	if ( MPLInit(5) )		// Average over 32 samples providing
							// update rate about 10 Hz
		BLIDeadStop("EA", 2);
        #endif
	//*******************************************************************
	uint			RC			= 0;
	ulong			Alarm		= 0;
	ulong			TS			= 0;
	//-------------------------------
	struct
		{
		ulong			TS;
                MPUData                 IMUData;
		HMCSample		MagData;
		MPLData 		AltData;
		}	UData;
	//*******************************************************************
	BLIAsyncStart(100, 50);
        #ifdef __MPL_Use__
	RC = MPLSetGround();
	if (RC) BLIDeadStop("SOS", 3);	// Failure...
        #endif
	BLIAsyncStop();
	//====================================================
	
	BLISignalOFF();
	//====================================================
	// Testing MPU, HMC, and MPL together in a real-life
	// scenario
	//====================================================
	if(MPUAsyncStart()) 	BLIDeadStop("SG", 2);
	//------------------------
        #ifdef __HMC_Use__
        if(HMCAsyncStart())		BLIDeadStop("SM", 2);
        #endif
	//------------------------
        #ifdef __MPL_Use__
	if(MPLAsyncStart())		BLIDeadStop("SA", 2);
	RC = MPLAsyncReadWhenReady(&UData.AltData);
	if (RC) BLIDeadStop("SAS", 3);	// Failure...
        #endif
	//====================================================
	while (TRUE)
		{
		Alarm = TMRSetAlarm(500);
		//------------------------------------
		RC 	= MPUAsyncReadIfReady(&UData.IMUData);
		if (MPU_OK != RC && MPU_NRDY != RC)
			BLIDeadStop("G", 1);
		//------------------------
                #ifdef __HMC_Use__
		RC 	= HMCAsyncReadIfReady(&UData.MagData);
		if (HMC_OK != RC && HMC_NRDY != RC)
			BLIDeadStop("M", 1);
                #endif
		//------------------------
                #ifdef __MPL_Use__
		RC = MPLAsyncReadIfReady(&UData.AltData);
		if (MPL_OK != RC && MPL_NRDY != RC)
			BLIDeadStop("A", 3);	// Failure...
                #endif
		//-------------------------
		UData.TS	= TMRGetTS();
		//-------------------------
		if (0 == TS)	TS = UData.TS;
		UData.TS -= TS;
		BLISignalFlip();
		//-------------------------
		UARTPostIfReady((byte*)&UData, sizeof(UData));
		//-------------------------
		TMRWaitAlarm(Alarm);

		}
	//====================================================
	
	

	return 1;
	}

