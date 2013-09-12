#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "MCM\MCM.h"
#include "RC\RC.h"
#include "RC\RCSym.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "HMCMAG\HMCMAG.h"
#include "UART\UART.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	MCMInit(1);			// Initialize Motor Control for PWM at 1 kHz
	//--------------------------
	RCInit(4);			// Initialize Receiver interface with Priority=4
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
						// BaudRate =  1	=>   2400 bps
						// BaudRate =  2	=>   4800 bps
						// ...
						// BaudRate = 48	=> 115200 bps
						// BaudRate = 99	=> 250000 bps - special case
	//*******************************************************************
	MCMData		MC;
	RCData		RC;
	//-------------------------------------------------
	BLIAsyncMorse(	"SOS", 3);
	RCSymArm();	
	BLIAsyncStop();
	//-------------------------------------------------
	BLISignalON();
	while(1)
		{
		RCSymReadWhenReady(&RC);
		//---------------------------------------------	
		MC.F	= RC.Throttle;
		MC.B	= RC.Yaw;
		//--------------
		MC.L	= RC.Roll;
		MC.R	= RC.Pitch;
		//--------------
		MCMSet(&MC);
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&RC, sizeof(RC));
		//---------------------------------------------	
		BLISignalFlip();
		}
	return 1;
	}



