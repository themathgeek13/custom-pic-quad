#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "MPU6050\MPU6050_Local.h"
#include "UART\UART.h"


int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	ADCInit(3);			// Initialize ADC to control battery
	I2CInit(5, 0);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	TMRDelay(1000);		// Wait for 1 sec so that the shake from turning
						// power switch on dissipates...
	//--------------------------
	BLISignalON();
	//--------------------------
	if (MPUInit(3, 1))	// Initialize motion Sensor - 1 kHz/4 (250 Hz)
		BLIDeadStop("A", 1);
	//--------------------------
	BLISignalOFF();
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
						// BaudRate =  1	=>   2400 bps
						// BaudRate =  2	=>   4800 bps
						// ...
						// BaudRate = 48	=> 115200 bps
						// BaudRate = 99	=> 250000 bps - special case
	//*******************************************************************
	MPUSample		Sample;
	//*******************************************************************
	if ( MPUAsyncStart() )
		BLIDeadStop("E", 1);
	//--------------------------
	while(1)
		{
		TMRDelay(500);
		//------------------------	
		if (ADCGetBatteryStatus() < 30)
			BLIDeadStop("SOS", 3);
		//------------------------
		if ( MPUAsyncReadWhenReady(&Sample) )
			BLIDeadStop("M", 1);
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&Sample, sizeof(Sample));
		//---------------------------------------------	
		}
	return 1;
	}






