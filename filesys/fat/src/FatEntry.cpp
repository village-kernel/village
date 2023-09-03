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


/// @brief attr is hidden 
/// @param entry 
/// @return 
inline bool FatEntry::IsHidden(FATEnt* entry)
{
	return ((entry->sfn.attr & _ATTR_HIDDEN) == _ATTR_HIDDEN);
}


/// @brief attr is hidden
/// @param entry 
/// @return 
bool FatEntry::IsHidden(DirEntry* entry)
{
	return IsHidden(&entry->dir);
}


/// @brief attr is directory
/// @param entry 
/// @return 
inline bool FatEntry::IsDirectory(FATEnt* entry)
{
	return ((entry->sfn.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_DIRECTORY);
}


/// @brief attr is directory
/// @param entry 
/// @return 
bool FatEntry::IsDirectory(DirEntry* entry)
{
	return IsDirectory(&entry->dir);
}


/// @brief attr is volume
/// @param entry 
/// @return 
inline bool FatEntry::IsVolume(FATEnt* entry)
{
	return ((entry->sfn.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_VOLUME_ID);
}


/// @brief attr is volume
/// @param entry 
/// @return 
bool FatEntry::IsVolume(DirEntry* entry)
{
	return IsVolume(&entry->dir);
}


/// @brief attr is file
/// @param entry 
/// @return 
inline bool FatEntry::IsFile(FATEnt* entry)
{
	return ((entry->sfn.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_FILE);
}


/// @brief attr is file
/// @param entry 
/// @return 
bool FatEntry::IsFile(DirEntry* entry)
{
	return IsFile(&entry->dir);
}


/// @brief Not dir
/// @param path 
/// @return 
char* FatEntry::NotDir(const char* path)
{
	uint8_t pos = strlen(path);
	char ch = 0; do { ch = path[--pos]; } while ('/' != ch && pos);
	return (char*)path + pos + 1;
}


/// @brief Check entry
/// @param data 
/// @param sdir 
/// @return 
int FatEntry::CheckConflict(DirData* data, FATEnt* entry)
{
	uint8_t count = 0;
	for (DirEntry* dir = data->dirs.Begin(); !data->dirs.IsEnd(); dir = data->dirs.Next())
	{
		for (uint8_t i = 0; i < 11; i++)
		{
			if (dir->dir.sfn.name[i] != entry->sfn.name[i])
			{
				count++; break;
			}
		}
	}
	return (data->size == count) ? _OK : _ERR;
}


/// @brief Search space
/// @param data 
/// @param size 
/// @return 
int FatEntry::SearchSpace(DirData* data, uint8_t size)
{
	FATEnt*&   ents   = data->ents;
	uint32_t&  index  = data->index;
	uint32_t&  clust  = data->clust;
	uint32_t&  sector = data->sector;

	DirData record;
	uint8_t count = 0;

	while (0 != sector)
	{
		fatDisk->ReadOneSector((char*)ents, sector);

		for (index = 0; index < info->entriesPerSec; index++)
		{
			if ((ents[index].lfn.ord == dir_free_flag) ||
				(ents[index].lfn.ord == 0))
			{
				if (record.IsEmpty())
				{
					record.Clone(data);
				}
				if (++count >= size)
				{
					data->Clone(&record);
					return _OK;
				}
			}
			else
			{
				count = 0;
				record.Clear();
			}
		}

		fatDisk->CalcNextSector(clust, sector);
	}

	return _ERR;
}


/// @brief WriteEntries
/// @param data 
/// @param ldir 
/// @param sdir 
/// @param size 
/// @return 
int FatEntry::WirteEntires(DirData* data, FATEnt* entries, uint8_t size)
{
	FATEnt*&   ents   = data->ents;
	uint32_t&  index  = data->index;
	uint32_t&  clust  = data->clust;
	uint32_t&  sector = data->sector;

	fatDisk->ReadOneSector((char*)ents, sector);

	for (uint8_t i = 0; i < size; i++)
	{
		ents[index] = entries[i];

		if (i < (size - 1)) index++;

		if (index >= info->entriesPerSec)
		{
			index = 0;
			fatDisk->WriteOneSector((char*)ents, sector);
			fatDisk->CalcNextSector(clust, sector);
			fatDisk->ReadOneSector((char*)ents, sector);
		}
	}

	fatDisk->WriteOneSector((char*)ents, sector);

	return _OK;
}


/// @brief Set entry name
/// @param data 
/// @param name 
int FatEntry::SetEntryName(DirData* data, const char* name, int attr)
{
	uint8_t namelen = strlen(name);
	uint8_t dotpos = namelen;
	while ('.' != name[--dotpos] && dotpos);
	uint8_t extlen = dotpos ? (namelen - dotpos - 1) : 0;
	uint8_t bodylen = dotpos ? dotpos : namelen;
	bool isNameLoss = (bodylen > 8 || extlen > 3);
	uint8_t mod = (namelen % (long_name_size - 1)) ? 1 : 0;
	uint8_t num = isNameLoss ? ((namelen / (long_name_size - 1)) + mod) : 0;

	//Alloc entires space
	FATEnt* ents = new FATEnt[num + 1]();
	
	//Set entry attr
	ents[num].sfn.attr = attr;

	//Set short name
	fatName->SetShortName(&ents[num], name);

	//Set long name
	if (isNameLoss)
	{
		ents[num].sfn.NTRes |= _NS_LOSS;

		for (uint8_t i = 1; i < 100; i++)
		{
			fatName->GenNumName(ents + num, i);
			if (_OK == CheckConflict(data, ents + num)) break;
		}

		ents[0].lfn.ord = num + dir_seq_flag;
		fatName->SetLongName(ents, name);
	}

	//Put to disk
	if (_OK == SearchSpace(data, num + 1) && 
		_OK == WirteEntires(data, ents, num + 1))
	{
		return _OK;
	}

	return _ERR;
}


/// @brief Get entry name
/// @param entries 
/// @param idx 
/// @param clust 
/// @param sector 
/// @return 
char* FatEntry::GetEntryName(DirData* data)
{
	FATEnt*&   ents   = data->ents;
	uint32_t&  index  = data->index;
	uint32_t&  clust  = data->clust;
	uint32_t&  sector = data->sector;
	char*      name   = NULL;

	//Get long name
	if ((ents[index].lfn.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
	{
		uint8_t n = ents[index].lfn.ord - dir_seq_flag + 1;

		FATEnt* entires = new FATEnt[n]();

		for (uint8_t i = 0; i < n; i++)
		{
			entires[i] = ents[index];

			if (i < (n - 1)) index++;

			if (index >= info->entriesPerSec)
			{
				fatDisk->CalcNextSector(clust, sector);
				if (0 != sector)
				{
					fatDisk->ReadOneSector((char*)ents, sector);
					index = 0;
				}
				else
				{
					delete[] entires;
					delete data;
					return name;
				}
			}
		}

		name = fatName->GetLongName(entires);

		delete[] entires;
	}
	//Get short name
	else
	{
		name = fatName->GetShortName(&ents[index]);
	}

	return name;
}


/// @brief Search path
/// @param path 
/// @return 
FatEntry::DirEntry* FatEntry::SearchPath(const char* path, int forward)
{
	Regex regex;
	regex.Split(path, '/');
	char** dirNames = regex.ToArray();
	int8_t dirIndex = regex.Size() - forward;
	
	DirEntry* entry = NULL;

	if (dirIndex <= 1)
	{
		entry = new DirEntry();
		entry->dir.sfn.attr = _ATTR_DIRECTORY;
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
FatEntry::DirEntry* FatEntry::SearchDir(DirEntry* entry, const char* dir)
{
	DirData*   data   = new DirData();
	FATEnt*&   ents   = data->ents;
	uint32_t&  index  = data->index;
	uint32_t&  clust  = data->clust;
	uint32_t&  sector = data->sector;
	
	//Allocate the dirEntires space
	ents = (FATEnt*)new char[dbr->bpb.bytesPerSec]();

	//Calculate the dir cluster and sector
	fatDisk->CalcFirstSector(entry, clust, sector);

	//Search target dir
	while (0 != sector)
	{
		fatDisk->ReadOneSector((char*)ents, sector);

		for (index = 0; index < info->entriesPerSec; index++)
		{
			if ((ents[index].lfn.ord != dir_free_flag) &&
				(ents[index].lfn.ord != 0))
			{
				char* dirname = GetEntryName(data);

				if (0 == strcmp(dirname, dir))
				{
					DirEntry* found = new DirEntry(ents[index], dirname);
					delete data;
					return found;
				}
			}
		}

		fatDisk->CalcNextSector(clust, sector);
	}

	delete data;
	return NULL;
}


/// @brief Create file
/// @param entry 
/// @param name 
/// @return 
FatEntry::DirEntry* FatEntry::CreateFile(DirEntry* entry, const char* name)
{
	//Open parent directory
	DirData*   pare   = OpenDir(entry);
	FATEnt*&   ents   = pare->ents;
	uint32_t&  index  = pare->index;
	uint32_t&  clust  = pare->clust;
	uint32_t&  sector = pare->sector;
	int        attr   = _ATTR_FILE;

	//Calculate the dir cluster and sector
	fatDisk->CalcFirstSector(entry, clust, sector);

	//Set entry name
	if (_OK == SetEntryName(pare, name, attr))
	{
		return new DirEntry(ents[index], (char*)name);
	}

	return NULL;
}


/// @brief Create directory
/// @param entry 
/// @param name 
/// @return 
FatEntry::DirData* FatEntry::CreateDir(DirEntry* entry, const char* name)
{
	//Open parent directory
	DirData*   pare   = OpenDir(entry);
	uint32_t&  clust  = pare->clust;
	uint32_t&  sector = pare->sector;
	int        attr   = _ATTR_DIRECTORY;

	//Calculate the dir cluster and sector
	fatDisk->CalcFirstSector(entry, clust, sector);

	//Set entry name
	if (_OK == SetEntryName(pare, name, attr))
	{
		
	}

	return NULL;
}


/// @brief Open dir
/// @param entry 
/// @return 
FatEntry::DirData* FatEntry::OpenDir(DirEntry* entry)
{
	DirData*   data   = new DirData();
	FATEnt*&   ents   = data->ents;
	uint32_t&  index  = data->index;
	uint32_t&  clust  = data->clust;
	uint32_t&  sector = data->sector;

	//Allocate the dir entires space
	ents = (FATEnt*)new char[dbr->bpb.bytesPerSec]();

	//Calculate the dir cluster and sector
	fatDisk->CalcFirstSector(entry, clust, sector);

	//Search target dir
	while (0 != sector)
	{
		fatDisk->ReadOneSector((char*)ents, sector);

		for (index = 0; index < info->entriesPerSec; index++)
		{
			if ((ents[index].lfn.ord != dir_free_flag) &&
				(ents[index].lfn.ord != 0))
			{
				char* dirname = GetEntryName(data);

				if (0 != strcmp(dirname, ""))
				{
					DirEntry* found = new DirEntry(ents[index], dirname);

					if (IsFile(found) || IsDirectory(found))
					{
						data->dirs.Add(found);
						data->size++;
					}
					else delete found;
				}
			}
		}

		fatDisk->CalcNextSector(clust, sector);
	}

	//Set dir begin
	data->dirs.Begin();

	return data;
}


/// @brief Get volume label
/// @return 
char* FatEntry::GetVolumeLabel()
{
	uint32_t  clust  = 0;
	uint32_t  sector = 0;

	//Allocate the dir entires space
	FATEnt* ents = (FATEnt*)new char[dbr->bpb.bytesPerSec]();

	//Calculate the dir cluster and sector
	fatDisk->CalcFirstSector(NULL, clust, sector);

	//Read ents data
	fatDisk->ReadOneSector((char*)ents, sector);

	//Get volume label
	char* label = IsVolume(&ents[0]) ? fatName->GetVolumeLabel(&ents[0]) : (char*)"NONAME";

	//Free ents
	delete[] ents;

	return label;
}


/// @brief Set volume label
/// @param name 
/// @return 
int FatEntry::SetVolumeLabel(const char* name)
{
	uint32_t  clust  = 0;
	uint32_t  sector = 0;

	//Allocate the dir entires space
	FATEnt* ents = (FATEnt*)new char[dbr->bpb.bytesPerSec]();

	//Calculate the dir cluster and sector
	fatDisk->CalcFirstSector(NULL, clust, sector);

	//Read ents data
	fatDisk->ReadOneSector((char*)ents, sector);

	//Check is volume entry
	if (IsVolume(&ents[0]))
	{
		//Set volume label
		fatName->SetVolumeLabel(&ents[0], name);

		//Update volume label to disk
		fatDisk->WriteOneSector((char*)ents, sector);
	}
	 
	//Free ents
	delete[] ents;

	return _OK;
}
