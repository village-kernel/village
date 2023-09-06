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
FatDir::DirEntries* FatDir::Create(const char* path)
{
	DirEntry* dir = fatData->SearchPath(path, 1);
	
	if (NULL == dir) return NULL;
	
	if (dir->body.IsDirectory())
	{
		DirEntries* found = fatData->CreateDir(dir, fatData->NotDir(path));
		found->path = (char*)path;
		return found;
	}

	return NULL;
}


/// @brief Open dir
/// @param dirName 
/// @return 
FatDir::DirEntries* FatDir::Open(const char* path, int mode)
{
	DirEntry* dir = fatData->SearchPath(path);
	
	if (NULL == dir)
	{
		if ((mode & _CreateNew) == _CreateNew)
			return Create(path);
		else
			return NULL;
	}
	
	if (dir->body.IsDirectory())
	{
		DirEntries* found = fatData->OpenDir(dir);
		found->path = (char*)path;
		return found;
	}

	return NULL;
}


/// @brief Read dir
/// @param data 
/// @return 
FatDir::DirEntry* FatDir::Read(DirEntries* data)
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
int FatDir::Size(DirEntries* data)
{
	return data->dirs.GetSize();
}


/// @brief Close dir
/// @param entry 
void FatDir::Close(DirEntries* data)
{
	delete data;
}
