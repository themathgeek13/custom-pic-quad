#include "ADC/ADC.h"

//=====================================================
#ifndef __ADCLocal_H
#define __ADCLocal_H
	
//=====================================================
extern uint				_ADCIL;
//-----------------------------------------------------
extern ulong	volatile	_ADCValue;
//-----------------------------------------------------
extern ulong	volatile	_ADCBuffer;
extern uint		volatile	_ADCSCnt;
//=====================================================
//-----------------------------------------------------
//	Run Variables (set in ADCGetCellCount())
//-----------------------------------------------------
extern uint 				_ADCCellCnt;	
extern uint 				_ADCBatMinV;
extern uint 				_ADCBatRange;
extern float				_ADCBatNomV;
//-----------------------------------------------------
//	Constants
//-----------------------------------------------------
extern uint		const		_ADCMinV;
extern uint		const		_ADCRange;
//-----------------------------------------------------
extern float 	const		_ADCVRate;
//=====================================================

#endif



