//###########################################################################
// FatDir.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_DIR_H__
#define __FAT_DIR_H__

#include "FatObjs.h"


/// @brief FatDir
class FatDir : public FatObjs
{
public:
	//Attr Methods
	bool IsHidden(DirEntry* entry);
	bool IsDirectory(DirEntry* entry);
	bool IsVolume(DirEntry* entry);
	bool IsFile(DirEntry* entry);

	//Directory Methods
	DirEntry* SearchPath(const char* path);
	DirEntry* SearchDir(DirEntry* entry, const char* dir);
	DirData* OpenDir(DirEntry* entry);

	//Open API
	DirData* Open(const char* path, int mode);
	DirEntry* Read(DirData* data);
	int Size(DirData* data);
	void Close(DirData* data);
};

#endif //!__FAT_DIR_H__
