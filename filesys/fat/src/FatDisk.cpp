//###########################################################################
// FATDisk.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"


/// @brief 
/// @param clusHI 
/// @param clusLO 
/// @return 
uint32_t FAT::MergeCluster(uint16_t clusHI, uint16_t clusLO)
{
	return (uint32_t)clusHI << 16 | clusLO;
}


/// @brief 
/// @param clusHI 
/// @param clusLO 
/// @return 
uint32_t FAT::ClusterToSector(uint32_t clus)
{
	return ((clus - 2) * dbr->bpb.secPerClus) + fat->firstDataSector;
}


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


/// @brief 
/// @param data 
/// @param SecSize 
/// @param sector 
void FAT::ReadSector(char* data, uint32_t secSize, uint32_t sector)
{
	if (NULL != disk)
	{
		disk->Read((uint8_t*)data, secSize, sector + startSector);
	}	
}


/// @brief 
/// @param data 
/// @param clusSize 
/// @param clus 
void FAT::ReadCluster(char* data, uint32_t clusSize, uint32_t clus)
{
	for (uint32_t i = 0; i < clusSize; i++)
	{

	}
}
