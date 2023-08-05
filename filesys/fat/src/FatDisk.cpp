//###########################################################################
// FATDisk.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatDisk.h"
#include "Kernel.h"
#include "Debug.h"


/// @brief 
/// @param fstSecNum 
void FatDisk::Initialize(FATData* fat, FATDBR* dbr, uint32_t fstSecNum)
{
	this->fat = fat;
	this->dbr = dbr;
	this->startSector = fstSecNum;

	disk = device.GetDriver(DriverID::_storage + 1);
	
	if (NULL == disk)
	{
		debug.Error("Not disk driver found");
		return;
	}
}


/// @brief Meger cluster
/// @param clusHI 
/// @param clusLO 
/// @return cluster
uint32_t FatDisk::MergeCluster(uint16_t clusHI, uint16_t clusLO)
{
	return (uint32_t)clusHI << 16 | clusLO;
}


/// @brief Cluster to sector number
/// @param clust 
/// @return sector number
uint32_t FatDisk::ClusterToSector(uint32_t clust)
{
	return ((clust - 2) * dbr->bpb.secPerClus) + fat->firstDataSector;
}


/// @brief Calculate the next cluster
/// @param clust 
/// @return next cluster
uint32_t FatDisk::CalcNextCluster(uint32_t clust)
{
	bool isEOC = false;
	uint32_t fatOffset = 0;
	uint32_t fatClusEntry = 0;

	if (_FAT16 == fat->type)
		fatOffset = clust * 2;
	else if (_FAT32 == fat->type)
		fatOffset = clust * 4;

	uint32_t thisFATSecNum = dbr->bpb.rsvdSecCnt + (fatOffset / dbr->bpb.bytsPerSec);
	uint32_t thisFATEntOffset = fatOffset % dbr->bpb.bytsPerSec;

	char* secBuff = new char[dbr->bpb.bytsPerSec]();
	
	ReadOneSector(secBuff, thisFATSecNum);

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


/// @brief Calc first sector
/// @param clust 
/// @param sector 
void FatDisk::CalcFirstSector(DirEntry* entry, uint32_t& clust, uint32_t& sector)
{
	if (NULL == entry)
	{
		if (_FAT16 == fat->type)
		{
			clust   = 0;
			sector = fat->firstRootDirSecNum;
		}
		else if (_FAT32 == fat->type)
		{
			clust   = fat->rootClus;
			sector = ClusterToSector(clust);
		}
	}
	else
	{
		clust   = MergeCluster(entry->sdir.fstClusHI, entry->sdir.fstClusLO);
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
		uint32_t dirEndedSec = fat->firstRootDirSecNum + fat->rootDirSectors;
		sector = (++sector < dirEndedSec) ? sector : 0;
	}
	//FatDisk data dir
	else
	{ 
		if ((++sector - ClusterToSector(clust)) >= dbr->bpb.secPerClus)
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
	if (NULL != disk)
	{
		disk->Read((uint8_t*)data, 1, sector + startSector);
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
	if (NULL != disk)
	{
		disk->Read((uint8_t*)data, secSize, sector + startSector);
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
	uint32_t bytsPerSec = dbr->bpb.bytsPerSec;
	uint32_t secPerClus = dbr->bpb.secPerClus;

	for (uint32_t i = 0; i < clustSize; i++)
	{
		uint32_t secNum = ClusterToSector(clust);
		uint32_t offset = i * bytsPerSec * secPerClus;

		if (secPerClus != ReadSector(data + offset, secPerClus, secNum))
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
