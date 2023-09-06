//###########################################################################
// FatOpts.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatOpts.h"
#include "Kernel.h"
#include "Debug.h"
#include "stdio.h"


/// @brief Constructor
FatOpts::FatOpts()
{
}


/// @brief Destructor
FatOpts::~FatOpts()
{
	Exit();
}


/// @brief Setup
/// @param dat 
/// @return result
int FatOpts::Setup(FatObjs* dat)
{
	FatObjs::Clone(dat);
	
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


/// @brief Exit
void FatOpts::Exit()
{
	files.Release();
	dirs.Release();
}


/// @brief Read DBR
/// @return 
int FatOpts::ReadDBR()
{
	static const uint8_t dbr_sector = 0;

	if (NULL != dbr)
	{
		fatDisk->ReadOneSector((char*)dbr, dbr_sector);
		
		if (magic == dbr->magic) return _OK;
	}

	return _ERR;
}


/// @brief Check fs
/// @return 
int FatOpts::CheckFS()
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

		//Calc the entries per sector
		info->entriesPerSec = dbr->bpb.bytesPerSec / dir_entry_size;

		return _OK;
	}

	return _ERR;
}


/// @brief FAT mount
/// @return 
int FatOpts::Mount(const char* path, const char* mount, int opt)
{
	return _OK;
}


/// @brief FAT unmount
/// @return 
int FatOpts::Unmount(const char* mount)
{
	return _OK;
}


/// @brief Set volume label
/// @param name 
/// @return 
int FatOpts::SetVolumeLabel(const char* name)
{
	return fatData->SetVolumeLabel(name);
}


/// @brief Get volume label
/// @return 
char* FatOpts::GetVolumeLabel()
{
	return fatData->GetVolumeLabel();
}


/// @brief FAT open
/// @param name 
/// @param mode 
/// @return 
int FatOpts::Open(const char* name, int mode)
{
	DirEntry* entry = fatData->Open(name, mode);
	if (NULL != entry)
	{
		return files.Add(entry);
	}
	return -1;
}


/// @brief FAT write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatOpts::Write(int fd, char* data, int size, int offset)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatData->Write(data, size, entry);
	}
	return -1;
}


/// @brief FAT read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatOpts::Read(int fd, char* data, int size, int offset)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatData->Read(data, size, entry);
	}
	return -1;
}


/// @brief FAT size
/// @return 
int FatOpts::Size(int fd)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatData->Size(entry);
	}
	return 0;
}


/// @brief FAT close
/// @return 
void FatOpts::Close(int fd)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		files.Remove(entry, fd);
	}
}


/// @brief Open directory
/// @param name
/// @param mode 
/// @return 
int FatOpts::OpenDir(const char* name, int mode)
{
	DirEntries* data = fatData->OpenDir(name, mode);
	if (NULL != data)
	{
		return dirs.Add(data);
	}
	return -1;
}


/// @brief Get file type
/// @param entry 
/// @return file type
FileType FatOpts::GetFileType(DirEntry* entry)
{
	if (entry->body.IsFile())
		return FileType::_File;
	else if (entry->body.IsDirectory())
		return FileType::_Diretory;
	else if (entry->body.IsVolume())
		return FileType::_Volume;
	else
		return FileType::_Unknown;
}


/// @brief Get file attr
/// @param entry 
/// @return file attr
FileAttr FatOpts::GetFileAttr(DirEntry* entry)
{
	return entry->body.IsHidden() ? FileAttr::_Hidden : FileAttr::_Visible;
}


/// @brief Read directory
/// @param fd 
/// @param data 
/// @return 
int FatOpts::ReadDir(int fd, FileDir* dirs, int size, int offset)
{
	DirEntries* data = this->dirs.GetItem(fd);
	
	if (NULL != data)
	{
		for (int i = 0; i < size; i++)
		{
			DirEntry* ent = fatData->ReadDir(data);
			if (NULL != ent)
			{
				char* path = new char[strlen(data->path) + strlen(ent->name) + 2]();
				sprintf(path, "%s/%s", data->path, ent->name);
				dirs[i].path = path;
				dirs[i].name = ent->name;
				dirs[i].type = GetFileType(ent);
				dirs[i].attr = GetFileAttr(ent);
			}
			else return i;
		}
	}
	else return 0;

	return size;
}


/// @brief Size dir
/// @param fd 
/// @return 
int FatOpts::SizeDir(int fd)
{
	DirEntries* data = dirs.GetItem(fd);
	if (NULL != data)
	{
		return fatData->SizeDir(data);
	}
	return -1;
}


/// @brief Close dir
/// @param fd 
/// @return 
void FatOpts::CloseDir(int fd)
{
	DirEntries* data = dirs.GetItem(fd);
	if (NULL != data)
	{
		dirs.Remove(data, fd);
	}
}


/// @brief FAT rename
/// @param old 
/// @param now 
/// @return 
int FatOpts::Rename(int fd, const char* old, const char* now)
{
	return 0;
}


/// @brief FAT copy
/// @param from 
/// @param to 
/// @return 
int FatOpts::Copy(int fd, const char* from, const char* to)
{
	return 0;
}


/// @brief FAT remove
/// @return 
int FatOpts::Remove(int fd)
{
	return 0;
}
