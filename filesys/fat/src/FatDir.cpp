//###########################################################################
// FATDir.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"
#include "Debug.h"


///// @brief 
///// @param dir 
//int FAT::ListDir(FATSDir* dir)
//{
//	return _OK;
//}


///// @brief 
///// @param dir 
//int FAT::CheckDir(FATSDir* dir)
//{
//	if ((dir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == 0x00)
//	{
//		//Found a file
//	}
//	else if ((dir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_DIRECTORY)
//	{
//		//Found a directory
//	}
//	else if ((dir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_VOLUME_ID)
//	{
//		//Found a volume label
//	}
//	else
//	{
//		//Found an invalid directory entry
//	}
//	return _ERR;
//}


/// @brief Search dir
/// @param entry 
/// @param dirName 
/// @return 
FAT::DirEntry* FAT::SearchDir(DirEntry* entry, const char* dirName)
{
	char* name = NULL;
	uint32_t dirCluster = 0;
	uint32_t dirSecNum  = 0;

	//Calculate the dir cluster and sector
	if (NULL == entry)
	{
		dirCluster = (_FAT16 == fat->type) ? 0 : fat->rootClus;
		dirSecNum  = (_FAT16 == fat->type) ? fat->firstRootDirSecNum : 0;
	}
	else
	{
		dirCluster = MergeCluster(entry->sdir.fstClusHI, entry->sdir.fstClusLO);
		dirSecNum  = ClusterToSector(dirCluster);
	}

	//Calculate max size of dir entries
	uint32_t maxDirEntires = dbr->bpb.bytsPerSec / dir_entry_size;

	//Allocate the dirEntires space
	DirEntry* dirEntires = (DirEntry*)new char[dbr->bpb.bytsPerSec]();

	//Search target dir
	while (0 != dirSecNum)
	{
		ReadSector((char*)dirEntires, 1, dirSecNum);

		for (uint32_t idx = 0; idx < maxDirEntires; idx++)
		{
			if (dirEntires[idx].ldir.ord != dir_free_flag)	
			{
				if ((dirEntires[idx].ldir.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
				{
					uint8_t n = dirEntires[idx].ldir.ord - dir_seq_flag;

					FATLDir* ldirs = new FATLDir[n]();

					for (uint8_t ndx = 0; ndx < n; ndx++)
					{
						ldirs[ndx] = dirEntires[idx++].ldir;

						if (idx >= maxDirEntires)
						{
							CalcNextSector(dirCluster, dirSecNum);
							if (0 != dirSecNum)
							{
								ReadSector((char*)dirEntires, 1, dirSecNum);
								idx = 0;
							}
							else
							{
								delete[] dirEntires;
								delete[] ldirs;
								return NULL;
							}
						}
					}

					name = GetLongName(ldirs, &dirEntires[idx].sdir);

					delete[] ldirs;
				}
				else
				{
					name = GetShortName(&dirEntires[idx].sdir);
				}

				if (0 == strcmp(name, dirName))
				{
					DirEntry* found = new DirEntry();
					*found = dirEntires[idx];
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
