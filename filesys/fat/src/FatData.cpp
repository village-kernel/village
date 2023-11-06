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


/// @brief Get dir name
/// @return name
char* FatData::GetDirName(FatEntry* entry)
{
	char* name = NULL;

	UnionEntry* unient = entry->Item();

	if (unient->IsValid())
	{
		uint8_t size = unient->IsLongName() ? unient->OrdSize() : 1;
		UnionEntry* unients = new UnionEntry[size]();

		if (entry->Pop(unients, size) == size)
		{
			if (unients->IsLongName())
				name = fatName.GetLongName(unients);
			else
				name = fatName.GetShortName(unients);
		}
		
		delete[] unients;
	}

	return name;
}


/// @brief Check dir name
/// @param dirents 
/// @param entry 
/// @return 
int FatData::CheckDirName(DirEntries* dirents, UnionEntry* entry)
{
	uint8_t count = 0;
	for (DirEntry* dir = dirents->dirs.Begin(); !dirents->dirs.IsEnd(); dir = dirents->dirs.Next())
	{
		for (uint8_t i = 0; i < 11; i++)
		{
			if (dir->body.sfe.name[i] != entry->sfe.name[i])
			{
				count++; break;
			}
		}
	}
	return (dirents->dirs.GetSize() == count) ? _OK : _ERR;
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
	
	DirEntry* dirent = NULL;

	if (dirIndex <= 1)
	{
		dirent = new DirEntry();
		dirent->body.sfe.attr = _ATTR_DIRECTORY;
		dirent->name = (char*)"/";
		return dirent;
	}

	for (uint8_t i = 1; i < dirIndex; i++)
	{
		dirent = SearchDir(dirent, dirNames[i]);

		if (NULL == dirent) return NULL;
	}

	return dirent;
}


/// @brief Search dir
/// @param dirent 
/// @param dir 
/// @return 
FatData::DirEntry* FatData::SearchDir(DirEntry* dirent, const char* dir)
{
	FatEntry* entry = new FatEntry(&fatDisk, info, dirent);
	DirEntry* found = NULL;

	for (entry->Begin(); !entry->IsEnd(); entry->Next())
	{
		char* name = GetDirName(entry);

		if (NULL != name && 0 == strcmp(name, dir))
		{
			found = new DirEntry(*entry->Item(), name);
			break;
		}
	}

	delete entry;
	return found;
}


/// @brief Open dir
/// @param dirent 
/// @return 
FatData::DirEntries* FatData::OpenDir(DirEntry* dirent)
{
	FatEntry*   entry   = new FatEntry(&fatDisk, info, dirent);
	DirEntries* dirents = new DirEntries();

	for (entry->Begin(); !entry->IsEnd(); entry->Next())
	{
		char* name = GetDirName(entry);

		if (NULL != name && 0 != strcmp(name, ""))
		{
			UnionEntry* unient = entry->Item();
			if (unient->IsFile() || unient->IsDirectory())
			{
				dirents->dirs.Add(new DirEntry(*unient, name));
			}
		}
	}

	dirents->dirs.Begin();

	delete entry;
	return dirents;
}


/// @brief 
/// @param dirent 
/// @param name 
/// @param entries 
/// @param num 
/// @return 
FatData::UnionEntry* FatData::CreateEntry(DirEntry* dirent, const char* name, uint8_t& num)
{
	DirEntries* dirents = OpenDir(dirent);

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
	UnionEntry* unients = new UnionEntry[num + 1]();

	//Set short name
	fatName.SetShortName(&unients[num], name);

	//Set long name
	if (isNameLoss)
	{
		unients[num].sfe.NTRes |= _NS_LOSS;

		for (uint8_t i = 1; i < 100; i++)
		{
			fatName.GenNumName(unients + num, i);
			if (_OK == CheckDirName(dirents, unients + num)) break;
		}

		unients[0].lfe.ord = num + dir_seq_flag;
		fatName.SetLongName(unients, name);
	}

	return unients;
}


/// @brief Create file
/// @param dirent 
/// @param name 
/// @return 
FatData::DirEntry* FatData::CreateFile(DirEntry* dirent, const char* name)
{
	uint8_t     num  = 0;
	UnionEntry* unients = CreateEntry(dirent, name, num);
	FatEntry*   entry = new FatEntry(&fatDisk, info, dirent);

	//Set entry attr
	unients[num].sfe.attr = _ATTR_FILE;

	//Put to disk
	uint8_t size = num + 1;
	if (_OK == entry->FindSpace(size) && 
		size == entry->Push(unients, size))
	{
		return new DirEntry(unients[num], (char*)name);
	}

	return NULL;
}


/// @brief Create directory
/// @param dirent 
/// @param name 
/// @return 
FatData::DirEntries* FatData::CreateDir(DirEntry* dirent, const char* name)
{
	uint8_t     num = 0;
	UnionEntry* unients = CreateEntry(dirent, name, num);
	FatEntry*   entry = new FatEntry(&fatDisk, info, dirent);

	uint32_t clust = fatDisk.AllocCluster(1);

	//Set entry attr
	unients[num].sfe.attr = _ATTR_DIRECTORY;
	unients[num].sfe.fstClustHI = (clust >> 16) & 0xffff;
	unients[num].sfe.fstClustLO = (clust >> 0)  & 0xffff;

	//Put to disk
	uint8_t size = num + 1;
	if (_OK == entry->FindSpace(size) && 
		size == entry->Push(unients, size))
	{
		UnionEntry* childUnients = new UnionEntry[2]();
		childUnients[0].sfe = childUnients[num].sfe;
		childUnients[1].sfe = dirent->body.sfe;

		childUnients[0].sfe.attr |= _ATTR_HIDDEN;
		childUnients[1].sfe.attr |= _ATTR_HIDDEN;

		memcpy(childUnients[0].sfe.name, ".          ", 11);
		memcpy(childUnients[1].sfe.name, "..         ", 11);

		DirEntry* childDirent = new DirEntry(childUnients[num], (char*)name);
		FatEntry* childEntry  = new FatEntry(&fatDisk, info, childDirent);
		childEntry->Push(childUnients, 2);

		delete childEntry;
		delete[] childUnients;

		return OpenDir(childDirent);
	}

	return NULL;
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
		return CreateFile(dirent, NotDir(path));
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
		DirEntries* found = CreateDir(dirent, NotDir(path));
		found->path = (char*)path;
		return found;
	}

	return NULL;
}


/// @brief Get volume label
/// @return 
char* FatData::GetVolumeLabel()
{
	FatEntry*   entry  = new FatEntry(&fatDisk, info, NULL);
	UnionEntry* unient = entry->Item();

	char* label = (char*)"NONAME";

	//Check is volume entry
	if (unient->IsVolume())
	{
		//Get volume label
		label = fatName.GetVolumeLabel(unient);
	}

	delete entry;
	return label;
}


/// @brief Set volume label
/// @param name 
/// @return 
int FatData::SetVolumeLabel(const char* name)
{
	FatEntry*   entry  = new FatEntry(&fatDisk, info, NULL);
	UnionEntry* unient = entry->Item();

	//Check is volume entry
	if (unient->IsVolume())
	{
		//Set volume label
		fatName.SetVolumeLabel(unient, name);

		//Push ent to disk
		entry->Push(unient);
	}
	
	delete entry;
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
	if (false == dirents->dirs.IsEnd())
	{
		DirEntry* dirent = dirents->dirs.Item();
		dirents->dirs.Next();
		return dirent;
	}
	return NULL;
}


/// @brief Size dir
/// @param dirents 
/// @return 
int FatData::SizeDir(DirEntries* dirents)
{
	return dirents->dirs.GetSize();
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
