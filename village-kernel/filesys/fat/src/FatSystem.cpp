//###########################################################################
// FAT.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"
#include "FatEntry.h"
#include "FileSys.h"
#include "Regex.h"
#include "Debug.h"
#include "Kernel.h"


/// @brief Constructor
FatVolume::FatVolume()
{
}


/// @brief Destructor
FatVolume::~FatVolume()
{
}


/// @brief FatVolume Setup
/// @param diskdrv 
/// @param fstSec 
/// @return 
bool FatVolume::Setup(DrvStream* diskdrv, uint32_t fstSec)
{
	return disk.Setup(diskdrv, fstSec);
}


/// @brief FatVolume Exit
void FatVolume::Exit()
{
	disk.Exit();
}


/// @brief Not dir
/// @param path 
/// @return 
char* FatVolume::NotDir(const char* path)
{
	uint8_t pos = strlen(path);
	char ch = 0; do { ch = path[--pos]; } while ('/' != ch && pos);
	return (char*)path + pos + 1;
}


/// @brief Search path
/// @param path 
/// @param reserve 
/// @return 
FatObject* FatVolume::SearchPath(const char* path, int reserve)
{
	FatObject* obj = NULL;

	Regex regex;
	regex.Split(path, '/');
	char** names = regex.ToArray();
	int8_t size  = regex.Size() - reserve;
	
	if (0 == size)
	{
		obj = new FatObject(new FatUnionEntry());
		obj->SetAttribute(_FAT_ATTR_DIRECTORY);
	}

	for (int8_t i = 0; i < size; i++)
	{
		obj = SearchDir(obj, names[i]);
		if (NULL == obj) return NULL;
	}

	return obj;
}


/// @brief Search dir
/// @param obj 
/// @param name
/// @return 
FatObject* FatVolume::SearchDir(FatObject* obj, const char* name)
{
	FatEntry entry(disk, obj);

	for (entry.Begin(); !entry.IsEnd(); entry.Next())
	{
		char* dirname = entry.Item()->GetObjectName();

		int isSame = strcmp(dirname, name);

		delete dirname; 
		
		if (0 == isSame)
		{
			delete obj;
			return new FatObject(entry.Item());
		}
	}

	delete obj;
	return NULL;
}


/// @brief Create dir
/// @param path 
/// @param attr 
/// @return 
FatObject* FatVolume::CreateDir(const char* path, int attr)
{
	FatObject* obj = SearchPath(path, 1);
	
	if (NULL == obj) return NULL;
	
	if (FileType::_Diretory == obj->GetObjectType())
	{
		obj = FatEntry(disk, obj).Create(NotDir(path), attr);
	}

	return obj;
}


/// @brief Set volume label
/// @param label 
/// @return 
bool FatVolume::SetVolumeLabel(const char* label)
{
	FatObject* obj = FatEntry(disk).Item();

	if (FileType::_Volume == obj->GetObjectType())
	{
		obj->SetRawName(label);

		FatEntry(disk, obj).Update();
	}

	return true;
}


/// @brief Get volume label
/// @return 
char* FatVolume::GetVolumeLabel()
{
	FatObject* obj = FatEntry(disk).Item();

	char* label = (char*)"NONAME";

	if (FileType::_Volume == obj->GetObjectType())
	{
		label = obj->GetRawName();
	}
	
	return label;
}


/// @brief Open
/// @param name 
/// @param mode 
/// @return 
int FatVolume::Open(const char* name, int mode)
{
	FatObject* obj = SearchPath(name);

	if ((NULL == obj) && ((mode & _CreateNew) == _CreateNew))
	{
		obj = CreateDir(name, _FAT_ATTR_FILE);
	}

	if (NULL == obj) return -1;

	return objs.Add(obj);
}


/// @brief Write
/// @param fd 
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::Write(int fd, char* data, int size, int offset)
{
	FatObject* obj = objs.GetItem(fd);

	if (NULL == obj) return -1;

	bool isDone = false;
	uint32_t fileSize = obj->GetFileSize();
	uint32_t bytesPerSec = disk.GetInfo().bytesPerSec;
	uint32_t secPerClust = disk.GetInfo().secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstClust = obj->GetFirstCluster();

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	memcpy((void*)allocBuff, (const void*)data, size);

	if (clusSize == disk.WriteCluster(allocBuff, fstClust, clusSize)) isDone = true;

	delete[] allocBuff;

	return isDone ? size : 0;
}


/// @brief Read
/// @param fd 
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::Read(int fd, char* data, int size, int offset)
{
	FatObject* obj = objs.GetItem(fd);

	if (NULL == obj) return -1;

	bool isDone = false;
	uint32_t fileSize = obj->GetFileSize();
	uint32_t bytesPerSec = disk.GetInfo().bytesPerSec;
	uint32_t secPerClust = disk.GetInfo().secPerClust;
	uint32_t secSize = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
	uint32_t clusSize = (secSize + (secPerClust - 1)) / secPerClust;
	uint32_t fstClust = obj->GetFirstCluster();

	char* allocBuff = (char*)new char[clusSize * secPerClust * bytesPerSec]();
	
	if (clusSize == disk.ReadCluster(allocBuff, fstClust, clusSize))
	{
		memcpy((void*)data, (const void*)allocBuff, size);
		isDone = true;
	}

	delete[] allocBuff;

	return isDone ? size : 0;
}


/// @brief Size
/// @param fd 
/// @return 
int FatVolume::Size(int fd)
{
	FatObject* obj = objs.GetItem(fd);
	
	if (NULL == obj) return -1;
	
	return obj->GetFileSize();
}


/// @brief Close
/// @param fd 
void FatVolume::Close(int fd)
{
	FatObject* obj = objs.GetItem(fd);
	
	if (NULL == obj) return;

	objs.Remove(obj, fd);
}


/// @brief OpenDir
/// @param name 
/// @param mode 
/// @return 
int FatVolume::OpenDir(const char* path, int mode)
{
	FatObject* obj = SearchPath(path);
	
	if ((NULL == obj) && ((mode & _CreateNew) == _CreateNew))
	{
		obj = CreateDir(path, _FAT_ATTR_DIRECTORY);
	}

	if (NULL == obj) return -1;

	return objs.Add(obj);
}


/// @brief ReadDir
/// @param fd 
/// @param dirs 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::ReadDir(int fd, FileDir* dirs, int size, int offset)
{
	FatObject* obj = objs.GetItem(fd);
	
	if (NULL == obj) return 0;

	int index = 0;

	FatEntry entry(disk, obj);

	for (entry.Begin(); !entry.IsEnd(); entry.Next())
	{
		FatObject* sub = entry.Item();

		if (index < size && NULL != sub)
		{
			dirs[index].name = sub->GetObjectName();
			dirs[index].type = sub->GetObjectType();
			dirs[index].attr = sub->GetObjectAttr();
			index++;
		}
		else break;
	}

	return index;
}


/// @brief SizeDir
/// @param fd 
/// @return 
int FatVolume::SizeDir(int fd)
{
	FatObject* obj = objs.GetItem(fd);

	if (NULL == obj) return 0;

	return FatEntry(disk, obj).GetSize();
}


/// @brief CloseDir
/// @param fd 
void FatVolume::CloseDir(int fd)
{
	FatObject* obj = objs.GetItem(fd);

	if (NULL == obj) return;

	objs.Remove(obj, fd);
}


/// @brief Remove
/// @param name 
/// @return 
bool FatVolume::Remove(const char* name)
{
	FatObject* obj = SearchPath(name);

	if (NULL == obj) return false;

	if (FileType::_File     == obj->GetObjectType() ||
		FileType::_Diretory == obj->GetObjectType())
	{
		FatEntry(disk, obj).Remove();
		return true;
	}
	
	return false;
}


/// @brief GetSystemID
/// @return system id
uint32_t FatSystem::GetSystemID()
{
	const static uint32_t systemID = 11;
	return systemID;
}


/// @brief CreateVolume
/// @return fat volume
FileVol* FatSystem::CreateVolume()
{
	return new FatVolume();
}


///Register file system
REGISTER_FS(new FatSystem(), fat);
