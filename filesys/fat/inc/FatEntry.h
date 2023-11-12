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
#include "FatName.h"


/// @brief 
class FatEntry : public FatDefs
{
private:
	//Data Members
	Info*    info;
	FatDisk* fatDisk;
	FatName  fatName;

	//Iterator Methods
	bool ReadBegin(DirEntry* dirent);
	bool ReadNext(DirEntry* dirent);
	bool WriteNext(DirEntry* dirent);
	bool IsEnded(DirEntry* dirent);
	UnionEntry& Item(DirEntry* dirent);

	int Find(DirEntry* dirent, uint32_t size);
	uint32_t Pop(DirEntry* dirent, EntryInfo& pop);
	uint32_t Push(DirEntry* dirent, EntryInfo& push);

	int CheckDirName(DirEntry* dirent, UnionEntry* unient);
public:
	FatEntry();
	~FatEntry();

	//Methods
	void Setup(FatDisk* fatDisk, Info* info);
	DirEntry* Create(DirEntry* dirent, const char* name, DirAttr attr);
	DirEntry* Read(DirEntry* dirent);
	bool Update(DirEntry* dirent);
};

#endif //!__FAT_ENTRY_H__
