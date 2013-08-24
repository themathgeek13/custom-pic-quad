#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "ADC\ADC.h"
#include "I2C\I2C.h"
#include "MPU6050\MPU6050.h"
#include "UART\UART.h"
#include "DCM\DCM.h"

struct
	{
	// Telemetry data exchange format
	//-----------------------------------------------
	ulong	TS;				// Timestamp (ticks)
	ulong	DCMStep;		// Time interval (ticks)
	//----------------------
	DCMData	IMUResult;		// Orientation data from DCM
			// Roll, Pitch, Yaw, Incl, Vector RotationRateBF
	//----------------------
	Vector	Acc;			// Accelleration vector
	//--------------------------------------------------
	// Earth axis in the Body frame of reference:
	// (each of these vectors represent a row of DCM)	
	//--------------------------------------------------
	Vector	XEarth;			
	Vector	YEarth;			
	Vector	ZEarth;			
	//--------------------------------------------------
	} 		TMData;




int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	ADCInit(3);			// Initialize ADC to control battery
	//--------------------------
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at 115200 bps
						// BaudRate =  1	=>   2400 bps
						// BaudRate =  2	=>   4800 bps
						// ...
						// BaudRate = 48	=> 115200 bps
						// BaudRate = 99	=> 250000 bps - special case
	//--------------------------
	I2CInit(5, 1);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	TMRDelay(1000);		// Wait for 1 sec so that the shake from turning on
						// power switch dissipates...
	//--------------------------
	BLISignalON();
	if (MPUInit(0, 1))	// Initialize MPU - 1 kHz/(1+1) (500 Hz, 2ms)	
						// DLPF = 3 => Bandwidth 44 Hz (delay: 4.9 msec)

		BLIDeadStop("EA", 2);
	BLISignalOFF();
	//*******************************************************************
	uint		RC		= 0;
	//----------------------------
	MPUSample	MPUReading;
	//----------------------------
	//*******************************************************************
	if (MPUAsyncStart())
		BLIDeadStop("A", 1);
	//------------------------	
	RC 	= MPUAsyncReadWhenReady(&MPUReading);
	if (RC) BLIDeadStop("T", 1);
	//====================================================================	
	uint		IsReady	= 0;
	ulong		StCount	= 0;
	//----------------------
	BLISignalON();
	DCMReset();
	while (0 == IsReady)
		{
		RC 	= MPUAsyncReadWhenReady(&MPUReading);
		if (RC) BLIDeadStop("T", 1);
		//----------------------------
		IsReady = DCMPerformStep(	&MPUReading.G, &MPUReading.A, 
									&TMData.IMUResult);
		//----------------------------
		StCount++;
		}
	BLISignalOFF();
	//====================================================================	
	ulong		StartTS			= TMRGetTS();
	ulong		DCMStartTS		= 0;
	ulong		LoopStartRTC	= TMRGetRTC();
	ulong		LoopCurrRTC		= 0;  
	//-----------------------------------------
	while(1)
		{
		//------------------------	
		MPUAsyncRead(&MPUReading);
		//----------------------------
		DCMStartTS =  TMRGetTS();
		DCMPerformStep(	&MPUReading.G, &MPUReading.A, 
						&TMData.IMUResult);
		TMData.DCMStep	= TMRGetTS() - DCMStartTS;
		//----------------------------
		LoopCurrRTC	= TMRGetRTC();
		if ( (LoopCurrRTC - LoopStartRTC) > 100)
			{
			LoopStartRTC = LoopCurrRTC;		// Start new loop...
			//----------------------------
			VectorCopy(&MPUReading.A, &TMData.Acc);
			//----------------------------
			DCMGetMatrix(	&TMData.XEarth,
							&TMData.YEarth,
							&TMData.ZEarth);
			//----------------------------
			TMData.TS	= TMRGetTS() - StartTS;
			//----------------------------
			UARTPostIfReady((uchar*)&TMData, sizeof(TMData));
			//----------------------------
			BLISignalFlip();
			}
		}
	return 1;
	}









