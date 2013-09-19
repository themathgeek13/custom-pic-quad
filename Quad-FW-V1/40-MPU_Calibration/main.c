#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "MPU6050\MPU6050_Local.h"
#include "UART\UART.h"

void DeadStop(char * pStr, uint Length);

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	ADCInit(3);			// Initialize ADC to control battery
	I2CInit(5, 0);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	BLISignalON();
	//--------------------------
	if (MPUInit(3, 1))	// Initialize motion Sensor - 1 kHz/4 (250 Hz)
		DeadStop("A", 1);
	//--------------------------
	BLISignalOFF();
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
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
	uint			RC			= 0;
	//--------------------------
	_MPURawData	RawData;
	//--------------------------
	struct 
		{
		ulong	TS;		// Timestamp of the cycle
		//-----------------------------------------------
		// Temperature
		//-----------------------------------------------
		float			Temp;
		//-----------------------------------------------
		// Accelerometer
		//-----------------------------------------------
		float			AX;
		float			AY;
		float			AZ;
		//-----------------------------------------------
		// Gyroscopes
		//-----------------------------------------------
		float			GX;
		float			GY;
		float			GZ;
		//-----------------------------------------------
		} UData;
	//*******************************************************************
	long	AX, AY, AZ, GX, GY, GZ, Temp;
	//*******************************************************************
	while(1)
		{
		//------------------------	
		if (ADCGetBatteryStatus() < 30)
			DeadStop("SOS", 3);
		//------------------------
		AX= AY= AZ= GX= GY= GZ= Temp = 0;
		//------------------------
		int i;
		for (i=0; i<128; i++)	
			{
			RC 	= _MPUReadRawData(&RawData);
			if (RC) DeadStop("A", 1);
			//-----------------------------
			AX	+=	RawData.AX;
			AY	+=	RawData.AY;
			AZ	+=	RawData.AZ;
			//-----------------
			GX	+=	RawData.GX;
			GY	+=	RawData.GY;
			GZ	+=	RawData.GZ;
			//-----------------
			Temp+=	RawData.Temp;
			//-----------------------------
			}
		//---------------------------------------------	
		UData.TS	= 	TMRGetTS();
		//------------------------
		UData.Temp	=	((float)Temp/128.0 - _MPU_Temp_OffsetTo0) * _MPU_Temp_Sensitivity - 25.0;
		//------------------------
		UData.AX	= 	(float)AX/128.0;
		UData.AY	=	(float)AY/128.0;
		UData.AZ	=	(float)AZ/128.0;
		//------------------------
		UData.GX	= 	(float)GX/128.0;
		UData.GY	=	(float)GY/128.0;
		UData.GZ	=	(float)GZ/128.0;
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&UData, sizeof(UData));
		//---------------------------------------------	
		}
	return 1;
	}

void DeadStop(	char * pStr, uint Length)
	{
	BLIAsyncMorse(pStr, Length);
	while (1);
	}





