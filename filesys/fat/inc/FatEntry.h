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
	DirEntry* body;
	FATEnt*   ents;

	uint32_t  index;
	uint32_t  clust;
	uint32_t  sector;

	//Methods
	bool IsEmpty();
	void Clone(FatEntry* data);
	void Clear();
public:
	FatEntry(FatDisk* fatDisk = NULL, Info* info = NULL, DirEntry* entry = NULL);
	~FatEntry();

	//Iterator Methods
	void Begin();
	void Next();
	bool IsEnd();

	//Item Methods
	FATEnt* Item();
	char* GetName();

	//Methods
	void Setup(FatDisk* fatDisk, Info* info, DirEntry* entry);
	int FindSpace(uint32_t size);
	uint32_t Pop(FATEnt* pop, uint32_t size = 1);
	uint32_t Push(FATEnt* push, uint32_t size = 1);
};

#endif //!__FAT_ENTRY_H__
