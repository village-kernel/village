//###########################################################################
// FatDisk.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_DISk_H__
#define __FAT_DISk_H__

#include "FatDefs.h"


/// @brief FatDisk
class FatDisk : public FatDefs
{
private:
	//Data Members
	Info*    info;

	//Driver Members
	Driver*  diskdrv;
	uint32_t fstSec;
public:
	//Method
	void Setup(Driver* diskdrv, uint32_t fstSec, Info* info);

	//Cluster and sector Methods
	uint32_t GetFirstClust(ShortEntry sfe);
	uint32_t ClusterToSector(uint32_t clust);
	
	uint32_t GetNextCluster(uint32_t clust);
	uint32_t SetNextCluster(uint32_t clust);

	uint32_t GetPrevCluster(uint32_t clust);
	uint32_t ClearPrevCluster(uint32_t clust);
	
	void CalcFirstSector(DirEntry* dirent);
	void CalcNextSector(DirEntry* dirent);
	void CalcPrevSector(DirEntry* dirent);
	void ReadUnionEntries(DirEntry* dirent);
	void WriteUnionEntries(DirEntry* dirent);

	//Disk IO Methods
	uint32_t ReadOneSector(char* data, uint32_t sector);
	uint32_t ReadSector(char* data, uint32_t secSize, uint32_t sector);
	uint32_t ReadCluster(char* data, uint32_t clustSize, uint32_t clust);

	uint32_t WriteOneSector(char* data, uint32_t sector);
	uint32_t WriteSector(char* data, uint32_t secSize, uint32_t sector);
	uint32_t WriteCluster(char* data, uint32_t clustSize, uint32_t clust);
	uint32_t ClearCluster(uint32_t clust, uint32_t clustSize);

	uint32_t AllocCluster(uint32_t clustSize = 1);
	uint32_t FreeCluster(uint32_t clustSize = 1, uint32_t clust = 0);
};

#endif //!__FAT_DISK_H__
