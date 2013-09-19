//=====================================================
#ifndef __SYSTEM_H
#define __SYSTEM_H
//=====================================================
// Include HW Profile definition
#include "Profile.h"
//-----------------------------------------------------
// Include proper device header file
#if defined(__PIC24F__) 
	#include <p24Fxxxx.h>		// PIC24F processor
#elif defined(__PIC24FK__) 
	#include <p24Fxxxx.h>		// PIC24F processor
#elif defined(__dsPIC30F__) 
	#include <p30fxxxx.h>		// dsPIC30F processor
#elif defined(__PIC24H__) 
	#include <p24Hxxxx.h>		// PIC24H processor
#elif defined(__dsPIC33F__) 
	#include <p33Fxxxx.h>		// dsPIC33F processor
#elif defined(__PIC24E__) 	
	#include <p24Exxxx.h>		// PIC24E processor
#elif defined(__dsPIC33E__) 
	#include <p33Exxxx.h>		// dsPIC33E processor
#else
	#error Unknown processor.  See Compiler.h
#endif
//-----------------------------------------------------
#ifndef	NULL
	#define	NULL	(0)
#endif	/* NULL */
//-----------------------------------------------------

typedef enum  
		{ FALSE = 0, TRUE } 	BOOL;	// "int" size 

//-----------------------------------------------------
// 8-bit un-signed integer
//-----------------------------------------------------
typedef unsigned char           BYTE;		
typedef unsigned char           byte;
typedef unsigned char           uchar;

//-----------------------------------------------------
// 8-bit signed integer
//-----------------------------------------------------
typedef signed char           	sbyte;


//-----------------------------------------------------
// 16-bit un-signed integer
//-----------------------------------------------------
typedef unsigned short      	WORD;		
typedef	unsigned short			uint;


//-----------------------------------------------------
// 32-bit un-signed integer
//-----------------------------------------------------
typedef unsigned long           DWORD;	
typedef unsigned long           ulong;

//=====================================================
#endif


