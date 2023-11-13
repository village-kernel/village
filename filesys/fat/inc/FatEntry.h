//###########################################################################
// FatEntry.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_ENTRY_H__
#define __FAT_ENTRY_H__

#include "FatDefs.h"
#include "FatDisk.h"

/// @brief 
class FatEntry : public FatDefs
{
private:
	//Data Members
	FatInfo* fatInfo;
	FatDisk* fatDisk;

	//Disk Methods
	void CalcFirstSector(DirEntry* dirent);
	void CalcNextSector(DirEntry* dirent);
	void ReadUnionEntries(DirEntry* dirent);
	void WriteUnionEntries(DirEntry* dirent);
public:
	//Methods
	FatEntry();
	~FatEntry();
	void Setup(FatDisk* fatDisk, FatInfo* fatInfo);

	//Iterator Methods
	bool ReadBegin(DirEntry* dirent);
	bool ReadNext(DirEntry* dirent);
	bool WriteNext(DirEntry* dirent);
	bool IsEnded(DirEntry* dirent);
	UnionEntry& Item(DirEntry* dirent);

	//Methods
	int Find(DirEntry* dirent, uint32_t size);
	uint32_t Pop(DirEntry* dirent, EntryInfo& pop);
	uint32_t Push(DirEntry* dirent, EntryInfo& push);
};

#endif //!__FAT_ENTRY_H__
