//###########################################################################
// DirStream.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DirStream.h"
#include "Kernel.h"


/// @brief Constructor
DirStream::DirStream(const char* name, int mode)
	:fd(-1),
	volume(NULL)
{
	filesys = (FileSys*)kernel->feature.GetModule("filesys");
	if (NULL == filesys)
	{
		kernel->debug.Error("file system feature not support");
		return;
	}
	if (NULL != name) Open(name, mode);
}


/// @brief Destructor
DirStream::~DirStream()
{
}


/// @brief DirStream is exist
/// @param name 
/// @return 
bool DirStream::IsExist(const char* name)
{
	if (NULL != filesys)
	{
		volume = filesys->GetVolume(name);
	}

	if (NULL != volume)
	{
		fd = volume->OpenDir(name, FileMode::_OpenExisting);
	}
	
	if (fd != -1)
	{
		volume->CloseDir(fd);
		return true;
	}

	return false;
}


/// @brief DirStream open
/// @param name 
/// @param mode 
/// @return 
bool DirStream::Open(const char* name, int mode)
{
	if (NULL != filesys)
	{
		volume = filesys->GetVolume(name);
	}

	if (NULL != volume)
	{
		fd = volume->OpenDir(name, mode);
	}
	
	return (fd != -1);
}


/// @brief DirStream read
/// @param dirs 
/// @param size 
/// @param offset 
/// @return 
int DirStream::Read(FileDir* dirs, int size, int offset)
{
	if (NULL != volume)
	{
		return volume->ReadDir(fd, dirs, size, offset);
	}
	return 0;
}


/// @brief DirStream size
/// @return 
int DirStream::Size()
{
	if (NULL != volume)
	{
		return volume->SizeDir(fd);
	}
	return 0;
}


/// @brief DirStream close
void DirStream::Close()
{
	if (NULL != volume)
	{
		volume->CloseDir(fd);
	}
}
