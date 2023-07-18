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
	virtual int Mount(const char* path, const char* mount, int opt) = 0;
	virtual int Unmount(const char* mount)               = 0;
	virtual int Open(const char* name, int opt)          = 0;
	virtual int Write(char* data, int size, int offset)  = 0;
	virtual int Read(char* data, int size, int offset)   = 0;
	virtual int Seek(int offset)                         = 0;
	virtual int Rename(const char* old, const char* now) = 0;
	virtual int Copy(const char* from, const char* to)   = 0;
	virtual int Remove()                                 = 0;
	virtual int Size()                                   = 0;
	virtual int Close()                                  = 0;
};

#endif //!__FILE_SYSTEM_INTERFACE_H__
