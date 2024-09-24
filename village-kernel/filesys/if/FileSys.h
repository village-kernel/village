//###########################################################################
// FileSystem.h
// Specifies the interface for all classes that contain file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYSTEM_INTERFACE_H__
#define __FILE_SYSTEM_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"
#include "FileDefs.h"


/// @brief DevStream
class DevStream;


/// @brief FileVol
class FileVol
{
public:
	//Constructor
	FileVol() {}
	
	//Destructor
	virtual ~FileVol() {};

	//Methods
	virtual bool Setup(DevStream* device, uint32_t startingLBA)      = 0;
	virtual void Exit()                                              = 0;

	//Volume methods
	virtual bool  SetName(const char* name)                          = 0;
	virtual char* GetName()                                          = 0;

	//File methods
	virtual int  Open(const char* name, int mode)                    = 0;
	virtual int  Write(int fd, char* data, int size, int offset)     = 0;
	virtual int  Read(int fd, char* data, int size, int offset)      = 0;
	virtual int  Size(int fd)                                        = 0;
	virtual void Flush(int fd)                                       = 0;
	virtual void Close(int fd)                                       = 0;

	//Dir methods
	virtual int  OpenDir(const char* name, int mode)                 = 0;
	virtual int  ReadDir(int fd, FileDir* dirs, int size, int offset)= 0;
	virtual int  SizeDir(int fd)                                     = 0;
	virtual void CloseDir(int fd)                                    = 0;

	//Opt methods
	virtual FileType GetFileType(const char* name)                   = 0;
	virtual bool IsExist(const char* name, FileType type)            = 0;
	virtual bool Remove(const char* name)                            = 0;
};


/// @brief FileSys
class FileSys
{
public:
	//Constructor
	FileSys() {}
	
	//Destructor
	virtual ~FileSys() {};

	//Methods
	virtual uint32_t GetSystemID() = 0;
	virtual FileVol* CreateVolume() = 0;
};

#endif //!__FILE_SYSTEM_INTERFACE_H__
