//###########################################################################
// FAT.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"
#include "FatSystem.h"
#include "Kernel.h"
#include "Debug.h"
#include "stdio.h"


/// @brief Constructor
FAT::FAT()
{
}


/// @brief Destructor
FAT::~FAT()
{
}


/// @brief Setup
void FAT::Setup()
{
	mbr     = new MBR();
	dbr     = new DBR();
	info    = new Info();
	
	fatDisk = new FatDisk();
	fatName = new FatName();
	fatDir  = new FatDir();
	fatFile = new FatFile();

	diskdrv = device.GetDriver(DriverID::_storage + 1);

	fatDisk->Setup(this);
	fatName->Setup(this);
	fatDir->Setup(this);
	fatFile->Setup(this);
	
	if (NULL == diskdrv)
	{
		debug.Error("Not disk driver found");
		return;
	}

	if (_ERR == ReadMBR())
	{
		debug.Error("Not a valid disk");
		return;
	}

	if (_ERR == ReadDBR())
	{
		debug.Error("Not DBR found");
		return;
	}

	if (_ERR == CheckFS())
	{
		debug.Error("Not filesystem found");
		return;
	}

	debug.Output(Debug::_Lv2, "Fat setup done");
}


/// @brief FAT exit
void FAT::Exit()
{
	delete mbr;
	delete dbr;
	delete info;
	
	delete fatDisk;
	delete fatName;
	delete fatDir;
	delete fatFile;
}


/// @brief Read MBR
int FAT::ReadMBR()
{
	static const uint8_t mbr_sector = 0;

	if (NULL != mbr)
	{
		diskdrv->Read((uint8_t*)mbr, 1, mbr_sector);

		if (magic == mbr->magic) return _OK;
	}

	return _ERR;
}


/// @brief Read DBR
/// @return 
int FAT::ReadDBR()
{
	static const uint8_t dbr_sector = 1;

	if (NULL != dbr)
	{
		diskdrv->Read((uint8_t*)dbr, 1, dbr_sector);
		
		if (magic == dbr->magic) return _OK;
	}

	return _ERR;
}


/// @brief Check fs
/// @return 
int FAT::CheckFS()
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

		//Calc the start sector
		info->startSector = mbr->dpt[0].relativeSectors;

		return _OK;
	}

	return _ERR;
}


/// @brief FAT mount
/// @return 
int FAT::Mount(const char* path, const char* mount, int opt)
{
	debug.Output(Debug::_Lv2, "%s -> %s mount successful", path, mount);

	return _OK;
}


/// @brief FAT unmount
/// @return 
int FAT::Unmount(const char* mount)
{
	return _OK;
}


/// @brief FAT open
/// @param name 
/// @param mode 
/// @return 
int FAT::Open(const char* name, int mode)
{
	DirEntry* entry = fatFile->Open(name, mode);
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
int FAT::Write(int fd, char* data, int size, int offset)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatFile->Write(data, size, entry);
	}
	return -1;
}


/// @brief FAT read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FAT::Read(int fd, char* data, int size, int offset)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatFile->Read(data, size, entry);
	}
	return -1;
}


/// @brief FAT size
/// @return 
int FAT::Size(int fd)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatFile->Size(entry);
	}
	return 0;
}


/// @brief FAT close
/// @return 
void FAT::Close(int fd)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		files.Remove(entry, fd);
	}
}


/// @brief 
/// @param dirname 
/// @return 
int FAT::OpenDir(const char* name, int mode)
{
	DirData* data = fatDir->Open(name, mode);
	if (NULL != data)
	{
		return dirs.Add(data);
	}
	return -1;
}


/// @brief Get file type
/// @param entry 
/// @return file type
FileType FAT::GetFileType(DirEntry* entry)
{
	if (fatDir->IsFile(entry))
		return FileType::_File;
	else if (fatDir->IsDirectory(entry))
		return FileType::_Diretory;
	else if (fatDir->IsVolume(entry))
		return FileType::_Volume;
	else
		return FileType::_Unknown;
}


/// @brief Get file attr
/// @param entry 
/// @return file attr
FileAttr FAT::GetFileAttr(DirEntry* entry)
{
	return fatDir->IsHidden(entry) ? FileAttr::_Hidden : FileAttr::_Visible;
}


/// @brief 
/// @param fd 
/// @param data 
/// @return 
int FAT::ReadDir(int fd, FileDir* dirs, int size, int offset)
{
	DirData* data = this->dirs.GetItem(fd);
	
	if (NULL != data)
	{
		for (int i = 0; i < size; i++)
		{
			DirEntry* ent = fatDir->Read(data);
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
int FAT::SizeDir(int fd)
{
	DirData* data = dirs.GetItem(fd);
	if (NULL != data)
	{
		return fatDir->Size(data);
	}
	return -1;
}


/// @brief Close dir
/// @param fd 
/// @return 
void FAT::CloseDir(int fd)
{
	DirData* data = dirs.GetItem(fd);
	if (NULL != data)
	{
		dirs.Remove(data, fd);
	}
}


/// @brief FAT rename
/// @param old 
/// @param now 
/// @return 
int FAT::Rename(int fd, const char* old, const char* now)
{
	return 0;
}


/// @brief FAT copy
/// @param from 
/// @param to 
/// @return 
int FAT::Copy(int fd, const char* from, const char* to)
{
	return 0;
}


/// @brief FAT remove
/// @return 
int FAT::Remove(int fd)
{
	return 0;
}


///Register file system
REGISTER_FS(new FAT(), fat);
