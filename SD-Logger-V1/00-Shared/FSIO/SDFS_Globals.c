
#include "FSIO\SDFS.h"



/*****************************************************************************/
/*                         Global Variables                                  */
/*****************************************************************************/
// SDFS Initialization status - preset to "Not Initialized" (FALSE)
BOOL			SDFS_InitStatus		= FALSE;

// Global structure containing device information.
__VOL 			SDFS_VolumeInfo;         

// Global current working directory
FSFILE   		SDFS_CWD;               






