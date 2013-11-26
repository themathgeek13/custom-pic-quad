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
// If MaxBotix Ultrasound range finder is available please uncomment
// the following line
#define __MXB_Use__
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Angle (in radians) that the orientation of the Control Board need to be
// adjusted with regards to the front of the Model.
#define __CB_To_MF_Angle__		-0.785398163
// In the case above -0.785398163 in radians indicates that the front of
// the model is 45 degrees to the left of the front of the CB

//===========================================================================
#endif	/* __PROFILE_H */

