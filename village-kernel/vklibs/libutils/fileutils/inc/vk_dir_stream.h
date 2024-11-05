//###########################################################################
// vk_dir_stream.h
// Declarations of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DIR_STREAM_H__
#define __VK_DIR_STREAM_H__

#include "vk_filesystem.h"


/// @brief DirStream
class DirStream
{
private:
	//Members
	int fd;
	FileVol* volume;
public:
	//Methods
	DirStream(const char* name = NULL, int mode = 0);
	~DirStream();
	bool IsExist(const char* name);
	bool Open(const char* name, int mode);
	int Read(FileDir* dirs, int size, int offset = 0);
	int Size();
	void Close();
};

#endif //!__VK_DIR_STREAM_H__
