#ifndef  SDFS_VolumeMgmt_H
#define  SDFS_VolumeMgmt_H
//===============================================================================

//************************************************************************************
// MBR and Boot Sector signatures
//************************************************************************************
// The FAT_GOOD_SIGN_0 macro is used to determine that the first byte (offset 510) of
// the MBR or boot sector signature code is correct
//------------------------------------------------------------------------------------
#define FAT_GOOD_SIGN_0     0x55
//------------------------------------------------------------------------------------
// The FAT_GOOD_SIGN_1 macro is used to determine that the second byte (offset 511))
// of the MBR or boot sector signature code is correct
#define FAT_GOOD_SIGN_1     0xAA
//************************************************************************************

//************************************************************************************
// The NUMBER_OF_BYTES_IN_DIR_ENTRY macro represents the number of bytes in one 
// directory entry. It is used to calculate the number of sectors in the root 
// directory based on information in the boot sector as well as number of 
// directory entries per FAT sector.
#define NUMBER_OF_BYTES_IN_DIR_ENTRY    32
//************************************************************************************


//************************************************************************************
// The SWORD structure is used to defined a 24-bit data type.  For 16+ bit
// architectures, this must be represented as an array of three bytes.
//------------------------------------------------------------------------------------
typedef struct
	{
    unsigned char array[3];
	} __attribute__ ((packed)) SWORD;
//************************************************************************************


//************************************************************************************
// The PT structure defines a partition table (typically found in the MBR of a device)
//------------------------------------------------------------------------------------
typedef struct
	{
    BYTE      PTE_BootDes;            // The boot descriptor (should be 0x00 in a non-bootable device)
    SWORD     PTE_FrstPartSect;       // The cylinder-head-sector address of the first sector of the partition
    BYTE      PTE_FSDesc;             // The file system descriptor
    SWORD     PTE_LstPartSect;        // The cylinder-head-sector address of the last sector of the partition
    DWORD     PTE_FrstSect;           // The logical block address of the first sector of the partition
    DWORD     PTE_NumSect;            // The number of sectors in a partition
    } __attribute__ ((packed)) __PTE;
//************************************************************************************


//************************************************************************************
// The __MBR structure defines the organization of the master boot record.  When the
// MBR is loaded from the device, it will be cast as a __MBR structure so the MBR
// elements can be easily accessed.
//------------------------------------------------------------------------------------
typedef struct
	{
    BYTE    BootCode[446];		// Boot code, usually ignored
    //-----------------------------------------------------------------
    // Up to 4 Partition Tables
    //-----------------------------------------------------------------
    __PTE	Partition0;			// The first partition table entry
    __PTE	Partition1;			// The second partition table entry
    __PTE	Partition2; 		// The third partition table entry
    __PTE	Partition3;			// The fourth partition table entry
    //-----------------------------------------------------------------
    // Last two bytes of the MBR sector - FAT signature
    //-----------------------------------------------------------------
    BYTE	Signature0;			// MBR signature code - equal to 0x55
    BYTE	Signature1;			// MBR signature code - equal to 0xAA
    //-----------------------------------------------------------------
	}__attribute__((packed)) __MBR;
//************************************************************************************



//************************************************************************************
// The __BSEXT_FAT16 structure provides a layout of the section of the "bios parameter
// block" in the boot sector starting at offset "36" of a FAT16 partition.
//------------------------------------------------------------------------------------
typedef struct 
	{
    BYTE  BS_DrvNum;			// ( 36) Drive number for INT 0x13
    BYTE  BS_Reserved;			// ( 37) Reserved space; should ALWAYS be 0 for FAT   							
    BYTE  BS_BootSig;			// ( 38) Boot signature - equal to 0x29
    BYTE  BS_VolID[4];			// ( 39) Volume ID
    BYTE  BS_VolLab[11];		// ( 43) Volume Label
    BYTE  BS_FSType[8];			// ( 54) File system type in ASCII - One of the strings
    							// “FAT12   ”, “FAT16   ”, or “FAT     ”.   
    							// Not used for determination of the actual File system
    } __attribute__ ((packed)) __BSEXT_FAT16;
//************************************************************************************



//************************************************************************************
// The __BSEXT_FAT32 structure provides a layout of the section of the "bios parameter
// block" in the boot sector starting at offset "36" of a FAT32 partition.
//------------------------------------------------------------------------------------
typedef struct 
	{
    DWORD BPB_FATSz32;			// ( 36) Sectors per FAT (32 bits)
    WORD  BPB_ExtFlags;			// ( 40) Presently active FAT. Defined by bits 0-3 if
    							// bit 7 is 1. Otherwise (bit 7 = 0) FAT is mirrored
    							// at runtime.
    WORD  BPB_FSVers;			// ( 42) FAT32 filesystem version.  Should be 0:0
    DWORD BPB_RootClus;			// ( 44) Start cluster number of the root directory;
    							// Preferebly should be 2, but could be any other number
    WORD  BPB_FSInfo;			// ( 48) Sector number of the FSInfo structure in the
    							// reserved area of the FAT32 volume.
    WORD  BPB_BkBPB;         	// ( 50) If non-zero, indicates the sector number in
    							// the reserved area of the volume of a copy of the boot
    							// record. Usually 6. No value other than 6 is recommended.
    BYTE  BS_Reserved[12];		// ( 52) Reserved space
    
    BYTE  BS_DrvNum;			// ( 64) Drive number
    BYTE  BS_Reserved1;			// ( 65) Reserved space
    BYTE  BS_BootSig;			// ( 66) Boot signature - 0x29
    BYTE  BS_VolID[4];			// ( 67) Volume ID
    BYTE  BS_VolLab[11];		// ( 71) Volume Label
    BYTE  BS_FSType[8];			// ( 82) File system type in ASCII - “FAT32   ” string.   
    							// Not used for determination of the actual File system  
    } __attribute__ ((packed)) __BSEXT_FAT32;
//************************************************************************************


//************************************************************************************
// The __BS structure provides a layout of the Boot Sector for both FAT16 and FAT32
// partitions.
//------------------------------------------------------------------------------------
typedef struct
	{
   //------------------------------------------------------------------------------------------
   //							 Offset  Description
   //------------------------------------------------------------------------------------------
    SWORD 	BS_jmpBoot;			// (  0) Jump Command
    BYTE  	BS_OEMName[8];		// (  3) OEM name
    //------------------------------------------------------------------------------------------
    // Common FAT16 and FAT32 fields
    //------------------------------------------------------------------------------------------
    WORD	BPB_BytsPerSec;		// ( 11) Number of bytes per sector

    BYTE 	BPB_SecPerClus;		// ( 13) Number of sectors per cluster

    WORD	BPB_RsvdSecCnt;		// ( 14) Number of reserved sectors at the
    							// beginning of the partition

    BYTE 	BPB_NumFATs;		// ( 16) Number of FATs on the partition

    WORD	BPB_RootEntCnt16;	// ( 17) Number of root directory entries;
    							// Valid only for FAT16, should be 0 for FAT32

    WORD	BPB_TotSec16;		// ( 19) Total number of sectors;
    							// Valid for both FAT16 and FAT32;
    							// if "0" use value in BPB_TotSec32

    BYTE 	BPB_Media;			// ( 21) Media descriptor
								// 0xF8 is the standard value for “fixed” (non-removable) media.
								// For removable media, 0xF0 is frequently used. The legal values
								// for this field are 0xF0, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE,
								// and 0xFF. The only other important point is that whatever value
								// is put in here must also be put in the low byte of the FAT[0] entry.    

    WORD	BPB_FATSz16;		// ( 22) Number of sectors per FAT
   								// Valid only for FAT16, should be 0 for FAT32,
   								// which uses new field BPB_FATSz32 
   								
    WORD	BPB_SecPerTrk;		// ( 24) Number of sectors per track for INT 0x13.
    							// This field is only relevant for media that have a geometry
    							// (volume is broken down into tracks by multiple heads and
    							// cylinders) and are visible on INT 0x13. 
    							
    WORD	BPB_NumHeads;		// ( 26) Number of heads for INT 0x13.
    
    DWORD	BPB_HiddSec;		// ( 28) Number of hidden sectors sectors preceding the partition that
    							// contains this FAT volume. This field is generally only relevant for
    							// media visible on INT 0x13. This field should always be zero on media
    							// that are not partitioned. 

    DWORD	BPB_TotSec32;		// ( 32) Total sector count (32 bits) - valid for FAT32 and newer
    							// implementations of FAT16; mutually exclusive with BPB_TotSec16.   
    //------------------------------------------------------------------------------------------
    // A union of different bios parameter blocks
    union
    	{
        __BSEXT_FAT32  FAT_32;
        __BSEXT_FAT16  FAT_16;
    	} FAT;
    BYTE    Reserved[512 - 36 - sizeof(__BSEXT_FAT32) - 2]; 	// Reserved space
    //---------------------------------------------------
    BYTE    Signature0;         					// Boot sector signature code - equal to 0x55
    BYTE    Signature1;         					// Boot sector signature code - equal to 0xAA
    } __attribute__ ((packed)) __BS;


//===============================================================================
#endif				// #ifndef  SDFS_VolumeMgmt_H
