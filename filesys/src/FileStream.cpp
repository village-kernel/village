//###########################################################################
// FileStream.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileStream.h"
#include "FileSystem.h"


/// @brief Constructor
FileStream::FileStream(const char* name, int mode)
	:fd(0)
{
	if (NULL != name) fd = Open(name, mode);
}


/// @brief Deconstructor
FileStream::~FileStream()
{
}


/// @brief FileStream open
/// @param name 
/// @param opt 
/// @return 
int FileStream::Open(const char* name, int mode)
{
	opt = filesystem.GetFileOpt("fat");
	if (NULL != opt)
	{
		fd = opt->Open(name, mode);
	}
	return (fd != -1) ? _OK : _ERR;
}


/// @brief FileStream write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FileStream::Write(char* data, int size, int offset)
{
	return 0;
}


/// @brief FileStream read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FileStream::Read(char* data, int size, int offset)
{
	opt = filesystem.GetFileOpt("fat");
	if (NULL != opt)
	{
		return opt->Read(fd, data, size, offset);
	}
	return 0;
}


/// @brief FileStream seek
/// @param offset 
/// @return 
int FileStream::Seek(int offset)
{
	return 0;
}


/// @brief FileStream size
/// @return 
int FileStream::Size()
{
	opt = filesystem.GetFileOpt("fat");
	if (NULL != opt)
	{
		return opt->Size(fd);
	}
	return 0;
}


/// @brief FileStream close
/// @return 
int FileStream::Close()
{
	return 0;
}
