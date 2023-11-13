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
	this->dbr = new DBR();
	
	fatDisk.Setup(diskdrv, fstSec, &fatInfo);

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

	fatEntry.Setup(&fatDisk, &fatInfo);

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
	//Calc fat size
	if (0 != dbr->bpb.FATSz16)
		fatInfo.fatSize = dbr->bpb.FATSz16;
	else
		fatInfo.fatSize = dbr->fat32.FATSz32;
	
	//Calc total sectors
	if (0 != dbr->bpb.totSec16)
		fatInfo.totalSectors = dbr->bpb.totSec16;
	else
		fatInfo.totalSectors = dbr->bpb.totSec32;

	//Calc rsvd sector count
	fatInfo.rsvdSecCnt = dbr->bpb.rsvdSecCnt;

	//Calc the sector number of start/ended of FAT
	fatInfo.startOfFatSector = dbr->bpb.rsvdSecCnt;
	fatInfo.endedOfFatSector = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fatInfo.fatSize) - 1;

	//Calc fat12/16 root dir sector
	fatInfo.firstRootSector = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fatInfo.fatSize);
	fatInfo.countOfRootSecs = ((dbr->bpb.rootEntCnt * dir_entry_size) + (dbr->bpb.bytesPerSec - 1)) / dbr->bpb.bytesPerSec;
	
	//Calc fat data sector
	fatInfo.firstDataSector = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fatInfo.fatSize) + fatInfo.countOfRootSecs;
	fatInfo.countOfDataSecs = fatInfo.totalSectors - (dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fatInfo.fatSize) - fatInfo.countOfRootSecs);

	//Calc counts of clusters
	fatInfo.countOfClusters = fatInfo.countOfDataSecs / dbr->bpb.secPerClust;

	//Detected fat type
	if (fatInfo.countOfClusters < 4085)
		fatInfo.fatType = _FAT12;
	else if (fatInfo.countOfClusters < 65525)
		fatInfo.fatType = _FAT16;
	else
		fatInfo.fatType = _FAT32;

	//Fat32 root cluster
	fatInfo.rootClust = (_FAT32 == fatInfo.fatType) ? dbr->fat32.rootClust : 0;

	//Calc the info data
	fatInfo.entriesPerSec = dbr->bpb.bytesPerSec / dir_entry_size;
	fatInfo.bytesPerSec = dbr->bpb.bytesPerSec;
	fatInfo.secPerClust = dbr->bpb.secPerClust;

	return _OK;
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

	while (NULL != (found = ReadEntry(dirent)))
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

	while (NULL != (found = ReadEntry(dirent)))
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
		return CreateEntry(dirent, NotDir(path), _ATTR_FILE);
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
		DirEntries* found = OpenDir(CreateEntry(dirent, NotDir(path), _ATTR_DIRECTORY));
		found->path = (char*)path;
		return found;
	}

	return NULL;
}


/// @brief Check dir name
/// @param dirents 
/// @param entry 
/// @return 
int FatData::CheckDirName(DirEntry* dirent, UnionEntry* unient)
{
	fatEntry.ReadBegin(dirent);

	for (DirEntry* child = ReadEntry(dirent); NULL != child; child = ReadEntry(dirent))
	{
		if (0 == strncmp(child->body.sfe.name, unient->sfe.name, 11))
		{
			return _ERR;
		}
	}
	
	return _OK;
}


/// @brief 
/// @param name 
/// @param attr 
/// @return 
FatData::DirEntry* FatData::CreateEntry(DirEntry* dirent, const char* name, DirAttr attr)
{
	DirEntry* child = new DirEntry();

	//Cal the size of entries
	uint8_t namelen = strlen(name);
	uint8_t dotpos = namelen;
	while ('.' != name[--dotpos] && dotpos);
	uint8_t extlen  = dotpos ? (namelen - dotpos - 1) : 0;
	uint8_t bodylen = dotpos ? dotpos : namelen;
	bool isNameLoss = (bodylen > 8 || extlen > 3);
	uint8_t mod = (namelen % (long_name_size - 1)) ? 1 : 0;

	//Alloc entires space
	child->name         = (char*)name;
	child->self.size    = isNameLoss ? ((namelen / (long_name_size - 1)) + mod + 1) : 1;
	child->self.unients = new UnionEntry[child->self.size]();

	//Set attr and clust
	uint32_t clust         = fatDisk.AllocCluster();
	UnionEntry* unient     = &child->self.unients[child->self.size - 1];
	unient->sfe.attr       = attr;
	unient->sfe.fstClustHI = (clust >> 16) & 0xffff;
	unient->sfe.fstClustLO = (clust >> 0)  & 0xffff;

	//Set short name
	fatName.SetShortName(unient, name);

	//Set long name
	if (isNameLoss)
	{
		unient->sfe.NTRes |= _NS_LOSS;

		for (uint8_t i = 1; i < 100; i++)
		{
			fatName.GenNumName(unient, i);
			if (_OK == CheckDirName(dirent, unient)) break;
		}

		child->self.unients[0].lfe.ord = child->self.size + dir_seq_flag - 1;
		fatName.SetLongName(child->self.unients, name);
	}

	//Put to disk
	if (_OK == fatEntry.Find(dirent, child->self.size))
	{
		child->self.index  = dirent->temp.index;
		child->self.clust  = dirent->temp.clust;
		child->self.sector = dirent->temp.sector;
		child->body        = *unient;
		
		if (child->self.size == fatEntry.Push(dirent, child->self))
		{
			if ((child->body.sfe.attr & _ATTR_DIRECTORY) == _ATTR_DIRECTORY)
			{
				EntryInfo sub;
				sub.index = 0;
				sub.size  = 2;
				sub.unients = new UnionEntry[sub.size]();
				sub.unients[0].sfe = child->body.sfe;
				sub.unients[1].sfe = dirent->body.sfe;
				sub.unients[0].sfe.attr |= _ATTR_HIDDEN;
				sub.unients[1].sfe.attr |= _ATTR_HIDDEN;
				memcpy(sub.unients[0].sfe.name, ".          ", 11);
				memcpy(sub.unients[1].sfe.name, "..         ", 11);
				fatEntry.ReadBegin(child);
				fatEntry.Push(child, sub);
			}
			return child;
		}
	}

	delete child;
	return NULL;
}


/// @brief FatData read
/// @return 
FatData::DirEntry* FatData::ReadEntry(DirEntry* dirent)
{
	if (NULL == dirent->temp.unients)
		fatEntry.ReadBegin(dirent);

	if (fatEntry.IsEnded(dirent)) return NULL;

	while (!fatEntry.Item(dirent).IsValid()) 
	{
		fatEntry.ReadNext(dirent);
		if (fatEntry.IsEnded(dirent)) return NULL;
	}

	DirEntry* child      = new DirEntry();
	child->self.clust    = dirent->temp.clust;
	child->self.sector   = dirent->temp.sector;
	child->self.index    = dirent->temp.index;
	child->self.size     = fatEntry.Item(dirent).IsLongName() ? fatEntry.Item(dirent).OrdSize() : 1;
	child->self.unients  = new UnionEntry[child->self.size]();

	if (fatEntry.Pop(dirent, child->self) == child->self.size)
	{
		if (child->self.unients->IsLongName())
			child->name = fatName.GetLongName(child->self.unients);
		else
			child->name = fatName.GetShortName(child->self.unients);

		child->body = child->self.unients[child->self.size - 1];
	}

	return child;
}


/// @brief FatData Update
/// @param dirent 
/// @return 
bool FatData::UpdateEntry(DirEntry* dirent)
{
	dirent->temp.index  = dirent->self.index;
	dirent->temp.clust  = dirent->self.clust;
	dirent->temp.sector = dirent->self.sector;

	return (dirent->self.size == fatEntry.Push(dirent, dirent->self));
}


/// @brief Get volume label
/// @return 
char* FatData::GetVolumeLabel()
{
	DirEntry* dirent = ReadEntry(new DirEntry());

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
	DirEntry* dirent = ReadEntry(new DirEntry());

	//Check is volume entry
	if (dirent->body.IsVolume())
	{
		//Set volume label
		fatName.SetVolumeLabel(dirent->self.unients, name);

		//Push ent to disk
		UpdateEntry(dirent);
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
	uint32_t bytesPerSec = fatInfo.bytesPerSec;
	uint32_t secPerClust = fatInfo.secPerClust;
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
	uint32_t bytesPerSec = fatInfo.bytesPerSec;
	uint32_t secPerClust = fatInfo.secPerClust;
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

	UpdateEntry(dirent);

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
