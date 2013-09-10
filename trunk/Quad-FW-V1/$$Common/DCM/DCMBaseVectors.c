#include "DCM\DCMLocal.h"

//==================================================================================
// DCMGetMatrix returns current Rotation Matrix by rows.
// NOTE: rows of the DCM represent Earth frame axis in the
//		 Body frame od reference
//----------------------------------------------------------------------------------
void		DCMGetMatrix(	Vector*		XEarth,
							Vector*		YEarth,
							Vector*		ZEarth)
	{
	DCMXEarth(&_DCMRM, XEarth);
	DCMYEarth(&_DCMRM, YEarth);
	DCMZEarth(&_DCMRM, ZEarth);
	}
//==================================================================================







