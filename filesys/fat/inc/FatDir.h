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
private:
	//Methods
	DirEntries* Create(const char* path);
public:
	//Methods
	DirEntries* Open(const char* path, int mode);
	DirEntry* Read(DirEntries* data);
	int Size(DirEntries* data);
	void Close(DirEntries* data);
};

#endif //!__FAT_DIR_H__
