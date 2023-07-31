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
int FAT::ReadFile(char* data, uint32_t size, FATSDir* dir)
{
	uint32_t cluster = MergeCluster(dir->fstClusHI, dir->fstClusLO);
	uint32_t secNum  = ClusterToSector(cluster);
	uint16_t secSize = (dir->fileSize + (dbr->bpb.bytsPerSec - 1)) / dbr->bpb.bytsPerSec;
	
	char* file = (char*)new char[secSize * dbr->bpb.bytsPerSec]();

	ReadSector(file, secSize, secNum);
	memcpy((void*)data, (const void*)file, size);

	delete[] file;

	return size;
}


/// @brief 
/// @param dir 
/// @return 
uint32_t FAT::FileSize(FATSDir* dir)
{
	return dir->fileSize;
}
