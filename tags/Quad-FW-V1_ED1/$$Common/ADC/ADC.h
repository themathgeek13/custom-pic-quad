#include "System.h"

//=====================================================
#ifndef __ADC_H
#define __ADC_H
//=====================================================

//=====================================================
// ADC subroutines in this program use AN1
//=====================================================

void	ADCInit(uint IL);	// Parameter (1<=IL<=7) defines the
							// priority of ADC interrupt routine.
//-----------------------------------------------------

uint inline		ADCGetRawSample();
uint inline		ADCGetCellCount();

float inline	ADCGetBatteryStatus();	// Charge level in %
float inline	ADCGetBatteryVoltage();

//=====================================================
#endif



