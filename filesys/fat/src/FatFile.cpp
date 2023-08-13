//###########################################################################
// FatFile.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatFile.h"


/// @brief 
/// @param fat 
/// @param dbr 
/// @param startSector 
void FatFile::Initialize(FATData* fat, FATDBR* dbr, uint32_t startSector)
{
	this->dbr = dbr;
	this->fat = fat;
	disk.Initialize(fat, dbr, startSector);
}


/// @brief 
/// @param data 
/// @param dir 
int FatFile::Read(char* data, uint32_t size, DirEntry* entry)
{
	bool isDone = false;
	uint32_t fileSize = entry->dir.sdir.fileSize;
	uint32_t bytesPerSec = dbr->bpb.bytesPerSec;
	uint32_t secPerClust = dbr->bpb.secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstCluster = disk.MergeCluster(entry->dir.sdir.fstClustHI, entry->dir.sdir.fstClustLO);

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	if (clusSize == disk.ReadCluster(allocBuff, clusSize, fstCluster))
	{
		memcpy((void*)data, (const void*)allocBuff, size);
		isDone = true;
	}

	delete[] allocBuff;
	return isDone ? size : 0;
}


/// @brief 
/// @param dir 
/// @return 
uint32_t FatFile::Size(DirEntry* entry)
{
	return entry->dir.sdir.fileSize;
}
