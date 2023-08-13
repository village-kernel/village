//###########################################################################
// FatDir.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatDir.h"
#include "Debug.h"
#include "Regex.h"


/// @brief 
/// @param fat 
/// @param dbr 
/// @param startSector 
void FatDir::Initialize(FATData* fat, FATDBR* dbr, uint32_t startSector)
{
	this->dbr = dbr;
	this->fat = fat;
	disk.Initialize(fat, dbr, startSector);
	name.Initialize(fat, dbr, startSector);
}


/// @brief 
/// @param dir 
int FatDir::CheckDir(DirEntry* entry, DirAttr attr)
{
	return ((entry->dir.sdir.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == attr) ? _OK : _ERR;
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

	for (uint8_t i = 0; i < dirIndex; i++)
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
	disk.CalcFirstSector(entry, clust, sector);

	//Search target dir
	while (0 != sector)
	{
		disk.ReadOneSector((char*)ents, sector);

		for (index = 0; index < fat->entriesPerSec; index++)
		{
			if (ents[index].ldir.ord != dir_free_flag)
			{
				char* dirname = name.GetDirName(data);

				if (0 == strcmp(dirname, dir))
				{
					DirEntry* found = new DirEntry(ents[index], dirname);
					delete data;
					return found;
				}
			}
		}

		disk.CalcNextSector(clust, sector);
	}

	delete data;
	return NULL;
}


/// @brief 
/// @param dirName 
/// @return 
FatDir::DirData* FatDir::OpenDir(const char* path)
{
	DirEntry* dir = SearchPath(path);
	
	if (NULL == dir) return NULL;
	
	if (_OK == CheckDir(dir, _ATTR_DIRECTORY))
	{
		return OpenDir(dir);
	}
	return NULL;
}


/// @brief 
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
	disk.CalcFirstSector(entry, clust, sector);

	//Search target dir
	while (0 != sector)
	{
		disk.ReadOneSector((char*)ents, sector);

		for (index = 0; index < fat->entriesPerSec; index++)
		{
			if (ents[index].ldir.ord != dir_free_flag)	
			{
				char* dirname = name.GetDirName(data);

				if (0 != strcmp(dirname, ""))
				{
					data->dirs.InsertByName(new DirEntry(ents[index], dirname), dirname);
				}
			}
		}

		disk.CalcNextSector(clust, sector);
	}

	//Set dir begin
	data->dirs.Begin();

	return data;
}


/// @brief 
/// @param data 
/// @return 
FatDir::DirEntry* FatDir::ReadDir(DirData* data)
{
	if (false == data->dirs.IsEnd())
	{
		DirEntry* ent = data->dirs.Item();
		data->dirs.Next();
		return ent;
	}
	return NULL;
}


/// @brief 
/// @param entry 
void FatDir::CloseDir(DirData* data)
{
	delete data;
}


void FatDir::Test()
{
	DirData* dirp = OpenDir("libraries");
	DirEntry* dp = NULL;
	
	if (dirp == NULL) return;

	while ((dp = ReadDir(dirp)) != NULL)
	{
		debug.Output(Debug::_Lv2, dp->name);
	}

	CloseDir(dirp);
}
