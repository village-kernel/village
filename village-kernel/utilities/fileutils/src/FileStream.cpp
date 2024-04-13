//###########################################################################
// FileStream.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileStream.h"
#include "Kernel.h"


/// @brief Constructor
FileStream::FileStream(const char* name, int mode)
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
FileStream::~FileStream()
{
}


/// @brief FileStream is exist
/// @param name 
/// @return 
bool FileStream::IsExist(const char* name)
{
	if (NULL != filesys)
	{
		volume = filesys->GetVolume(name);
	}

	if (NULL != volume)
	{
		fd = volume->Open(name, FileMode::_OpenExisting);
	}
	
	if (fd != -1)
	{
		volume->Close(fd);
		return true;
	}

	return false;
}


/// @brief FileStream open
/// @param name 
/// @param opt 
/// @return 
bool FileStream::Open(const char* name, int mode)
{
	if (NULL != filesys)
	{
		volume = filesys->GetVolume(name);
	}

	if (NULL != volume)
	{
		fd = volume->Open(name, mode);
	}

	return (fd != -1);
}


/// @brief FileStream write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FileStream::Write(char* data, int size, int offset)
{
	if (NULL != volume)
	{
		return volume->Write(fd, data, size, offset);
	}
	return 0;
}


/// @brief FileStream read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FileStream::Read(char* data, int size, int offset)
{
	if (NULL != volume)
	{
		return volume->Read(fd, data, size, offset);
	}
	return 0;
}


/// @brief FileStream size
/// @return 
int FileStream::Size()
{
	if (NULL != volume)
	{
		return volume->Size(fd);
	}
	return 0;
}


/// @brief FileStream close
void FileStream::Close()
{
	if (NULL != volume)
	{
		volume->Close(fd);
	}
}