//###########################################################################
// FATDisk.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatDisk.h"
#include "Kernel.h"
#include "Debug.h"


/// @brief Meger cluster
/// @param clustHI 
/// @param clustLO 
/// @return cluster
uint32_t FatDisk::MergeCluster(uint16_t clustHI, uint16_t clustLO)
{
	return (uint32_t)clustHI << 16 | clustLO;
}


/// @brief Cluster to sector number
/// @param clust 
/// @return sector number
uint32_t FatDisk::ClusterToSector(uint32_t clust)
{
	return ((clust - 2) * dbr->bpb.secPerClust) + info->firstDataSector;
}


/// @brief Calculate the next cluster
/// @param clust 
/// @return next cluster
uint32_t FatDisk::CalcNextCluster(uint32_t clust)
{
	bool isEOC = false;
	uint32_t fatOffset = 0;
	uint32_t fatClust = 0;

	if (_FAT16 == info->fatType)
		fatOffset = clust * 2;
	else if (_FAT32 == info->fatType)
		fatOffset = clust * 4;

	uint32_t thisFatSecNum = dbr->bpb.rsvdSecCnt + (fatOffset / dbr->bpb.bytesPerSec);
	uint32_t thisFatEntOffset = fatOffset % dbr->bpb.bytesPerSec;

	char* secBuff = new char[dbr->bpb.bytesPerSec]();
	
	ReadOneSector(secBuff, thisFatSecNum);

	if (_FAT16 == info->fatType)
	{
		fatClust = *((uint16_t*)&secBuff[thisFatEntOffset]);
		if (fatClust >= fat16_eoc_flag) isEOC = true;
	}
	else if (_FAT32 == info->fatType)
	{
		fatClust = (*((uint32_t*)&secBuff[thisFatEntOffset])) & 0x0fffffff;
		if (fatClust >= fat32_eoc_flag) isEOC = true;
	}
	
	delete[] secBuff;

	return isEOC ? 0 : fatClust;
}


/// @brief Calc first sector
/// @param clust 
/// @param sector 
void FatDisk::CalcFirstSector(DirEntry* entry, uint32_t& clust, uint32_t& sector)
{
	if (NULL == entry || entry->root)
	{
		if (_FAT16 == info->fatType)
		{
			clust  = 0;
			sector = info->firstRootSector;
		}
		else if (_FAT32 == info->fatType)
		{
			clust  = info->rootClust;
			sector = ClusterToSector(clust);
		}
	}
	else
	{
		clust  = MergeCluster(entry->dir.sdir.fstClustHI, entry->dir.sdir.fstClustLO);
		sector = ClusterToSector(clust);
	}
}


/// @brief Calc next sector
/// @param clust 
/// @param sector 
void FatDisk::CalcNextSector(uint32_t& clust, uint32_t& sector)
{
	//FAT16 root dir
	if (clust < 2)
	{
		uint32_t dirEndedSec = info->firstRootSector + info->countOfRootSecs;
		sector = (++sector < dirEndedSec) ? sector : 0;
	}
	//FatDisk data dir
	else
	{ 
		if ((++sector - ClusterToSector(clust)) >= dbr->bpb.secPerClust)
		{
			clust = CalcNextCluster(clust);
			sector = (0 != clust) ? ClusterToSector(clust) : 0;
		}
	}
}


/// @brief Read one sector
/// @param data 
/// @param secSize 
/// @param sector 
/// @return 
uint32_t FatDisk::ReadOneSector(char* data, uint32_t sector)
{
	if (NULL != diskdrv)
	{
		diskdrv->Read((uint8_t*)data, 1, sector + info->startSector);
	}
	return 1;
}


/// @brief Read Sector
/// @param data 
/// @param secSize 
/// @param sector 
/// @return read sector size
uint32_t FatDisk::ReadSector(char* data, uint32_t secSize, uint32_t sector)
{
	if (NULL != diskdrv)
	{
		diskdrv->Read((uint8_t*)data, secSize, sector + info->startSector);
	}
	return secSize;
}


/// @brief Read cluster
/// @param data 
/// @param clusSize 
/// @param clust 
/// @return read cluster size
uint32_t FatDisk::ReadCluster(char* data, uint32_t clustSize, uint32_t clust)
{
	uint32_t bytesPerSec = dbr->bpb.bytesPerSec;
	uint32_t secPerClust = dbr->bpb.secPerClust;

	for (uint32_t i = 0; i < clustSize; i++)
	{
		uint32_t sector = ClusterToSector(clust);
		uint32_t offset = i * bytesPerSec * secPerClust;

		if (secPerClust != ReadSector(data + offset, secPerClust, sector))
		{
			return i + 1;
		}

		if (clustSize > 1)
		{
			clust = CalcNextCluster(clust);
			if (0 == clust) return i + 1;
		}
	}

	return clustSize;
}
