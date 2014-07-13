#include "MCM\MCMLocal.h"
#include <math.h>

//**********************************************************************
//**********************************************************************
//**********************************************************************
// MCMInitF(...) and MCMInitT(...) initialize Motor Control Module
// for PPM mode. For both functions second parameter, UpTime, defines
// the time (in msec.) during which the ouput will be maintained at
// 100% on each of the channels, after which it will be dropped to 0%
// to allow ESC to capture Throttle range on each of the channels.
//**********************************************************************
//**********************************************************************
//**********************************************************************
// Parameter "Freq" (50 <= Freq <= 400) defines PPM refresh frequency in
// Hertz; acceptable values correspond to periods from 20 to 2.5 msec.
//-----------------------------------------------------
void	MCMInitF(uint Freq, uint UpTime)
	{
	if (Freq < 50)	Freq =  50;
	if (Freq > 400)	Freq = 400;
	// Calculate PPM refresh period (in msec.)
	float Period = 1000.0F / (float)Freq;
	//----------------------------------
	MCMInitT(Period, UpTime);
	}
//**********************************************************************
//**********************************************************************
//**********************************************************************
// Parameter "Period" (2.5 <= Period <= 20) defines PPM refresh period
// in msec.; acceptable vallues correspond to frequencies in the range
// from 50 to 400 Hz.
//-----------------------------------------------------
void	MCMInitT(float Period, uint UpTime)
	{
	if (Period <  2.5F)	Period =  2.5F;
	if (Period > 20.0F)	Period = 20.0F;
	//----------------------------------
	if (UpTime > 5000)
		UpTime = 5000;	// Max Up-Time for Throttle=100%
	//--------------------------------------------------
	MCMInitLocal(Period, UpTime);
	}
//**********************************************************************
//**********************************************************************
//**********************************************************************
// The Output Compare module uses default Timer2.
//-----------------------------------------------------
// MCMInitLocal(...) function besides initializing OC1-OC4 also
// initializes Timer2 module for the requested refresh frequency/period.
// Please Do Not Change Timer2 settings to avoid breaking
// MC operation.
//-----------------------------------------------------
// Control Board uses the following pins:
//		RB7/RP7  -> OC1 (Front)
//		RB8/RP8  -> OC2 (Back)
//		RB9/RP9  -> OC3 (Left)
//		RC6/RP22 -> OC4 (Right)
//-----------------------------------------------------
// NOTE: uses TMR (timer) module for calculating time
//		 interval; Please issue TMRInit(...) prior to
//		 this call - otherwise Timer will be initialized
//		 with default IL.
//-----------------------------------------------------
void	MCMInitLocal(float Period, uint UpTime)
	{
	if (_MC_Init)
		return;		// Already initialized
	//--------------------------------------------------
	_MC_Init = 1;

	//********************************************************
	// MCM Component relies on Timer functions, so if Timer is
	// not initialized, it is a good time to initialize it now...
	//--------------------------------------------------------
	TMRInitDefault();

	//=========================================================
	// Output-Compare module is being used in this application
	// to generate MC PPM signal to control 4 DC motors through
	// Brushless ESC.
	// All 4 OC (Output Compare) channels are being used for MC.
	//---------------------------------------------------------
	// Disable OC modules for configuration and reset all 
	// control bits	
	OC1CON		= 0;
	OC2CON		= 0;
	OC3CON		= 0;
	OC4CON		= 0;
	//---------------------------------------------------------
	// Enable OC1-OC4 if were disabled through PMD
	//---------------------------------------------------------
	_OC1MD		= 0;
	_OC2MD		= 0;
	_OC3MD		= 0;
	_OC4MD		= 0;
	//=========================================================

	//=========================================================
	// The Output Compare module uses default Timer2
	//---------------------------------------------------------
	// Stop/Disable Timer2; reset all flags
	//---------------------------------------------------------
	T2CON		= 0;
	// Enable Timer2 if disabled through PMD
	_T2MD		= 0;	// Timer2 module enabled
	//=========================================================
	// Timer prescaler and rollover counter are calculated
	// assuming Fcy = 40 MHz based upon specified refresh Period.
	//---------------------------------------------------------
	if (Period > 12.5F)
		// Low resolution mode
		{
		T2CONbits.TCKPS	= 0b10;		// Set Timer2 prescaler to 1:64 (tick = 1.6 usec)
		//-----------------------
		_MC_Base_Value	=   625;	// 1 msec at current prescaler
		_MC_OCMax		=   625.0F; 
		//-----------------------
		_MC_Tmr_Count	= (uint)floorf(Period/0.0016F + 0.5F);	
		}
	else
		// If the period is low enough
		// we may use high-resolution mode 
		{
		T2CONbits.TCKPS	= 0b01;		// Set Timer2 prescaler to 1:8 (tick = 0.2 usec)
		//-----------------------
		_MC_Base_Value	=  5000;	// 1 msec at current prescaler
		_MC_OCMax		=  5000.0F; 
		//-----------------------
		_MC_Tmr_Count	= (uint)floorf(Period/0.0002F + 0.5F);	
		}
	//=========================================================


	//---------------------------------------------------------							
	// Re-set Timer2 counter
	TMR2			= 0;
	// Set Timer2 rolover threshold (MC frequency counter)
	PR2				= _MC_Tmr_Count;
	//---------------------------------------------------------							

	//---------------------------------------------------------							
	// Configure Timer2 interrupts
	//---------------------------------------------------------							
	_T2IF 		= 0 ; 		// Clear TMR2 interrupt flag
	_T2IE 		= 0 ;   	// Disable TMR2 CPU interrupt
	//=========================================================

	//=========================================================
	// Configure Duty Cycle slave (OCxR) and Duty Cycle master
	// (OCxRS) registers for respective (PWM or PPM) mode.
	//---------------------------------------------------------
	if (UpTime > 0) // Fail-safe PPM init
		// Special case for PPM: start with 100% motor control output
		{
		uint MaxValue	= 2 * _MC_Base_Value;
		//-----------------------
		OC1R			= MaxValue;
		OC1RS			= MaxValue;
		//-----------------------
		OC2R			= MaxValue;
		OC2RS			= MaxValue;
		//-----------------------
		OC3R			= MaxValue;
		OC3RS			= MaxValue;
		//-----------------------
		OC4R			= MaxValue;
		OC4RS			= MaxValue;
		}
	//---------------------------------------------------------

	//=========================================================
	// On PIC24H family of MCUs OC module has to be associated
	// with the output pin using "Peripheral Pin Select" feature:
	//---------------------------------------------------------
	// Control Board uses the following pins:
	//		RB7/RP7  -> OC1 (Front)
	//		RB8/RP8  -> OC2 (Back)
	//		RB9/RP9  -> OC3 (Left)
	//		RC6/RP22 -> OC4 (Right)
	//-----------------------------------------------------
	// Reset respective pins
	//-----------------------------------------------------
	_TRISB7		= 0;
	_LATB7		= 0;
	//--------------
	_TRISB8		= 0;
	_LATB8		= 0;
	//--------------
	_TRISB9		= 0;
	_LATB9		= 0;
	//--------------
	_TRISC6		= 0;
	_LATC6		= 0;
	//-----------------------------------------------------
	// Associate respective pins with OC1...OC4
	//-----------------------------------------------------
	_RP7R		= 0b10010;	// OC1 on RB7/RP7
	_RP8R		= 0b10011;	// OC2 on RB8/RP8
	_RP9R		= 0b10100;	// OC3 on RB9/RP9
	_RP22R		= 0b10101;	// OC4 on RC6/RP22
	//=========================================================

	//=========================================================
	// Configure OC modules:
	/*---------------------------------------------------------
	bit 13 OCSIDL: 		0 = Output compare x will continue to operate in CPU Idle mode
	bit 3 OCTSEL: 		0 = Timer2 is the clock source for OC module
	bit 2-0 OCM<2:0>: 	Output Compare Mode Select bits
				111 = MC mode on OCx, Fault pin enabled
				110 = MC mode on OCx, Fault pin disabled
				101 = Initialize OCx pin low, generate continuous output pulses on OCx pin
				100 = Initialize OCx pin low, generate single output pulse on OCx pin
				011 = Compare event toggles OCx pin
				010 = Initialize OCx pin high, compare event forces OCx pin low
				001 = Initialize OCx pin low, compare event forces OCx pin high
				000 = Output compare channel is disabled
	-------------------------------------------------------*/
	// Put all OC modules into the MC mode
	//---------------------------------------------------------
	OC1CONbits.OCM		= 0b110;	// Simple PWM mode on OC1, Fault pin disabled
	OC2CONbits.OCM		= 0b110;	// Simple PWM mode on OC2, Fault pin disabled
	OC3CONbits.OCM		= 0b110;	// Simple PWM mode on OC3, Fault pin disabled
	OC4CONbits.OCM		= 0b110;	// Simple PWM mode on OC4, Fault pin disabled
	//=========================================================

	//=========================================================
	//Start MC by enabling Timer2
	//-----------------------------------------------------
	T2CONbits.TON 	= 0b1;
	//=========================================================

	if (UpTime > 0)
		// Reset Motor Control to 0% after initialization timeout
		{
		TMRDelay(UpTime);
		//---------------------------------
		// Reset duty cycle to Base Value
		//---------------------------------
		OC1RS	= _MC_Base_Value;
		OC2RS	= _MC_Base_Value;
		OC3RS	= _MC_Base_Value;
		OC4RS	= _MC_Base_Value;
		//---------------------------------
		// Wait until ESC captures Low Throttle Value
		//---------------------------------
		TMRDelay(5000);		// 5 sec
		}
	}
//**********************************************************************
//**********************************************************************
//**********************************************************************
