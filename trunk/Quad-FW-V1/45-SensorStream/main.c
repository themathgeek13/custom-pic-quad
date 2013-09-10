#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "HMCMAG\HMCMAG.h"
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
	if (MPUInit(3, 1))	// Initialize motion Sensor - 1 kHz/4 (250 Hz)
		DeadStop("EA", 2);
	//--------------------------
	if (HMCInit(6, 1))	// Initialize magnetic Sensor - max ODR (75 Hz), 1.3 Gs
		DeadStop("EM", 2);
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
	MPUSample		AGSample;
	HMCSample		MSample;
	//--------------------------
	if (MPUAsyncStart())
		DeadStop("A", 1);
	//--------------------------
	if (HMCAsyncStart())
		DeadStop("M", 1);
	//--------------------------
	struct 
		{
		ulong	TS;		// Timestamp of the cycle
		//-----------------------------------------------
		ulong	MPUCount;	// Sequential number of MPU sample
		ulong	MAGCount;	// Sequential number of MAG sample
		//-----------------------------------------------
		// Accelerometer (in units of G)
		//-----------------------------------------------
		Vector	A;
		//-----------------------------------------------
		// Gyroscopes	(in Rad/sec)
		//-----------------------------------------------
		Vector	G;
		//-----------------------------------------------
		// Magnetometer (in mGs)
		//-----------------------------------------------
		Vector	M;
		} UData;
	//*******************************************************************
	BLISignalON();
	while(1)
		{
		TMRDelay(100);
		//------------------------	
		if (ADCGetBatteryStatus() < 30)
			DeadStop("SOS", 3);
		//------------------------	
		RC 	= HMCAsyncReadWhenReady(&MSample);
		if (RC) DeadStop("M", 1);
		//------------------------	
		RC 	= MPUAsyncReadWhenReady(&AGSample);
		if (RC) DeadStop("A", 1);
		//---------------------------------------------	
		UData.MPUCount	= AGSample.Count;
		UData.MAGCount	= MSample.Count;
		//------------------------
		VectorCopy(&AGSample.A, &UData.A);
		VectorCopy(&AGSample.G, &UData.G);
		VectorCopy(&MSample.M,  &UData.M);
		//------------------------
		UData.TS	= AGSample.TS;
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&UData, sizeof(UData));
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





