//###########################################################################
// FatEntry.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatEntry.h"
#include "FatDisk.h"


/// @brief Constructor
DirEntry::DirEntry(FatDisk* fatDisk, FatInfo* fatInfo)
	:name(NULL)
{
	this->fatDisk = fatDisk;
	this->fatInfo = fatInfo;
}


/// @brief Destructor
DirEntry::~DirEntry()
{
	delete[] name;
	delete[] self.unients;
	delete[] temp.unients;
}


/// @brief Calc first sector
/// @param clust 
/// @param sector 
void DirEntry::CalcFirstSector()
{
	if (fatDisk->GetFirstClust(body.sfe) < 2)
	{
		if (_FAT16 == fatInfo->fatType)
		{
			temp.clust  = 0;
			temp.sector = fatInfo->firstRootSector;
		}
		else if (_FAT32 == fatInfo->fatType)
		{
			temp.clust  = fatInfo->rootClust;
			temp.sector = fatDisk->ClusterToSector(temp.clust);
		}
	}
	else
	{
		temp.clust  = fatDisk->GetFirstClust(body.sfe);
		temp.sector = fatDisk->ClusterToSector(temp.clust);
	}
}


/// @brief Calc next sector
/// @param clust 
/// @param sector 
void DirEntry::CalcNextSector()
{
	//FAT16 root dir
	if (temp.clust < 2)
	{
		uint32_t dirEndedSec = fatInfo->firstRootSector + fatInfo->countOfRootSecs;
		temp.sector  = (++temp.sector < dirEndedSec) ? temp.sector : 0;
	}
	//FatDisk data dir
	else
	{ 
		if ((++temp.sector - fatDisk->ClusterToSector(temp.clust)) >= fatInfo->secPerClust)
		{
			temp.clust = fatDisk->GetNextCluster(temp.clust);
			temp.sector = (0 != temp.clust) ? fatDisk->ClusterToSector(temp.clust) : 0;
		}
	}
}


/// @brief 
/// @param dirent 
void DirEntry::ReadUnionEntries()
{
	fatDisk->ReadOneSector((char*)temp.unients, temp.sector);
}


/// @brief 
/// @param dirent 
void DirEntry::WriteUnionEntries()
{
	fatDisk->WriteOneSector((char*)temp.unients, temp.sector);
}


/// @brief Iterator begin
bool DirEntry::ReadBegin()
{
	temp.index  = 0;
	temp.clust  = 0;
	temp.sector = 0;

	if (NULL == temp.unients)
	{
		temp.unients = (UnionEntry*)new char[fatInfo->bytesPerSec]();
	}

	CalcFirstSector();
	ReadUnionEntries();

	return true;
}


/// @brief Iterator next
bool DirEntry::ReadNext()
{
	if (++temp.index >= fatInfo->entriesPerSec)
	{
		CalcNextSector();
		if (0 != temp.sector)
		{
			ReadUnionEntries();
			temp.index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator next
bool DirEntry::WriteNext()
{
	if (++temp.index >= fatInfo->entriesPerSec)
	{
		WriteUnionEntries();

		CalcNextSector();
		if (0 != temp.sector)
		{
			ReadUnionEntries();
			temp.index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator is ended
/// @return res
bool DirEntry::IsEnded()
{
	return 0 == temp.sector;
}


/// @brief Get item
/// @return item
DirEntry::UnionEntry& DirEntry::Item()
{
	return temp.unients[temp.index];
}


/// @brief Find free space
/// @param size 
/// @return res
int DirEntry::Find(uint32_t size)
{
	bool      isBackup  = true;
	uint32_t  freeCount = 0;
	EntryInfo backup;

	for (ReadBegin(); !IsEnded(); ReadNext())
	{
		if (!Item().IsValid())
		{
			if (true == isBackup)
			{
				backup = temp;
				isBackup = false;
			}
			if (++freeCount >= size)
			{
				temp = backup;
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
uint32_t DirEntry::Pop(EntryInfo& pop)
{
	for (uint32_t i = 0; i < pop.size; i++)
	{
		pop.unients[i] = Item();
	
		if (false == ReadNext()) return i;
	}
	return pop.size;
}


/// @brief Push entry
/// @param push 
/// @param size 
/// @return size
uint32_t DirEntry::Push(EntryInfo& push)
{
	ReadUnionEntries();

	for (uint32_t i = 0; i < push.size; i++)
	{
		Item() = push.unients[i];

		if (false == WriteNext()) return i;
	}

	WriteUnionEntries();

	return push.size;
}


/// @brief FatData Update
/// @param dirent 
/// @return 
bool DirEntry::Update()
{
	temp.index  = self.index;
	temp.clust  = self.clust;
	temp.sector = self.sector;
	return (self.size == Push(self));
}


/// @brief 
/// @return 
bool DirEntry::Remove()
{
	for (uint8_t i = 0; i < self.size; i++)
	{
		self.unients[i].lfe.ord = dir_free_flag;
	}
	return Update();
}


/// @brief Check dir name
/// @param dirents 
/// @param entry 
/// @return 
int DirEntry::CheckDirName(UnionEntry* unient)
{
	ReadBegin();

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
DirEntry* DirEntry::Create(const char* name, DirAttr attr)
{
	DirEntry* child = new DirEntry(fatDisk, fatInfo);

	//Cal the size of entries
	uint8_t namelen = strlen(name);
	uint8_t dotpos = namelen;
	while ('.' != name[--dotpos] && dotpos);
	uint8_t extlen  = dotpos ? (namelen - dotpos - 1) : 0;
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
			if (_OK == CheckDirName(unient)) break;
		}

		child->self.unients[0].lfe.ord = child->self.size + dir_seq_flag - 1;
		fatName.SetLongName(child->self.unients, name);
	}

	//Put to disk
	if (_OK == Find(child->self.size))
	{
		child->self.index  = temp.index;
		child->self.clust  = temp.clust;
		child->self.sector = temp.sector;
		child->body        = *unient;
		
		if (child->self.size == Push(child->self))
		{
			if ((child->body.sfe.attr & _ATTR_DIRECTORY) == _ATTR_DIRECTORY)
			{
				DirEntry::EntryInfo sub;
				sub.index = 0;
				sub.size  = 2;
				sub.unients = new UnionEntry[sub.size]();
				sub.unients[0].sfe = child->body.sfe;
				sub.unients[1].sfe = body.sfe;
				sub.unients[0].sfe.attr |= _ATTR_HIDDEN;
				sub.unients[1].sfe.attr |= _ATTR_HIDDEN;
				memcpy(sub.unients[0].sfe.name, ".          ", 11);
				memcpy(sub.unients[1].sfe.name, "..         ", 11);
				child->ReadBegin();
				child->Push(sub);
			}
			return child;
		}
	}

	delete child;
	return NULL;
}


/// @brief FatData read
/// @return 
DirEntry* DirEntry::Read()
{
	if (NULL == temp.unients)
		ReadBegin();

	if (IsEnded()) return NULL;

	while (!Item().IsValid())
	{
		ReadNext();
		if (IsEnded()) return NULL;
	}

	DirEntry* child      = new DirEntry(fatDisk, fatInfo);
	child->self.clust    = temp.clust;
	child->self.sector   = temp.sector;
	child->self.index    = temp.index;
	child->self.size     = Item().IsLongName() ? Item().OrdSize() : 1;
	child->self.unients  = new UnionEntry[child->self.size]();

	if (Pop(child->self) == child->self.size)
	{
		if (child->self.unients->IsLongName())
			child->name = fatName.GetLongName(child->self.unients);
		else
			child->name = fatName.GetShortName(child->self.unients);

		child->body = child->self.unients[child->self.size - 1];
	}

	return child;
}
