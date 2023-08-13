//###########################################################################
// DirStream.h
// Declarations of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DIR_STREAM_H__
#define __DIR_STREAM_H__

#include "Module.h"
#include "FileOpt.h"
#include "FileDefs.h"


/// @brief DirStream
class DirStream
{
private:
	//Members
	int fd;
	FileOpt* opt;
public:
	//Methods
	DirStream(const char* name = NULL);
	~DirStream();
	int Open(const char* name);
	int Read(FileDir* dirs, int size, int offset = 0);
	int Size();
	void Close();
};

#endif //!__DIR_STREAM_H__
