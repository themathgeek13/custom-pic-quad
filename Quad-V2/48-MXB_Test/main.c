#include "System.h"
//---------------------------------
#include "Init/Init.h"
#include "TMR/TMR.h"
#include "BLI/BLI.h"
#include "UART/UART_TX.h"

//---------------------------------
#include "MXB/MXB.h"
#include "MXB/MXBLocal.h"
//---------------------------------

#include <string.h>		// Required for memcpy(...)

//***************************************************
// Telemetry data exchange format
//***************************************************
struct
	{
	ulong	TS;				// Timestamp (ticks)
	//-----------------------------------------------
	float	BaseOffset;
	//-----------------------------------------------
	MXBData	MXBDLPF;
	//----------------------
	MXBData	MXBNative;
	//----------------------
	} TM;		// Telemetry data structure
//=====================================================

int main(void)
	{
	//*******************************************************************
	// Initialization of HW components/modules
	//===================================================================
	Init();
	TMRInit(2);			// Initialize Timer interface with Priority=2
	BLIInit();			// Initialize Signal interface
	//--------------------------
	BLIAsyncMorse("S", 1);	// dot-dot-dot
	UARTInitTX(6, 48);	// Initialize UART1 for TX on IPL=6 at
						// BaudRate =   48	=>   115,200 bps	- ZigBEE
						//--------------------------------------
						// BaudRate =  100	=>   250,000 bps
						// BaudRate =  200	=>   500,000 bps
						// BaudRate =  250	=>   625,000 bps
						// BaudRate =  350	=>   833,333 bps	- SD Logger
						// BaudRate =  500	=> 1,250,000 bps
						// BaudRate = 1000	=> 2,500,000 bps
	//===================================================================

	//*******************************************************************
	// Quadrocopter control variables
	//-------------------------------------------------------------------
	ulong		StartTS		= 0;
	ulong		StepTS;

	//==================================================================
	// Initialize sensors...
	//------------------------------------------------------------------
	BLIAsyncMorse(	"I", 1);
	//============================================================
	// Let MaxBotix initialize HW
	//============================================================
	TMRDelay(1000);
	//==================================================================
	// Initialize MaxBotix range finder
	//--------------------------------------------------------------
	if (0 == MXBInit(4, &TM.MXBDLPF))
		BLIDeadStop("ES", 2);
	//--------------------------------------------------------------
	BLIAsyncStop();
	
	//*******************************************************************
	// Control Loop
	//-------------------------------------------------------------------
	BLISignalON();
	while (1)
		{
		//============================================================
		// Simulate control loop duration
		//============================================================
		TMRDelay(10);
		//-----------------------------------------
		
		//===========================================================
		// Load and post telemetry data (non-blocking call)
		//-----------------------------------------------------------
		StepTS =  TMRGetTS();
		//-----------------------------------------
		if (0 == StartTS)
			// Time stamp of cycle start!
			StartTS =  StepTS;
		//-----------------------------------------
		TM.TS			= StepTS - StartTS;
		//----------------------
		TM.BaseOffset	= _MXBOffset;
		MXBReadDLPF(8, &TM.MXBDLPF);
		memcpy(&TM.MXBNative, &_NewMXBReading, sizeof(TM.MXBNative));
		//===========================================================
		UARTPostIfReady( (unsigned char *) &TM, sizeof(TM)	);
		//===========================================================

		}
	//*******************************************************************
	return 1;
	}






