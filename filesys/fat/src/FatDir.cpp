//###########################################################################
// FatDir.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatDir.h"
#include "FatDisk.h"
#include "FatEntry.h"


/// @brief Create dir
/// @param path 
/// @return 
FatDir::DirData* FatDir::Create(const char* path)
{
	DirEntry* dir = fatEntry->SearchPath(path, 1);
	
	if (NULL == dir) return NULL;
	
	if (dir->body.IsDirectory())
	{
		return fatEntry->CreateDir(dir, fatEntry->NotDir(path));
	}

	return NULL;
}


/// @brief Open dir
/// @param dirName 
/// @return 
FatDir::DirData* FatDir::Open(const char* path, int mode)
{
	DirEntry* dir = fatEntry->SearchPath(path);
	
	if (NULL == dir)
	{
		if ((mode & _CreateNew) == _CreateNew)
			return Create(path);
		else
			return NULL;
	}
	
	if (dir->body.IsDirectory())
	{
		DirData* found = fatEntry->OpenDir(dir);
		found->path = (char*)path;
		return found;
	}

	return NULL;
}


/// @brief Read dir
/// @param data 
/// @return 
FatDir::DirEntry* FatDir::Read(DirData* data)
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
int FatDir::Size(DirData* data)
{
	return data->dirs.GetSize();
}


/// @brief Close dir
/// @param entry 
void FatDir::Close(DirData* data)
{
	delete data;
}
