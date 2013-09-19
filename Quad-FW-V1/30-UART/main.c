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
	// This initialization routine accepts BaudRate in multiples
	// of 2400 bps; Thus:
	// BaudRate =   1	=>   2400 bps
	// BaudRate =   2	=>   4800 bps
	// ...
	// BaudRate =  48	=> 115200 bps
	//------------------------------------------------------------
	// High speed
	//------------------------------------------------------------
	// BaudRate =  100	=>   250,000 bps
	// BaudRate =  200	=>   500,000 bps
	// BaudRate =  250	=>   625,000 bps
	// BaudRate =  350	=>   833,333 bps
	// BaudRate =  500	=> 1,250,000 bps
	// BaudRate = 1000	=> 2,500,000 bps
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

