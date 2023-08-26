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
public:
	//Attr Methods
	bool IsHidden(DirEntry* entry);
	bool IsDirectory(DirEntry* entry);
	bool IsVolume(DirEntry* entry);
	bool IsFile(DirEntry* entry);

	//Directory Methods
	DirEntry* SearchPath(const char* path);
	DirEntry* SearchDir(DirEntry* entry, const char* dir);
	DirData* OpenDir(DirEntry* entry);

	//Volume Methods
	char* GetVolumeLabel();
	int SetVolumeLabel(const char* name);
};

#endif //!__FAT_ENTRY_H__
