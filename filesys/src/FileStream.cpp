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
{
	if (NULL != name) Open(name, mode);
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
	opt = filesystem.GetFileOpt("fatfs");
	if (NULL != opt)
	{
		return opt->Open(name, mode);
	}
	return _ERR;
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
	opt = filesystem.GetFileOpt("fatfs");
	if (NULL != opt)
	{
		return opt->Read(data, size, offset);
	}
	return _ERR;
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
	opt = filesystem.GetFileOpt("fatfs");
	if (NULL != opt)
	{
		return opt->Size();
	}
	return 0;
}


/// @brief FileStream close
/// @return 
int FileStream::Close()
{
	return 0;
}
