#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "UART\UART_TX.h"
#include "ADC\ADC.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	ADCInit(3);			// Initialize ADC
	UARTInitTX(6, 350);	// Initialize UART1 for TX
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

	int i = 0;
	int j = 0;
	BLISignalON();
	while(j < 10)
		{
		TMRDelay(10);
		//--------------------------
		UData.V		= ADCGetBatteryVoltage();
		UData.Raw 	= ADCGetRawSample();
		UData.Stat	= ADCGetBatteryStatus();
		//--------------------------
		UARTPostWhenReady((uchar*)&UData, sizeof(UData));
		i++;
		//--------------------------
		if (i >= 100)
			{
			UARTPostWhenReady(NULL, 0);
			BLISignalFlip();
			//------------------------
			i = 0;
			j++;
			}
		TMRDelay(10);
		}


	return 1;
	}

