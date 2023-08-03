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


/// @brief 
/// @param dirSecNum 
/// @param dirSecSize 
FAT::DirEntry* FAT::ReadDir(DirEntry* entry, const char* dirName)
{
	char*    name = NULL;
	uint32_t clus = (NULL == entry) ? fat->rootClus : MergeCluster(entry->sdir.fstClusHI, entry->sdir.fstClusLO);
	uint32_t maxEntires = dbr->bpb.secPerClus * dbr->bpb.bytsPerSec / dir_entry_size;

	DirEntry* dirEntires = (DirEntry*)new char[dbr->bpb.secPerClus * dbr->bpb.bytsPerSec]();

	for (uint32_t readClus = clus; 0 != readClus; readClus = CalcNextCluster(readClus))
	{
		ReadCluster((char*)dirEntires, 1, clus);

		for (uint32_t idx = 0; idx < maxEntires; idx++)
		{	
			if (dirEntires[idx].ldir.ord != dir_free_flag)
			{
				if ((dirEntires[idx].ldir.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
				{
					uint8_t n = dirEntires[idx].ldir.ord - dir_seq_flag;

					DirEntry* tmpDirEntires = new DirEntry[n + 1]();

					for (uint8_t ndx = 0; ndx <= n; ndx++)
					{
						if (idx >= maxEntires)
						{
							readClus = CalcNextCluster(readClus);
							if (0 != readClus)
							{
								ReadCluster((char*)dirEntires, 1, readClus);
								idx = 0;
							}
						}

						tmpDirEntires[ndx] = dirEntires[idx++];
					}

					idx -= 1;

					name = GetLongName(tmpDirEntires);

					delete[] tmpDirEntires;
				}
				else
				{
					name = GetShortName(dirEntires + idx);
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
	}

	delete[] dirEntires;
	return NULL;
}


/// @brief 
/// @param dirSecNum 
/// @param dirSecSize 
FAT::DirEntry* FAT::ReadRootDir(const char* dirName)
{
	char* name = NULL;

	uint32_t dirRootSec = fat->firstRootDirSecNum;
	uint32_t dirEndSec = fat->rootDirSectors + dirRootSec;
	uint32_t maxEntires = dbr->bpb.bytsPerSec / dir_entry_size;

	DirEntry* dirEntires = (DirEntry*)new char[dbr->bpb.bytsPerSec]();

	for (uint32_t dirSecNum = dirRootSec; dirSecNum < dirEndSec; dirSecNum++)
	{
		ReadSector((char*)dirEntires, 1, dirSecNum);

		for (uint32_t idx = 0; idx < maxEntires; idx++)
		{
			if (dirEntires[idx].ldir.ord != dir_free_flag)	
			{
				if ((dirEntires[idx].ldir.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
				{
					uint8_t n = dirEntires[idx].ldir.ord - dir_seq_flag;

					DirEntry* tmpDirEntires = new DirEntry[n + 1]();

					for (uint8_t ndx = 0; ndx <= n; ndx++)
					{
						if ((idx >= maxEntires) && (++dirSecNum < dirEndSec))
						{
							ReadSector((char*)dirEntires, 1, dirSecNum);
							idx = 0;
						}

						tmpDirEntires[ndx] = dirEntires[idx++];
					}

					idx -= 1;

					name = GetLongName(tmpDirEntires);

					delete[] tmpDirEntires;
				}
				else
				{
					name = GetShortName(dirEntires + idx);
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
	}

	delete[] dirEntires;
	return NULL;
}


/// @brief 
/// @param name 
/// @return 
FAT::DirEntry* FAT::SearchDir(const char* path)
{
	regex.Split(path, '/');
	char**  dirNames = regex.ToArray();
	uint8_t dirIndex = regex.Size();
	
	DirEntry* entry;

	for (uint8_t i = 0; i < dirIndex; i++)
	{
		if (0 == i)
		{
			if (_FAT16 == fat->type)
				entry = ReadRootDir(dirNames[i]);
			else
				entry = ReadDir(entry, dirNames[i]);
		}
		else
		{
			entry = ReadDir(entry, dirNames[i]);
		}

		if (NULL == entry)
		{
			debug.Output(Debug::_Lv2, "%s file not found", path);
			return NULL;
		}
	}

	return entry;
}
