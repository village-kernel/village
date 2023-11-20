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
	//Static constants
	static const uint8_t entry_size = 32;
	static const uint8_t long_name_size = 13;
	static const uint8_t dir_seq_flag = 0x40;

	//Members
	FatDiskio&       disk;
	FatDiskio::Info& info;

	//Data Members
	FatObject*       self;
	FatObject*       temp;

	//Disk Methods
	void CalcFirstSector();
	void CalcNextSector();
	void ReadUnionEntries();
	void WriteUnionEntries();
	
	//Iterator Methods
	bool ReadBegin();
	bool ReadNext();
	bool WriteNext();
	bool IsEnded();
	FatObject::UnionEntry& Item();

	int Find(uint32_t size);
	uint32_t Pop(FatObject* pop);
	uint32_t Push(FatObject* push);

	//Methods
	int CheckDirName(FatObject* obj);
public:
	//Methods
	FatEntry(FatDiskio& disk, FatObject* object);
	~FatEntry();

	FatObject* Create(const char* name, int attr);
	FatObject* Read();
	uint32_t Size();

	bool Update();
	bool Remove();
};

#endif //!__FAT_ENTRY_H__
