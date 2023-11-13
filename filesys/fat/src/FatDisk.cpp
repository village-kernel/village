//###########################################################################
// FATDisk.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatDisk.h"
#include "Kernel.h"
#include "Debug.h"


/// @brief Setup
/// @param diskdrv 
/// @param fstSec 
/// @param fatInfo 
void FatDisk::Setup(Driver* diskdrv, uint32_t fstSec, FatInfo* fatInfo)
{
	this->diskdrv = diskdrv;
	this->fstSec  = fstSec;
	this->fatInfo = fatInfo; 
}



/// @brief Get first clust
/// @param sfe 
/// @return clust
uint32_t FatDisk::GetFirstClust(ShortEntry sfe)
{
	return (uint32_t)(sfe.fstClustHI << 16) | sfe.fstClustLO;
}


/// @brief Cluster to sector number
/// @param clust 
/// @return sector number
uint32_t FatDisk::ClusterToSector(uint32_t clust)
{
	return ((clust - 2) * fatInfo->secPerClust) + fatInfo->firstDataSector;
}


/// @brief Get the next cluster
/// @param clust 
/// @return next cluster
uint32_t FatDisk::GetNextCluster(uint32_t clust)
{
	bool isEOC = false;
	uint32_t fatOffset = 0;
	uint32_t fatMaxOffset = 0;
	uint32_t fatClust = 0;

	if (_FAT16 == fatInfo->fatType)
	{
		fatOffset = clust * 2;
		fatMaxOffset = fatInfo->bytesPerSec / 2;
	}	
	else if (_FAT32 == fatInfo->fatType)
	{
		fatOffset = clust * 4;
		fatMaxOffset = fatInfo->bytesPerSec / 4;
	}

	uint32_t thisFatSecNum = fatInfo->rsvdSecCnt + (fatOffset / fatInfo->bytesPerSec);
	uint32_t thisFatEntOffset = clust % fatMaxOffset;

	char* secBuff = new char[fatInfo->bytesPerSec]();
	
	ReadOneSector(secBuff, thisFatSecNum);

	if (_FAT16 == fatInfo->fatType)
	{
		fatClust = ((uint16_t*)secBuff)[thisFatEntOffset];
		if (fatClust >= fat16_eoc_flag) isEOC = true;
	}
	else if (_FAT32 == fatInfo->fatType)
	{
		fatClust = ((uint32_t*)secBuff)[thisFatEntOffset] & 0x0fffffff;
		if (fatClust >= fat32_eoc_flag) isEOC = true;
	}
	
	delete[] secBuff;

	return isEOC ? 0 : fatClust;
}


/// @brief Set the next cluster
/// @param clust 
/// @return next cluster
uint32_t FatDisk::SetNextCluster(uint32_t clust)
{
	uint32_t fatOffset = 0;
	uint32_t fatMaxOffset = 0;
	uint32_t fatClust = (clust < 2) ? 2 : clust;
	bool isAllocMode = (clust < 2) ? true : false;

	if (_FAT16 == fatInfo->fatType)
	{
		fatOffset = fatClust * 2;
		fatMaxOffset = fatInfo->bytesPerSec / 2;
	}	
	else if (_FAT32 == fatInfo->fatType)
	{
		fatOffset = fatClust * 4;
		fatMaxOffset = fatInfo->bytesPerSec / 4;
	}

	uint32_t thisFatSecNum = fatInfo->rsvdSecCnt + (fatOffset / fatInfo->bytesPerSec);
	uint32_t thisFatEntOffset = fatClust % fatMaxOffset;
	uint32_t nextFatSecNum = thisFatSecNum;
	uint32_t nextFatEntOffset = thisFatEntOffset;

	char* secBuff = new char[fatInfo->bytesPerSec]();

	//Read sector buff
	ReadOneSector(secBuff, thisFatSecNum);

	//Search next fat clust
	do
	{
		if (++nextFatEntOffset >= fatMaxOffset)
		{
			nextFatEntOffset = 0;

			if (nextFatSecNum <= fatInfo->endedOfFatSector)
			{
				ReadOneSector(secBuff, nextFatSecNum++);
			}
			else
			{
				delete[] secBuff;
				return 0;
			}
		}
		
		if (_FAT16 == fatInfo->fatType)
			clust = ((uint16_t*)secBuff)[nextFatEntOffset];
		else if (_FAT32 == fatInfo->fatType)
			clust = ((uint32_t*)secBuff)[nextFatEntOffset] & 0x0fffffff;

		fatClust++;
	}
	while (0 != clust);

	//Set fat clust list table
	if (_FAT16 == fatInfo->fatType)
	{
		if (nextFatSecNum == thisFatSecNum)
		{
			if (false == isAllocMode)
			{
				((uint16_t*)secBuff)[thisFatEntOffset] = fatClust;
			}
			
			((uint16_t*)secBuff)[nextFatEntOffset] = fat16_eoc_flag;
			WriteOneSector(secBuff, nextFatSecNum);
		}
		else
		{
			((uint16_t*)secBuff)[nextFatEntOffset] = fat16_eoc_flag;
			WriteOneSector(secBuff, nextFatSecNum);

			if (false == isAllocMode)
			{
				ReadOneSector(secBuff, thisFatSecNum);
				((uint16_t*)secBuff)[thisFatEntOffset] = fatClust;
				WriteOneSector(secBuff, thisFatSecNum);
			}
		}
	}
	else if (_FAT32 == fatInfo->fatType)
	{
		if (nextFatSecNum == thisFatSecNum)
		{
			if (false == isAllocMode)
			{
				((uint32_t*)secBuff)[thisFatEntOffset] &= 0xf0000000;
				((uint32_t*)secBuff)[thisFatEntOffset] |= fatClust;
			}

			((uint32_t*)secBuff)[nextFatEntOffset] &= 0xf0000000;
			((uint32_t*)secBuff)[nextFatEntOffset] |= fat32_eoc_flag;
			WriteOneSector(secBuff, nextFatSecNum);
		}
		else
		{
			((uint32_t*)secBuff)[nextFatEntOffset] &= 0xf0000000;
			((uint32_t*)secBuff)[nextFatEntOffset] |= fat32_eoc_flag;
			WriteOneSector(secBuff, nextFatSecNum);
			
			if (false == isAllocMode)
			{
				ReadOneSector(secBuff, thisFatSecNum);
				((uint32_t*)secBuff)[thisFatEntOffset] &= 0xf0000000;
				((uint32_t*)secBuff)[thisFatEntOffset] |= fatClust;
				WriteOneSector(secBuff, thisFatSecNum);
			}
		}
	}

	delete[] secBuff;

	return fatClust;
}


/// @brief Clear prev cluster
/// @param clust 
/// @return 
uint32_t FatDisk::ClearPrevCluster(uint32_t clust)
{
	uint32_t fatOffset = 0;
	uint32_t fatMaxOffset = 0;
	uint32_t fatClust = clust;

	if (_FAT16 == fatInfo->fatType)
	{
		fatOffset = clust * 2;
		fatMaxOffset = fatInfo->bytesPerSec / 2;
	}	
	else if (_FAT32 == fatInfo->fatType)
	{
		fatOffset = clust * 4;
		fatMaxOffset = fatInfo->bytesPerSec / 4;
	}

	uint32_t thisFatSecNum = fatInfo->rsvdSecCnt + (fatOffset / fatInfo->bytesPerSec);
	uint32_t thisFatEntOffset = clust % fatMaxOffset;
	uint32_t prevFatSecNum = thisFatSecNum;
	uint32_t prevFatEntOffset = thisFatEntOffset;

	char* secBuff = new char[fatInfo->bytesPerSec]();

	//Read sector buff
	ReadOneSector(secBuff, thisFatSecNum);

	//Search prev fat clust
	do
	{
		if (--prevFatEntOffset <= 0)
		{
			prevFatEntOffset = fatMaxOffset;

			if (prevFatSecNum >= fatInfo->startOfFatSector)
			{
				ReadOneSector(secBuff, prevFatSecNum--);
			}
			else
			{
				delete[] secBuff;
				return 0;
			}
		}
		
		if (_FAT16 == fatInfo->fatType)
			fatClust = ((uint16_t*)secBuff)[prevFatEntOffset];
		else if (_FAT32 == fatInfo->fatType)
			fatClust = (((uint32_t*)secBuff)[prevFatEntOffset]) & 0x0fffffff;
	}
	while (fatClust != clust);

	//Set fat clust list table
	if (_FAT16 == fatInfo->fatType)
	{
		if (prevFatSecNum == thisFatSecNum)
		{
			((uint16_t*)secBuff)[thisFatEntOffset] = 0;
			((uint16_t*)secBuff)[prevFatEntOffset] = fat16_eoc_flag;
			WriteOneSector(secBuff, prevFatSecNum);
		}
		else
		{
			((uint16_t*)secBuff)[prevFatEntOffset] = fat16_eoc_flag;
			WriteOneSector(secBuff, prevFatSecNum);

			ReadOneSector(secBuff, thisFatSecNum);
			((uint16_t*)secBuff)[thisFatEntOffset] = 0;
			WriteOneSector(secBuff, thisFatSecNum);
		}
	}
	else if (_FAT32 == fatInfo->fatType)
	{
		if (prevFatSecNum == thisFatSecNum)
		{
			((uint32_t*)secBuff)[thisFatEntOffset] &= 0xf0000000;
			((uint32_t*)secBuff)[thisFatEntOffset] |= 0;

			((uint32_t*)secBuff)[prevFatEntOffset] &= 0xf0000000;
			((uint32_t*)secBuff)[prevFatEntOffset] |= fat32_eoc_flag;
			WriteOneSector(secBuff, prevFatSecNum);
		}
		else
		{
			((uint32_t*)secBuff)[prevFatEntOffset] &= 0xf0000000;
			((uint32_t*)secBuff)[prevFatEntOffset] |= fat32_eoc_flag;
			WriteOneSector(secBuff, prevFatSecNum);
			
			ReadOneSector(secBuff, thisFatSecNum);
			((uint32_t*)secBuff)[thisFatEntOffset] &= 0xf0000000;
			((uint32_t*)secBuff)[thisFatEntOffset] |= 0;
			WriteOneSector(secBuff, thisFatSecNum);
		}
	}

	delete[] secBuff;

	return fatClust;
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
		diskdrv->Read((uint8_t*)data, 1, sector + fstSec);
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
		diskdrv->Read((uint8_t*)data, secSize, sector + fstSec);
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
	uint32_t bytesPerSec = fatInfo->bytesPerSec;
	uint32_t secPerClust = fatInfo->secPerClust;

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
			clust = GetNextCluster(clust);
			if (0 == clust) return i + 1;
		}
	}

	return clustSize;
}

 
/// @brief Write one sector
/// @param data 
/// @param sector 
/// @return 
uint32_t FatDisk::WriteOneSector(char* data, uint32_t sector)
{
	if (NULL != diskdrv)
	{
		diskdrv->Write((uint8_t*)data, 1, sector + fstSec);
	}
	return 1;
}


/// @brief Write sector
/// @param data 
/// @param secSize 
/// @param sector 
/// @return 
uint32_t FatDisk::WriteSector(char* data, uint32_t secSize, uint32_t sector)
{
	if (NULL != diskdrv)
	{
		diskdrv->Write((uint8_t*)data, secSize, sector + fstSec);
	}
	return secSize;
}


/// @brief Write cluster
/// @param data 
/// @param clustSize 
/// @param clust 
/// @return 
uint32_t FatDisk::WriteCluster(char* data, uint32_t clustSize, uint32_t clust)
{
	uint32_t bytesPerSec = fatInfo->bytesPerSec;
	uint32_t secPerClust = fatInfo->secPerClust;

	for (uint32_t i = 0; i < clustSize; i++)
	{
		uint32_t sector = ClusterToSector(clust);
		uint32_t offset = i * bytesPerSec * secPerClust;

		if (secPerClust != WriteSector(data + offset, secPerClust, sector))
		{
			return i + 1;
		}

		if (clustSize > 1)
		{
			clust = SetNextCluster(clust);
			if (0 == clust) return i + 1;
		}
	}

	return clustSize;
}


/// @brief Clear cluster
/// @param clustSize 
/// @param clust 
/// @return 
uint32_t FatDisk::ClearCluster(uint32_t clust, uint32_t clustSize)
{
	uint32_t bytesPerSec = fatInfo->bytesPerSec;
	uint32_t secPerClust = fatInfo->secPerClust;

	char* zero = new char[bytesPerSec * secPerClust]();
	memset(zero, 0, bytesPerSec * secPerClust);

	for (uint32_t i = 0; i < clustSize; i++)
	{
		uint32_t sector = ClusterToSector(clust);

		if (secPerClust != WriteSector(zero, secPerClust, sector))
		{
			delete[] zero;
			return i + 1;
		}

		if (clustSize > 1)
		{
			clust = GetNextCluster(clust);
			if (0 == clust) { delete[] zero; return i + 1; }
		}
	}

	delete[] zero;
	return clustSize;
}


/// @brief Alloc cluster
/// @param clustSize 
/// @return clust
uint32_t FatDisk::AllocCluster(uint32_t clustSize)
{
	uint32_t clust = 0;
	uint32_t fstClust = 0;
	for (uint32_t i = 0; i < clustSize; i++)
	{
		clust = SetNextCluster(clust);
		if (0 == fstClust) fstClust = clust;
		if (0 == clust) return 0;
		ClearCluster(clust, 1);
	}
	return fstClust;
}


/// @brief Free cluster
/// @param clustSize 
/// @param clust 
/// @return 
uint32_t FatDisk::FreeCluster(uint32_t clustSize, uint32_t clust)
{
	for (uint32_t i = 0; i < clustSize; i++)
	{
		clust = ClearPrevCluster(clust);
		if (0 == clust) return 0;
	}
	return clust;
}
