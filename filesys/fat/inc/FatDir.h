//###########################################################################
// FatDir.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_DIR_H__
#define __FAT_DIR_H__

#include "Templates.h"
#include "FatDefs.h"

#include "FatDisk.h"

/// @brief 
class FatDir : FatDefs
{
private:
	//Members
	FatDisk  disk;
	List<DirEntry> dirs;
public:
	//Methods
	void Initialize(FATData* fat, DBR* dbr, uint32_t fstSecNum);

	//Name Methods
	uint8_t ChkSum(char* name);
	char* GetShortName(FATSDir* sdir);
	char* GetLongName(FATLDir* ldir, FATSDir* sdir);

	//Directory Methods
	int CheckDir(DirEntry* entry, DirAttr attr);
	char* GetDirName(DirEntry* entries, uint32_t& idx, uint32_t& clust, uint32_t& sector);
	DirEntry* SearchPath(const char* path);
	DirEntry* SearchDir(DirEntry* entry, const char* dirName);
	DirEntry* OpenDir(const char* path);
	DirEntry* ReadDir(DirEntry* entry);
	void CloseDir(DirEntry* entry);
	void Test();
};

#endif //!__FAT_DIR_H__
