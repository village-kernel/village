//###########################################################################
// FATFile.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"


/// @brief 
/// @param data 
/// @param dir 
int FAT::ReadFile(char* data, uint32_t size, DirEntry* entry)
{
	bool isDone = false;
	uint32_t fileSize = entry->sdir.fileSize;
	uint32_t bytsPerSec = dbr->bpb.bytsPerSec;
	uint32_t secPerClus = dbr->bpb.secPerClus;
	uint32_t secSize = (fileSize + (bytsPerSec - 1)) / bytsPerSec;
	uint32_t clusSize = (secSize + (secPerClus - 1)) / secPerClus;
	uint32_t fstCluster = MergeCluster(entry->sdir.fstClusHI, entry->sdir.fstClusLO);

	char* allocBuff = (char*)new char[clusSize * secPerClus * bytsPerSec]();
	
	if (clusSize == ReadCluster(allocBuff, clusSize, fstCluster))
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
uint32_t FAT::FileSize(DirEntry* entry)
{
	return entry->sdir.fileSize;
}
