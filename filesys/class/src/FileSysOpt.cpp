//###########################################################################
// FileSysOpt.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSysOpt.h"
#include "FileSystem.h"


/// @brief Constructor
FileSysOpt::FileSysOpt()
{
}


/// @brief Destructor
FileSysOpt::~FileSysOpt()
{
}


/// @brief File system move
/// @param from 
/// @param to 
/// @return 
int FileSysOpt::Move(const char* from, const char* to)
{
	FileOpts* opts = filesystem.GetFileOpts(from);

	if (NULL != opts)
	{
		return opts->Move(from, to);
	}

	return _ERR;
}


/// @brief File system copy
/// @param from 
/// @param to 
/// @return 
int FileSysOpt::Copy(const char* from, const char* to)
{
	FileOpts* opts = filesystem.GetFileOpts(from);

	if (NULL != opts)
	{
		return opts->Copy(from, to);
	}

	return _ERR;
}


/// @brief File system remove
/// @param name 
/// @return 
int FileSysOpt::Remove(const char* name)
{
	FileOpts* opts = filesystem.GetFileOpts(name);

	if (NULL != opts)
	{
		return opts->Remove(name);
	}

	return _ERR;
}


/// @brief File system move
/// @param from 
/// @param to 
/// @return 
int FileSysOpt::MoveDir(const char* from, const char* to)
{
	FileOpts* opts = filesystem.GetFileOpts(from);

	if (NULL != opts)
	{
		return opts->MoveDir(from, to);
	}

	return _ERR;
}


/// @brief File system copy
/// @param from 
/// @param to 
/// @return 
int FileSysOpt::CopyDir(const char* from, const char* to)
{
	FileOpts* opts = filesystem.GetFileOpts(from);

	if (NULL != opts)
	{
		return opts->CopyDir(from, to);
	}

	return _ERR;
}


/// @brief File system remove
/// @param name 
/// @return 
int FileSysOpt::RemoveDir(const char* name)
{
	FileOpts* opts = filesystem.GetFileOpts(name);

	if (NULL != opts)
	{
		return opts->RemoveDir(name);
	}

	return _ERR;
}
