//###########################################################################
// FileStream.h
// Declarations of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_STREAM_H__
#define __FILE_STREAM_H__

#include "Module.h"
#include "FileOpt.h"
#include "FileDefs.h"


/// @brief FileStream
class FileStream
{
private:
	//Members
	int fd;
	FileOpt* opt;
public:
	//Methods
	FileStream(const char* name = NULL, int mode = 0);
	~FileStream();
	int Open(const char* name, int mode);
	int Write(char* data, int size, int offset = 0);
	int Read(char* data, int size, int offset = 0);
	int Seek(int offset);
	int Size();
	int Close();
};

#endif //!__FILE_STREAM_H__
