//###########################################################################
// FileVolume.h
// Specifies the interface for all classes that contain file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_VOLUME_INTERFACE_H__
#define __FILE_VOLUME_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"
#include "DrvStream.h"


/// @brief FileVolume
class FileVolume
{
public:
	//Constructor
	FileVolume() {}
	
	//Destructor
	virtual ~FileVolume() {};

	//Methods
	virtual bool Setup(DrvStream* diskdrv, uint32_t fstSec)          = 0;
	virtual void Exit()                                              = 0;

	//Disk methods
	virtual bool SetVolumeLabel(const char* name)                    = 0;
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
	virtual bool Remove(const char* name)                            = 0;
};

#endif //!__FILE_VOLUME_INTERFACE_H__
