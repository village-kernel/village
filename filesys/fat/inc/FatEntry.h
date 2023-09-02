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
	//Attr Methods
	bool IsHidden(FATEnt* entry);
	bool IsDirectory(FATEnt* entry);
	bool IsVolume(FATEnt* entry);
	bool IsFile(FATEnt* entry);

	//Entry Methods
	int CheckConflict(DirData* data, FATEnt* entry);
	int SearchSpace(DirData* data, uint8_t size);
	int WirteEntires(DirData* data, FATEnt* entries, uint8_t size);
	int SetEntryName(DirData* data, const char* name, int attr = 0);
	char* GetEntryName(DirData* data);
public:
	//Attr Methods
	bool IsHidden(DirEntry* entry);
	bool IsDirectory(DirEntry* entry);
	bool IsVolume(DirEntry* entry);
	bool IsFile(DirEntry* entry);
	char* NotDir(const char* path);

	//Directory Methods
	DirEntry* SearchPath(const char* path, int forward = 0);
	DirEntry* SearchDir(DirEntry* entry, const char* name);
	DirEntry* CreateFile(DirEntry* entry, const char* name);
	DirData* CreateDir(DirEntry* entry, const char* name);
	DirData* OpenDir(DirEntry* entry);

	//Volume Methods
	char* GetVolumeLabel();
	int SetVolumeLabel(const char* name);
};

#endif //!__FAT_ENTRY_H__
