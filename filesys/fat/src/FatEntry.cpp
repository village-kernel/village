//###########################################################################
// FatEntry.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatEntry.h"
#include "FatDisk.h"
#include "FatName.h"


/// @brief 
FatEntry::FatEntry(FatDisk* fatDisk, Info* info, DirEntry* entry)
	:body(NULL),
	ents(NULL),
	index(0),
	clust(0),
	sector(0)
{
	if (fatDisk && info) Setup(fatDisk, info, entry);
}


/// @brief 
FatEntry::~FatEntry()
{
	delete[] ents;
}


/// @brief 
/// @param data 
void FatEntry::Clone(FatEntry* data)
{
	this->index  = data->index;
	this->clust  = data->clust;
	this->sector = data->sector;
}


/// @brief 
void FatEntry::Clear()
{
	this->index  = 0;
	this->clust  = 0;
	this->sector = 0;
}


/// @brief 
/// @return 
bool FatEntry::IsEmpty() { return !(index || clust || sector); }


/// @brief 
/// @return 
bool FatEntry::IsEnd() { return 0 == sector; }


/// @brief 
/// @return 
bool FatEntry::IsValid() { return ents[index].IsVaild(); }


/// @brief 
/// @return 
uint8_t FatEntry::GetSize() { return ents[index].OrdSize(); }


/// @brief 
/// @return 
FatEntry::FATEnt* FatEntry::Item() { return ents + index; }


/// @brief 
void FatEntry::Begin()
{
	this->index  = 0;
	this->clust  = 0;
	this->sector = 0;
	fatDisk->CalcFirstSector(body, clust, sector);
	fatDisk->ReadOneSector((char*)ents, sector);
}


/// @brief 
void FatEntry::Next()
{
	if (++index >= info->entriesPerSec)
	{
		fatDisk->CalcNextSector(clust, sector);
		if (0 != sector)
		{
			fatDisk->ReadOneSector((char*)ents, sector);
			index = 0;
		}
		else return;
	}
}


/// @brief 
/// @param entry 
void FatEntry::Setup(FatDisk* fatDisk, Info* info, DirEntry* entry)
{
	this->fatDisk = fatDisk;
	this->info    = info;
	this->body    = entry;

	ents = (FATEnt*)new char[info->bytesPerSec]();
	
	fatDisk->CalcFirstSector(body, clust, sector);

	fatDisk->ReadOneSector((char*)ents, sector);
}


/// @brief 
/// @param size 
/// @return 
int FatEntry::FindSpace(uint32_t size)
{
	FatEntry record;
	uint8_t  count = 0;

	for (Begin(); !IsEnd(); Next())
	{
		if (!ents[index].IsVaild())
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


/// @brief 
/// @param pop 
/// @param size 
/// @return 
uint32_t FatEntry::Pop(FATEnt* pop, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		pop[i] = ents[index];

		if (i < (size - 1)) index++;
	
		if (index >= info->entriesPerSec)
		{
			fatDisk->CalcNextSector(clust, sector);
			if (0 != sector)
			{
				fatDisk->ReadOneSector((char*)ents, sector);
				index = 0;
			}
			else return i;
		}
	}
	return size;
}


/// @brief 
/// @param push 
/// @param size 
/// @return 
uint32_t FatEntry::Push(FATEnt* push, uint32_t size)
{
	fatDisk->ReadOneSector((char*)ents, sector); 

	for (uint32_t i = 0; i < size; i++)
	{
		ents[index] = push[i];
	
		if (i < (size - 1)) index++;

		if (index >= info->entriesPerSec)
		{
			fatDisk->WriteOneSector((char*)ents, sector);

			fatDisk->CalcNextSector(clust, sector);
			if (0 != sector)
			{
				fatDisk->ReadOneSector((char*)ents, sector);
				index = 0;
			}
			else return i;
		}
	}

	fatDisk->WriteOneSector((char*)ents, sector);

	return size;
}
