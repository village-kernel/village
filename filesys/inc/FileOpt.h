//###########################################################################
// FileOpt.h
// Specifies the interface for all classes that contain file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYSTEM_INTERFACE_H__
#define __FILE_SYSTEM_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"

///FileOpt
class FileOpt
{
public:
	//Constructor
	FileOpt() {}
	
	//Deconstructor
	virtual ~FileOpt() {};

	//File methods
	virtual int Mount(const char* path, const char* mount, int opt, int fstSecNum) = 0;
	virtual int Unmount(const char* mount)                       = 0;
	virtual int Open(const char* name, int opt)                  = 0;
	virtual int Write(int fd, char* data, int size, int offset)  = 0;
	virtual int Read(int fd, char* data, int size, int offset)   = 0;
	virtual int Seek(int fd, int offset)                         = 0;
	virtual int Rename(int fd, const char* old, const char* now) = 0;
	virtual int Copy(int fd, const char* from, const char* to)   = 0;
	virtual int Remove(int fd)                                   = 0;
	virtual int Size(int fd)                                     = 0;
	virtual int Close(int fd)                                    = 0;
};

#endif //!__FILE_SYSTEM_INTERFACE_H__
