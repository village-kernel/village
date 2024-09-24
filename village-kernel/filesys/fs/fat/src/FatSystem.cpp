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

	FatObject fatObj;

	if (1 == folder.Read(&fatObj, 1))
	{
		if (FileType::_Volume == fatObj.GetObjectType())
		{
			fatObj.SetRawName(name);

			folder.Update(&fatObj);
		}
	}

	return (0 == strcmp(GetName(), name));
}


/// @brief Get volume name
/// @return 
char* FatVolume::GetName()
{
	char* name = (char*)"NONAME";

	FatFolder folder(fatDisk, SearchPath("/"));

	FatObject fatObj;

	if (1 == folder.Read(&fatObj, 1))
	{
		if (FileType::_Volume == fatObj.GetObjectType())
		{
			name = fatObj.GetRawName();
		}
	}

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
		FileLayer* layer = new FileLayer();
		layer->object    = fatObj;
		layer->fileMode  = mode;
		layer->fileSize  = fatObj->GetFileSize();

		if (layer->fileSize)
		{
			layer->fstClust = fatObj->GetFirstCluster();
			layer->secSize  = (layer->fileSize + (bytesPerSec - 1)) / bytesPerSec;
			layer->clusSize = (layer->secSize  + (secPerClust - 1)) / secPerClust;
			layer->buffSize =  layer->clusSize *  secPerClust * bytesPerSec;
			layer->buffer   = (char*)new char[layer->buffSize]();
			layer->clusSize = fatDisk.ReadCluster(layer->buffer, layer->fstClust, layer->clusSize);
		}

		return fileLayers.Add(layer);
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
	FileLayer* layer = fileLayers.GetItem(fd);

	if (NULL != layer)
	{
		int buffOffset = 0;

		if (layer->fileMode & FileMode::_OpenAppend)
			buffOffset = layer->fileSize;
		else if (layer->fileMode & FileMode::_Write)
			buffOffset = 0;

		layer->fileSize = buffOffset + size;

		if (layer->fileSize > layer->buffSize)
		{
			layer->secSize  = (layer->fileSize + (bytesPerSec - 1)) / bytesPerSec;
			layer->clusSize = (layer->secSize  + (secPerClust - 1)) / secPerClust;
			int    buffSize = (layer->clusSize *  secPerClust * bytesPerSec);
			char*  buffer   = (char*)new char[layer->buffSize]();

			if (buffOffset) memcpy((void*)buffer, (const void*)layer->buffer, layer->buffSize);
			delete[] layer->buffer;
			layer->buffSize = buffSize;
			layer->buffer   = buffer;
		}

		memcpy((void*)(layer->buffer + buffOffset), (const void*)(data + offset), size);

		layer->fileMode = FileMode::_OpenAppend;

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
	FileLayer* layer = fileLayers.GetItem(fd);

	if ((NULL != layer) && (layer->fileSize))
	{
		if (layer->fileSize < size) size = layer->fileSize;

		memcpy((void*)(data + offset), (const void*)layer->buffer, size);
		
		return size;
	}

	return 0;
}


/// @brief Size
/// @param fd 
/// @return 
int FatVolume::Size(int fd)
{
	FileLayer* layer = fileLayers.GetItem(fd);

	return (NULL != layer) ? layer->fileSize : 0;
}


/// @brief Flush
/// @param fd 
void FatVolume::Flush(int fd)
{
	FileLayer* layer = fileLayers.GetItem(fd);
	
	if (NULL != layer)
	{
		if (layer->clusSize == fatDisk.WriteCluster(layer->buffer, layer->fstClust, layer->clusSize))
		{
			layer->object->SetFileSize(layer->fileSize);
			FatFolder(fatDisk).Update(layer->object);
		}
	}
}


/// @brief Close
/// @param fd 
void FatVolume::Close(int fd)
{
	FileLayer* layer = fileLayers.GetItem(fd);
	
	if (NULL != layer)
	{
		delete[] layer->buffer;
		fileLayers.Remove(layer, fd);
		delete layer;
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

		DirLayer* layer   = new DirLayer();
		layer->object     = fatObj;
		layer->dirMode    = mode;
		layer->subSize    = folder->Size();
		layer->subObjs    = new FatObject[layer->subSize]();
		layer->subSize    = folder->Read(layer->subObjs, layer->subSize);
		
		folder->Close();
		delete folder;
		return dirLayers.Add(layer);
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
	DirLayer* layer = dirLayers.GetItem(fd);
	
	if (NULL != layer)
	{
		if (layer->subSize < size) size = layer->subSize;

		for (int i = 0; i < size; i++)
		{
			dirs[i].name = layer->subObjs[i].GetObjectName();
			dirs[i].type = layer->subObjs[i].GetObjectType();
			dirs[i].attr = layer->subObjs[i].GetObjectAttr();
		}
	}

	return size;
}


/// @brief SizeDir
/// @param fd 
/// @return 
int FatVolume::SizeDir(int fd)
{
	DirLayer* layer = dirLayers.GetItem(fd);
	
	return (NULL != layer) ? layer->subSize : 0;
}


/// @brief CloseDir
/// @param fd 
void FatVolume::CloseDir(int fd)
{
	DirLayer* layer = dirLayers.GetItem(fd);
	
	if (NULL != layer)
	{
		delete[] layer->subObjs;
		dirLayers.Remove(layer, fd);
		delete layer;
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
