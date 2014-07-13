#include "ADC\ADCLocal.h"


//************************************************************
uint inline		ADCGetRawSample()
	{
	return _ADCValue;				
	}
//************************************************************
uint inline		ADCGetCellCount()
	{
	return _ADCCellCnt;				
	}
//************************************************************
float inline		ADCGetBatteryStatus()
	{
	//--------------------------------------------------
	if (1 == _ADCCellCnt)
		// No external battery... 
		// The board powered from PicKit	
		return 100;	
	//--------------------------------------------------
	if (_ADCValue < _ADCBatMinV)
		return 0.0;	// Battery is depleted!
	//--------------------------------------------------
	// Battery charge value in percentages...
	float	Charge 	= ((float)(_ADCValue - _ADCBatMinV)) / _ADCBatRange;
	//--------------------------
	if (Charge > 1.0)
		Charge = 1.0;
	//--------------------------
	return Charge; 
	}
//************************************************************
float inline	ADCGetBatteryVoltage()
	{
	return ((float)_ADCValue) * _ADCVRate;
	}
//************************************************************
float inline	ADCGetBatteryNomVoltage()
	{
	return _ADCBatNomV;
	}
//************************************************************



