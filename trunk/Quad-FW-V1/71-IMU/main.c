#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "HMCMAG\HMCMAG.h"
#include "UART\UART.h"
#include "DCM\DCM.h"
#include "IMU\IMU.h"

#include "DBG\DBG.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	ADCInit(3);			// Initialize ADC to control battery
	//--------------------------
	TMRDelay(1000);		// Wait for 1 sec so that the shake from turning on
						// power switch dissipates...
	//--------------------------
	I2CInit(5, 1);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	if (MPUInit(3, 1))	// Initialize motion Sensor - 1 kHz/3 (333 Hz)
		BLIDeadStop("EA", 2);
	//--------------------------
	if (HMCInit(6, 1))	// Initialize magnetic Sensor - max ODR (75 Hz), 1.3 Gs
		BLIDeadStop("EM", 2);
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
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
		float Azimuth;
		} 		UARTData;
	//*******************************************************************
	DBG_1_ON();
	StCount = 	IMUInit();
	DBG_1_OFF();
	//*******************************************************************
	BLISignalOFF();
	while(1)
		{
		//------------------------	
		TMRDelay(17);
		//------------------------	
		if (ADCGetBatteryStatus() < 30)
			BLIDeadStop("SOS", 3);
		//------------------------	
		RC = IMUGetUpdate(&IMUResult);
		if (IMU_OK != RC)
				BLIDeadStop("SOS", 3);
		//------------------------	
		UARTData.Roll 		= IMUResult.Roll;
		UARTData.Pitch		= IMUResult.Pitch;
		UARTData.Yaw		= IMUResult.Yaw;
		UARTData.Azimuth	= IMUResult.Azimuth;
		//----------------------------
		UARTPostIfReady((uchar*)&UARTData, sizeof(UARTData));
		//---------------------------------------------	
		BLISignalFlip();
		}
	return 1;
	}






