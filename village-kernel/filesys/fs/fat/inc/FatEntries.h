//###########################################################################
// FatEntries.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_ENTRIES_H__
#define __FAT_ENTRIES_H__

#include "List.h"
#include "FatObject.h"
#include "FatDiskio.h"


/// @brief FatEntries
class FatEntries
{
private:
	//Members
	FatDiskio&        fatDisk;
	FatDiskio::Info&  volInfo;

	//Dirent Members
	uint32_t          index;
	uint32_t          clust;
	uint32_t          sector;
	FatEntry*         fatEnts;
	FatObject*        self;

	//Fatent Members
	uint32_t          objIdx;
	List<FatObject*>  objects;

	//Members
	void Prepare();
	void Release();
	void CalcFirstSector();
	void CalcNextSector();
	void ReadFatEnts();
	void WriteFatEnts();

	bool ReadBegin();
	bool ReadNext();
	bool WriteNext();
	bool IsReadEnd();
	
	bool Find(uint32_t size);
	uint32_t Pop(FatEntry* pop, uint32_t size);
	uint32_t Push(FatEntry* push, uint32_t size);

	bool CheckDirName(FatObject* object);
public:
	//Methods
	FatEntries(FatDiskio& fatDisk, FatObject* object = NULL);
	~FatEntries();

	void Begin();
	void Next();
	bool IsEnd();
	FatObject* Item();
	uint32_t GetSize();

	FatObject* Create(const char* name, int attr);
	uint32_t Write(FatObject* objects, uint32_t size);
	uint32_t Read(FatObject* objects, uint32_t size);
	void Remove();
	void Update();
};

#endif //!__FAT_ENTRIES_H__
