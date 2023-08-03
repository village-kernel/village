//###########################################################################
// FATDir.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"
#include "Debug.h"


char* FAT::GetDirEntry(uint32_t clus, uint32_t index, uint32_t size)
{
	static char* secBuff = new char[dbr->bpb.bytsPerSec]();
	static uint32_t secNum = 0;

	if (0 == (index * dir_entry_size) % dbr->bpb.bytsPerSec)
	{
		//if (0 != (index * dir_entry_size) / dbr->bpb.bytsPerSec)
		//{
		//	clus = CalcNextCluster(clus);
		//	if (0 == clus) return NULL;
		//}

		secNum = ClusterToSector(clus);
		ReadSector(secBuff, 1, secNum++);
	}

	uint32_t remaining = dbr->bpb.bytsPerSec - (index * dir_entry_size);
	uint32_t allocSize = size * dir_entry_size;
	char* allocBuff = new char[allocSize]();
	char* tmpBuff = secBuff + (index * dir_entry_size);

	if (allocSize > remaining)
	{
		memcpy((void*)allocBuff, (const void*)tmpBuff, remaining);
		
		ReadSector(secBuff, 1, secNum++);
		
		tmpBuff = secBuff;
		
		uint32_t read = allocSize - remaining;

		if (read) memcpy((void*)(allocBuff + remaining), (const void*)tmpBuff, read);
	}
	else
	{
		memcpy((void*)allocBuff, (const void*)tmpBuff, allocSize);
	}

	return allocBuff;
}


/// @brief 
/// @param dir 
//int FAT::ListDir(FATSDir* dir)
//{
//	if ((dir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_DIRECTORY)
//	{
//		char*    name = NULL;
//		FATLDir* ldir = NULL;
//		FATSDir* sdir = NULL;
//		uint32_t idx  = 0;
//		uint32_t clus = MergeCluster(dir->fstClusHI, dir->fstClusLO);
		
//		while (1)
//		{
//			ldir = (FATLDir*)GetDirEntry(clus, idx++, 1);

//			if (NULL == ldir) break;

//			if (ldir->ord != dir_free_flag)
//			{
//				if ((ldir->attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
//				{
//					uint8_t n = ldir->ord - dir_seq_flag;
//					ldir = (FATLDir*)GetDirEntry(clus, idx -= 1, n);
//					sdir = (FATSDir*)GetDirEntry(clus, idx += n, 1);
//					name = GetLongName(ldir, sdir);
//				}
//				else
//				{
//					sdir = (FATSDir*)ldir;
//					name = GetShortName(sdir);
//				}

//				debug.Output(Debug::_Lv2, name);
//			}
//		}
//	}

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
	
	DirEntry* dirEntires = (DirEntry*)new char[dbr->bpb.secPerClus * dbr->bpb.bytsPerSec]();

	ReadCluster((char*)dirEntires, 1, clus);

	for (uint32_t idx = 0; idx < 64; idx++)
	{	
		if (dirEntires[idx].ldir.ord != dir_free_flag)
		{
			if ((dirEntires[idx].ldir.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
			{
				uint8_t n = dirEntires[idx].ldir.ord - dir_seq_flag;
				name = GetLongName(dirEntires + idx);
				idx += n;
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

	delete[] dirEntires;
	return NULL;
}


/// @brief 
/// @param dirSecNum 
/// @param dirSecSize 
FAT::DirEntry* FAT::ReadRootDir(const char* readDir)
{
	char* secBuff = new char[dbr->bpb.bytsPerSec]();
	char* name = NULL;

	uint32_t dirSecNum = fat->firstRootDirSecNum;
	uint32_t dirSecSize = fat->rootDirSectors;

	for (uint32_t sec = 0; sec < dirSecSize; sec++)
	{
		ReadSector(secBuff, 1, dirSecNum + sec);
		char* tmpBuff = secBuff;

		while (((uint32_t)tmpBuff - (uint32_t)secBuff) < dbr->bpb.bytsPerSec)
		{
			FATLDir* ldir = (FATLDir*)(tmpBuff);
			
			//Found an active long name sub-component.
			if (((ldir->attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME) && (ldir->ord != dir_free_flag))
			{
				uint8_t  n = ldir->ord - dir_seq_flag;
				uint32_t allocSize = (n + 1) * dir_entry_size;
				DirEntry* allocBuff = (DirEntry*)new char[allocSize]();
				
				uint32_t remaining = dbr->bpb.bytsPerSec - ((uint32_t)tmpBuff - (uint32_t)secBuff);

				if (allocSize > remaining)
				{
					memcpy((void*)allocBuff, (const void*)tmpBuff, remaining);
					
					sec++; ReadSector(secBuff, 1, dirSecNum + sec); tmpBuff = secBuff;
					
					uint32_t read = allocSize - remaining;
					if (read) memcpy((void*)(allocBuff + remaining), (const void*)tmpBuff, read);
					
					tmpBuff += read;
				}
				else
				{
					memcpy((void*)allocBuff, (const void*)tmpBuff, allocSize);
					tmpBuff += allocSize;
				}

				name = GetLongName(allocBuff);
				
				if (0 == strcmp(name, readDir))
				{
					DirEntry* entry = new DirEntry();
					*entry = allocBuff[n];
					delete[] name;
					delete[] secBuff;
					delete[] allocBuff;
					return entry;
				}

				delete[] name;
				delete[] allocBuff;
			}
			else
			{
				if ((ldir->ord != 0) && (ldir->ord != dir_free_flag))
				{
					DirEntry* entry = (DirEntry*)(tmpBuff);

					name = GetShortName(entry);

					if (0 == strcmp(name, readDir))
					{
						DirEntry* found = new DirEntry();
						*found = *entry;
						delete[] name;
						delete[] secBuff;
						return found;
					}

					delete[] name;
				}

				tmpBuff += dir_entry_size;
			}
		}
	}

	delete[] secBuff;
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
