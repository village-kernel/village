//###########################################################################
// FatDir.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_DIR_H__
#define __FAT_DIR_H__

#include "FatDefs.h"


/// @brief FatDir
class FatDir : public FatDat
{
private:
	//Methods
	DirData* OpenDir(DirEntry* entry);
public:
	//Directory Methods
	bool IsHidden(DirEntry* entry);
	bool IsFile(DirEntry* entry);
	bool IsDirectory(DirEntry* entry);
	bool IsVolume(DirEntry* entry);
	DirEntry* SearchPath(const char* path);
	DirEntry* SearchDir(DirEntry* entry, const char* dirName);

	//Open API
	DirData* OpenDir(const char* path);
	DirEntry* ReadDir(DirData* data);
	int SizeDir(DirData* data);
	void CloseDir(DirData* data);
};

#endif //!__FAT_DIR_H__
