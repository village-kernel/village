//###########################################################################
// FAT.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"
#include "FatFolder.h"
#include "FileSys.h"
#include "Regex.h"
#include "Debug.h"
#include "Kernel.h"


/// @brief Constructor
FatVolume::FatVolume()
	:bytesPerSec(0),
	secPerClust(0)
{
}


/// @brief Destructor
FatVolume::~FatVolume()
{
}


/// @brief FatVolume Setup
/// @param device 
/// @param startingLBA 
/// @return 
bool FatVolume::Setup(DevStream* device, uint32_t startingLBA)
{
	if (fatDisk.Setup(device, startingLBA))
	{
		bytesPerSec = fatDisk.GetInfo().bytesPerSec;
		secPerClust = fatDisk.GetInfo().secPerClust;
	}
	return (bytesPerSec && secPerClust) ? true : false;
}


/// @brief FatVolume Exit
void FatVolume::Exit()
{
	fatDisk.Exit();
}


/// @brief BaseName
/// @param path 
/// @return 
char* FatVolume::BaseName(const char* path)
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
	Regex regex;
	regex.Split(path, '/');
	char** names = regex.ToArray();
	int8_t deep  = regex.Size() - reserve;

	//Create an directory fat object
	FatObject* fatObj = new FatObject(new FatEntry());
	fatObj->SetAttribute(FatDefs::_AttrDirectory);

	//Search directory
	FatObject* found = fatObj;
	for (int8_t i = 0; i < deep; i++)
	{
		found = FatFolder(fatDisk, found).Search(names[i]);
		if (NULL == found) break;
	}

	//Update fatObj
	if (NULL != found) 
	{
		fatObj->Setup(found);
		return fatObj;
	}

	return NULL;
}


/// @brief Create path
/// @param path 
/// @param attr 
/// @return 
FatObject* FatVolume::CreatePath(const char* path, int attr)
{
	FatObject* fatObj = SearchPath(path, 1);

	if (NULL != fatObj)
	{
		if (FileType::_Diretory == fatObj->GetObjectType())
		{
			FatObject* resObj = FatFolder(fatDisk, fatObj).Create(BaseName(path), attr);

			if (NULL != resObj)
			{
				fatObj->Setup(resObj);
				return fatObj;
			}
		}
	}

	return NULL;
}


/// @brief Set volume name
/// @param name 
/// @return 
bool FatVolume::SetName(const char* name)
{
	FatFolder folder(fatDisk, SearchPath("/"));

	FatObject* fatObj = new FatObject();

	if (1 == folder.Read(fatObj, 1))
	{
		if (FileType::_Volume == fatObj->GetObjectType())
		{
			fatObj->SetRawName(name);

			folder.Update(fatObj);
		}
	}

	delete fatObj;
	return (0 == strcmp(GetName(), name));
}


/// @brief Get volume name
/// @return 
char* FatVolume::GetName()
{
	char* name = (char*)"NONAME";

	FatFolder folder(fatDisk, SearchPath("/"));	

	FatObject* fatObj = new FatObject();

	if (1 == folder.Read(fatObj, 1))
	{
		if (FileType::_Volume == fatObj->GetObjectType())
		{
			name = fatObj->GetRawName();
		}
	}

	delete fatObj;
	return name;
}


/// @brief Open
/// @param name 
/// @param mode 
/// @return 
int FatVolume::Open(const char* name, int mode)
{
	FatObject* fatObj = SearchPath(name);

	if (NULL == fatObj)
	{
		if (mode & FileMode::_CreateNew)
		{
			fatObj = CreatePath(name, FatDefs::_AttrFile);
		}
	}

	if (NULL != fatObj)
	{
		fatObj->SetOpenMode(mode);
		return fatObjs.Add(fatObj);
	}

	return -1;
}


/// @brief Write
/// @param fd 
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::Write(int fd, char* data, int size, int offset)
{
	FatObject* fatObj = fatObjs.GetItem(fd);

	if (NULL != fatObj)
	{
		uint32_t dataSize  = 0;

		if (fatObj->GetOpenMode() & FileMode::_Write)
		{
			dataSize = 0;
		}
		else if (fatObj->GetOpenMode() & FileMode::_OpenAppend)
		{
			dataSize = fatObj->GetFileSize();
		}

		uint32_t fileSize  = dataSize + size;

		if (fileSize)
		{
			uint32_t fstClust  = fatObj->GetFirstCluster();
			uint32_t secSize   = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
			uint32_t clusSize  = (secSize  + (secPerClust - 1)) / secPerClust;
			uint32_t allocSize = (clusSize * secPerClust * bytesPerSec);
			char*    allocBuff = (char*)new char[allocSize]();

			if (dataSize) Read(fd, allocBuff, dataSize, offset);

			memcpy((void*)(allocBuff + dataSize), (const void*)(data + offset), size);

			if (clusSize == fatDisk.WriteCluster(allocBuff, fstClust, clusSize))
			{
				fatObj->SetFileSize(fileSize);
				FatFolder(fatDisk).Update(fatObj);
				delete[] allocBuff;
				return size;
			}

			delete[] allocBuff;
		}
	}

	return 0;
}


/// @brief Read
/// @param fd 
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::Read(int fd, char* data, int size, int offset)
{
	FatObject* fatObj = fatObjs.GetItem(fd);

	if (NULL != fatObj)
	{
		uint32_t fileSize  = fatObj->GetFileSize();

		if (fileSize)
		{
			uint32_t fstClust  = fatObj->GetFirstCluster();
			uint32_t secSize   = (fileSize + (bytesPerSec - 1)) / bytesPerSec;
			uint32_t clusSize  = (secSize  + (secPerClust - 1)) / secPerClust;
			uint32_t allocSize = clusSize * secPerClust * bytesPerSec;
			char*    allocBuff = (char*)new char[allocSize]();

			if (clusSize == fatDisk.ReadCluster(allocBuff, fstClust, clusSize))
			{
				memcpy((void*)(data + offset), (const void*)allocBuff, size);
				delete[] allocBuff;
				return size;
			}

			delete[] allocBuff;
		}
	}

	return 0;
}


/// @brief Size
/// @param fd 
/// @return 
int FatVolume::Size(int fd)
{
	FatObject* fatObj = fatObjs.GetItem(fd);
	
	if (NULL != fatObj)
	{
		return fatObj->GetFileSize();
	}

	return 0;
}


/// @brief Close
/// @param fd 
void FatVolume::Close(int fd)
{
	FatObject* fatObj = fatObjs.GetItem(fd);
	
	if (NULL != fatObj)
	{
		fatObjs.Remove(fatObj, fd);
		delete fatObj;
	}
}


/// @brief OpenDir
/// @param name 
/// @param mode 
/// @return 
int FatVolume::OpenDir(const char* path, int mode)
{
	FatObject* fatObj = SearchPath(path);
	
	if (NULL == fatObj)
	{
		if (mode & FileMode::_CreateNew)
		{
			fatObj = CreatePath(path, FatDefs::_AttrDirectory);
		}
	}

	if (NULL != fatObj)
	{
		fatObj->SetOpenMode(mode);
		fatObj->SetFolder(new FatFolder(fatDisk, fatObj));
		return fatObjs.Add(fatObj);
	}

	return -1;
}


/// @brief ReadDir
/// @param fd 
/// @param dirs 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::ReadDir(int fd, FileDir* dirs, int size, int offset)
{
	FatObject* fatObj = fatObjs.GetItem(fd);
	
	if (NULL != fatObj)
	{
		FatObject* subObjs = new FatObject[size]();

		size = fatObj->GetFolder()->Read(subObjs, size);
		
		for (int i = 0; i < size; i++)
		{
			dirs[i].name = subObjs[i].GetObjectName();
			dirs[i].type = subObjs[i].GetObjectType();
			dirs[i].attr = subObjs[i].GetObjectAttr();
		}

		delete[] subObjs;
	}

	return size;
}


/// @brief SizeDir
/// @param fd 
/// @return 
int FatVolume::SizeDir(int fd)
{
	FatObject* fatObj = fatObjs.GetItem(fd);

	if (NULL != fatObj)
	{
		return fatObj->GetFolder()->Size();
	}

	return 0;
}


/// @brief CloseDir
/// @param fd 
void FatVolume::CloseDir(int fd)
{
	FatObject* fatObj = fatObjs.GetItem(fd);

	if (NULL != fatObj)
	{
		fatObjs.Remove(fatObj, fd);
		fatObj->GetFolder()->Close();
		delete fatObj->GetFolder();
		delete fatObj;
	}
}


/// @brief Get file type
/// @param name 
/// @return 
FileType FatVolume::GetFileType(const char* name)
{
	FileType type = FileType::_Unknown;

	FatObject* fatObj = SearchPath(name);

	if (NULL != fatObj) 
	{
		type = fatObj->GetObjectType();
		delete fatObj;
	}

	return type;
}


/// @brief IsExist
/// @param name 
/// @param type
/// @return 
bool FatVolume::IsExist(const char* name, FileType type)
{
	return (type == GetFileType(name));
}


/// @brief Remove
/// @param name 
/// @return 
bool FatVolume::Remove(const char* name)
{
	FatObject* fatObj = SearchPath(name);

	if (NULL != fatObj)
	{
		if (FileType::_File     == fatObj->GetObjectType() ||
			FileType::_Diretory == fatObj->GetObjectType())
		{
			FatFolder(fatDisk).Remove(fatObj);
			delete fatObj;
			return true;
		}
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
