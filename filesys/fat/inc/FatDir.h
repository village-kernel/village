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
#include "FatName.h"


/// @brief 
class FatDir : FatDefs
{
private:
	//Members
	FatDisk  disk;
	FatName  fatName;
	List<DirEntry> dirs;
public:
	//Methods
	void Initialize(FATData* fat, FATDBR* dbr, uint32_t startSector);

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
