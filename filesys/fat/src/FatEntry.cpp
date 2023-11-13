//###########################################################################
// FatEntry.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatEntry.h"
#include "FatDisk.h"


/// @brief Constructor
FatEntry::FatEntry()
{
}


/// @brief Destructor
FatEntry::~FatEntry()
{
}


/// @brief FatEntry setup
/// @param fatDisk 
/// @param info 
void FatEntry::Setup(FatDisk* fatDisk, FatInfo* fatInfo)
{
	this->fatDisk = fatDisk;
	this->fatInfo = fatInfo;
}


/// @brief Calc first sector
/// @param clust 
/// @param sector 
void FatEntry::CalcFirstSector(DirEntry* dirent)
{
	if (fatDisk->GetFirstClust(dirent->body.sfe) < 2)
	{
		if (_FAT16 == fatInfo->fatType)
		{
			dirent->temp.clust  = 0;
			dirent->temp.sector = fatInfo->firstRootSector;
		}
		else if (_FAT32 == fatInfo->fatType)
		{
			dirent->temp.clust  = fatInfo->rootClust;
			dirent->temp.sector = fatDisk->ClusterToSector(dirent->temp.clust);
		}
	}
	else
	{
		dirent->temp.clust  = fatDisk->GetFirstClust(dirent->body.sfe);
		dirent->temp.sector = fatDisk->ClusterToSector(dirent->temp.clust);
	}
}


/// @brief Calc next sector
/// @param clust 
/// @param sector 
void FatEntry::CalcNextSector(DirEntry* dirent)
{
	//FAT16 root dir
	if (dirent->temp.clust < 2)
	{
		uint32_t dirEndedSec = fatInfo->firstRootSector + fatInfo->countOfRootSecs;
		dirent->temp.sector  = (++dirent->temp.sector < dirEndedSec) ? dirent->temp.sector : 0;
	}
	//FatDisk data dir
	else
	{ 
		if ((++dirent->temp.sector - fatDisk->ClusterToSector(dirent->temp.clust)) >= fatInfo->secPerClust)
		{
			dirent->temp.clust = fatDisk->GetNextCluster(dirent->temp.clust);
			dirent->temp.sector = (0 != dirent->temp.clust) ? fatDisk->ClusterToSector(dirent->temp.clust) : 0;
		}
	}
}


/// @brief 
/// @param dirent 
void FatEntry::ReadUnionEntries(DirEntry* dirent)
{
	fatDisk->ReadOneSector((char*)dirent->temp.unients, dirent->temp.sector);
}


/// @brief 
/// @param dirent 
void FatEntry::WriteUnionEntries(DirEntry* dirent)
{
	fatDisk->WriteOneSector((char*)dirent->temp.unients, dirent->temp.sector);
}


/// @brief Iterator begin
bool FatEntry::ReadBegin(DirEntry* dirent)
{
	dirent->temp.index  = 0;
	dirent->temp.clust  = 0;
	dirent->temp.sector = 0;

	if (NULL == dirent->temp.unients)
	{
		dirent->temp.unients = (UnionEntry*)new char[fatInfo->bytesPerSec]();
	}

	CalcFirstSector(dirent);
	ReadUnionEntries(dirent);

	return true;
}


/// @brief Iterator next
bool FatEntry::ReadNext(DirEntry* dirent)
{
	if (++dirent->temp.index >= fatInfo->entriesPerSec)
	{
		CalcNextSector(dirent);
		if (0 != dirent->temp.sector)
		{
			ReadUnionEntries(dirent);
			dirent->temp.index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator next
bool FatEntry::WriteNext(DirEntry* dirent)
{
	if (++dirent->temp.index >= fatInfo->entriesPerSec)
	{
		WriteUnionEntries(dirent);

		CalcNextSector(dirent);
		if (0 != dirent->temp.sector)
		{
			ReadUnionEntries(dirent);
			dirent->temp.index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator is ended
/// @return res
bool FatEntry::IsEnded(DirEntry* dirent)
{
	return 0 == dirent->temp.sector;
}


/// @brief Get item
/// @return item
FatEntry::UnionEntry& FatEntry::Item(DirEntry* dirent)
{
	return dirent->temp.unients[dirent->temp.index];
}


/// @brief Find free space
/// @param size 
/// @return res
int FatEntry::Find(DirEntry* dirent, uint32_t size)
{
	bool      isBackup  = true;
	uint32_t  freeCount = 0;
	EntryInfo backup;

	for (ReadBegin(dirent); !IsEnded(dirent); ReadNext(dirent))
	{
		if (!Item(dirent).IsValid())
		{
			if (true == isBackup)
			{
				backup = dirent->temp;
				isBackup = false;
			}
			if (++freeCount >= size)
			{
				dirent->temp = backup;
				return _OK;
			}
		}
		else
		{
			freeCount = 0;
			isBackup = true;
		}
	}

	return _ERR;
}


/// @brief Pop entry
/// @param pop 
/// @param size 
/// @return size
uint32_t FatEntry::Pop(DirEntry* dirent, EntryInfo& pop)
{
	for (uint32_t i = 0; i < pop.size; i++)
	{
		pop.unients[i] = Item(dirent);
	
		if (false == ReadNext(dirent)) return i;
	}
	return pop.size;
}


/// @brief Push entry
/// @param push 
/// @param size 
/// @return size
uint32_t FatEntry::Push(DirEntry* dirent, EntryInfo& push)
{
	ReadUnionEntries(dirent);

	for (uint32_t i = 0; i < push.size; i++)
	{
		Item(dirent) = push.unients[i];

		if (false == WriteNext(dirent)) return i;
	}

	WriteUnionEntries(dirent);

	return push.size;
}
