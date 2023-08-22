//###########################################################################
// DirStream.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DirStream.h"
#include "FileSystem.h"


/// @brief Constructor
DirStream::DirStream(const char* name, int mode)
	:fd(-1),
	opts(NULL)
{
	if (NULL != name) fd = Open(name, mode);
}


/// @brief Destructor
DirStream::~DirStream()
{
}


/// @brief DirStream open
/// @param name 
/// @param opt 
/// @return 
int DirStream::Open(const char* name, int mode)
{
	opts = filesystem.GetFileOpts(name);

	if (NULL != opts)
	{
		fd = opts->OpenDir(name, mode);
	}
	
	return (fd != -1) ? _OK : _ERR;
}


/// @brief DirStream read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int DirStream::Read(FileDir* dirs, int size, int offset)
{
	if (NULL != opts)
	{
		return opts->ReadDir(fd, dirs, size, offset);
	}
	return 0;
}


/// @brief DirStream size
/// @return 
int DirStream::Size()
{
	if (NULL != opts)
	{
		return opts->SizeDir(fd);
	}
	return 0;
}


/// @brief DirStream close
/// @return 
void DirStream::Close()
{
	if (NULL != opts)
	{
		opts->CloseDir(fd);
	}
}
