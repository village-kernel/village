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
#include "FileDefs.h"


/// @brief FileSystem
class FileSystem
{
public:
	//Constructor
	FileSystem() {}
	
	//Destructor
	virtual ~FileSystem() {};

	//Methods
	virtual void Setup() = 0;
	virtual void Exit()  = 0;
};

#endif //!__FILE_SYSTEM_INTERFACE_H__
