#include "System.h"
//---------------------------------
#include "Init/Init.h"
#include "TMR/TMR.h"
#include "BLI/BLI.h"
#include "I2C/I2C.h"
#include "MPU6050/MPU6050.h"
#include "MPU6050/MPU6050_Local.h"
// rich kopelow - 8/19/14
// change the following include
// #include "UART/UART.h"
#include "UART/UART_TX.h"


int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
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
	UARTInitTX(6, 350);	// Initialize UART1 for TX on IPL=6 at 115200 bps
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
	MPUData 		Sample;
	//*******************************************************************
	if ( MPUAsyncStart() )
		BLIDeadStop("E", 1);
	//--------------------------
	while(1)
		{
		TMRDelay(500);
		//------------------------
		if ( MPUAsyncReadIfReady(&Sample) )
			BLIDeadStop("M", 1);
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&Sample, sizeof(Sample));
		//---------------------------------------------
		}
	return 1;
	}






