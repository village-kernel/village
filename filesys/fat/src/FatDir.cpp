//###########################################################################
// FatDir.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatDir.h"
#include "FatEntry.h"


/// @brief Open dir
/// @param dirName 
/// @return 
FatDir::DirData* FatDir::Open(const char* path, int mode)
{
	DirEntry* dir = fatEntry->SearchPath(path);
	
	if (NULL == dir) return NULL;
	
	if (fatEntry->IsDirectory(dir))
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
	return data->size;
}


/// @brief Close dir
/// @param entry 
void FatDir::Close(DirData* data)
{
	delete data;
}
