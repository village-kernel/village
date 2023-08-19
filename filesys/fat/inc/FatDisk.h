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
class FatDisk : public FatDat
{
public:
	//Cluster and sector Methods
	uint32_t MergeCluster(uint16_t clustHI, uint16_t clustLO);
	uint32_t ClusterToSector(uint32_t clust);
	uint32_t CalcNextCluster(uint32_t clust);
	void CalcFirstSector(DirEntry* entry, uint32_t& clust, uint32_t& sector);
	void CalcNextSector(uint32_t& clust, uint32_t& sector);

	//Disk IO Methods
	uint32_t ReadOneSector(char* data, uint32_t sector);
	uint32_t ReadSector(char* data, uint32_t secSize, uint32_t sector);
	uint32_t ReadCluster(char* data, uint32_t clustSize, uint32_t clust);
};

#endif //!__FAT_DISK_H__
