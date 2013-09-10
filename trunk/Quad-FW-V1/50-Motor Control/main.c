#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "MCM\MCM.h"
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
	//--------------------------
//	uint	MCMFreq	=  0;	// PPM
	uint	MCMFreq	=  5;	// PWM at MCMFreq kHz
	//--------------------------
	MCMInit(MCMFreq);
	//--------------------------
	ulong	Delay;
	//-------------
	if (0 == MCMFreq)
		Delay = 20;			// 20 msec between updates
	else
		Delay = 1;			// 1 msec between updates	
	//*******************************************************************
	int		i;
	MCMData	MC;
	//-------------------------------------------------
	BLISignalON();
	while(1)
		{
		for (i = 0; i <= 100; i++)
			{
			TMRDelay(Delay);
			//--------------
			MC.F	= (float)i / 100.0;
			MC.B	= MC.F;
			//--------------
			MC.L	= 1.0 - MC.F;
			MC.R	= 1.0 - MC.B;
			//--------------
			MCMSet(&MC);
			//--------------
			BLISignalFlip();
			}
		}
	return 1;
	}



