#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "UART\UART.h"
#include "ADC\ADC.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	ADCInit(3);			// Initialize ADC
	UARTInitTX(6, 48);	// Initialize UART1 for TX
						// BaudRate =  1	=>   2400 bps
						// BaudRate =  2	=>   4800 bps
						// ...
						// BaudRate = 48	=> 115200 bps
						// BaudRate = 99	=> 250000 bps - special case
	
	//*******************************************************************
//	_T1IE 	= 0; 		// Temporarily disable Timer1 interrupt
	//*******************************************************************

	struct 
		{
		float			V;
		uint			Raw;
		uint			Stat;
		} UData;


	BLISignalON();
	while(1)	
		{
		TMRDelay(1000);
		//--------------------------
		UData.V		= ADCGetBatteryVoltage();
		UData.Raw 	= ADCGetRawSample();
		UData.Stat	= ADCGetBatteryStatus();
		//--------------------------
		UARTPostWhenReady((uchar*)&UData, sizeof(UData));
		BLISignalFlip();
		}


	return 1;
	}

