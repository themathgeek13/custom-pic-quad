#include "system.h"
#include "string.h"
#include "ctype.h"

#include "FSIO\FS.h"

#ifndef  SDFS_H
#define  SDFS_H
//===============================================================================

//*******************************************************************************
//                        Structures and defines                   
//*******************************************************************************


//===============================================================================
// FAT Cluster Markers
//===============================================================================
// The CLUSTER_EMPTY value is used to indicate that a FAT entry and it's 
// corresponding cluster are available.
#define CLUSTER_EMPTY           0x00000000 
//-------------------------------------------------------------------------------
// The BAD_CLUSTER_FAT32 value is used in FAT32 to designate "Bad Cluster" - 
// a cluster that should not be placed on the free list because it is prone to
// disk errors.
#define BAD_CLUSTER_FAT32       0x0FFFFFF7
//-------------------------------------------------------------------------------
// The EOC_CLUSTER_FAT32 macro is used when reading the FAT32 to indicate that 
// the corresponding cluster is the last one in the cluster chain for a file.
#define EOC_CLUSTER_FAT32      0x0FFFFFF8
//-------------------------------------------------------------------------------
// The CLUSTER_FAIL_FAT32 macro is used by the SDFS_FATCacheRead function to indicate that 
// an error occured reading a FAT32 file allocation able.
// NOTE: since 0x0FFFFFF7 is used to mark the bad clusters and 0x0FFFFFF8 is used
// to indicate the end-of-file (end of the cluster chain), the value '0x0FFFFFFF'
// can be used to indicate an error condition.
#define CLUSTER_FAIL_FAT32      0xFFFFFFFF
//===============================================================================


//===============================================================================
// Directory Entry markers
//===============================================================================
// The DIR_DEL macro is used to mark a directory entry as deleted.  When a file
// is deleted, this value will replace the first character in the file name, and 
// will indicate that the file the entry points to was deleted.
#define DIR_DEL             0xE5
//-------------------------------------------------------------------------------
// The DIR_EMPTY macro is used to indicate the last entry in a directory.  Since
// entries in use cannot start with a 0x00 and deleted entries start with the
// DIR_DEL character (0xE5), a 0x00 will mark the end of the in-use or previously
// used group of entries in a directory
#define DIR_EMPTY           0x00
//===============================================================================


//===============================================================================
// The __VOL structure contains information about the selected Volume on the
// device being accessed.
//===============================================================================
typedef struct
	{ 
    DWORD       firsts;         // LBA of the first sector of the FAT partition on the device
    DWORD       sectorCnt;		// The number of sectors in the volume.
    
    DWORD       fat;            // LBA of the FAT
    DWORD       fatsize;        // The number of sectors in the FAT
    
    DWORD       data;           // LBA of the first sector of the data section
    							// of the Volume. For FAT32 root directory is located
    							// together with the data.
    							
	DWORD		rootClsN;		// Cluster number of the first cluster of the Root
								// directory for FAT32; usually "2".    							
    							
    DWORD       clusterCnt;     // The number of clusters (starting from cluster 2)
    							// in the data section of the Volume.
    
    DWORD       clusterMax;     // NOTE: The maximum valid cluster number (FAT entry
    							// index) for the volume is clusterCnt + 1, and the
    							// “count of clusters including the two reserved clusters”
    							// is clusterCnt + 2.
    
    WORD		sectorSize;     // The size of a sector in bytes
    
    BYTE        fatCnt;			// The number of copies of the FAT in the partition
    
    BYTE        SecPerClus;     // The number of sectors per cluster in the data region
    
	} __attribute__ ((packed)) __VOL;
//===============================================================================



//*****************************************************************************
//                         Global Variables                               
//*****************************************************************************
// SDFS Initialization status - preset to "Not Initialized" (FALSE)
extern BOOL				SDFS_InitStatus;

// Global structure containing device information.
extern __VOL 			SDFS_VolumeInfo;   

// Global current working directory
extern FSFILE   		SDFS_CWD;               





/************************************************************************************/
/*                               Prototypes                                         */
/************************************************************************************/

//===================================================================================
// Volume Management Function                                        
//===================================================================================
CETYPE 				SDFS_MountVolume();
CETYPE 				SDFS_LoadMBR();
CETYPE 				SDFS_LoadBootSector();


//===================================================================================
// FAT Management Helpers
//===================================================================================
// FAT Cache Management
//-----------------------------------------------------------------------------------
DWORD 				SDFS_FATCacheFlush();
DWORD 				SDFS_FATCacheRead (DWORD ClusterNumber);
DWORD 				SDFS_FATCacheWrite (DWORD ClusterNumber, DWORD value);
//-----------------------------------------------------------------------------------
// FAT Data Management
//-----------------------------------------------------------------------------------
CETYPE 				SDFS_FATEraseClusterChain (DWORD ClusterNumber);
//-----------------------------------------------------------------------------------
//  Function:		DWORD SDFS_FATClusterToLBA(DWORD cluster)
//  Summary:		Convert a cluster number to the LBA of the first sector of the
//					corresponding cluster
//-----------------------------------------------------------------------------------
static inline DWORD SDFS_FATClusterToLBA(DWORD cluster)
	{
    // In FAT32, there is no separate ROOT region. It is as well stored in DATA region
    return ((cluster - 2) * SDFS_VolumeInfo.SecPerClus + SDFS_VolumeInfo.data);
	}


//===================================================================================
// Data Cache Management Helpers
//===================================================================================
CETYPE 				SDFS_DataCacheFlush();
CETYPE 				SDFS_DataCacheRead(DWORD SectorNumber, WORD Offset,
									    WORD Length, void * pDest);
CETYPE 				SDFS_DataCacheWrite(DWORD SectorNumber, void * pSource,
						   				WORD Offset, WORD	Length );
CETYPE 				SDFS_DataCacheSectorZeroOut (DWORD SectorNumber);


//===================================================================================
// 8.3 Name Management Helpers
//===================================================================================
BOOL 				SDFS_Validate8dot3Name(const char * strName, BOOL ForSearch);
BOOL 				SDFS_Format8dot3Name ( const char * strName, 
										   char   		fmtName[NAME_SIZE_8r3], 
										   BOOL   		ForSearch);
BOOL 				SDFS_Compare8dot3Name(	const char Pattern	[NAME_SIZE_8r3],
											const char TestName	[NAME_SIZE_8r3]);


//===================================================================================
// File Management Helpers
//===================================================================================
CETYPE 				SDFS_InitFSFILE(	FSFILE*	filePtr, 
										const char * FileName,	ATTR_TYPE FileAttr);
CETYPE 				SDFS_ClusterZeroOut(DWORD ClusterNumber);
CETYPE 				SDFS_ClusterGetNext(FSFILE* filePtr);
CETYPE 				SDFS_ClusterAllocateNew(FSFILE* filePtr);
//-----------------------------------------------------------------------------------
//  Function:		void SDFS_CopyFSFILE(pFSFILE foDest, pFSFILE foSource)
//  Summary:		The SDFS_CopyFSFILE function will make an exacy copy of
//    				a specified FSFILE object.
//-----------------------------------------------------------------------------------
static inline void SDFS_CopyFSFILE(FSFILE* foDest, FSFILE* foSource)
	{ memcpy(foDest, foSource, sizeof(FSFILE));	}


//===================================================================================
// Directory Management Helpers
//===================================================================================
CETYPE				SDFS_DirSetFOtoRoot(FSFILE* filePtr);
CETYPE				SDFS_DirResetEntry(	DIRENTRY* 	pDirEntry,
									 	const char* FileName, 
										ATTR_TYPE 	FileAttr);
CETYPE				SDFS_DirGetNext(FSFILE* filePtr, DIRENTRY* pDirEntry);
//------------------------------------------------------------------------
CETYPE				SDFS_DirFindEmpty(FSFILE* dirPtr, FSFILE* fileEmpty);
CETYPE 				SDFS_DirFindNext(FSFILE* dirPtr, FSFILE* foundPtr,
							ATTR_TYPE FindAttr,  ATTR_TYPE SkipAttr,  
							char Name[NAME_SIZE_8r3] );
//-----------------------------------------------------------------------------------
//  Function:		DWORD SDFS_DirGetFirstCluster (DIRENTRY* pDirEntry)
//  Summary:		Gets the cluster number from a directory entry
//-----------------------------------------------------------------------------------
static inline DWORD SDFS_DirGetFirstCluster(DIRENTRY* pDirEntry)
	{ return ( ((DWORD)(pDirEntry->DIR_FstClusHI)) << 16 ) | pDirEntry->DIR_FstClusLO; }
//-----------------------------------------------------------------------------------
//  Function:		void SDFS_DirSetFirstCluster (pDIRENTRY pDirEntry, DWORD ClusterNum)
//  Summary:		Gets the cluster number from a directory entry
//-----------------------------------------------------------------------------------
static inline void SDFS_DirSetFirstCluster (DIRENTRY* pDirEntry, DWORD ClusterNum)
	{
	pDirEntry->DIR_FstClusHI 	= (ClusterNum & 0x0FFF0000) >> 16;
	pDirEntry->DIR_FstClusLO 	= (ClusterNum & 0x0000FFFF);
	}



//===============================================================================
#endif				// #ifndef  SDFS_H




