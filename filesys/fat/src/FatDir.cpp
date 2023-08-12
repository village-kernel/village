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
	return ((entry->sdir.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == attr) ? _OK : _ERR;
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
	DirData*   data    = new DirData();
	DirEntry*& entries = data->entries;
	uint32_t&  index   = data->index;
	uint32_t&  clust   = data->clust;
	uint32_t&  sector  = data->sector;
	
	//Allocate the dirEntires space
	entries = (DirEntry*)new char[dbr->bpb.bytesPerSec]();

	//Calculate the dir cluster and sector
	disk.CalcFirstSector(entry, clust, sector);

	//Search target dir
	while (0 != sector)
	{
		disk.ReadOneSector((char*)entries, sector);

		for (index = 0; index < fat->entriesPerSec; index++)
		{
			if (entries[index].ldir.ord != dir_free_flag)	
			{
				char* dirname = name.GetDirName(data);

				if (0 == strcmp(dirname, dir))
				{
					DirEntry* found = new DirEntry(entries[index]);
					delete data;
					return found;
				}

				delete[] dirname;
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
FatDir::DirEntry* FatDir::OpenDir(const char* path)
{
	DirEntry* dir = SearchPath(path);
	
	if (NULL == dir) return NULL;
	
	if (_OK == CheckDir(dir, _ATTR_DIRECTORY))
	{
		OpenDir(dir);
		return dir;
	}
	return NULL;
}


/// @brief 
/// @param entry 
/// @return 
FatDir::DirEntry* FatDir::OpenDir(DirEntry* entry)
{
	DirData*   data    = new DirData();
	DirEntry*& entries = data->entries;
	uint32_t&  index   = data->index;
	uint32_t&  clust   = data->clust;
	uint32_t&  sector  = data->sector;

	//Allocate the dirEntires space
	entries = (DirEntry*)new char[dbr->bpb.bytesPerSec]();

	//Calculate the dir cluster and sector
	disk.CalcFirstSector(entry, clust, sector);

	//Search target dir
	while (0 != sector)
	{
		disk.ReadOneSector((char*)entries, sector);

		for (index = 0; index < fat->entriesPerSec; index++)
		{
			if (entries[index].ldir.ord != dir_free_flag)	
			{
				char* dirname = name.GetDirName(data);

				if (0 != strcmp(dirname, ""))
				{
					dirs.InsertByName(new DirEntry(entries[index]), dirname);
				}
			}
		}

		disk.CalcNextSector(clust, sector);
	}

	delete data;
	return NULL;
}


/// @brief 
/// @param entry 
/// @return 
FatDir::DirEntry* FatDir::ReadDir(DirEntry* entry)
{
	return NULL;
}


/// @brief 
/// @param entry 
void FatDir::CloseDir(DirEntry* entry)
{

}


void FatDir::Test()
{
	ReadDir(OpenDir("libraries"));
	
	for (DirEntry* entry = dirs.Begin(); !dirs.IsEnd(); entry = dirs.Next())
	{
		debug.Output(Debug::_Lv2, dirs.GetName());
	}
}
