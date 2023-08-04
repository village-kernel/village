//###########################################################################
// FATDisk.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"


/// @brief Meger cluster
/// @param clusHI 
/// @param clusLO 
/// @return cluster
uint32_t FAT::MergeCluster(uint16_t clusHI, uint16_t clusLO)
{
	return (uint32_t)clusHI << 16 | clusLO;
}


/// @brief Cluster to sector number
/// @param clus 
/// @return sector number
uint32_t FAT::ClusterToSector(uint32_t clus)
{
	return ((clus - 2) * dbr->bpb.secPerClus) + fat->firstDataSector;
}


/// @brief Calc next sector
/// @param clus 
/// @param sector 
void FAT::CalcNextSector(uint32_t& clus, uint32_t& sector)
{
	//FAT16 root dir
	if (clus < 2)
	{
		uint32_t dirEndedSec = fat->firstRootDirSecNum + fat->rootDirSectors;
		sector = (++sector < dirEndedSec) ? sector : 0;
	}
	//FAT data dir
	else
	{ 
		if ((sector - ClusterToSector(clus)) >= dbr->bpb.secPerClus)
		{
			clus = CalcNextCluster(clus);
			sector = (0 != clus) ? ClusterToSector(clus) : 0;
		}
		else sector++;
	}
}


/// @brief Calculate the next cluster
/// @param clus 
/// @return next cluster
uint32_t FAT::CalcNextCluster(uint32_t clus)
{
	bool isEOC = false;
	uint32_t fatOffset = 0;
	uint32_t fatClusEntry = 0;

	if (_FAT16 == fat->type)
		fatOffset = clus * 2;
	else if (_FAT32 == fat->type)
		fatOffset = clus * 4;

	uint32_t thisFATSecNum = dbr->bpb.rsvdSecCnt + (fatOffset / dbr->bpb.bytsPerSec);
	uint32_t thisFATEntOffset = fatOffset % dbr->bpb.bytsPerSec;

	char* secBuff = new char[dbr->bpb.bytsPerSec]();
	
	ReadSector(secBuff, 1, thisFATSecNum);

	if (_FAT16 == fat->type)
	{
		fatClusEntry = *((uint16_t*)&secBuff[thisFATEntOffset]);
		if (fatClusEntry >= fat16_eoc_flag) isEOC = true;
	}
	else if (_FAT32 == fat->type)
	{
		fatClusEntry = (*((uint32_t*)&secBuff[thisFATEntOffset])) & 0x0fffffff;
		if (fatClusEntry >= fat32_eoc_flag) isEOC = true;
	}
	
	delete[] secBuff;

	return isEOC ? 0 : fatClusEntry;
}


/// @brief Read Sector
/// @param data 
/// @param secSize 
/// @param sector 
/// @return read sector size
uint32_t FAT::ReadSector(char* data, uint32_t secSize, uint32_t sector)
{
	if (NULL != disk)
	{
		disk->Read((uint8_t*)data, secSize, sector + startSector);
	}
	return secSize;
}


/// @brief Read cluster
/// @param data 
/// @param clusSize 
/// @param clus 
/// @return read cluster size
uint32_t FAT::ReadCluster(char* data, uint32_t clusSize, uint32_t clus)
{
	uint32_t bytsPerSec = dbr->bpb.bytsPerSec;
	uint32_t secPerClus = dbr->bpb.secPerClus;

	for (uint32_t i = 0; i < clusSize; i++)
	{
		uint32_t secNum = ClusterToSector(clus);
		uint32_t offset = i * bytsPerSec * secPerClus;

		if (secPerClus != ReadSector(data + offset, secPerClus, secNum))
		{
			return i + 1;
		}

		if (clusSize > 1)
		{
			clus = CalcNextCluster(clus);
			if (0 == clus) return i + 1;
		}
	}

	return clusSize;
}
