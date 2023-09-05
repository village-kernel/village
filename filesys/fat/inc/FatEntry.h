//###########################################################################
// FatEntry.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_ENTRY_H__
#define __FAT_ENTRY_H__

#include "FatObjs.h"


/// @brief 
class FatData : public FatObjs
{
private:
	//Members
	DirEntry* body;
	FATEnt*   ents;

	uint32_t  index;
	uint32_t  clust;
	uint32_t  sector;

	//Methods
	bool IsEmpty();
	void Clone(FatData* data);
	void Clear();
public:
	FatData(FatObjs* objs = NULL, DirEntry* entry = NULL);
	~FatData();

	//Iterator Methods
	void Begin();
	void Next();
	bool IsEnd();
	bool IsValid();
	uint8_t GetSize();
	FATEnt* Item();

	//Methods
	void Setup(FatObjs* objs, DirEntry* entry);
	int FindSpace(uint32_t size);
	uint32_t Pop(FATEnt* pop, uint32_t size = 1);
	uint32_t Push(FATEnt* push, uint32_t size = 1);
};


/// @brief FatEntry
class FatEntry : public FatObjs
{
private:
	FatData* CreateEntry(DirEntry* entry, const char* name, FATEnt*& ents, uint8_t& num);
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
