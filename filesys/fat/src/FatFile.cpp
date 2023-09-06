//###########################################################################
// FatFile.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatFile.h"
#include "FatDisk.h"
#include "FatEntry.h"


/// @brief Create file
/// @param path 
/// @return 
FatFile::DirEntry* FatFile::Create(const char* path)
{
	DirEntry* dir = fatData->SearchPath(path, 1);
	
	if (NULL == dir) return NULL;
	
	if (dir->body.IsDirectory())
	{
		return fatData->CreateFile(dir, fatData->NotDir(path));
	}

	return NULL;
}


/// @brief Open
/// @param name 
/// @param mode 
/// @return 
FatFile::DirEntry* FatFile::Open(const char* name, int mode)
{
	DirEntry* dir = fatData->SearchPath(name);

	if (NULL == dir)
	{
		if ((mode & _CreateNew) == _CreateNew)
		{
			return Create(name);
		}
	}

	return dir;
}


/// @brief Write
/// @param data 
/// @param size 
/// @param entry 
/// @return 
int FatFile::Write(char* data, uint32_t size, DirEntry* entry)
{
	bool isDone = false;
	uint32_t fileSize = entry->body.fileSize;
	uint32_t bytesPerSec = dbr->bpb.bytesPerSec;
	uint32_t secPerClust = dbr->bpb.secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstCluster = fatDisk->MergeCluster(entry->body.fstClustHI, entry->body.fstClustLO);

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	memcpy((void*)allocBuff, (const void*)data, size);

	if (clusSize == fatDisk->WriteCluster(allocBuff, clusSize, fstCluster)) isDone = true;

	delete[] allocBuff;
	return isDone ? size : 0;
}


/// @brief Read
/// @param data 
/// @param dir 
/// @return 
int FatFile::Read(char* data, uint32_t size, DirEntry* entry)
{
	bool isDone = false;
	uint32_t fileSize = entry->body.fileSize;
	uint32_t bytesPerSec = dbr->bpb.bytesPerSec;
	uint32_t secPerClust = dbr->bpb.secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstCluster = fatDisk->MergeCluster(entry->body.fstClustHI, entry->body.fstClustLO);

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	if (clusSize == fatDisk->ReadCluster(allocBuff, clusSize, fstCluster))
	{
		memcpy((void*)data, (const void*)allocBuff, size);
		isDone = true;
	}

	delete[] allocBuff;
	return isDone ? size : 0;
}


/// @brief Size
/// @param dir 
/// @return 
int FatFile::Size(DirEntry* entry)
{
	return entry->body.fileSize;
}
