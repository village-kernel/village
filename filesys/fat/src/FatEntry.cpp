//###########################################################################
// FatEntry.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatEntry.h"
#include "FatDisk.h"
#include "FatName.h"
#include "Regex.h"


/// @brief 
FatEntry::FatEntry(FatObjs* objs, DirEntry* entry)
	:body(NULL),
	ents(NULL),
	index(0),
	clust(0),
	sector(0)
{
	if (NULL != objs) Setup(objs, entry);
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
void FatEntry::Setup(FatObjs* objs, DirEntry* entry)
{
	FatObjs::Clone(objs);

	this->body = entry;

	ents = (FATEnt*)new char[dbr->bpb.bytesPerSec]();
	
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


/// @brief Not dir
/// @param path 
/// @return 
char* FatData::NotDir(const char* path)
{
	uint8_t pos = strlen(path);
	char ch = 0; do { ch = path[--pos]; } while ('/' != ch && pos);
	return (char*)path + pos + 1;
}


/// @brief Search path
/// @param path 
/// @return 
FatData::DirEntry* FatData::SearchPath(const char* path, int forward)
{
	Regex regex;
	regex.Split(path, '/');
	char** dirNames = regex.ToArray();
	int8_t dirIndex = regex.Size() - forward;
	
	DirEntry* entry = NULL;

	if (dirIndex <= 1)
	{
		entry = new DirEntry();
		entry->body.attr = _ATTR_DIRECTORY;
		entry->root = true;
		entry->name = (char*)"/";
		return entry;
	}

	for (uint8_t i = 1; i < dirIndex; i++)
	{
		entry = SearchDir(entry, dirNames[i]);

		if (NULL == entry) return NULL;
	}

	return entry;
}


/// @brief Search dir
/// @param entry 
/// @param dir 
/// @return 
FatData::DirEntry* FatData::SearchDir(DirEntry* entry, const char* dir)
{
	FatEntry* data  = new FatEntry(this, entry);
	DirEntry* found = NULL;

	for (data->Begin(); !data->IsEnd(); data->Next())
	{
		if (!data->IsValid()) continue;
		
		uint8_t size = data->Item()->IsLongName() ? data->GetSize() : 1;
		FATEnt* ents = new FATEnt[size]();
		if (data->Pop(ents, size) != size) break;
		
		char* dirname = NULL;
		if (ents[0].IsLongName())
			dirname = fatName->GetLongName(ents);
		else
			dirname = fatName->GetShortName(ents);

		if (0 == strcmp(dirname, dir))
		{
			found = new DirEntry(ents[size - 1].sfn, dirname);
			delete[] ents;
			break;
		}

		delete[] ents;
	}

	delete data;
	return found;
}


/// @brief Open dir
/// @param entry 
/// @return 
FatData::DirEntries* FatData::OpenDir(DirEntry* entry)
{
	FatEntry*   data    = new FatEntry(this, entry);
	DirEntries* entries = new DirEntries();

	for (data->Begin(); !data->IsEnd(); data->Next())
	{
		if (!data->IsValid()) continue;
		
		uint8_t size = data->Item()->IsLongName() ? data->GetSize() : 1;
		FATEnt* ents = new FATEnt[size]();
		if (data->Pop(ents, size) != size) break;
		
		char* dirname = NULL;
		if (ents->IsLongName())
			dirname = fatName->GetLongName(ents);
		else
			dirname = fatName->GetShortName(ents);

		if (0 != strcmp(dirname, ""))
		{
			FATEnt* ent = &ents[size- 1];
			if (ent->sfn.IsFile() || ent->sfn.IsDirectory())
			{
				entries->dirs.Add(new DirEntry(ent->sfn, dirname));
			}
		}

		delete[] ents;
	}

	entries->dirs.Begin();

	delete data;
	return entries;
}


/// @brief 
/// @param entry 
/// @param ents 
/// @param name 
/// @return 
FatEntry* FatData::CreateEntry(DirEntry* entry, const char* name, FATEnt*& ents, uint8_t& num)
{
	DirEntries* entries = OpenDir(entry);
	FatEntry*   data    = new FatEntry(this, entry);

	//Cal the size of entries
	uint8_t namelen = strlen(name);
	uint8_t dotpos = namelen;
	while ('.' != name[--dotpos] && dotpos);
	uint8_t extlen = dotpos ? (namelen - dotpos - 1) : 0;
	uint8_t bodylen = dotpos ? dotpos : namelen;
	bool isNameLoss = (bodylen > 8 || extlen > 3);
	uint8_t mod = (namelen % (long_name_size - 1)) ? 1 : 0;
	num = isNameLoss ? ((namelen / (long_name_size - 1)) + mod) : 0;

	//Alloc entires space
	ents = new FATEnt[num + 1]();

	//Set short name
	fatName->SetShortName(&ents[num], name);

	//Set long name
	if (isNameLoss)
	{
		ents[num].sfn.NTRes |= _NS_LOSS;

		for (uint8_t i = 1; i < 100; i++)
		{
			fatName->GenNumName(ents + num, i);
			if (_OK == entries->CheckConflict(ents + num)) break;
		}

		ents[0].lfn.ord = num + dir_seq_flag;
		fatName->SetLongName(ents, name);
	}

	return data;
}


/// @brief Create file
/// @param entry 
/// @param name 
/// @return 
FatData::DirEntry* FatData::CreateFile(DirEntry* entry, const char* name)
{
	uint8_t   num  = 0;
	FATEnt*   ents = NULL;
	FatEntry* data = CreateEntry(entry, name, ents, num);

	//Set entry attr
	ents[num].sfn.attr = _ATTR_FILE;

	//Put to disk
	uint8_t size = num + 1;
	if (_OK == data->FindSpace(size) && 
		size == data->Push(ents, size))
	{
		return new DirEntry(ents[num].sfn, (char*)name);
	}

	return NULL;
}


/// @brief Create directory
/// @param entry 
/// @param name 
/// @return 
FatData::DirEntries* FatData::CreateDir(DirEntry* entry, const char* name)
{
	uint8_t   num = 0;
	FATEnt*   ents = NULL;
	FatEntry* data = CreateEntry(entry, name, ents, num);

	uint32_t clust = fatDisk->AllocCluster(1);

	//Set entry attr
	ents[num].sfn.attr = _ATTR_DIRECTORY;
	ents[num].sfn.fstClustHI = (clust >> 16) & 0xffff;
	ents[num].sfn.fstClustLO = (clust >> 0)  & 0xffff;

	//Put to disk
	uint8_t size = num + 1;
	if (_OK == data->FindSpace(size) && 
		size == data->Push(ents, size))
	{
		FATEnt* dirs = new FATEnt[2]();
		dirs[0].sfn = ents[num].sfn;
		dirs[1].sfn = entry->body;

		dirs[0].sfn.attr |= _ATTR_HIDDEN;
		dirs[1].sfn.attr |= _ATTR_HIDDEN;

		memcpy(dirs[0].sfn.name, ".          ", 11);
		memcpy(dirs[1].sfn.name, "..         ", 11);

		DirEntry* dir = new DirEntry(ents[num].sfn, (char*)name);
		FatEntry* child = new FatEntry(this, dir);
		child->Push(dirs, 2);
		delete child;
		delete[] dirs;

		return OpenDir(dir);
	}

	return NULL;
}


/// @brief Get volume label
/// @return 
char* FatData::GetVolumeLabel()
{
	FatEntry* data = new FatEntry(this, NULL);
	FATEnt*   ent  = data->Item();

	char* label = (char*)"NONAME";

	//Check is volume entry
	if (ent->sfn.IsVolume())
	{
		//Get volume label
		label = fatName->GetVolumeLabel(ent);
	}

	delete data;
	return label;
}


/// @brief Set volume label
/// @param name 
/// @return 
int FatData::SetVolumeLabel(const char* name)
{
	FatEntry* data = new FatEntry(this, NULL);
	FATEnt*   ent  = data->Item();

	//Check is volume entry
	if (ent->sfn.IsVolume())
	{
		//Set volume label
		fatName->SetVolumeLabel(ent, name);

		//Push ent to disk
		data->Push(ent);
	}
	
	delete data;
	return _OK;
}
