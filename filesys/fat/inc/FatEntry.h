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

	//Members
	DirEntry*   dirent;
	UnionEntry* unients;

	uint32_t  index;
	uint32_t  clust;
	uint32_t  sector;

	//Methods
	bool IsEmpty();
	void Clone(FatEntry* data);
	void Clear();

	//Iterator Methods
	void Begin();
	void Next();
	bool IsEnd();
	UnionEntry* Item();

	int FindSpace(uint32_t size);
	uint32_t Pop(UnionEntry* pop, uint32_t size = 1);
	uint32_t Push(UnionEntry* push, uint32_t size = 1);

	int CheckDirName(UnionEntry* unient);
public:
	FatEntry(FatDisk* fatDisk = NULL, Info* info = NULL, DirEntry* dirent = NULL);
	~FatEntry();

	//Methods
	void Setup(FatDisk* fatDisk, Info* info, DirEntry* dirent);
	DirEntry* Create(const char* name, DirAttr attr);
	DirEntry* Read();
	bool Write(DirEntry* dirent);
};

#endif //!__FAT_ENTRY_H__
