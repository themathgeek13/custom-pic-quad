
//===============================================================================
#ifndef __Log_H
#define __Log_H
//===============================================================================
// The LERROR enumeration is used to indicate different Log error conditions.
//===============================================================================
typedef enum _LERROR
	{
    LE_GOOD = 0,                    // No error
    //-----------------------------
    LE_NOT_INITIALIZED,     		// Log was not initialized
    //-----------------------------
    LE_INVALID_ARGUMENT,     		// One of the arguments passed to the
    								// function is invalid
    //-----------------------------
    LE_FSERROR						// FS error precluded successful operation
    								// Underlying FS error can be retrieved by
    								// calling LogLastFSError()
	} LERROR;
//===============================================================================

void	LogInit();
LERROR	LogNewFile(FSFILE* newLog);
//-------------------------------------------------------------------------------
CETYPE	LogLastFSError();
//===============================================================================
#endif



