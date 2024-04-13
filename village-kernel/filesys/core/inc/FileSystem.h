//###########################################################################
// FileSys.h
// Specifies the interface for all classes that contain file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYSTEM_INTERFACE_H__
#define __FILE_SYSTEM_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"
#include "FileVolume.h"


/// @brief FileSystem
class FileSystem
{
public:
	//Constructor
	FileSystem() {}
	
	//Destructor
	virtual ~FileSystem() {};

	//Methods
	virtual uint32_t GetSystemID() = 0;
	virtual FileVolume* CreateVolume() = 0;
};

#endif //!__FILE_SYSTEM_INTERFACE_H__
