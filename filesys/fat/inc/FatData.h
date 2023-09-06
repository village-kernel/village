//###########################################################################
// FatData.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_DATA_H__
#define __FAT_DATA_H__

#include "FatObjs.h"
#include "FatEntry.h"
#include "FatName.h"


/// @brief FatData
class FatData : public FatObjs
{
private:
	//Members
	FatName fatName;

	//Directory Methods
	char* NotDir(const char* path);
	DirEntry* SearchPath(const char* path, int forward = 0);
	DirEntry* SearchDir(DirEntry* entry, const char* name);
	DirEntries* OpenDir(DirEntry* entry);
	FatEntry* CreateEntry(DirEntry* entry, const char* name, FATEnt*& ents, uint8_t& num);
	DirEntry* CreateFile(DirEntry* entry, const char* name);
	DirEntries* CreateDir(DirEntry* entry, const char* name);
	DirEntry* CreateFile(const char* path);
	DirEntries* CreateDir(const char* path);
public:
	//File Methods
	DirEntry* Open(const char* name, int mode);
	int Write(char* data, uint32_t size, DirEntry* entry);
	int Read(char* data, uint32_t size, DirEntry* entry);
	int Size(DirEntry* entry);

	//Directory Methods
	DirEntries* OpenDir(const char* path, int mode);
	DirEntry* ReadDir(DirEntries* data);
	int SizeDir(DirEntries* data);

	//Volume Methods
	char* GetVolumeLabel();
	int SetVolumeLabel(const char* name);
};

#endif //!__FAT_DATA_H__
