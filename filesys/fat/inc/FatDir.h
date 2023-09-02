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
	DirData* Create(const char* path);
public:
	//Methods
	DirData* Open(const char* path, int mode);
	DirEntry* Read(DirData* data);
	int Size(DirData* data);
	void Close(DirData* data);
};

#endif //!__FAT_DIR_H__
