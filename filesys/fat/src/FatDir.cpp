//###########################################################################
// FatDir.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatDir.h"
#include "FatDisk.h"
#include "FatName.h"
#include "Debug.h"
#include "Regex.h"


/// @brief 
/// @param entry 
/// @return 
inline bool FatDir::IsHidden(FATEnt* entry)
{
	return ((entry->sdir.attr & _ATTR_HIDDEN) == _ATTR_HIDDEN);
}


/// @brief 
/// @param entry 
/// @return 
bool FatDir::IsHidden(DirEntry* entry)
{
	return IsHidden(&entry->dir);
}


/// @brief 
/// @param entry 
/// @return 
inline bool FatDir::IsDirectory(FATEnt* entry)
{
	return ((entry->sdir.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_DIRECTORY);
}


/// @brief 
/// @param entry 
/// @return 
bool FatDir::IsDirectory(DirEntry* entry)
{
	return IsDirectory(&entry->dir);
}


/// @brief 
/// @param entry 
/// @return 
inline bool FatDir::IsVolume(FATEnt* entry)
{
	return ((entry->sdir.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_VOLUME_ID);
}


/// @brief 
/// @param entry 
/// @return 
bool FatDir::IsVolume(DirEntry* entry)
{
	return IsVolume(&entry->dir);
}


/// @brief 
/// @param entry 
/// @return 
inline bool FatDir::IsFile(FATEnt* entry)
{
	return ((entry->sdir.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_FILE);
}


/// @brief 
/// @param entry 
/// @return 
bool FatDir::IsFile(DirEntry* entry)
{
	return IsFile(&entry->dir);
}


/// @brief Search path
/// @param path 
/// @return 
FatDir::DirEntry* FatDir::SearchPath(const char* path)
{
	Regex regex;
	regex.Split(path, '/');
	char**  dirNames = regex.ToArray();
	uint8_t dirIndex = regex.Size();
	
	DirEntry* entry = NULL;

	if (dirIndex <= 1)
	{
		entry = new DirEntry();
		entry->dir.sdir.attr = _ATTR_DIRECTORY;
		entry->root = true;
		entry->name = (char*)"/";
		return entry;
	}

	for (uint8_t i = 1; i < dirIndex; i++)
	{
		entry = SearchDir(entry, dirNames[i]);

		if (NULL == entry)
		{
			debug.Output(Debug::_Lv2, "%s file not found", path);
			return NULL;
		}
	}

	return entry;
}


/// @brief Search dir
/// @param entry 
/// @param dir 
/// @return 
FatDir::DirEntry* FatDir::SearchDir(DirEntry* entry, const char* dir)
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
			if (ents[index].ldir.ord != dir_free_flag)
			{
				char* dirname = fatName->GetDirName(data);

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


/// @brief Open dir
/// @param entry 
/// @return 
FatDir::DirData* FatDir::OpenDir(DirEntry* entry)
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
			if (ents[index].ldir.ord != dir_free_flag)
			{
				char* dirname = fatName->GetDirName(data);

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


/// @brief 
/// @return 
char* FatDir::GetVolumeLabel()
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
	char* label = IsVolume(&ents[0]) ? fatName->GetVolumeLabel(&ents[0].sdir) : (char*)"NONAME";

	//Free ents
	delete[] ents;

	return label;
}


/// @brief 
/// @param name 
/// @return 
int FatDir::SetVolumeLabel(const char* name)
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
		fatName->SetVolumeLabel(&ents[0].sdir, name);

		//Update volume label to disk
		fatDisk->WriteOneSector((char*)ents, sector);
	}
	 
	//Free ents
	delete[] ents;

	return _OK;
}



/// @brief Open dir
/// @param dirName 
/// @return 
FatDir::DirData* FatDir::Open(const char* path, int mode)
{
	DirEntry* dir = SearchPath(path);
	
	if (NULL == dir) return NULL;
	
	if (IsDirectory(dir))
	{
		DirData* found = OpenDir(dir);
		found->path = (char*)path;
		return found;
	}
	return NULL;
}


/// @brief Read dir
/// @param data 
/// @return 
FatDir::DirEntry* FatDir::Read(DirData* data)
{
	if (false == data->dirs.IsEnd())
	{
		DirEntry* ent = data->dirs.Item();
		data->dirs.Next();
		return ent;
	}
	return NULL;
}


/// @brief Size dir
/// @param data 
/// @return 
int FatDir::Size(DirData* data)
{
	return data->size;
}


/// @brief Close dir
/// @param entry 
void FatDir::Close(DirData* data)
{
	delete data;
}
