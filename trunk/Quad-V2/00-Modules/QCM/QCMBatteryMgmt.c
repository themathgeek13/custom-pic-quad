//**********************************************************************
#include "QCM\QCMLocal.h"
#include "BLI\BLI.h"
//**********************************************************************

//************************************************************
float	QCMBatteryMgmt()
	{
	static int	SoS		= 0;
	//----------------------------------------------------
	float	BattStat	= ADCGetBatteryStatus();
	//----------------------------------
	if (BattStat < 0.3 /*%*/ )
		{
		if (0 == SoS)
			{
			BLIAsyncMorse("SoS", 3);
			SoS = 1;
			}
		//----------------------------------
		if (BattStat < 0.05  /*%*/ )
			{
			MCMData			MC;
			// Shutdown due to low power
			MC.F = MC.B	= MC.L = MC.R	= 0;
			//---------------------------
			MCMSet(&MC);
			BLIAsyncMorse("SD", 2);
			while(1);	// Lockdown...
			}
		}
	else
		if (SoS)
			{
			BLIAsyncStop();
			SoS = 0;
			}
	//----------------------------------
	return BattStat;
	}
//************************************************************




