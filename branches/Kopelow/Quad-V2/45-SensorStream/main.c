#include "System.h"
//---------------------------------
#include "Init/Init.h"
#include "TMR/TMR.h"
#include "BLI/BLI.h"
#include "I2C/I2C.h"
#include "MPU6050/MPU6050.h"
#include "HMCMAG/HMCMAG.h"
#include "UART/UART_TX.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	I2CInit(5, 0);		// Initialize I2C1 module with IPL=5 and Fscl=400 KHz
	//--------------------------
	TMRDelay(1000);		// Wait for 1 sec so that the shake from turning on
						// power switch dissipates...
	//--------------------------
	if (MPUInit(3, 1))	// Initialize motion Sensor - 1 kHz/4 (250 Hz)
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
	//MPUSample		AGSample;
        MPUData 		AGSample;
	#ifdef __MAG_Use__
	HMCSample		MSample;
	#endif
	//--------------------------
	if (MPUAsyncStart())
		BLIDeadStop("A", 1);
	//--------------------------
	#ifdef __MAG_Use__
	if (HMCAsyncStart())
		BLIDeadStop("M", 1);
	#endif
	//--------------------------
	struct 
		{
		ulong	TS;		// Timestamp of the cycle
		//-----------------------------------------------
		ulong	MPUCount;	// Sequential number of MPU sample
		#ifdef __MAG_Use__
		ulong	MAGCount;	// Sequential number of MAG sample
		#endif
		//-----------------------------------------------
		// Accelerometer (in units of G)
		//-----------------------------------------------
		Vector	A;
		//-----------------------------------------------
		// Gyroscopes	(in Rad/sec)
		//-----------------------------------------------
		Vector	G;
		#ifdef __MAG_Use__
		//-----------------------------------------------
		// Magnetometer (in mGs)
		//-----------------------------------------------
		Vector	M;
		#endif
		} UData;
	//*******************************************************************
	BLISignalON();
	while(1)
		{
		TMRDelay(100);
		//------------------------	
		#ifdef __MAG_Use__
		RC 	= HMCAsyncReadWhenReady(&MSample);
		if (RC) BLIDeadStop("M", 1);
		#endif
		//------------------------	
		RC 	= MPUAsyncReadWhenReady(&AGSample);
		if (RC) BLIDeadStop("A", 1);
		//---------------------------------------------	
		UData.MPUCount	= AGSample.Count;
		#ifdef __MAG_Use__
		UData.MAGCount	= MSample.Count;
		#endif
		//------------------------
		VectorCopy(&AGSample.A, &UData.A);
		VectorCopy(&AGSample.G, &UData.G);
		#ifdef __MAG_Use__
		VectorCopy(&MSample.M,  &UData.M);
		#endif
		//------------------------
		UData.TS	= AGSample.TS;
		//---------------------------------------------	
		UARTPostWhenReady((uchar*)&UData, sizeof(UData));
		//---------------------------------------------	
		BLISignalFlip();
		}
	return 1;
	}


