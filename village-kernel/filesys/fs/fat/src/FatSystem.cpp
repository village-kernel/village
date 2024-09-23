//###########################################################################
// FatSystem.cpp
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

	if ((NULL == fatObj) && (mode & FileMode::_CreateNew))
	{
		fatObj = CreatePath(name, FatDefs::_AttrFile);
	}

	if (NULL != fatObj)
	{
		FileLayer* fl  = new FileLayer();
		fl->object     = fatObj;
		fl->openMode   = mode;
		fl->fileSize   = fatObj->GetFileSize();

		if (fl->fileSize)
		{
			fl->fstClust  = fatObj->GetFirstCluster();
			fl->secSize   = (fl->fileSize + (bytesPerSec - 1)) / bytesPerSec;
			fl->clusSize  = (fl->secSize  + (secPerClust - 1)) / secPerClust;
			fl->allocSize =  fl->clusSize *  secPerClust * bytesPerSec;
			fl->allocBuff = (char*)new char[fl->allocSize]();
			fl->clusSize  = fatDisk.ReadCluster(fl->allocBuff, fl->fstClust, fl->clusSize);
		}

		return fls.Add(fl);
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
	FileLayer* fl = fls.GetItem(fd);

	if (NULL != fl)
	{
		int buffOffset = 0;

		if (fl->openMode & FileMode::_Write)
			buffOffset = 0;
		else if (fl->openMode & FileMode::_OpenAppend)
			buffOffset = fl->fileSize;

		fl->fileSize = buffOffset + size;

		if (fl->fileSize > fl->allocSize)
		{
			fl->secSize     = (fl->fileSize + (bytesPerSec - 1)) / bytesPerSec;
			fl->clusSize    = (fl->secSize  + (secPerClust - 1)) / secPerClust;
			int   allocSize = (fl->clusSize *  secPerClust * bytesPerSec);
			char* allocBuff = (char*)new char[fl->allocSize]();

			if (buffOffset) memcpy((void*)allocBuff, (const void*)fl->allocBuff, fl->allocSize);
			delete[] fl->allocBuff;
			fl->allocSize = allocSize;
			fl->allocBuff = allocBuff;
		}

		memcpy((void*)(fl->allocBuff + buffOffset), (const void*)(data + offset), size);

		fl->openMode = FileMode::_OpenAppend;
		return size;
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
	FileLayer* fl = fls.GetItem(fd);

	if (NULL != fl)
	{
		if (fl->fileSize)
		{
			if (fl->fileSize < size) size = fl->fileSize;

			memcpy((void*)(data + offset), (const void*)fl->allocBuff, size);
			
			return size;
		}
	}

	return 0;
}


/// @brief Size
/// @param fd 
/// @return 
int FatVolume::Size(int fd)
{
	FileLayer* fl = fls.GetItem(fd);

	return (NULL != fl) ? fl->fileSize : 0;
}


/// @brief Flush
/// @param fd 
void FatVolume::Flush(int fd)
{
	FileLayer* fl = fls.GetItem(fd);
	
	if (NULL != fl)
	{
		if (fl->clusSize == fatDisk.WriteCluster(fl->allocBuff, fl->fstClust, fl->clusSize))
		{
			fl->object->SetFileSize(fl->fileSize);
			FatFolder(fatDisk).Update(fl->object);
		}
	}
}


/// @brief Close
/// @param fd 
void FatVolume::Close(int fd)
{
	FileLayer* fl = fls.GetItem(fd);
	
	if (NULL != fl)
	{
		delete[] fl->allocBuff;
		fls.Remove(fl, fd);
		delete fl;
	}
}


/// @brief OpenDir
/// @param name 
/// @param mode 
/// @return 
int FatVolume::OpenDir(const char* path, int mode)
{
	FatObject* fatObj = SearchPath(path);
	
	if ((NULL == fatObj) && (mode & FileMode::_CreateNew))
	{
		fatObj = CreatePath(path, FatDefs::_AttrDirectory);
	}

	if (NULL != fatObj)
	{
		FatFolder* folder = new FatFolder(fatDisk, fatObj);
		DirLayer* dl      = new DirLayer();
		dl->object        = fatObj;
		dl->openMode      = mode;
		dl->subSize       = folder->Size();
		dl->subObjs       = new FatObject[dl->subSize]();
		dl->subSize       = folder->Read(dl->subObjs, dl->subSize);
		
		folder->Close();
		delete folder;
		return dls.Add(dl);
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
	DirLayer* dl = dls.GetItem(fd);
	
	if (NULL != dl)
	{
		if (dl->subSize < size) size = dl->subSize;

		for (int i = 0; i < size; i++)
		{
			dirs[i].name = dl->subObjs[i].GetObjectName();
			dirs[i].type = dl->subObjs[i].GetObjectType();
			dirs[i].attr = dl->subObjs[i].GetObjectAttr();
		}
	}

	return size;
}


/// @brief SizeDir
/// @param fd 
/// @return 
int FatVolume::SizeDir(int fd)
{
	DirLayer* dl = dls.GetItem(fd);
	
	return (NULL != dl) ? dl->subSize : 0;
}


/// @brief CloseDir
/// @param fd 
void FatVolume::CloseDir(int fd)
{
	DirLayer* dl = dls.GetItem(fd);
	
	if (NULL != dl)
	{
		delete[] dl->subObjs;
		dls.Remove(dl, fd);
		delete dl;
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
