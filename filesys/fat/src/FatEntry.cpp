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
void FatEntry::Setup(FatDisk* fatDisk, Info* info)
{
	this->fatDisk = fatDisk;
	this->info    = info;
}


/// @brief Iterator begin
bool FatEntry::ReadBegin(DirEntry* dirent)
{
	dirent->temp.index  = 0;
	dirent->temp.clust  = 0;
	dirent->temp.sector = 0;

	if (NULL == dirent->temp.unients)
	{
		dirent->temp.unients = (UnionEntry*)new char[info->bytesPerSec]();
	}

	fatDisk->CalcFirstSector(dirent);
	fatDisk->ReadUnionEntries(dirent);

	return true;
}


/// @brief Iterator next
bool FatEntry::ReadNext(DirEntry* dirent)
{
	if (++dirent->temp.index >= info->entriesPerSec)
	{
		fatDisk->CalcNextSector(dirent);
		if (0 != dirent->temp.sector)
		{
			fatDisk->ReadUnionEntries(dirent);
			dirent->temp.index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator next
bool FatEntry::WriteNext(DirEntry* dirent)
{
	if (++dirent->temp.index >= info->entriesPerSec)
	{
		fatDisk->WriteUnionEntries(dirent);

		fatDisk->CalcNextSector(dirent);
		if (0 != dirent->temp.sector)
		{
			fatDisk->ReadUnionEntries(dirent);
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
	fatDisk->ReadUnionEntries(dirent);

	for (uint32_t i = 0; i < push.size; i++)
	{
		Item(dirent) = push.unients[i];

		if (false == WriteNext(dirent)) return i;
	}

	fatDisk->WriteUnionEntries(dirent);

	return push.size;
}


/// @brief Check dir name
/// @param dirents 
/// @param entry 
/// @return 
int FatEntry::CheckDirName(DirEntry* dirent, UnionEntry* unient)
{
	ReadBegin(dirent);

	for (DirEntry* child = Read(dirent); NULL != child; child = Read(dirent))
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
FatEntry::DirEntry* FatEntry::Create(DirEntry* dirent, const char* name, DirAttr attr)
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
	child->name         = (char*)name;
	child->self.size    = isNameLoss ? ((namelen / (long_name_size - 1)) + mod + 1) : 1;
	child->self.unients = new UnionEntry[child->self.size]();

	//Set attr and clust
	uint32_t clust         = fatDisk->AllocCluster();
	UnionEntry* unient     = &child->self.unients[child->self.size - 1];
	unient->sfe.attr       = attr;
	unient->sfe.fstClustHI = (clust >> 16) & 0xffff;
	unient->sfe.fstClustLO = (clust >> 0)  & 0xffff;

	//Set short name
	fatName.SetShortName(unient, name);

	//Set long name
	if (isNameLoss)
	{
		unient->sfe.NTRes |= _NS_LOSS;

		for (uint8_t i = 1; i < 100; i++)
		{
			fatName.GenNumName(unient, i);
			if (_OK == CheckDirName(dirent, unient)) break;
		}

		child->self.unients[0].lfe.ord = child->self.size + dir_seq_flag - 1;
		fatName.SetLongName(child->self.unients, name);
	}

	//Put to disk
	if (_OK == Find(dirent, child->self.size))
	{
		child->self.index  = dirent->temp.index;
		child->self.clust  = dirent->temp.clust;
		child->self.sector = dirent->temp.sector;
		child->body        = *unient;
		
		if (child->self.size == Push(dirent, child->self))
		{
			if ((child->body.sfe.attr & _ATTR_DIRECTORY) == _ATTR_DIRECTORY)
			{
				EntryInfo sub;
				sub.index = 0;
				sub.size  = 2;
				sub.unients = new UnionEntry[sub.size]();
				sub.unients[0].sfe = child->body.sfe;
				sub.unients[1].sfe = dirent->body.sfe;
				sub.unients[0].sfe.attr |= _ATTR_HIDDEN;
				sub.unients[1].sfe.attr |= _ATTR_HIDDEN;
				memcpy(sub.unients[0].sfe.name, ".          ", 11);
				memcpy(sub.unients[1].sfe.name, "..         ", 11);
				ReadBegin(child);
				Push(child, sub);
			}
			return child;
		}
	}

	delete child;
	return NULL;
}


/// @brief FatEntry read
/// @return 
FatEntry::DirEntry* FatEntry::Read(DirEntry* dirent)
{
	if (NULL == dirent->temp.unients) ReadBegin(dirent);

	if (IsEnded(dirent)) return NULL;

	while (!Item(dirent).IsValid()) { ReadNext(dirent); if (IsEnded(dirent)) return NULL; }

	DirEntry* child      = new DirEntry();
	child->self.clust    = dirent->temp.clust;
	child->self.sector   = dirent->temp.sector;
	child->self.index    = dirent->temp.index;
	child->self.size     = Item(dirent).IsLongName() ? Item(dirent).OrdSize() : 1;
	child->self.unients  = new UnionEntry[child->self.size]();

	if (Pop(dirent, child->self) == child->self.size)
	{
		if (child->self.unients->IsLongName())
			child->name = fatName.GetLongName(child->self.unients);
		else
			child->name = fatName.GetShortName(child->self.unients);

		child->body = child->self.unients[child->self.size - 1];
	}

	return child;
}


/// @brief FatEntry Update
/// @param dirent 
/// @return 
bool FatEntry::Update(DirEntry* dirent)
{
	dirent->temp.index  = dirent->self.index;
	dirent->temp.clust  = dirent->self.clust;
	dirent->temp.sector = dirent->self.sector;

	return (dirent->self.size == Push(dirent, dirent->self));
}
