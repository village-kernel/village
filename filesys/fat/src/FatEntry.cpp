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
	
		if (++index >= info->entriesPerSec)
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

		if (++index >= info->entriesPerSec)
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


/// @brief Check dir name
/// @param dirents 
/// @param entry 
/// @return 
int FatEntry::CheckDirName(UnionEntry* unient)
{
	Begin();

	for (DirEntry* child = Read(); NULL != child; child = Read())
	{
		if (0 == strncmp(child->body.sfe.name, unient->sfe.name, 11))
		{
			return _ERR;
		}
	}
	
	return _OK;
}


/// @brief 
/// @param name 
/// @param attr 
/// @return 
FatEntry::DirEntry* FatEntry::Create(const char* name, DirAttr attr)
{
	DirEntry* child = new DirEntry();

	//Cal the size of entries
	uint8_t namelen = strlen(name);
	uint8_t dotpos = namelen;
	while ('.' != name[--dotpos] && dotpos);
	uint8_t extlen = dotpos ? (namelen - dotpos - 1) : 0;
	uint8_t bodylen = dotpos ? dotpos : namelen;
	bool isNameLoss = (bodylen > 8 || extlen > 3);
	uint8_t mod = (namelen % (long_name_size - 1)) ? 1 : 0;

	//Alloc entires space
	child->name    = (char*)name;
	child->size    = isNameLoss ? ((namelen / (long_name_size - 1)) + mod + 1) : 1;
	child->unients = new UnionEntry[child->size]();

	//Alloc clust
	uint32_t childClust = fatDisk->AllocCluster(1);

	//Set attr and clust
	UnionEntry* unient     = &child->unients[child->size - 1];
	unient->sfe.attr       = attr;
	unient->sfe.fstClustHI = (childClust >> 16) & 0xffff;
	unient->sfe.fstClustLO = (childClust >> 0)  & 0xffff;

	//Set short name
	fatName.SetShortName(unient, name);

	//Set long name
	if (isNameLoss)
	{
		unient->sfe.NTRes |= _NS_LOSS;

		for (uint8_t i = 1; i < 100; i++)
		{
			fatName.GenNumName(unient, i);
			if (_OK == CheckDirName(unient)) break;
		}

		child->unients[0].lfe.ord = child->size + dir_seq_flag - 1;
		fatName.SetLongName(child->unients, name);
	}

	//Put to disk
	if (_OK == FindSpace(child->size))
	{
		child->index  = index;
		child->clust  = childClust;
		child->sector = sector;
		child->body   = *unient;
		
		if (child->size == Push(child->unients, child->size))
		{
			if ((child->body.sfe.attr & _ATTR_DIRECTORY) == _ATTR_DIRECTORY)
			{
				UnionEntry* childUnients = new UnionEntry[2]();
				childUnients[0].sfe = child->body.sfe;
				childUnients[1].sfe = dirent->body.sfe;

				childUnients[0].sfe.attr |= _ATTR_HIDDEN;
				childUnients[1].sfe.attr |= _ATTR_HIDDEN;

				memcpy(childUnients[0].sfe.name, ".          ", 11);
				memcpy(childUnients[1].sfe.name, "..         ", 11);

				fatDisk->CalcFirstSector(child, clust, sector);
				Push(childUnients, 2);
			}
			return child;
		}
	}

	delete child;
	return NULL;
}


/// @brief FatEntry read
/// @return 
FatEntry::DirEntry* FatEntry::Read()
{
	if (IsEnd()) return NULL;

	while (!Item()->IsValid()) { Next(); if (IsEnd()) return NULL; }

	DirEntry* child = new DirEntry();
	child->clust    = clust;
	child->sector   = sector;
	child->index    = index;
	child->size     = Item()->IsLongName() ? Item()->OrdSize() : 1;
	child->unients  = new UnionEntry[child->size]();

	if (this->Pop(child->unients, child->size) == child->size)
	{
		if (child->unients->IsLongName())
			child->name = fatName.GetLongName(child->unients);
		else
			child->name = fatName.GetShortName(child->unients);

		child->body = child->unients[child->size - 1];
	}

	return child;
}


/// @brief FatEntry write
/// @param dirent 
/// @return 
bool FatEntry::Write(DirEntry* dirent)
{
	index  = dirent->index;
	clust  = dirent->clust;
	sector = dirent->sector;

	return (dirent->size == Push(dirent->unients, dirent->size));
}
