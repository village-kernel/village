//###########################################################################
// FatEntry.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatEntry.h"


/// @brief Constructor
FatEntry::FatEntry(FatDiskio& disk, FatObject* object)
	:disk(disk),
	info(disk.GetInfo()),
	self(object)
{
	temp = new FatObject(new char[info.bytesPerSec]());
	ReadBegin();
}


/// @brief Destructor
FatEntry::~FatEntry()
{
}


/// @brief Calc first sector
/// @param clust 
/// @param sector 
void FatEntry::CalcFirstSector()
{
	if (self->GetFirstCluster() < 2)
	{
		if (FatDiskio::_FAT16 == info.fatType)
		{
			temp->clust  = 0;
			temp->sector = info.firstRootSector;
		}
		else if (FatDiskio::_FAT32 == info.fatType)
		{
			temp->clust  = info.rootClust;
			temp->sector = disk.ClusterToSector(temp->clust);
		}
	}
	else
	{
		temp->clust  = self->GetFirstCluster();
		temp->sector = disk.ClusterToSector(temp->clust);
	}
}


/// @brief Calc next sector
/// @param clust 
/// @param sector 
void FatEntry::CalcNextSector()
{
	//FAT16 root dir
	if (temp->clust < 2)
	{
		uint32_t dirEndedSec = info.firstRootSector + info.countOfRootSecs;
		temp->sector  = (++temp->sector < dirEndedSec) ? temp->sector : 0;
	}
	//FatDisk data dir
	else
	{ 
		if ((++temp->sector - disk.ClusterToSector(temp->clust)) >= info.secPerClust)
		{
			temp->clust = disk.GetNextCluster(temp->clust);
			temp->sector = (0 != temp->clust) ? disk.ClusterToSector(temp->clust) : 0;
		}
	}
}


/// @brief 
/// @param dirent 
void FatEntry::ReadUnionEntries()
{
	disk.ReadSector((char*)temp->ufe, temp->sector);
}


/// @brief 
/// @param dirent 
void FatEntry::WriteUnionEntries()
{
	disk.WriteSector((char*)temp->ufe, temp->sector);
}


/// @brief Iterator begin
bool FatEntry::ReadBegin()
{
	temp->index  = 0;
	temp->clust  = 0;
	temp->sector = 0;

	CalcFirstSector();
	ReadUnionEntries();

	return true;
}


/// @brief Iterator next
bool FatEntry::ReadNext()
{
	if (++temp->index >= info.entriesPerSec)
	{
		CalcNextSector();
		if (0 != temp->sector)
		{
			ReadUnionEntries();
			temp->index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator next
bool FatEntry::WriteNext()
{
	if (++temp->index >= info.entriesPerSec)
	{
		WriteUnionEntries();

		CalcNextSector();
		if (0 != temp->sector)
		{
			ReadUnionEntries();
			temp->index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator is ended
/// @return res
bool FatEntry::IsEnded()
{
	return 0 == temp->sector;
}


/// @brief Get item
/// @return item
FatObject::UnionEntry& FatEntry::Item()
{
	return temp->ufe[temp->index];
}


/// @brief Find free space
/// @param size 
/// @return res
int FatEntry::Find(uint32_t size)
{
	bool      isBackup  = true;
	uint32_t  freeCount = 0;
	FatObject backup;

	for (ReadBegin(); !IsEnded(); ReadNext())
	{
		if (!Item().IsValid())
		{
			if (true == isBackup)
			{
				backup = *temp;
				isBackup = false;
			}
			if (++freeCount >= size)
			{
				*temp = backup;
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
uint32_t FatEntry::Pop(FatObject::UnionEntry* pop, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		pop[i] = Item();
	
		if (false == ReadNext()) return i;
	}
	return size;
}


/// @brief Push entry
/// @param push 
/// @param size 
/// @return size
uint32_t FatEntry::Push(FatObject::UnionEntry* push, uint32_t size)
{
	ReadUnionEntries();

	for (uint32_t i = 0; i < size; i++)
	{
		Item() = push[i];

		if (false == WriteNext()) return i;
	}

	WriteUnionEntries();

	return size;
}


/// @brief Check dir name
/// @param dirents 
/// @param entry 
/// @return 
int FatEntry::CheckDirName(FatObject* obj)
{
	ReadBegin();

	for (FatObject* child = Read(); NULL != child; child = Read())
	{
		if (0 == strncmp(child->GetShortName(), obj->GetShortName(), 11))
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
FatObject* FatEntry::Create(const char* name, int attr)
{
	////Cal the size of entries
	//uint8_t namelen = strlen(name);
	//uint8_t dotpos = namelen;
	//while ('.' != name[--dotpos] && dotpos);
	//uint8_t extlen  = dotpos ? (namelen - dotpos - 1) : 0;
	//uint8_t bodylen = dotpos ? dotpos : namelen;
	//bool isNameLoss = (bodylen > 8 || extlen > 3);
	//uint8_t mod = (namelen % (long_name_size - 1)) ? 1 : 0;

	////Alloc entires space
	//child->self.size    = isNameLoss ? ((namelen / (long_name_size - 1)) + mod + 1) : 1;
	//child->self.unients = new UnionEntry[child->self.size]();

	//FatObject* obj = new FatObject((char*)child->self.unients);
	//obj->SetShortName(name);

	////Set attr and clust
	//uint32_t clust         = disk.AllocCluster();
	//FatObject::UnionEntry* unient  = &child->self.unients[child->self.size - 1];
	//unient->sfe.attr       = attr;
	//unient->sfe.fstClustHI = (clust >> 16) & 0xffff;
	//unient->sfe.fstClustLO = (clust >> 0)  & 0xffff;

	////Set long name
	//if (isNameLoss)
	//{
	//	unient->sfe.NTRes |= FatObject::_NS_LOSS;

	//	for (uint8_t i = 1; i < 100; i++)
	//	{
	//		obj->GenNumName(i);
	//		if (_OK == CheckDirName(unient)) break;
	//	}

	//	child->self.unients[0].lfe.ord = child->self.size + dir_seq_flag - 1;
	//	obj->SetLongName(name);
	//}

	////Put to disk
	//if (_OK == Find(child->self.size))
	//{
	//	child->self.index  = temp->index;
	//	child->self.clust  = temp->clust;
	//	child->self.sector = temp->sector;
	//	child->body        = *unient;
		
	//	if (child->self.size == Push(child->self))
	//	{
	//		if ((child->body.sfe.attr & _ATTR_DIRECTORY) == _ATTR_DIRECTORY)
	//		{
	//			FatEntry::EntryInfo sub;
	//			sub.index = 0;
	//			sub.size  = 2;
	//			sub.unients = new UnionEntry[sub.size]();
	//			sub.unients[0].sfe = child->body.sfe;
	//			sub.unients[1].sfe = body.sfe;
	//			sub.unients[0].sfe.attr |= _ATTR_HIDDEN;
	//			sub.unients[1].sfe.attr |= _ATTR_HIDDEN;
	//			memcpy(sub.unients[0].sfe.name, ".          ", 11);
	//			memcpy(sub.unients[1].sfe.name, "..         ", 11);
	//			child->ReadBegin();
	//			child->Push(sub);
	//		}
	//		return child;
	//	}
	//}

	//delete child;
	return NULL;
}


/// @brief FatData read
/// @return 
FatObject* FatEntry::Read()
{
	for (; !IsEnded(); ReadNext())
	{
		if (Item().IsValid())
		{
			uint32_t clust  = temp->clust;
			uint32_t sector = temp->sector;
			uint32_t index  = temp->index;
			uint32_t size   = Item().AllocSize();
			FatObject::UnionEntry* ufe = new FatObject::UnionEntry[size]();

			if (Pop(ufe, size) == size)
			{
				FatObject* obj = new FatObject((char*)ufe);
				obj->clust  = clust;
				obj->sector = sector;
				obj->index  = index;
				return obj;
			}
			else
			{
				delete[] ufe;
			}
		}
	}
	return NULL;
}


/// @brief FatEntry size
/// @return 
uint32_t FatEntry::Size()
{
	uint32_t size = 0;

	ReadBegin();

	for (FatObject* obj = Read(); NULL != obj; obj = Read())
	{
		size++; delete obj;
	}

	ReadBegin();

	return size;
}


/// @brief FatEntry update
/// @param dirent 
/// @return 
bool FatEntry::Update()
{
	temp[0] = self[0];
	return (self->size == Push(self->ufe, self->size));
}


/// @brief FatEntry remove
/// @return 
bool FatEntry::Remove()
{
	self->SetEntryFree();
	return Update();
}
