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
	this->dbr      = new DBR();
	this->info     = new Info();
	
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


/// @brief Search path
/// @param path 
/// @return 
FatData::DirEntry* FatData::SearchPath(const char* path, int forward)
{
	Regex regex;
	regex.Split(path, '/');
	char** dirNames = regex.ToArray();
	int8_t dirIndex = regex.Size() - forward;
	
	DirEntry* entry = NULL;

	if (dirIndex <= 1)
	{
		entry = new DirEntry();
		entry->body.attr = _ATTR_DIRECTORY;
		entry->root = true;
		entry->name = (char*)"/";
		return entry;
	}

	for (uint8_t i = 1; i < dirIndex; i++)
	{
		entry = SearchDir(entry, dirNames[i]);

		if (NULL == entry) return NULL;
	}

	return entry;
}


/// @brief Search dir
/// @param entry 
/// @param dir 
/// @return 
FatData::DirEntry* FatData::SearchDir(DirEntry* entry, const char* dir)
{
	FatEntry* data  = new FatEntry(&fatDisk, info, entry);
	DirEntry* found = NULL;

	for (data->Begin(); !data->IsEnd(); data->Next())
	{
		if (!data->IsValid()) continue;
		
		uint8_t size = data->Item()->IsLongName() ? data->GetSize() : 1;
		FATEnt* ents = new FATEnt[size]();
		if (data->Pop(ents, size) != size) break;
		
		char* dirname = NULL;
		if (ents[0].IsLongName())
			dirname = fatName.GetLongName(ents);
		else
			dirname = fatName.GetShortName(ents);

		if (0 == strcmp(dirname, dir))
		{
			found = new DirEntry(ents[size - 1].sfn, dirname);
			delete[] ents;
			break;
		}

		delete[] ents;
	}

	delete data;
	return found;
}


/// @brief Open dir
/// @param entry 
/// @return 
FatData::DirEntries* FatData::OpenDir(DirEntry* entry)
{
	FatEntry*   data    = new FatEntry(&fatDisk, info, entry);
	DirEntries* entries = new DirEntries();

	for (data->Begin(); !data->IsEnd(); data->Next())
	{
		if (!data->IsValid()) continue;
		
		uint8_t size = data->Item()->IsLongName() ? data->GetSize() : 1;
		FATEnt* ents = new FATEnt[size]();
		if (data->Pop(ents, size) != size) break;
		
		char* dirname = NULL;
		if (ents->IsLongName())
			dirname = fatName.GetLongName(ents);
		else
			dirname = fatName.GetShortName(ents);

		if (0 != strcmp(dirname, ""))
		{
			FATEnt* ent = &ents[size- 1];
			if (ent->sfn.IsFile() || ent->sfn.IsDirectory())
			{
				entries->dirs.Add(new DirEntry(ent->sfn, dirname));
			}
		}

		delete[] ents;
	}

	entries->dirs.Begin();

	delete data;
	return entries;
}


/// @brief 
/// @param entry 
/// @param ents 
/// @param name 
/// @return 
FatEntry* FatData::CreateEntry(DirEntry* entry, const char* name, FATEnt*& ents, uint8_t& num)
{
	DirEntries* entries = OpenDir(entry);
	FatEntry*   data    = new FatEntry(&fatDisk, info, entry);

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
	ents = new FATEnt[num + 1]();

	//Set short name
	fatName.SetShortName(&ents[num], name);

	//Set long name
	if (isNameLoss)
	{
		ents[num].sfn.NTRes |= _NS_LOSS;

		for (uint8_t i = 1; i < 100; i++)
		{
			fatName.GenNumName(ents + num, i);
			if (_OK == entries->CheckConflict(ents + num)) break;
		}

		ents[0].lfn.ord = num + dir_seq_flag;
		fatName.SetLongName(ents, name);
	}

	return data;
}


/// @brief Create file
/// @param entry 
/// @param name 
/// @return 
FatData::DirEntry* FatData::CreateFile(DirEntry* entry, const char* name)
{
	uint8_t   num  = 0;
	FATEnt*   ents = NULL;
	FatEntry* data = CreateEntry(entry, name, ents, num);

	//Set entry attr
	ents[num].sfn.attr = _ATTR_FILE;

	//Put to disk
	uint8_t size = num + 1;
	if (_OK == data->FindSpace(size) && 
		size == data->Push(ents, size))
	{
		return new DirEntry(ents[num].sfn, (char*)name);
	}

	return NULL;
}


/// @brief Create directory
/// @param entry 
/// @param name 
/// @return 
FatData::DirEntries* FatData::CreateDir(DirEntry* entry, const char* name)
{
	uint8_t   num = 0;
	FATEnt*   ents = NULL;
	FatEntry* data = CreateEntry(entry, name, ents, num);

	uint32_t clust = fatDisk.AllocCluster(1);

	//Set entry attr
	ents[num].sfn.attr = _ATTR_DIRECTORY;
	ents[num].sfn.fstClustHI = (clust >> 16) & 0xffff;
	ents[num].sfn.fstClustLO = (clust >> 0)  & 0xffff;

	//Put to disk
	uint8_t size = num + 1;
	if (_OK == data->FindSpace(size) && 
		size == data->Push(ents, size))
	{
		FATEnt* dirs = new FATEnt[2]();
		dirs[0].sfn = ents[num].sfn;
		dirs[1].sfn = entry->body;

		dirs[0].sfn.attr |= _ATTR_HIDDEN;
		dirs[1].sfn.attr |= _ATTR_HIDDEN;

		memcpy(dirs[0].sfn.name, ".          ", 11);
		memcpy(dirs[1].sfn.name, "..         ", 11);

		DirEntry* dir = new DirEntry(ents[num].sfn, (char*)name);
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
	DirEntry* dir = SearchPath(path, 1);
	
	if (NULL == dir) return NULL;
	
	if (dir->body.IsDirectory())
	{
		return CreateFile(dir, NotDir(path));
	}

	return NULL;
}


/// @brief Create dir
/// @param path 
/// @return 
FatData::DirEntries* FatData::CreateDir(const char* path)
{
	DirEntry* dir = SearchPath(path, 1);
	
	if (NULL == dir) return NULL;
	
	if (dir->body.IsDirectory())
	{
		DirEntries* found = CreateDir(dir, NotDir(path));
		found->path = (char*)path;
		return found;
	}

	return NULL;
}


/// @brief Get volume label
/// @return 
char* FatData::GetVolumeLabel()
{
	FatEntry* data = new FatEntry(&fatDisk, info, NULL);
	FATEnt*   ent  = data->Item();

	char* label = (char*)"NONAME";

	//Check is volume entry
	if (ent->sfn.IsVolume())
	{
		//Get volume label
		label = fatName.GetVolumeLabel(ent);
	}

	delete data;
	return label;
}


/// @brief Set volume label
/// @param name 
/// @return 
int FatData::SetVolumeLabel(const char* name)
{
	FatEntry* data = new FatEntry(&fatDisk, info, NULL);
	FATEnt*   ent  = data->Item();

	//Check is volume entry
	if (ent->sfn.IsVolume())
	{
		//Set volume label
		fatName.SetVolumeLabel(ent, name);

		//Push ent to disk
		data->Push(ent);
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
	DirEntry* dir = SearchPath(name);

	if (NULL == dir)
	{
		if ((mode & _CreateNew) == _CreateNew)
		{
			return CreateFile(name);
		}
	}

	return dir;
}


/// @brief Write
/// @param data 
/// @param size 
/// @param entry 
/// @return 
int FatData::Write(char* data, uint32_t size, DirEntry* entry)
{
	bool isDone = false;
	uint32_t fileSize = entry->body.fileSize;
	uint32_t bytesPerSec = info->bytesPerSec;
	uint32_t secPerClust = info->secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstCluster = fatDisk.MergeCluster(entry->body.fstClustHI, entry->body.fstClustLO);

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	memcpy((void*)allocBuff, (const void*)data, size);

	if (clusSize == fatDisk.WriteCluster(allocBuff, clusSize, fstCluster)) isDone = true;

	delete[] allocBuff;
	return isDone ? size : 0;
}


/// @brief Read
/// @param data 
/// @param dir 
/// @return 
int FatData::Read(char* data, uint32_t size, DirEntry* entry)
{
	bool isDone = false;
	uint32_t fileSize = entry->body.fileSize;
	uint32_t bytesPerSec = info->bytesPerSec;
	uint32_t secPerClust = info->secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstCluster = fatDisk.MergeCluster(entry->body.fstClustHI, entry->body.fstClustLO);

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	if (clusSize == fatDisk.ReadCluster(allocBuff, clusSize, fstCluster))
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
int FatData::Size(DirEntry* entry)
{
	return entry->body.fileSize;
}


/// @brief Open dir
/// @param dirName 
/// @return 
FatData::DirEntries* FatData::OpenDir(const char* path, int mode)
{
	DirEntry* dir = SearchPath(path);
	
	if (NULL == dir)
	{
		if ((mode & _CreateNew) == _CreateNew)
			return CreateDir(path);
		else
			return NULL;
	}
	
	if (dir->body.IsDirectory())
	{
		DirEntries* found = OpenDir(dir);
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
