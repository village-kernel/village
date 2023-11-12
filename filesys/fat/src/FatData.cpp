//###########################################################################
// FatData.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatData.h"
#include "Regex.h"
#include "Debug.h"


/// @brief Setup
/// @param diskdrv 
/// @param fstSec 
/// @return 
int FatData::Setup(Driver* diskdrv, uint32_t fstSec)
{
	this->dbr  = new DBR();
	this->info = new Info();
	
	fatDisk.Setup(diskdrv, fstSec, info);

	if (_ERR == ReadDBR())
	{
		debug.Error("Not DBR found");
		return _ERR;
	}

	if (_ERR == CheckFS())
	{
		debug.Error("Not filesystem found");
		return _ERR;
	}

	fatEntry.Setup(&fatDisk, info);

	return _OK;
}


/// @brief Read DBR
/// @return 
int FatData::ReadDBR()
{
	static const uint8_t dbr_sector = 0;

	if (NULL != dbr)
	{
		fatDisk.ReadOneSector((char*)dbr, dbr_sector);
		
		if (magic == dbr->magic) return _OK;
	}

	return _ERR;
}


/// @brief Check fs
/// @return 
int FatData::CheckFS()
{
	if (NULL != info)
	{
		//Calc fat size
		if (0 != dbr->bpb.FATSz16)
			info->fatSize = dbr->bpb.FATSz16;
		else
			info->fatSize = dbr->fat32.FATSz32;
		
		//Calc total sectors
		if (0 != dbr->bpb.totSec16)
			info->totalSectors = dbr->bpb.totSec16;
		else
			info->totalSectors = dbr->bpb.totSec32;

		//Calc rsvd sector count
		info->rsvdSecCnt = dbr->bpb.rsvdSecCnt;

		//Calc the sector number of start/ended of FAT
		info->startOfFatSector = dbr->bpb.rsvdSecCnt;
		info->endedOfFatSector = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * info->fatSize) - 1;

		//Calc fat12/16 root dir sector
		info->firstRootSector = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * info->fatSize);
		info->countOfRootSecs = ((dbr->bpb.rootEntCnt * dir_entry_size) + (dbr->bpb.bytesPerSec - 1)) / dbr->bpb.bytesPerSec;
		
		//Calc fat data sector
		info->firstDataSector = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * info->fatSize) + info->countOfRootSecs;
		info->countOfDataSecs = info->totalSectors - (dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * info->fatSize) - info->countOfRootSecs);

		//Calc counts of clusters
		info->countOfClusters = info->countOfDataSecs / dbr->bpb.secPerClust;

		//Detected fat type
		if (info->countOfClusters < 4085)
			info->fatType = _FAT12;
		else if (info->countOfClusters < 65525)
			info->fatType = _FAT16;
		else
			info->fatType = _FAT32;

		//Fat32 root cluster
		info->rootClust = (_FAT32 == info->fatType) ? dbr->fat32.rootClust : 0;

		//Calc the info data
		info->entriesPerSec = dbr->bpb.bytesPerSec / dir_entry_size;
		info->bytesPerSec = dbr->bpb.bytesPerSec;
		info->secPerClust = dbr->bpb.secPerClust;

		return _OK;
	}

	return _ERR;
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
	
	DirEntry* dirent = new DirEntry();

	if (dirIndex <= 1)
	{
		dirent->body.sfe.attr = _ATTR_DIRECTORY;
		dirent->name = (char*)"/";
		return dirent;
	}

	for (int8_t i = 1; i < dirIndex; i++)
	{
		dirent = SearchDir(dirent, dirNames[i]);
		if (NULL == dirent->name) return NULL;
	}

	return dirent;
}


/// @brief Search dir
/// @param dirent 
/// @param dir 
/// @return 
FatData::DirEntry* FatData::SearchDir(DirEntry* dirent, const char* dir)
{
	DirEntry* found = NULL;

	while (NULL != (found = fatEntry.Read(dirent)))
	{
		if (0 != strcmp(found->name, dir))
			delete found;
		else
			break;
	}

	return found;
}


/// @brief Open dir
/// @param dirent 
/// @return 
FatData::DirEntries* FatData::OpenDir(DirEntry* dirent)
{
	if (NULL == dirent) return NULL;

	DirEntries* dirents = new DirEntries();
	DirEntry*   found   = NULL;

	while (NULL != (found = fatEntry.Read(dirent)))
	{
		if (found->body.IsFile() || found->body.IsDirectory())
			dirents->list.Add(found);
		else
			delete found;
	}

	dirents->list.Begin();

	return dirents;
}


/// @brief Create file
/// @param path 
/// @return 
FatData::DirEntry* FatData::CreateFile(const char* path)
{
	DirEntry* dirent = SearchPath(path, 1);
	
	if (NULL == dirent) return NULL;
	
	if (dirent->body.IsDirectory())
	{
		return fatEntry.Create(dirent, NotDir(path), _ATTR_FILE);
	}

	return NULL;
}


/// @brief Create dir
/// @param path 
/// @return 
FatData::DirEntries* FatData::CreateDir(const char* path)
{
	DirEntry* dirent = SearchPath(path, 1);
	
	if (NULL == dirent) return NULL;
	
	if (dirent->body.IsDirectory())
	{
		DirEntries* found = OpenDir(fatEntry.Create(dirent, NotDir(path), _ATTR_DIRECTORY));
		found->path = (char*)path;
		return found;
	}

	return NULL;
}


/// @brief Get volume label
/// @return 
char* FatData::GetVolumeLabel()
{
	DirEntry* dirent = fatEntry.Read(new DirEntry());

	char* label = (char*)"NONAME";

	//Check is volume entry
	if (dirent->body.IsVolume())
	{
		//Get volume label
		label = fatName.GetVolumeLabel(dirent->self.unients);
	}

	return label;
}


/// @brief Set volume label
/// @param name 
/// @return 
int FatData::SetVolumeLabel(const char* name)
{
	DirEntry* dirent = fatEntry.Read(new DirEntry());

	//Check is volume entry
	if (dirent->body.IsVolume())
	{
		//Set volume label
		fatName.SetVolumeLabel(dirent->self.unients, name);

		//Push ent to disk
		fatEntry.Update(dirent);
	}
	
	return _OK;
}


/// @brief Open
/// @param name 
/// @param mode 
/// @return 
FatData::DirEntry* FatData::Open(const char* name, int mode)
{
	DirEntry* dirent = SearchPath(name);

	if (NULL == dirent)
	{
		if ((mode & _CreateNew) == _CreateNew)
		{
			return CreateFile(name);
		}
	}

	return dirent;
}


/// @brief Write
/// @param data 
/// @param size 
/// @param entry 
/// @return 
int FatData::Write(char* data, uint32_t size, DirEntry* dirent)
{
	bool isDone = false;
	uint32_t fileSize = dirent->body.sfe.fileSize;
	uint32_t bytesPerSec = info->bytesPerSec;
	uint32_t secPerClust = info->secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstClust = fatDisk.GetFirstClust(dirent->body.sfe);

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	memcpy((void*)allocBuff, (const void*)data, size);

	if (clusSize == fatDisk.WriteCluster(allocBuff, clusSize, fstClust)) isDone = true;

	delete[] allocBuff;
	return isDone ? size : 0;
}


/// @brief Read
/// @param data 
/// @param dir 
/// @return 
int FatData::Read(char* data, uint32_t size, DirEntry* dirent)
{
	bool isDone = false;
	uint32_t fileSize = dirent->body.sfe.fileSize;
	uint32_t bytesPerSec = info->bytesPerSec;
	uint32_t secPerClust = info->secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstClust = fatDisk.GetFirstClust(dirent->body.sfe);

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	if (clusSize == fatDisk.ReadCluster(allocBuff, clusSize, fstClust))
	{
		memcpy((void*)data, (const void*)allocBuff, size);
		isDone = true;
	}

	delete[] allocBuff;
	return isDone ? size : 0;
}


/// @brief Size
/// @param dir 
/// @return 
int FatData::Size(DirEntry* dirent)
{
	return dirent->body.sfe.fileSize;
}


/// @brief Open dir
/// @param dirName 
/// @return 
FatData::DirEntries* FatData::OpenDir(const char* path, int mode)
{
	DirEntry* dirent = SearchPath(path);
	
	if (NULL == dirent)
	{
		if ((mode & _CreateNew) == _CreateNew)
			return CreateDir(path);
		else
			return NULL;
	}
	
	if (dirent->body.IsDirectory())
	{
		DirEntries* found = OpenDir(dirent);
		found->path = (char*)path;
		return found;
	}

	return NULL;
}


/// @brief Read dir
/// @param dirents 
/// @return 
FatData::DirEntry* FatData::ReadDir(DirEntries* dirents)
{
	if (false == dirents->list.IsEnd())
	{
		DirEntry* dirent = dirents->list.Item();
		dirents->list.Next();
		return dirent;
	}
	return NULL;
}


/// @brief Size dir
/// @param dirents 
/// @return 
int FatData::SizeDir(DirEntries* dirents)
{
	return dirents->list.GetSize();
}


/// @brief Move
/// @param from 
/// @param to 
/// @return 
int FatData::Move(const char* from, const char* to)
{
	return _OK;
}


/// @brief Copy
/// @param from 
/// @param to 
/// @return 
int FatData::Copy(const char* from, const char* to)
{
	return _OK;
}


/// @brief Remove
/// @param name 
/// @return 
int FatData::Remove(const char* name)
{
	DirEntry* dirent = SearchPath(name);
	
	for (uint8_t i = 0; i < dirent->self.size; i++)
	{
		dirent->self.unients[i].lfe.ord = dir_free_flag;
	}

	fatEntry.Update(dirent);

	return _OK;
}


/// @brief MoveDir
/// @param from 
/// @param to 
/// @return 
int FatData::MoveDir(const char* from, const char* to)
{
	return _OK;
}


/// @brief CopyDir
/// @param from 
/// @param to 
/// @return 
int FatData::CopyDir(const char* from, const char* to)
{
	return _OK;
}


/// @brief RemoveDir
/// @param name 
/// @return 
int FatData::RemoveDir(const char* name)
{
	return _OK;
}
