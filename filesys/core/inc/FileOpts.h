//###########################################################################
// FileOpt.h
// Specifies the interface for all classes that contain file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_OPERATION_INTERFACE_H__
#define __FILE_OPERATION_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"
#include "FileDefs.h"


/// @brief FileOpts
class FileOpts
{
public:
	//Constructor
	FileOpts() {}
	
	//Destructor
	virtual ~FileOpts() {};

	//Disk methods
	virtual int Mount(const char* path, const char* mount, int opt)  = 0;
	virtual int Unmount(const char* mount)                           = 0;
	virtual int SetVolumeLabel(const char* name)                     = 0;
	virtual char* GetVolumeLabel()                                   = 0;

	//File methods
	virtual int Open(const char* name, int mode)                     = 0;
	virtual int Write(int fd, char* data, int size, int offset)      = 0;
	virtual int Read(int fd, char* data, int size, int offset)       = 0;
	virtual int Size(int fd)                                         = 0;
	virtual void Close(int fd)                                       = 0;

	//Dir methods
	virtual int OpenDir(const char* name, int mode)                  = 0;
	virtual int ReadDir(int fd, FileDir* dirs, int size, int offset) = 0;
	virtual int SizeDir(int fd)                                      = 0;
	virtual void CloseDir(int fd)                                    = 0;

	//Opt methods
	virtual int Move(int fd, const char* from, const char* to)       = 0;
	virtual int Copy(int fd, const char* from, const char* to)       = 0;
	virtual int Remove(int fd)                                       = 0;
};

#endif //!__FILE_OPERATION_INTERFACE_H__
