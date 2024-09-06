//###########################################################################
// FatFolder.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FOLDER_H__
#define __FAT_FOLDER_H__

#include "List.h"
#include "FatObject.h"
#include "FatDiskio.h"


/// @brief FatFolder
class FatFolder
{
private:
	//Members
	FatDiskio&        fatDisk;
	FatDiskio::Info&  fatInfo;

	//Dirent Members
	uint32_t          index;
	uint32_t          clust;
	uint32_t          sector;
	FatEntry*         buffer;
	FatObject*        parent;

	//FatObject Members
	List<FatObject*>  fatObjs;

	//Members
	void CalcFirstSector();
	void CalcNextSector();
	void ReadEntries();
	void WriteEntries();

	bool ReadBegin();
	bool ReadNext();
	bool WriteNext();
	bool IsReadEnd();
	
	bool Find(uint32_t size);
	uint32_t Pop(FatEntry* pop, uint32_t size);
	uint32_t Push(FatEntry* push, uint32_t size);

	bool CheckDirName(FatObject* fatObj);
public:
	//Methods
	FatFolder(FatDiskio& fatDisk, FatObject* fatObj);
	~FatFolder();

	void Open(FatObject* fatObj);
	FatObject* Search(const char* name);
	FatObject* Create(const char* name, int attr);
	uint32_t Write(FatObject* fatObjs, uint32_t size);
	uint32_t Read(FatObject* fatObjs, uint32_t size);
	void Remove(FatObject* fatObjs);
	void Update(FatObject* fatObjs);
	void Close();

	List<FatObject*> GetLists();
};

#endif //!__FAT_FOLDER_H__
