//###########################################################################
// FileSys.h
// Declarations of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include "Module.h"
#include "FileSystem.h"
#include "FileVolume.h"


/// @brief FileSys
class FileSys : public Module
{
public:
	//Methods
	virtual void RegisterFS(FileSystem* fs, const char* name) = 0;
	virtual void DeregisterFS(FileSystem* fs, const char* name) = 0;
	virtual int AttachVolume(FileVolume* volume) = 0;
	virtual int DetachVolume(FileVolume* volume) = 0;
	virtual FileVolume* GetVolume(const char* name) = 0;
};

#endif //!__FILE_SYSTEM_H__
