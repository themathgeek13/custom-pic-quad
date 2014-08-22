#include "BLI/BLILocal.h"

typedef struct
	{
	uint	Count;
	byte	DitDah[];
	}	BLIMorseLetter;

BLIMorseLetter		BLIMorseA	= { 2, { 1, 3 }};
BLIMorseLetter		BLIMorseB	= { 4, { 3, 1, 1, 1 }};
BLIMorseLetter		BLIMorseC	= { 4, { 3, 1, 3, 1 }};
BLIMorseLetter		BLIMorseD	= { 3, { 3, 1, 1 }};
BLIMorseLetter		BLIMorseE	= { 1, { 1 } };
BLIMorseLetter		BLIMorseF	= { 4, { 1, 1, 3, 1 }};
BLIMorseLetter		BLIMorseG	= { 3, { 3, 3, 1 }};
BLIMorseLetter		BLIMorseH	= { 4, { 1, 1, 1, 1 }};
BLIMorseLetter		BLIMorseI	= { 2, { 1, 1 }};
BLIMorseLetter		BLIMorseJ	= { 4, { 1, 3, 3, 3 }};
BLIMorseLetter		BLIMorseK	= { 3, { 3, 1, 3 }};
BLIMorseLetter		BLIMorseL	= { 4, { 1, 3, 1, 1 }};
BLIMorseLetter		BLIMorseM	= { 2, { 3, 3 }};
BLIMorseLetter		BLIMorseN	= { 2, { 3, 1 }};
BLIMorseLetter		BLIMorseO	= { 3, { 3, 3, 3 }};
BLIMorseLetter		BLIMorseP	= { 4, { 1, 3, 3, 1 }};
BLIMorseLetter		BLIMorseQ	= { 4, { 3, 3, 1, 3 }};
BLIMorseLetter		BLIMorseR	= { 3, { 1, 3, 1 }};
BLIMorseLetter		BLIMorseS	= { 3, { 1, 1, 1 }};
BLIMorseLetter		BLIMorseT	= { 1, { 3 }};
BLIMorseLetter		BLIMorseU	= { 3, { 1, 1, 3 }};
BLIMorseLetter		BLIMorseV	= { 4, { 1, 1, 1, 3 }};
BLIMorseLetter		BLIMorseW	= { 3, { 1, 3, 3 }};
BLIMorseLetter		BLIMorseX	= { 4, { 3, 1, 1, 3 }};
BLIMorseLetter		BLIMorseY	= { 4, { 3, 1, 3, 3 }};
BLIMorseLetter		BLIMorseZ	= { 4, { 3, 3, 1, 1 }};


BLIMorseLetter *	BLIMorseAlphabet[] =
		{
		&BLIMorseA,
		&BLIMorseB,
		&BLIMorseC,
		&BLIMorseD,
		&BLIMorseE,
		&BLIMorseF,
		&BLIMorseG,
		&BLIMorseH,
		&BLIMorseI,
		&BLIMorseJ,
		&BLIMorseK,
		&BLIMorseL,
		&BLIMorseM,
		&BLIMorseN,
		&BLIMorseO,
		&BLIMorseP,
		&BLIMorseQ,
		&BLIMorseR,
		&BLIMorseS,
		&BLIMorseT,
		&BLIMorseU,
		&BLIMorseV,
		&BLIMorseW,
		&BLIMorseX,
		&BLIMorseY,
		&BLIMorseZ
		};

//************************************************************
void	BLIAsyncMorse(	char * pStr, uint Length)
	{
	//---------------------------------------------------
	// First, stop current Asynch operation, if any
	//---------------------------------------------------
	if (_BLIAsync)
		BLIAsyncStop();
	//---------------------------------------------------
	// Second, if not initialized - Initialize!
	//---------------------------------------------------
	if (0 == _BLIInit)
		BLIInit();
	//---------------------------------------------------
	// Third, all ASYNC operations should start in the
	// OFF State for UI
	//---------------------------------------------------
	BLISignalOFF();
	//---------------------------------------------------
	// Fourth, validate parameters
	//---------------------------------------------------
	if (Length <= 0)
		return;			// Nothing to do...
	//---------------------------------------------------
	int		CharPos		= 0;
	int		CharValue	= 0;
	//----------------------
	int		PlaySize	= 0;
	//---------------------------------------------------
	for (CharPos = 0; CharPos < Length; CharPos++)
		{
		CharValue	= (int)(pStr[CharPos]);
		if (32 == CharValue)
			{
			// Space...
			if (PlaySize > 0)
				// Not the first character in a string...
				// Last inteval should have been 7 "Dih" to indicate End-of-word
				_BLIAsyncTimes[PlaySize - 1] = 896;
			//---------------------------------------
			// Skip Space
			continue;
			}
		//-----------------------------------------------
		CharValue	-=  65;							// Move to Capital characters
		if (CharValue > 25	)	CharValue -= 32;	// Maybe, low case letter?	
		if (CharValue <  0	)	continue;			// Skip Special character
		if (CharValue > 25  )	continue;			// Skip Invalid character
		//-----------------------------------------------
		BLIMorseLetter *	pLetter	= BLIMorseAlphabet[CharValue];
		if (PlaySize + 2*pLetter->Count > _BLIAsynchMax)
			break;			// Asynchonous play array exhausted...
		//-----------------------------------------------
		int	SignalIdx;
		for (SignalIdx = 0; SignalIdx < pLetter->Count; SignalIdx++)
			{
			// NOTE: 1 "Dih" = 128 msec
			//-------------------------
			_BLIAsyncTimes[PlaySize] = ((uint)(pLetter->DitDah[SignalIdx])) << 7;
			PlaySize++;
			// Now add 1 "Dih" interval 
			_BLIAsyncTimes[PlaySize] = 128;
			PlaySize++;	
			}
		// Last inteval should have been 3 "Dih" to indicate End-of-character
		_BLIAsyncTimes[PlaySize - 1] = 384;
		}
	// Last inteval should have been 7 "Dih" to indicate End-of-word
	_BLIAsyncTimes[PlaySize - 1] = 896;
	//---------------------------------------------------
	// Initialize asynchronous play of prepared timing array
	//---------------------------------------------------
	// Set size of timing array:
	_BLIAsync			= PlaySize;	// Flag Asynch operation;
	//---------------------------------------------------
	// Request immediate callback to initialize the sequence
	//---------------------------------------------------
	TMRCallBackAfter(0, &_BLICallBack); 			
	//---------------------------------------------------
	return;
	}
//************************************************************



