#ifndef  FS_H
#define  FS_H
//===============================================================================


//===============================================================================
//	Interface Strunctures, Enums, and Defines              
//===============================================================================

//===============================================================================
// The CETYPE enumeration is used to indicate different error conditions during
// device operation.
//===============================================================================
typedef enum _CETYPE
	{
    CE_GOOD = 0,                    // No error
    //-----------------------------
    CE_MEDIA_NOT_PRESENT,           // SD Card is not present
    CE_MEDIA_NOT_INITIALIZED,       // SD Card initialization error has occured
    //-----------------------------
    CE_INIT_ERROR,                  // An initialization error has occured
    CE_NOT_FORMATTED,               // The disk is of an unsupported format
    CE_INVALID_FORMAT,              // Format of some directory entries in invalid
    CE_UNSUPPORTED_FS,              // The file system type is unsupported
    CE_UNSUPPORTED_SECTOR_SIZE,     // Unsupported sector size
    //-----------------------------
    CE_NOT_INIT,                    // An operation was performed on an uninitialized device
    //-----------------------------
   	CE_DISK_ERROR,                 	// I/O error accessing disk
    CE_WRITE_ERROR,                 // Could not write to a sector
    CE_BAD_SECTOR_READ,             // A bad read of a sector occured
    //-----------------------------
    CE_INVALID_CLUSTER,             // Invalid cluster value > clusterCnt
    CE_ERASE_FAIL,                  // An erase failed
    CE_DISK_FULL,                   // All clusters in partition are taken
    //-----------------------------
    CE_INVALID_ARGUMENT,            // Invalid argument
    //-----------------------------
    CE_INVALID_FILENAME,            // Invalid file name
    CE_FILENAME_DEST_TOO_SMALL,     // Destination area for file name is too small
    CE_NOT_A_FILE,				    // Provided File Object is invalid
    //-----------------------------
    CE_READONLY,                    // The file is read-only
    //-----------------------------
    CE_FILENAME_EXISTS,             // A specified filename already exists on the device
    CE_NOT_FOUND,					// FS_CreateFile with mode READ_ONLY did not find a
    								// file with the specified name
    //-----------------------------
    CE_DELETE_DIR,                  // The user tried to delete a directory with FS_Remove
    CE_DIR_NOT_EMPTY,               // This directory is not empty yet, remove files
    								// before deleting (DelTree = FALSE for FS_rmDir(...))
    CE_NOT_A_DIRECTORY,				// Provided file is not a Directory
   	CE_ROOT_DIRECTORY,				// CWD is volume's Root directory - certain operations
   									// (like FSchDirUp, FS_rmDir)cannot be carried out
    //-----------------------------
    CE_DIRECTORY,					// The user attempted File operation on a Directory
    CE_RECOVERY_FAIL,				// Recovery of a damaged file failed
    //-----------------------------
	CE_NOT_IMPLEMENTED,    			// Required feature is not implemented (yet)
    //-----------------------------
	CE_EOF                			// Error that indicates that the end of the file has
									// been reached; for SEARCH operation indicates that
									// the requested object was not found
    
	} CETYPE;



//=======================================================================================
//	ATTR_TYPE enumerator defines files and directories attributes             
//=======================================================================================
typedef enum
	{
	ATTR_NONE			= 0x00,		// No attributes - used as "ignore attributes"
									// designator in search function.
	ATTR_READONLY   	= 0x01,
	ATTR_HIDDEN 		= 0x02,
	ATTR_SYSTEM 		= 0x04,
	ATTR_VOLUME 		= 0x08,		// Special attribute that can be set ONLY on the
									// first entry in the root directory - indicates 
									// that the file name field of this entry is actually
									// the name of the volume
	ATTR_DIRECTORY		= 0x10,
	ATTR_ARCHIVE  		= 0x20,
	ATTR_LFN			= 0x0F,		// Special case - indicates that the Directory
									// entry with this (set of) attribute set represent
									// component of the long file name (not supported in
									// this library)
	ATTR_ALL			= 0x37		// Member defining ALL setable attributes
	}	ATTR_TYPE;
//=======================================================================================


//===============================================================================
// Summary: 	Enumerator of the FILE_MODE parameter for the FS_FileOpen(...) 
//				function which defines the disposition of the file to be opened.
//===============================================================================
typedef enum
	{
	FS_CREATE_NEW,		// Create a new file or replace an existing file
						// with the read/write access.
	FS_APPEND,			// Open existing file or create new file for 
						// read/write access; file positioned just past
						// the last byte.
	FS_OPEN_EXISTING,	// Open existing file for read/write access; file
						// positioned at the beginning.
	FS_READ_ONLY		// Open existing file in read-only mode; file
						// positioned at the beginning.
	} FILE_MODE;
//===============================================================================


//===============================================================================
// Directory/File Name size constants for "8.3" names
//===============================================================================
// Description: The NAME_SIZE_8r3 macro is used when validating 8.3 filenames
#define NAME_SIZE_8r3			11
//===============================================================================


//===============================================================================
// Directory entry structure
//===============================================================================
typedef struct
	{
    //-----------------------------------------------------------------
    // Required fileds - should be supported by the Driver
    //-----------------------------------------------------------------
    char      DIR_Name[NAME_SIZE_8r3]; 	// FAT-formatted object
    											// name
    BYTE      DIR_Attr;                         // File attributes
    //-----------------------------------------------------------------
    // NULLable fields: Reserver or Optional
    //-----------------------------------------------------------------
    BYTE      DIR_NTRes;                        // Reserved byte
    BYTE      DIR_CrtTimeTenth_Opt;				// Create time (millisecond field)
    											// Optional - can be 0
    WORD      DIR_CrtTime_Opt;                  // Create time (second, minute, hour field)
    											// Optional - can be 0
    WORD      DIR_CrtDate_Opt;					// Create date
    											// Optional - can be 0
    WORD      DIR_LstAccDate_Opt;				// Last access date	- Optional!!!
    											// Optional - can be 0
    //-----------------------------------------------------------------
    // Required fileds - should be supported by the Driver
    //-----------------------------------------------------------------
    WORD      DIR_FstClusHI;                    // High word of the file's first cluster number
    WORD      DIR_WrtTime;                      // Last update time
    WORD      DIR_WrtDate;                      // Last update date
    WORD      DIR_FstClusLO;                    // Low word of the file's first cluster number
    DWORD     DIR_FileSize;                     // The 32-bit file size; ignored for files
    											// representing directories - set to 0
    //-----------------------------------------------------------------
	} __attribute__ ((packed)) 	
		  DIRENTRY, 
		*pDIRENTRY;                   // A pointer to a directory entry structure


//===============================================================================
// The FSFILE structure is used to hold file information for an open file as it's
// being modified or accessed.  A pointer to an open file's FSFILE structure will
// be passeed to any library function that will read or modify the file.
//===============================================================================
typedef struct
	{
    //---------------------------------------------------------------------------
	DIRENTRY		dirFileEntry;		// Directory entry for this file object
    //---------------------------------------------------------------------------
    // Disk location of the Directory entry for this File Object
    //---------------------------------------------------------------------------
    DWORD           dirFrstCls;			// The first cluster of the file's directory
    									// (required to find "." and ".." entries)
    DWORD           dirLBA;				// LBA of this file's Directory Entry
    WORD            dirOffset;			// The position of the file's directory entry
    									// in it's Sector pointed to by dirLBA
    //---------------------------------------------------------------------------
	// File Object current position
    //---------------------------------------------------------------------------
    DWORD           fileCrntCls;		// The current cluster of the file
    DWORD           fileSeek;			// The absolute position in the file
    WORD            fileCrntSec;		// The current sector in the current cluster
    									// of the file
    WORD            fileCrntSecPos;		// The position in the current sector
    //---------------------------------------------------------------------------
	} 	__attribute__ ((packed)) 	__attribute__ ((aligned(4)))
		FSFILE, *pFSFILE;


//===============================================================================
// Summary: 	Contains the disk properties retrieved through the call
//				the FS_GetDiskProperties(...) function.  
//===============================================================================
typedef struct
	{
	DWORD		TotalClusters;		// the total number of data clusters on the drive 
	DWORD		FreeClusters;       // the number of free (unused) data clusters on drive 
	WORD 		SectorSize;			// sector size of the drive 
	WORD		SectorsPerCluster;	// number of sectors per cluster 
	char		VolLabel[NAME_SIZE_8r3];
	} FS_DISK_PROPERTIES;

//===============================================================================
// Summary: 	A structure used for searching for files on a device.
// Description: The SEARCH_STATE structure is used when searching for file or 
//				directory on a device. It contains parameters that will be loaded 
//				with the search parameters by FS_FindFirst(...) and reused on
//				subsequent calls to FS_FindNext(...).
//-------------------------------------------------------------------------------
//				This structure is for INTERNAL USE only - please do not change
//				values in this structure between calls to FS_FindFirst(...) and
//				subsequent calls to FS_FindNext(...).
//===============================================================================
typedef struct
	{
    char		SearchName[NAME_SIZE_8r3];	// The 8.3 formated Search Name or
    										// Pattern (Internal use only)
	//----------------------------------------------------------------------------    										
    ATTR_TYPE 	FindAttr;					// The attributes required to be set
    										// on matching files 
    										// (Internal use only)
	//----------------------------------------------------------------------------    										
    ATTR_TYPE 	SkipAttr;					// The attributes required to be NOT
    										// set on matching files 
    										// (Internal use only)
	//----------------------------------------------------------------------------    										
    FSFILE		SrcDir;						// The state of the directory that this
    										// search is being performed in. 
											// (Internal use only)
	} SEARCH_STATE;




//*********************************************************************************
// Prototypes                                                            
//*********************************************************************************
// FAT32 Driver System functions
//*********************************************************************************
CETYPE 		FS_Init(void);
CETYPE 		FS_GetDiskProperties(FS_DISK_PROPERTIES* properties);
//=================================================================================

//*********************************************************************************
// File Management functions
//*********************************************************************************
CETYPE 		FS_CreateFile (	const char * 	fileName, 
							FILE_MODE 		fileMode,
							FSFILE* 		filePtr );
CETYPE 		FS_Flush(FSFILE* filePtr);
CETYPE		FS_Rename (FSFILE* filePtr, const char * newName);
CETYPE		FS_Delete (FSFILE* filePtr);
CETYPE 		FS_FindFirst(	const char* Pattern,
							ATTR_TYPE FindAttr,  ATTR_TYPE SkipAttr,  
						 	SEARCH_STATE* statePtr, FSFILE* foundPtr);
CETYPE 		FS_FindNext(	SEARCH_STATE* statePtr, FSFILE* foundPtr);
//---------------------------------------------------------------------------------
CETYPE 		FS_GetName(char* Name, WORD Length, FSFILE* filePtr);
//---------------------------------------------------------------------------------
CETYPE		FS_Recover(FSFILE* filePtr);
//=================================================================================

//*********************************************************************************
// Directory Management functions
//*********************************************************************************
CETYPE 		FS_GetCWD(FSFILE* cwdPtr);
CETYPE 		FS_mkDir (char * Name, ATTR_TYPE Attr, FSFILE* newDir);
CETYPE 		FS_chDir (FSFILE* chDir);
CETYPE 		FS_chDirUp();
CETYPE 		FS_chDirToRoot ();
CETYPE 		FS_rmDir (FSFILE* rmDir, BOOL DelTree);


//*********************************************************************************
// I/O functions
//*********************************************************************************
CETYPE		FS_Read(FSFILE* filePtr,  void* dest, WORD length, WORD* readcnt );
CETYPE 		FS_Write(FSFILE* filePtr, const void* origin, WORD length );
CETYPE 		FS_WriteSector(FSFILE* filePtr, const void* origin );
//=================================================================================

//*********************************************************************************
// File control functions
//*********************************************************************************
CETYPE 		FS_SeekAbs (FSFILE * filePtr, DWORD Seek);
CETYPE 		FS_Attrib (FSFILE * filePtr, ATTR_TYPE Attributes);
//---------------------------------------------------------------------------------
//  Summary:		Reset the position of the specified file to the beginning of 
//					the file. This function is faster than FS_FileSeekAbs(..., 0)
//---------------------------------------------------------------------------------
CETYPE static inline 	FS_SeekStart (FSFILE * filePtr)
	{
    filePtr->fileCrntCls 		= // SDFS_DirGetFirstCluster(&filePtr->dirFileEntry)
    							  ( ((DWORD)(filePtr->dirFileEntry.DIR_FstClusHI)) << 16 )
    							| filePtr->dirFileEntry.DIR_FstClusLO;
    filePtr->fileSeek 			= 0;
    filePtr->fileCrntSecPos 	= 0;
    filePtr->fileCrntSec 		= 0;
    //-------------------------------
    return CE_GOOD;
	}
//---------------------------------------------------------------------------------
//  Summary:		Reset the position of the specified file to the end of the file
//---------------------------------------------------------------------------------
CETYPE static inline	FS_SeekEnd (FSFILE * filePtr)
	{return FS_SeekAbs (filePtr, filePtr->dirFileEntry.DIR_FileSize);}
//---------------------------------------------------------------------------------
//  Summary:		Moves the current position in the file SeekFwd bytes forward
//---------------------------------------------------------------------------------
CETYPE static inline	FS_SeekFwd (FSFILE * filePtr, DWORD SeekFwd)
	{return FS_SeekAbs (filePtr, filePtr->fileSeek + SeekFwd);}
//---------------------------------------------------------------------------------
//  Summary:		Moves the current position in the file SeekBck bytes backward
//---------------------------------------------------------------------------------
CETYPE static inline 	FS_SeekBck (FSFILE * filePtr, DWORD SeekBck)
	{
	if (SeekBck > filePtr->fileSeek)
		return CE_INVALID_ARGUMENT;
	//-----------------------------------------
    return FS_SeekAbs (filePtr, filePtr->fileSeek - SeekBck);
	}
//---------------------------------------------------------------------------------
//  Summary:		Returns size of the file
//---------------------------------------------------------------------------------
DWORD static inline FS_GetSize (FSFILE * filePtr)
	{return (filePtr->dirFileEntry.DIR_FileSize);}
//---------------------------------------------------------------------------------
//  Summary:		Returns current position in the file
//---------------------------------------------------------------------------------
DWORD static inline FS_GetPosition (FSFILE * filePtr)
	{return (filePtr->fileSeek);}
//---------------------------------------------------------------------------------
//  Summary:		Indicates whether the current file position is at the end
//---------------------------------------------------------------------------------
BOOL static inline FS_IsEOF( FSFILE * filePtr )
	{return filePtr->fileSeek >= filePtr->dirFileEntry.DIR_FileSize ? TRUE : FALSE;}
//---------------------------------------------------------------------------------
//  Summary:		Indicates whether the current file represents a Directory
//---------------------------------------------------------------------------------
BOOL static inline FS_IsDirectory( FSFILE * filePtr )
	{return filePtr->dirFileEntry.DIR_Attr & ATTR_DIRECTORY;}
//---------------------------------------------------------------------------------
//  Summary:		Indicates whether the current file is Hidden
//---------------------------------------------------------------------------------
BOOL static inline FS_IsHidden( FSFILE * filePtr )
	{return filePtr->dirFileEntry.DIR_Attr & ATTR_HIDDEN;}
//---------------------------------------------------------------------------------
//  Summary:		Indicates whether the current file is System
//---------------------------------------------------------------------------------
BOOL static inline FS_IsSystem( FSFILE * filePtr )
	{return filePtr->dirFileEntry.DIR_Attr & ATTR_SYSTEM;}
//---------------------------------------------------------------------------------
//  Summary:		Indicates whether the current file is Read-Only
//---------------------------------------------------------------------------------
BOOL static inline FS_IsReadOnly( FSFILE * filePtr )
	{return filePtr->dirFileEntry.DIR_Attr & ATTR_READONLY;}
//=================================================================================


//===============================================================================
#endif				// #ifndef  FS_H


