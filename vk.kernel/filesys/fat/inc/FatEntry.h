//###########################################################################
// FatEntry.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_ENTRY_H__
#define __FAT_ENTRY_H__

#include "Templates.h"
#include "FatObject.h"
#include "FatDiskio.h"

/// @brief FatEntry
class FatEntry
{
private:
	//Members
	FatDiskio&       disk;
	FatDiskio::Info& info;

	//Dirent Members
	uint32_t          index;
	uint32_t          clust;
	uint32_t          sector;
	FatUnionEntry*    unients;
	FatObject*        self;

	//Fatent Members
	uint32_t          objIdx;
	List<FatObject*>  objects;

	//Members
	void Prepare();
	void CalcFirstSector();
	void CalcNextSector();
	void ReadUnionEntries();
	void WriteUnionEntries();
	bool ReadBegin();
	bool ReadNext();
	bool WriteNext();
	bool IsReadEnd();
	bool Find(uint32_t size);
	uint32_t Pop(FatUnionEntry* pop, uint32_t size);
	uint32_t Push(FatUnionEntry* push, uint32_t size);
	bool CheckDirName(FatObject* object);
public:
	//Methods
	FatEntry(FatDiskio& disk, FatObject* object = NULL);
	~FatEntry();

	void Begin();
	void Next();
	bool IsEnd();
	FatObject* Item();
	uint32_t GetSize();

	FatObject* Create(const char* name, int attr);
	uint32_t Write(FatObject* objs, uint32_t size);
	uint32_t Read(FatObject* objs, uint32_t size);
	void Remove();
	void Update();
};

#endif //!__FAT_ENTRY_H__
