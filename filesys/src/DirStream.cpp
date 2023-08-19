//###########################################################################
// DirStream.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DirStream.h"
#include "FileSystem.h"


/// @brief Constructor
DirStream::DirStream(const char* name)
	:fd(-1),
	opt(NULL)
{
	if (NULL != name) fd = Open(name);
}


/// @brief Deconstructor
DirStream::~DirStream()
{
}


/// @brief DirStream open
/// @param name 
/// @param opt 
/// @return 
int DirStream::Open(const char* name)
{
	opt = filesystem.ChangeVolume(name);

	if (NULL != opt)
	{
		fd = opt->OpenDir(name);
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
	if (NULL != opt)
	{
		return opt->ReadDir(fd, dirs, size, offset);
	}
	return 0;
}


/// @brief DirStream size
/// @return 
int DirStream::Size()
{
	if (NULL != opt)
	{
		return opt->SizeDir(fd);
	}
	return 0;
}


/// @brief DirStream close
/// @return 
void DirStream::Close()
{
	if (NULL != opt)
	{
		opt->CloseDir(fd);
	}
}
