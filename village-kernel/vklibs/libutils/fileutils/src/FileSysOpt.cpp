//###########################################################################
// FileSysOpt.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSysOpt.h"
#include "Kernel.h"


/// @brief Constructor
FileSysOpt::FileSysOpt()
{
}


/// @brief Destructor
FileSysOpt::~FileSysOpt()
{
}


/// @brief File system move
/// @param source 
/// @param target 
/// @return 
bool FileSysOpt::Move(const char* source, const char* target)
{
	return false;
}


/// @brief File system copy
/// @param source 
/// @param target 
/// @return 
bool FileSysOpt::Copy(const char* source, const char* target)
{
	return false;
}


/// @brief File system remove
/// @param source 
/// @return 
bool FileSysOpt::Remove(const char* source)
{
	FileVol* volume = kernel->filesys.GetVolume(source);
	
	if (NULL != volume)
	{
		return volume->Remove(source);
	}

	return false;
}
