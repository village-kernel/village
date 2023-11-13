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
class DirEntry : public FatDefs
{
public:
	//Structures
	struct EntryInfo
	{
		uint32_t    clust;
		uint32_t    sector;
		uint32_t    index;
		uint32_t    size;
		UnionEntry* unients;

		EntryInfo()
			:clust(0),
			sector(0),
			index(0),
			size(0),
			unients(NULL)
		{}

		~EntryInfo()
		{
			delete[] unients;
		}
	};

//private:
	//Members
	FatInfo* fatInfo;
	FatDisk* fatDisk;
	FatName  fatName;

	//Data Members
	EntryInfo   self;
	EntryInfo   temp;
	UnionEntry  body;
	char*       name;

	//Disk Methods
	void CalcFirstSector();
	void CalcNextSector();
	void ReadUnionEntries();
	void WriteUnionEntries();

	int CheckDirName(UnionEntry* unient);
public:
	//Methods
	DirEntry(FatDisk* fatDisk, FatInfo* fatInfo);
	~DirEntry();

	//Iterator Methods
	bool ReadBegin();
	bool ReadNext();
	bool WriteNext();
	bool IsEnded();
	UnionEntry& Item();

	//Methods
	int Find(uint32_t size);
	uint32_t Pop(EntryInfo& pop);
	uint32_t Push(EntryInfo& push);
	bool Update();
	bool Remove();

	DirEntry* Create(const char* name, DirAttr attr);
	DirEntry* Read();
};


/// @brief 
class DirEntries
{
public:
	List<DirEntry> list;
	char*          path;

	DirEntries() :
		path(NULL)
	{}

	~DirEntries()
	{
		list.Release();
		delete[] path;
	}
};

#endif //!__FAT_ENTRY_H__
