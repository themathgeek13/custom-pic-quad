#ifndef __PROFILE_H
#define	__PROFILE_H
//--------------------------------------------------------------------------
// Configuration settings controlling orientation of the control board
// in relationship to the "front" of the craft
//--------------------------------------------------------------------------
// General configuration settings for the project controlling use of
// optional HW Components
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// If MPL3115A2 Barometric Altimeter is available please uncomment
// the following line
#define __MPL_Use__
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// If SR04 (or similar US-020) Ultrasonic Altimeter is available please
// uncomment the following line
#define __SR04_Use__
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Angle (in radians) that the orientation of the Control Board need to be
// adjusted with regards to the front of the Model.
#define __CB_To_MF_Angle__		-0.785398163
// In the case above -0.785398163 in radians indicates that the front of
// the model is 45 degrees to the left of the front of the CB

//===========================================================================
#endif	/* __PROFILE_H */

