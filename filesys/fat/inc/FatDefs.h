//###########################################################################
// FatDefs.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_DEFS_H__
#define __FAT_DEFS_H__

#include "Defines.h"
#include "FileDefs.h"
#include "Templates.h"
#include "Driver.h"

/// @brief 
class FatDefs
{
protected:
	enum BootIndicator
	{
		_NotBootable = 0x00,
		_Bootable    = 0x80,
	};

	enum FATType
	{
		_NoneType = 0,
		_FAT12,
		_FAT16,
		_FAT32,
		_EXTFAT,
	};

	enum DirAttr
	{
		_ATTR_FILE       = 0x00,
		_ATTR_READ_ONLY  = 0x01,
		_ATTR_HIDDEN     = 0x02,
		_ATTR_SYSTEM     = 0x04,
		_ATTR_VOLUME_ID  = 0x08,
		_ATTR_DIRECTORY  = 0x10,
		_ATTR_ARCHIVE    = 0x20,
		_ATTR_LONG_NAME  = _ATTR_READ_ONLY | _ATTR_HIDDEN | _ATTR_SYSTEM | _ATTR_VOLUME_ID,
		_ATTR_LONG_NAME_MASK = _ATTR_READ_ONLY | _ATTR_HIDDEN | _ATTR_SYSTEM | _ATTR_VOLUME_ID | _ATTR_DIRECTORY | _ATTR_ARCHIVE,
	};

	enum NSFlag
	{
		_NS_NONE     = 0x00,
		_NS_LOSS     = 0x01,   /* Out of 8.3 format */
		_NS_LFN      = 0x02,   /* Force to create LFN entry */
		_NS_LAST     = 0x04,   /* Last segment */
		_NS_BODY     = 0x08,   /* Lower case flag (body) */
		_NS_EXT      = 0x10,   /* Lower case flag (ext) */
		_NS_DOT      = 0x20,   /* Dot entry */
		_NS_NOLFN    = 0x40,   /* Do not find LFN */
		_NS_NONAME   = 0x80,   /* Not followed */
	};

	struct DPT
	{
		uint32_t bootIndicator : 8;
		uint32_t startingHead : 8;
		uint32_t startingSector : 6;
		uint32_t startingCylinder: 10;
		uint32_t systemID : 8;
		uint32_t endingHead : 8;
		uint32_t endingSector : 6;
		uint32_t endingCylinder : 10;
		uint32_t relativeSectors;
		uint32_t totalSectors;
	} __attribute__((packed));

	struct MBR
	{
		uint8_t  boot[446];
		DPT      dpt[4];
		uint16_t magic;
	} __attribute__((packed));

	struct BS
	{
		uint8_t jmpBoot[3];
		uint8_t OEMName[8];
	} __attribute__((packed));

	struct BPB
	{
		uint16_t bytesPerSec;
		uint8_t  secPerClust;
		uint16_t rsvdSecCnt;
		uint8_t  numFATs;
		uint16_t rootEntCnt;
		uint16_t totSec16;
		uint8_t  media;
		uint16_t FATSz16;
		uint16_t secPerTrk;
		uint16_t numHeads;
		uint32_t hiddSec;
		uint32_t totSec32;
	}  __attribute__((packed));

	struct FAT1216
	{
		uint8_t  drvNum;
		uint8_t  reserved1;
		uint8_t  bootSig;
		uint32_t volID;
		uint8_t  volLab[11];
		uint8_t  filSysType[8];
		uint8_t  reserved[28];
	} __attribute__((packed));

	struct FAT32
	{
		uint32_t FATSz32;
		uint16_t extFlags;
		uint16_t FSVer;
		uint32_t rootClust;
		uint16_t FSInfo;
		uint16_t bkBootSec;
		uint8_t  reserved[12];
		uint8_t  drvNum;
		uint8_t  reserved1;
		uint8_t  bootSig;
		uint32_t volID;
		uint8_t  volLab[11];
		uint8_t  filSysType[8];
	} __attribute__((packed));

	struct DBR
	{
		BS  bs;
		BPB bpb;
		union {
			FAT1216 fat1216;
			FAT32   fat32;
		};
		uint8_t  reserved[420];
		uint16_t magic;
	} __attribute__((packed));

	struct FAT32FSInfo
	{
		uint32_t leadSig;
		uint8_t  reserved1[480];
		uint32_t structSig;
		uint32_t freeCount;
		uint32_t nextFree;
		uint8_t  reserved2[12];
		uint32_t trailSig;
	} __attribute__((packed));

	struct FATSDir
	{
		char     name[11];
		uint8_t  attr;
		uint8_t  NTRes;
		uint8_t  crtTimeTenth;
		uint16_t crtTime;
		uint16_t crtDate;
		uint16_t lstAccDate;
		uint16_t fstClustHI;
		uint16_t wrtTime;
		uint16_t wrtDate;
		uint16_t fstClustLO;
		uint32_t fileSize;

		FATSDir()          { memset((void*)this, 0, 32); }
		bool IsDirectory() { return ((attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_DIRECTORY); }
		bool IsVolume()    { return ((attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_VOLUME_ID); }
		bool IsFile()      { return ((attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_FILE     ); }
		bool IsHidden()    { return ((attr &  _ATTR_HIDDEN                      ) == _ATTR_HIDDEN   ); }

	} __attribute__((packed));

	struct FATLDir
	{
		uint8_t  ord;
		uint16_t name1[5];
		uint8_t  attr;
		uint8_t  type;
		uint8_t  chksum;
		uint16_t name2[6];
		uint16_t fstClustLO;
		uint16_t name3[2];

		void Fill()
		{
			memset((void*)name1, 0xff, 10);
			memset((void*)name2, 0xff, 12);
			memset((void*)name3, 0xff, 4);
		}
	} __attribute__((packed));

	union FATEnt
	{
		FATLDir lfn;
		FATSDir sfn;
		
		FATEnt()           { memset((void*)this, 0, 32); }
		bool IsLongName()  { return ((lfn.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME); }
		bool IsVaild()     { return ((lfn.ord) && (lfn.ord != dir_free_flag)); }
		uint8_t OrdSize()  { return (lfn.ord - dir_seq_flag + 1); }

	} __attribute__((packed));

	struct DirEntry
	{
		FATSDir body;
		bool    root;
		char*   name;

		DirEntry(FATSDir body = FATSDir(), char* name = NULL)
		{
			this->body = body;
			this->name = name;
			this->root = false;
		}

		~DirEntry()
		{
			delete[] name;
		}
	} __attribute__((packed));

	struct DirEntries
	{
		List<DirEntry> dirs;
		char*          path;

		DirEntries() :
			path(NULL)
		{}

		~DirEntries()
		{
			dirs.Release();
			delete[] path;
		}

		int CheckConflict(FATEnt* entry)
		{
			uint8_t count = 0;
			for (DirEntry* dir = dirs.Begin(); !dirs.IsEnd(); dir = dirs.Next())
			{
				for (uint8_t i = 0; i < 11; i++)
				{
					if (dir->body.name[i] != entry->sfn.name[i])
					{
						count++; break;
					}
				}
			}
			return (dirs.GetSize() == count) ? _OK : _ERR;
		}
	};

	struct Info
	{
		FATType  fatType;
		uint32_t fatSize;

		uint32_t rsvdSecCnt;
		uint32_t totalSectors;
		uint32_t countOfClusters;

		uint32_t startOfFatSector;
		uint32_t endedOfFatSector;

		uint32_t rootClust;
		uint32_t firstRootSector;
		uint32_t countOfRootSecs;

		uint32_t firstDataSector;
		uint32_t countOfDataSecs;

		uint32_t entriesPerSec;
		uint32_t bytesPerSec;
		uint32_t secPerClust;
	};

	struct DskSzToSecPerClus
	{
		uint32_t diskSize;
		uint8_t  secPerClusVal;
	} __attribute__((packed));

	/*
	*This is the table for FAT16 drives. NOTE that this table includes
	* entries for disk sizes larger than 512 MB even though typically
	* only the entries for disks < 512 MB in size are used.
	* The way this table is accessed is to look for the first entry
	* in the table for which the disk size is less than or equal
	* to the DiskSize field in that table entry.  For this table to
	* work properly BPB_RsvdSecCnt must be 1, BPB_NumFATs
	* must be 2, and BPB_RootEntCnt must be 512. Any of these values
	* being different may require the first table entries DiskSize value
	* to be changed otherwise the cluster count may be to low for FAT16.
	*/
	const DskSzToSecPerClus dskTableFAT16[8] = {
		{ 8400,       0  }, /* disks up to 4.1 MB, the 0 value for SecPerClusVal trips an error */
		{ 23680,      2  }, /* disks up to  16 MB,  1k cluster */
		{ 262144,     4  }, /* disks up to 128 MB,  2k cluster */
		{ 524288,     8  }, /* disks up to 256 MB,  4k cluster */
		{ 1048576,    16 }, /* disks up to 512 MB,  8k cluster */
		/* The entries after this point are not used unless FAT16 is forced */
		{ 2097152,    32 }, /* disks up to   1 GB, 16k cluster */
		{ 4194304,    64 }, /* disks up to   2 GB, 32k cluster */
		{ 0xffffffff, 0  }  /* any disk greater than 2GB, 0 value for SecPerClusVal trips an error */
	};

	/*
	* This is the table for FAT32 drives. NOTE that this table includes
	* entries for disk sizes smaller than 512 MB even though typically
	* only the entries for disks >= 512 MB in size are used.
	* The way this table is accessed is to look for the first entry
	* in the table for which the disk size is less than or equal
	* to the DiskSize field in that table entry. For this table to
	* work properly BPB_RsvdSecCnt must be 32, and BPB_NumFATs
	* must be 2. Any of these values being different may require the first
	* table entries DiskSize value to be changed otherwise the cluster count
	* may be to low for FAT32.
	*/
	const DskSzToSecPerClus dskTableFAT32[6] = {
		{ 66600,       0  }, /* disks up to 32.5 MB, the 0 value for SecPerClusVal trips an error */
		{ 532480,      1  }, /* disks up to  260 MB,  .5k cluster */
		{ 16777216,    8  }, /* disks up to    8 GB,   4k cluster */
		{ 33554432,    16 }, /* disks up to   16 GB,   8k cluster */
		{ 67108864,    32 }, /* disks up to   32 GB,  16k cluster */
		{ 0xffffffff,  64 } /* disks greater than 32GB, 32k cluster */
	};

	//Static constants
	static const uint16_t magic = 0xaa55;
	static const uint8_t  dir_entry_size = 32;
	static const uint8_t  long_name_size  = 13;
	static const uint8_t  short_name_size = 11;
	static const uint8_t  volume_label_size = 11;
	static const uint8_t  dir_seq_flag = 0x40;
	static const uint8_t  dir_free_flag = 0xe5;
	static const uint16_t fat12_eoc_flag = 0xff8;
	static const uint16_t fat16_eoc_flag = 0xfff8;
	static const uint32_t fat32_eoc_flag = 0xffffff8;
};

#endif //!__FAT_DEFS_H__
