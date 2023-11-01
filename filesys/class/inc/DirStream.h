//###########################################################################
// DirStream.h
// Declarations of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DIR_STREAM_H__
#define __DIR_STREAM_H__

#include "Module.h"
#include "FileOpts.h"


/// @brief DirStream
class DirStream
{
private:
	//Members
	int fd;
	FileOpts* opts;
public:
	//Methods
	DirStream(const char* name = NULL, int mode = 0);
	~DirStream();
	bool IsExist(const char* name);
	int Open(const char* name, int mode);
	int Read(FileDir* dirs, int size, int offset = 0);
	int Size();
	void Close();
};

#endif //!__DIR_STREAM_H__
