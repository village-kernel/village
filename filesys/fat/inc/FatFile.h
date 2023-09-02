//###########################################################################
// FatFile.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_H__
#define __FAT_FILE_H__

#include "FatObjs.h"


/// @brief FatFile
class FatFile : public FatObjs
{
private:
	//Methods
	DirEntry* Create(const char* path);
public:
	//File Methods
	DirEntry* Open(const char* name, int mode);
	int Write(char* data, uint32_t size, DirEntry* entry);
	int Read(char* data, uint32_t size, DirEntry* entry);
	int Size(DirEntry* entry);
};

#endif //!__FAT_FILE_H__
