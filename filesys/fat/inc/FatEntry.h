//###########################################################################
// FatEntry.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_ENTRY_H__
#define __FAT_ENTRY_H__

#include "FatObjs.h"


/// @brief FatEntry
class FatEntry : public FatObjs
{
private:
	//Entry Methods
	int SearchSpace(DirData* data, uint8_t size);
	int WirteEntires(DirData* data, FATEnt* entries, uint8_t size);
	int SetEntryName(DirData* data, DirEntries* entries, const char* name, int attr = 0);
	char* GetEntryName(DirData* data);
public:
	//Directory Methods
	char* NotDir(const char* path);
	DirEntry* SearchPath(const char* path, int forward = 0);
	DirEntry* SearchDir(DirEntry* entry, const char* name);
	DirEntry* CreateFile(DirEntry* entry, const char* name);
	DirEntries* CreateDir(DirEntry* entry, const char* name);
	DirEntries* OpenDir(DirEntry* entry);

	//Volume Methods
	char* GetVolumeLabel();
	int SetVolumeLabel(const char* name);
};

#endif //!__FAT_ENTRY_H__
