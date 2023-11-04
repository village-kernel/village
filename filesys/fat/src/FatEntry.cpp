//###########################################################################
// FatEntry.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatEntry.h"
#include "FatDisk.h"


/// @brief Constructor
FatEntry::FatEntry(FatDisk* fatDisk, Info* info, DirEntry* dirent)
	:dirent(NULL),
	unients(NULL),
	index(0),
	clust(0),
	sector(0)
{
	if (fatDisk && info) Setup(fatDisk, info, dirent);
}


/// @brief Destructor
FatEntry::~FatEntry()
{
	delete[] unients;
}


/// @brief data is empty
/// @return 
bool FatEntry::IsEmpty()
{
	return !(index || clust || sector);
}


/// @brief low clone data
/// @param data 
void FatEntry::Clone(FatEntry* data)
{
	this->index  = data->index;
	this->clust  = data->clust;
	this->sector = data->sector;
}


/// @brief clear data
void FatEntry::Clear()
{
	this->index  = 0;
	this->clust  = 0;
	this->sector = 0;
}


/// @brief Iterator begin
void FatEntry::Begin()
{
	this->index  = 0;
	this->clust  = 0;
	this->sector = 0;
	fatDisk->CalcFirstSector(dirent, clust, sector);
	fatDisk->ReadOneSector((char*)unients, sector);
}


/// @brief Iterator next
void FatEntry::Next()
{
	if (++index >= info->entriesPerSec)
	{
		fatDisk->CalcNextSector(clust, sector);
		if (0 != sector)
		{
			fatDisk->ReadOneSector((char*)unients, sector);
			index = 0;
		}
		else return;
	}
}


/// @brief Iterator is ended
/// @return res
bool FatEntry::IsEnd()
{
	return 0 == sector;
}


/// @brief Get item
/// @return item
FatEntry::UnionEntry* FatEntry::Item()
{
	return unients + index;
}


/// @brief Setup
/// @param entry 
void FatEntry::Setup(FatDisk* fatDisk, Info* info, DirEntry* dirent)
{
	this->fatDisk = fatDisk;
	this->info    = info;
	this->dirent  = dirent;

	unients = (UnionEntry*)new char[info->bytesPerSec]();
	fatDisk->CalcFirstSector(dirent, clust, sector);
	fatDisk->ReadOneSector((char*)unients, sector);
}


/// @brief Find free space
/// @param size 
/// @return res
int FatEntry::FindSpace(uint32_t size)
{
	FatEntry record;
	uint8_t  count = 0;

	for (Begin(); !IsEnd(); Next())
	{
		if (!unients[index].IsValid())
		{
			if (record.IsEmpty())
			{
				record.Clone(this);
			}
			if (++count >= size)
			{
				this->Clone(&record);
				return _OK;
			}
		}
		else
		{
			count = 0;
			record.Clear();
		}
	}

	return _ERR;
}


/// @brief Pop entry
/// @param pop 
/// @param size 
/// @return size
uint32_t FatEntry::Pop(UnionEntry* pop, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		pop[i] = unients[index];

		if (i < (size - 1)) index++;
	
		if (index >= info->entriesPerSec)
		{
			fatDisk->CalcNextSector(clust, sector);
			if (0 != sector)
			{
				fatDisk->ReadOneSector((char*)unients, sector);
				index = 0;
			}
			else return i;
		}
	}
	return size;
}


/// @brief Push entry
/// @param push 
/// @param size 
/// @return size
uint32_t FatEntry::Push(UnionEntry* push, uint32_t size)
{
	fatDisk->ReadOneSector((char*)unients, sector); 

	for (uint32_t i = 0; i < size; i++)
	{
		unients[index] = push[i];
	
		if (i < (size - 1)) index++;

		if (index >= info->entriesPerSec)
		{
			fatDisk->WriteOneSector((char*)unients, sector);

			fatDisk->CalcNextSector(clust, sector);
			if (0 != sector)
			{
				fatDisk->ReadOneSector((char*)unients, sector);
				index = 0;
			}
			else return i;
		}
	}

	fatDisk->WriteOneSector((char*)unients, sector);

	return size;
}
