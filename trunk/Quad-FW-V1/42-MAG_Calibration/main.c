#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "HMCMAG\HMCMAG.h"
#include "HMCMAG\HMCMAG_Local.h"
#include "UART\UART.h"

void DeadStop(char * pStr, uint Length);

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	ADCInit(3);			// Initialize ADC to control battery
	I2CInit(5, 0);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	TMRDelay(1000);		// Wait for 1 sec so that the shake from turning on
						// power switch dissipates...
	//--------------------------
//	if (HMCInit(6, 0))	// Initialize magnetic Sensor - max ODR (75 Hz), 0.88 Gs
	if (HMCInit(6, 1))	// Initialize magnetic Sensor - max ODR (75 Hz), 1.30 Gs
//	if (HMCInit(6, 2))	// Initialize magnetic Sensor - max ODR (75 Hz), 1.90 Gs
		DeadStop("M", 1);
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
						// BaudRate =  1	=>   2400 bps
						// BaudRate =  2	=>   4800 bps
						// ...
						// BaudRate = 48	=> 115200 bps
						// BaudRate = 99	=> 250000 bps - special case
	//*******************************************************************
	uint			RC			= 0;
	//--------------------------
	HMCSample		MSample;
	_HMCRawData		MRawData;
	//--------------------------
//	if (HMCAsyncStart())
//		DeadStop("E", 1);
	//*******************************************************************
	BLISignalON();
	while(1)
		{
		TMRDelay(13);
		//------------------------	
		if (ADCGetBatteryStatus() < 30)
			DeadStop("SOS", 3);
		//------------------------	
		RC 	= _HMCReadRawData(&MRawData);
		if (RC) DeadStop("M", 1);
		//-----------------------------------------------
		// Timestamp and Count
		//-----------------------------------------------
		MSample.TS 	= TMRGetTS();
		MSample.Count	= ++_HMC_Count;
		//-----------------------------------------------
		// Raw magnetometer data
		//-----------------------------------------------
		MSample.M.X		= MRawData.MX;
		MSample.M.Y		= MRawData.MY;
		MSample.M.Z		= MRawData.MZ;
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&MSample, sizeof(MSample));
		//---------------------------------------------	
		BLISignalFlip();
		}
	return 1;
	}

void DeadStop(	char * pStr, uint Length)
	{
	BLIAsyncMorse(pStr, Length);
	while (1);
	}





