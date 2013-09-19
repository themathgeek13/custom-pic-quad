#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "I2C\I2C.h"
#include "I2C\I2C_Local.h"
#include "MPU6050\MPU6050.h"
#include "HMCMAG\HMCMAG.h"

#include "DBG\DBG.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	//*******************************************************************
	_T1IE 	= 0; 		// Temporarily disable Timer1 interrupt
	//*******************************************************************
	BLIInit();			// Initialize Signal interface
	DBGInit();
	I2CInit(5, 1);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//*******************************************************************
	uint			RC			= 0;
	int				i;
	//--------------------------
	MPUSample		AGSample;
	HMCSample		MSample;
	//*******************************************************************
	RC = MPUInit(2, 1);		// Initialize Sensor - 1 kHz / 3 (3 msec)
		while(RC);
	//--------------------------
	RC = HMCInit(6, 2, 0);		// Initialize Sensor:
								// ODR  = 6 (max, 75 Hz),
								// Gain = 2 (1.3 Gs)
								// DLPF = 0 (no averaging)
		while(RC);
	//*******************************************************************
	BLISignalOFF();

	//====================================================
	// Testing MPU and HMC together in real-life scenario
	//====================================================
	RC = MPUAsyncStart();
	if(RC)
		BLIDeadStop("S", 1);
	//------------------------
	RC = HMCAsyncStart();
	if(RC)
		BLIDeadStop("S", 1);
	//------------------------------------
	DBG_2_ON();
	RC 	= HMCAsyncReadWhenReady(&MSample);
	DBG_2_OFF();
	if (RC)
		BLIDeadStop("M", 1);
	//------------------------
	DBG_1_ON();
	RC 	= MPUAsyncReadWhenReady(&AGSample);
	DBG_1_OFF();
	if (RC)
		BLIDeadStop("A", 1);
	//====================================================
	// Alternate 1
	//====================================================
	while (1)
		{
		BLISignalFlip();
		// Work cycle - about 20 msec
		//------------------------------------
		TMRDelay(17);
		//------------------------------------
		DBG_1_ON();
		RC 	= MPUAsyncReadWhenReady(&AGSample);
		DBG_1_OFF();
		if (RC)
			BLIDeadStop("A", 1);
		//------------------------------------
		DBG_2_ON();
		RC 	= HMCAsyncRead(&MSample);
		DBG_2_OFF();
		}


	//====================================================
	// Alternate 2
	//====================================================
	while (1)
		{
		BLISignalFlip();
		// Work cycle - about 20 msec
		for (i = 0; i < 6; i++)
			{
			//------------------------------------
			DBG_1_ON();
			RC 	= MPUAsyncReadWhenReady(&AGSample);
			DBG_1_OFF();
			if (RC)
				BLIDeadStop("A", 1);
			//------------------------------------
			DBG_2_ON();
			RC 	= HMCAsyncRead(&MSample);
			DBG_2_OFF();
			}
		}


	//====================================================
	// Testing HMC alone
	//====================================================
	while (1)
		{
		DBG_1_ON();
		RC = HMCAsyncStart();
		if(RC)
			BLIDeadStop("S", 1);
		for (i=0; i<3; i++)
			{
			TMRDelay(15);
			DBG_2_ON();
			RC 	= HMCAsyncReadWhenReady(&MSample);
			DBG_2_OFF();
			if (RC)
				BLIDeadStop("M", 1);
			BLISignalFlip();
			}
		DBG_1_OFF();
		//---------------------------
		RC = HMCAsyncStop();
		if(RC)
			BLIDeadStop("T", 1);
		TMRDelay(30);
		}


	//====================================================
	// Testing MPU alone
	//====================================================
	while (1)
		{
		DBG_1_ON();
		RC = MPUAsyncStart();
		if(RC)
			BLIDeadStop("S", 1);
		for (i=0; i<3; i++)
			{
//			TMRDelay(5);
			DBG_2_ON();
			RC 	= MPUAsyncReadWhenReady(&AGSample);
			DBG_2_OFF();
			if (RC)
				BLIDeadStop("A", 1);
			BLISignalFlip();
			}
		DBG_1_OFF();
		//---------------------------
		RC = MPUAsyncStop();
		if(RC)
			BLIDeadStop("T", 1);
		TMRDelay(6);
		}


	return 1;
	}

