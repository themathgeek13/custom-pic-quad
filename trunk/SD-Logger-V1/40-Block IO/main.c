#include "System.h"
//---------------------------------
#include "Init\Init.h"
#include "TMR\TMR.h"
#include "BLI\BLI.h"
#include "DBG\DBG.h"

#include "FSIO\FS.h"
#include "LOG\LOG.h"

int main(void)
	{
	//*******************************************************************
	Init();
	TMRInit(2);		// Initialize Timer interface with Priority=2
	BLIInit();		// Initialize Signal interface
	//*******************************************************************
	//_T1IE 	= 0; 	// Temporarily disable Timer1 interrupt
	//*******************************************************************
	LogInit();	// Initialize Data Logger	
	//*******************************************************************
	//-------------------------------------------------------------------
	#define		MaxRec		60
	//-------------------------------------------------------------------
	struct
		{
		DWORD	TS;
		WORD	Index;
		char	filler[506];
		}	Data;
	//-------------------------------------------------------------------
	uint	i;
	for (i = 0; i < sizeof(Data.filler); i++)
		{
		Data.filler[i] = 0;
		}
	//-------------------------------------------------------------------
	DWORD	TimeStart;
	float	TimePoints[MaxRec];
//	WORD	TimeIndex[MaxRec];
	//-------------------------------------------------------------------
	char		pFN[15];

	
	WORD			RC;
	
	uint			ReadCnt;
	FSFILE			File;
	//*******************************************************************
	BLISignalON();
	//------------------------------
	// Create (Open) Log file for Writing and Reading 
	//------------------------------
	RC = LogNewFile(&File);
	while ( RC != LE_GOOD );
	//------------------------------
	// Retrieve and save for future new log file name 
	//------------------------------
	RC = FS_GetName(pFN, 15, &File);
	while ( RC != LE_GOOD );
	//------------------------------
	// Write sample data to file
	//------------------------------
	for (i=0; i < MaxRec; i++)
		{
		Data.Index 	= i;
		Data.TS		= TMRGetTS();
	   	RC = FS_WriteSector(&File, &Data);
		while (CE_GOOD != RC);
		}
	//------------------------------
	// Check position in the file
	//------------------------------
   	i = FS_GetPosition (&File);
	while (i != 512*MaxRec);
	//------------------------------
	// Close the file - save changes
	//------------------------------
	RC = FS_Flush(&File);
   	while ( RC != CE_GOOD );
	//------------------------------

	//------------------------------
	// Open file for Reading 
	//------------------------------
	RC = FS_CreateFile(pFN, FS_READ_ONLY, &File);
	while ( RC != CE_GOOD );
	//------------------------------
	// Reed records
	//------------------------------
	for (i=0; i < MaxRec; i++)
		{
	   	RC = FS_Read (&File, &Data, sizeof(Data), &ReadCnt);
		while (CE_GOOD != RC);
		//--------------------------
//		TimeIndex[i] = Data.Index;
		//--------------------------
		if (0 == i)
			TimeStart = Data.TS;
		//--------------------------
		TimePoints[i] = (Data.TS - TimeStart) * TMRGetTSRate() * 1000.0;	// in msec
		//--------------------------
		TimeStart = Data.TS;
		}
	//------------------------------
	// Close the file - save changes
	//------------------------------
	RC = FS_Flush(&File);
   	while ( RC != CE_GOOD );
	//*******************************************************************
	BLISignalOFF();
	//------------------------------
	i = 1 + i;
	//------------------------------
	while(1);
	return 0;
	}

/*
TimePoints	Byte Write	Block Write	Savings (abs)	Savings (%)
 [0]		 0.00000	 0.00000	0.00000			0
 [1]		 1.54200	 0.09620	1.44580			93.76%
 [2]		 5.88660	 4.43500	1.45160			24.66%
 [3]		 4.65180	 3.13980	1.51200			32.50%
 [4]		 4.63020	 3.16260	1.46760			31.70%
 [5]		12.48000	10.97760	1.50240			12.04%
 [6]		 4.63580	 3.14260	1.49320			32.21%
 [7]		 4.63860	 3.15120	1.48740			32.07%
 [8]		 4.64140	 3.16300	1.47840			31.85%
 [9]		11.22420	 9.74320	1.48100			13.19%
[10]		 4.61140	 3.13620	1.47520			31.99%
[11]		 4.58100	 3.13440	1.44660			31.58%
[12]		 4.59620	 3.14300	1.45320			31.62%
[13]		11.13460	 9.68180	1.45280			13.05%
[14]		 4.59820	 3.16640	1.43180			31.14%
[15]		 4.56220	 3.13480	1.42740			31.29%
[16]		 4.58080	 3.13460	1.44620			31.75%
[17]		11.14040	 9.53740	1.60300			14.39%
[18]		 4.51000	 3.14620	1.36380			30.24%
[19]		 4.51280	 3.14840	1.36440			30.23%
*/







