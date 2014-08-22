#include "System.h"
//---------------------------------
#include "Init/Init.h"
#include "TMR/TMR.h"
#include "BLI/BLI.h"
#include "MCM/MCM.h"

void DeadStop(char * pStr, uint Length);

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	MCMInitF(50, 0);	// Updates of ESC control signal happens at
						// 50 Hz (range: 50 to 400 Hz)
	//--------------------------
	ulong	Delay;
	//-------------
	Delay = 20;			// 20 msec between updates
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



