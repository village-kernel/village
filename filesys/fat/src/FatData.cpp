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
char* FatData::GetDirName(FatEntry* data)
{
	char* name = NULL;

	UnionEntry* entry = data->Item();

	if (entry->IsValid())
	{
		uint8_t size = entry->IsLongName() ? entry->OrdSize() : 1;
		UnionEntry* entries = new UnionEntry[size]();

		if (data->Pop(entries, size) == size)
		{
			if (entries->IsLongName())
				name = fatName.GetLongName(entries);
			else
				name = fatName.GetShortName(entries);
		}
		
		delete[] entries;
	}

	return name;
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
		dirent->root = true;
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
/// @param entry 
/// @param dir 
/// @return 
FatData::DirEntry* FatData::SearchDir(DirEntry* dirent, const char* dir)
{
	FatEntry* data  = new FatEntry(&fatDisk, info, dirent);
	DirEntry* found = NULL;

	for (data->Begin(); !data->IsEnd(); data->Next())
	{
		char* name = GetDirName(data);

		if (NULL != name && 0 == strcmp(name, dir))
		{
			found = new DirEntry(*data->Item(), name);
			break;
		}
	}

	delete data;
	return found;
}


/// @brief Open dir
/// @param entry 
/// @return 
FatData::DirEntries* FatData::OpenDir(DirEntry* dirent)
{
	FatEntry*   data    = new FatEntry(&fatDisk, info, dirent);
	DirEntries* dirents = new DirEntries();

	for (data->Begin(); !data->IsEnd(); data->Next())
	{
		char* name = GetDirName(data);

		if (NULL != name && 0 != strcmp(name, ""))
		{
			UnionEntry* entry = data->Item();
			if (entry->IsFile() || entry->IsDirectory())
			{
				dirents->dirs.Add(new DirEntry(*entry, name));
			}
		}
	}

	dirents->dirs.Begin();

	delete data;
	return dirents;
}


/// @brief 
/// @param dirent 
/// @param name 
/// @param entries 
/// @param num 
/// @return 
FatEntry* FatData::CreateEntry(DirEntry* dirent, const char* name, UnionEntry*& entries, uint8_t& num)
{
	DirEntries* dirents = OpenDir(dirent);
	FatEntry*   data    = new FatEntry(&fatDisk, info, dirent);

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
	entries = new UnionEntry[num + 1]();

	//Set short name
	fatName.SetShortName(&entries[num], name);

	//Set long name
	if (isNameLoss)
	{
		entries[num].sfe.NTRes |= _NS_LOSS;

		for (uint8_t i = 1; i < 100; i++)
		{
			fatName.GenNumName(entries + num, i);
			if (_OK == dirents->CheckConflict(entries + num)) break;
		}

		entries[0].lfe.ord = num + dir_seq_flag;
		fatName.SetLongName(entries, name);
	}

	return data;
}


/// @brief Create file
/// @param entry 
/// @param name 
/// @return 
FatData::DirEntry* FatData::CreateFile(DirEntry* dirent, const char* name)
{
	uint8_t     num  = 0;
	UnionEntry* entries = NULL;
	FatEntry*   data = CreateEntry(dirent, name, entries, num);

	//Set entry attr
	entries[num].sfe.attr = _ATTR_FILE;

	//Put to disk
	uint8_t size = num + 1;
	if (_OK == data->FindSpace(size) && 
		size == data->Push(entries, size))
	{
		return new DirEntry(entries[num], (char*)name);
	}

	return NULL;
}


/// @brief Create directory
/// @param entry 
/// @param name 
/// @return 
FatData::DirEntries* FatData::CreateDir(DirEntry* dirent, const char* name)
{
	uint8_t     num = 0;
	UnionEntry* entries = NULL;
	FatEntry*   data = CreateEntry(dirent, name, entries, num);

	uint32_t clust = fatDisk.AllocCluster(1);

	//Set entry attr
	entries[num].sfe.attr = _ATTR_DIRECTORY;
	entries[num].sfe.fstClustHI = (clust >> 16) & 0xffff;
	entries[num].sfe.fstClustLO = (clust >> 0)  & 0xffff;

	//Put to disk
	uint8_t size = num + 1;
	if (_OK == data->FindSpace(size) && 
		size == data->Push(entries, size))
	{
		UnionEntry* dirs = new UnionEntry[2]();
		dirs[0].sfe = entries[num].sfe;
		dirs[1].sfe = dirent->body.sfe;

		dirs[0].sfe.attr |= _ATTR_HIDDEN;
		dirs[1].sfe.attr |= _ATTR_HIDDEN;

		memcpy(dirs[0].sfe.name, ".          ", 11);
		memcpy(dirs[1].sfe.name, "..         ", 11);

		DirEntry* dir = new DirEntry(entries[num], (char*)name);
		FatEntry* child = new FatEntry(&fatDisk, info, dir);
		child->Push(dirs, 2);
		delete child;
		delete[] dirs;

		return OpenDir(dir);
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
	FatEntry*   data  = new FatEntry(&fatDisk, info, NULL);
	UnionEntry* entry = data->Item();

	char* label = (char*)"NONAME";

	//Check is volume entry
	if (entry->IsVolume())
	{
		//Get volume label
		label = fatName.GetVolumeLabel(entry);
	}

	delete data;
	return label;
}


/// @brief Set volume label
/// @param name 
/// @return 
int FatData::SetVolumeLabel(const char* name)
{
	FatEntry*  data   = new FatEntry(&fatDisk, info, NULL);
	UnionEntry* entry = data->Item();

	//Check is volume entry
	if (entry->IsVolume())
	{
		//Set volume label
		fatName.SetVolumeLabel(entry, name);

		//Push ent to disk
		data->Push(entry);
	}
	
	delete data;
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
/// @param data 
/// @return 
FatData::DirEntry* FatData::ReadDir(DirEntries* data)
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
int FatData::SizeDir(DirEntries* data)
{
	return data->dirs.GetSize();
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
