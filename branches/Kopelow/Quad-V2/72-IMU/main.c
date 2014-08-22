#include "System.h"
//---------------------------------
#include "Init/Init.h"
#include "TMR/TMR.h"
#include "BLI/BLI.h"
#include "ADC/ADC.h"
#include "I2C/I2C.h"
#include "MPU6050/MPU6050.h"
#ifdef __MAG_Use__
#include "HMCMAG/HMCMAG.h"
#endif
#include "UART/UART_TX.h"
#include "DCM/DCM.h"
#include "IMU/IMU.h"

#include "DBG/DBG.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	TMRDelay(1000);		// Wait for 1 sec so that the shake from turning on
						// power switch dissipates...
	//--------------------------
	I2CInit(5, 1);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	if (MPUInit(3, 1))	// Initialize motion Sensor - 1 kHz/3 (333 Hz)
		BLIDeadStop("EA", 2);
	//--------------------------
	#ifdef __MAG_Use__
	if (HMCInit(6, 1, 0))	// Initialize magnetic Sensor
						// ODR  = 6 (max, 75 Hz),
						// Gain = 2 (1.3 Gs)
						// DLPF = 0 (no averaging)
		BLIDeadStop("EM", 2);
	#endif
	//--------------------------
	UARTInitTX(6, 350);	// Initialize UART1 for TX on IPL=6 at 115200 bps
						// BaudRate =  1	=>   2400 bps
						// BaudRate =  2	=>   4800 bps
						// ...
						// BaudRate = 48	=> 115200 bps
						// BaudRate = 99	=> 250000 bps - special case
	//*******************************************************************
	ulong		StCount	= 0;
	uint		RC;
	DBGInit();
	//==================================================================
	DCMData		IMUResult;
	//--------------------------
	struct 
		{
		float Roll;
		float Pitch;
		float Yaw;
		#ifdef __MAG_Use__
		float Azimuth;
		#endif
		} 		UARTData;
	//*******************************************************************
	DBG_1_ON();
	//StCount = 	IMUInit();
	StCount = 	IMUReset();
	DBG_1_OFF();
	//*******************************************************************
	BLISignalOFF();
	while(1)
		{
		//------------------------	
		TMRDelay(17);
		//------------------------	
		RC = IMUGetUpdate(&IMUResult);
		if (IMU_OK != RC)
				BLIDeadStop("SOS", 3);
		//------------------------	
		UARTData.Roll 		= IMUResult.Roll;
		UARTData.Pitch		= IMUResult.Pitch;
		UARTData.Yaw		= IMUResult.Yaw;
		#ifdef __MAG_Use__
		UARTData.Azimuth	= IMUResult.Azimuth;
		#endif
		//----------------------------
		UARTPostWhenReady((uchar*)&UARTData, sizeof(UARTData));
		//---------------------------------------------	
		BLISignalFlip();
		}
	return 1;
	}






