#include "FSIO\SDFS.h"

//************************************************************************************
//  Function:		BOOL SDFS_Validate8dot3Name(const char * strName, BOOL ForSearch)
//  Summary:		Validates 8.3 name
//  Input:
//    				strName   - The name to be validated
//    				ForSearch - Flag indicating whether <name> should allow for string
//								search with wildcard ('*' and '?') characters.
//  Return Values:
//    				TRUE  - Name is valid
//    				FALSE - Name is invalid
//  Description:
//    				The SDFS_Validate8dot3Name function will compare characters in a
//    				specified name to determine if they're permissable in the FAT 
//					file system as 8.3 names. It will also validate the structure of
//					the name to ensure that a) name part does not exceed 8 characters,
//					b) only one Dot is present, and c) extension does not exceed 3
//					characters. 
//					If all conditions are satisfied, the function returns TRUE,
//					otherwise - FALSE.
//************************************************************************************
BOOL SDFS_Validate8dot3Name(const char * strName, BOOL ForSearch)
	{
	uint	NameLen	= 0;

	//-----------------------------------------------
	NameLen 	= strlen(strName);
	if (0 == NameLen || NameLen > (NAME_SIZE_8r3 + 1))	// "+1" to account for period "."
		return FALSE;
	//-----------------------------------------------

    BOOL 	radix 			= FALSE;
    
    BYTE	asciiValue;
    int 	index;

	for( index = 0; index < NameLen; index++ )
		{
		asciiValue = strName[index];
		
		// Check character codes
		if	(
				(asciiValue <= 0x20) 
			|| 	(asciiValue == 0x22)	// "
				// Wildcard char '*' allowed only in search strings
	    	|| 	(asciiValue == 0x2A  &&  ForSearch == FALSE)
				// Wildcard char '+' allowed only in search strings
				// (matches any one numeric symbol)
	    	||	(asciiValue == 0x2B  &&  ForSearch == FALSE)
	    	|| 	(asciiValue == 0x2C) 	// ,
  	    		// Only one radix ('.') character is allowed in 8P3 format
  	    		// and it should not be the first character in the name
	    	|| 	(asciiValue == 0x2E  &&  radix == TRUE)
			||	(asciiValue == 0x2F) 	// /
			|| 	(asciiValue == 0x3A) 	// :
	    	||	(asciiValue == 0x3B) 	// ;
			|| 	(asciiValue == 0x3C) 	// <
	    	|| 	(asciiValue == 0x3D) 	// =
			||	(asciiValue == 0x3E) 	// >
				// Wildcard char '?' allowed only in search strings
				// (matches any one alpha-numeric symbol)
	    	|| 	(asciiValue == 0x3F  &&  ForSearch == FALSE)
	    	|| 	(asciiValue == 0x5B) 	// [
			|| 	(asciiValue == 0x5C) 	// "\"
	    	||  (asciiValue == 0x5D) 	// ]
			|| 	(asciiValue == 0x7C)	// |
			||	(asciiValue >= 0x7F)	// extended set
			)
			return FALSE;
			

    	    if (asciiValue == 0x2E)		// '.'
    	    	{
	    	    if (index == 0)
	    	    	return FALSE;		// Name cannot start with Dot!
	    	    //-------------------------
	   	        radix = TRUE;
	    	    //-------------------------
	   	        // Verify extension length
	   	        if ( (NameLen - index) > 4 )	// Remember: index is 0-based!
	   	        	return FALSE;				// Extension longer than 3 chars!
	    	    //-------------------------
	   	     	}   


    	    if 	(	radix == FALSE
    	    	&&	index >  7		)			// Remember: index is 0-based!
    	    		return FALSE;				// Name part is longer than 8 chars!
		}

	return TRUE;
	}
//====================================================================================

//************************************************************************************
//  Function:		BOOL SDFS_Format8dot3Name (	const char * strName, 
//												char   fmtName[NAME_SIZE_8r3], 
//												BOOL   ForSearch)
//  Summary:		Format a name into 8.3 format
//  Input:
//    				strName   - The name to be formatted
//					fmtName	  - pointer to the first character of the array sized to
//								to NAME_SIZE_8r3 to accept formatted name
//    				ForSearch - Flag indicating whether <name> should allow for string
//								search with wildcard ('*' and '?') characters.
//  Return Values:
//    				TRUE  - Name is formatted
//    				FALSE - Name cannot be formatted
//  Description:
//    				Formats a name into a 8.3 filename and stores formatted name into
//					the output array. If the name part is less than 8 chars, then it 
//					will be padded with spaces. If the extension name is fewer than 3 
//					chars, then it will also be padded with spaces. The
//    				SDFS_Validate8dot3Name(...) function is used to ensure the characters 
//					in the specified name and its structure are valid for 8.3 format.
//  				As part of the formatting process lower case characters are 
//					converted to upper case in accordance with the 8.3 file name 
//					specification.
//************************************************************************************
BOOL SDFS_Format8dot3Name (const char * strName, 
					  char   	   fmtName[NAME_SIZE_8r3], 
					  BOOL   	   ForSearch)
	{
	//------------------------------------------------------------------
	// Validate input string format
	//------------------------------------------------------------------
    BOOL	RC	= SDFS_Validate8dot3Name(strName, ForSearch);
    if (RC == FALSE)
    	return RC;		// Invalid input string format!
	//------------------------------------------------------------------

	int		strLen 	= strlen(strName);
	int		outPos	= 0;
	int		index;

	//------------------------------------------------------------------
	// Blank out output array
	//------------------------------------------------------------------
	for (index = 0; index < NAME_SIZE_8r3; index++)
		fmtName[index] = ' ';


	//------------------------------------------------------------------
	// Format input string (validated!) into output array
	//------------------------------------------------------------------
	// NOTE: outPos pre-set to 0
	//------------------------------------------------------------------
	for (index = 0; index < strLen; index++)
	    {
	    if (strName[index] == '.')		// '.'
	    	{
		    outPos = 8;					// Set outPos to the first position
		    							// of the Extension part
		    continue;					// Ignore radix, skip to the next
		    							// character
	    	}

	    // Normal character
		if ( strName[index] >= 0x61  &&  strName[index] <= 0x7A )
			// Convert lower-case to upper-case
		    fmtName[outPos] = strName[index] - 0x20;
		else
			// Copy character
		    fmtName[outPos] = strName[index];

		outPos++;
	    }

	return TRUE;
	}
//====================================================================================

//************************************************************************************
//  Function:		BOOL SDFS_Compare8dot3Name(	const char Pattern	[NAME_SIZE_8r3],
//												const char TestName	[NAME_SIZE_8r3])
//  Summary:		Compares 8.3 TestName to 8.3 Pattern
//  Input:
//    				Pattern   - comparizon pattern, which may include wildcard chars.
//					TestName  - name to compare to pattern
//  Return Values:
//    				TRUE  - Name matches pattern
//    				FALSE - Name does not match pattern
//  Description:
//    				Compares 8.3 TestName to 8.3 Pattern; pattern may include wildcard
//					characters "*" and "?". Wildcard "*" matches any sequence of 
//					characters, while "?" matches any one valid character.
//************************************************************************************
BOOL SDFS_Compare8dot3Name(	const char Pattern[NAME_SIZE_8r3], const char TestName	[NAME_SIZE_8r3])
	{
	//-----------------------------------------
	typedef enum
		{
		Match,
		Question,
		Plus,
		Star,
		PostStar
		}	States;
	//-----------------------------------------
	States SearchState = Match;
	//-----------------------------------------
	WORD	iP	= 0;
	WORD	iT	= 0;
	//-----------------------------------------
	while ( (iP < NAME_SIZE_8r3) && (iT < NAME_SIZE_8r3) )
		{
		switch (SearchState)
			{
			//----------------------------------------------
			case	Star:
				if ('*' == Pattern[iP] || ' ' == Pattern[iP])
					{
					iP++;
					break;
					}
				SearchState = PostStar;
				break;
			//----------------------------------------------
			case	PostStar:
				if (Pattern[iP] == TestName[iT])
					{
					iP++;
					iT++;	
					SearchState = Match;
					break;
					}
				iT++;	// Consuming '*'...
				break;
			//----------------------------------------------
			case	Question:
				if ( isalnum(TestName[iT]))
					{
					iP++;
					iT++;	// '?' consumed
					SearchState = Match;
					break;
					}
				else
					return FALSE;
			//----------------------------------------------
			case	Plus:
				if ( isdigit(TestName[iT]))
					{
					iP++;
					iT++;	// '+' consumed
					SearchState = Match;
					break;
					}
				else
					return FALSE;
			//----------------------------------------------
			default:	// 	case	Match:
				if ('*' == Pattern[iP])
					{
					SearchState = Star;
					iP++;
					break;
					}
				if ('?' == Pattern[iP])
					{
					SearchState = Question;
					break;
					}
				if ('+' == Pattern[iP])
					{
					SearchState = Plus;
					break;
					}
				// Comparing non-wildcard characters
				if (Pattern[iP] != TestName[iT])
					return FALSE;	// No Match...
				iP++;
				iT++;	
				SearchState = Match;
				break;
			}					
		}
	//------------------------------------------------
	// Confirm that the Pattern is consumed completely
	//------------------------------------------------
	while (iP < NAME_SIZE_8r3)
		{
		if (' ' != Pattern[iP])
			return FALSE;	// Unmatched characters in the pattern...
		iP++;
		}
	//------------------------------------------------
	// Decide based upon last state
	//------------------------------------------------
	if 	( 	Match 	== SearchState
		||
			Star	== SearchState
		)
		return TRUE;
	else
		return FALSE;
	}
//====================================================================================




