//###########################################################################
// FATDir.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"
#include "Debug.h"


/// @brief 
/// @param dir 
int FAT::CheckDir(DirEntry* entry, DIRAttr attr)
{
	return ((entry->sdir.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == attr) ? _OK : _ERR;
}


/// @brief Search path
/// @param name 
/// @return 
FAT::DirEntry* FAT::SearchPath(const char* path)
{
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


/// @brief 
/// @param entries 
/// @param idx 
/// @param clust 
/// @param sector 
/// @return 
char* FAT::GetDirName(DirEntry* entries, uint32_t& idx, uint32_t& clust, uint32_t& sector)
{
	char* name = NULL;

	if ((entries[idx].ldir.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
	{
		uint32_t maxDirEntires = dbr->bpb.bytsPerSec / dir_entry_size;

		uint8_t n = entries[idx].ldir.ord - dir_seq_flag;

		FATLDir* ldirs = new FATLDir[n]();

		for (uint8_t ndx = 0; ndx < n; ndx++)
		{
			ldirs[ndx] = entries[idx++].ldir;

			if (idx >= maxDirEntires)
			{
				CalcNextSector(clust, sector);
				if (0 != sector)
				{
					ReadOneSector((char*)entries, sector);
					idx = 0;
				}
				else
				{
					delete[] entries;
					delete[] ldirs;
					return NULL;
				}
			}
		}

		name = GetLongName(ldirs, &entries[idx].sdir);

		delete[] ldirs;
	}
	else
	{
		name = GetShortName(&entries[idx].sdir);
	}

	return name;
}


/// @brief Search dir
/// @param entry 
/// @param dirName 
/// @return 
FAT::DirEntry* FAT::SearchDir(DirEntry* entry, const char* dirName)
{
	char* name = NULL;
	uint32_t dirCluster = 0;
	uint32_t dirSecNum  = 0;

	//Calculate max size of dir entries
	uint32_t maxDirEntires = dbr->bpb.bytsPerSec / dir_entry_size;

	//Allocate the dirEntires space
	DirEntry* dirEntires = (DirEntry*)new char[dbr->bpb.bytsPerSec]();

	//Calculate the dir cluster and sector
	CalcFirstSector(entry, dirCluster, dirSecNum);

	//Search target dir
	while (0 != dirSecNum)
	{
		ReadOneSector((char*)dirEntires, dirSecNum);

		for (uint32_t idx = 0; idx < maxDirEntires; idx++)
		{
			if (dirEntires[idx].ldir.ord != dir_free_flag)	
			{
				name = GetDirName(dirEntires, idx, dirCluster, dirSecNum);

				if (0 == strcmp(name, dirName))
				{
					DirEntry* found = new DirEntry(dirEntires[idx]);
					delete[] dirEntires;
					delete[] name;
					return found;
				}

				delete[] name;
			}
		}

		CalcNextSector(dirCluster, dirSecNum);
	}

	delete[] dirEntires;
	return NULL;
}


/// @brief 
/// @param dirName 
/// @return 
FAT::DirEntry* FAT::OpenDir(const char* path)
{
	DirEntry* dir = SearchPath(path);
	if (NULL != dir)
	{
		if (_OK == CheckDir(dir, _ATTR_DIRECTORY)) return dir;
	}
	return NULL;
}


/// @brief 
/// @param entry 
/// @return 
FAT::DirEntry* FAT::ReadDir(DirEntry* entry)
{
	char* name = NULL;
	uint32_t dirCluster = 0;
	uint32_t dirSecNum  = 0;

	//Calculate max size of dir entries
	uint32_t maxDirEntires = dbr->bpb.bytsPerSec / dir_entry_size;

	//Allocate the dirEntires space
	DirEntry* dirEntires = (DirEntry*)new char[dbr->bpb.bytsPerSec]();

	//Calculate the dir cluster and sector
	CalcFirstSector(entry, dirCluster, dirSecNum);

	//Search target dir
	while (0 != dirSecNum)
	{
		ReadOneSector((char*)dirEntires, dirSecNum);

		for (uint32_t idx = 0; idx < maxDirEntires; idx++)
		{
			if (dirEntires[idx].ldir.ord != dir_free_flag)	
			{
				name = GetDirName(dirEntires, idx, dirCluster, dirSecNum);

				if (0 != strcmp(name, ""))
				{
					dirs.InsertByName(new DirEntry(dirEntires[idx]), name);
				}
			}
		}

		CalcNextSector(dirCluster, dirSecNum);
	}

	delete[] dirEntires;
	return NULL;
}


/// @brief 
/// @param entry 
void FAT::CloseDir(DirEntry* entry)
{

}
