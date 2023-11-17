//###########################################################################
// FileSysOpt.h
// Declarations of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYS_OPT_H__
#define __FILE_SYS_OPT_H__

#include "Module.h"
#include "FileOpts.h"


/// @brief FileSysOpt
class FileSysOpt
{
public:
	//Methods
	FileSysOpt();
	~FileSysOpt();
	int Move(const char* from, const char* to);
	int Copy(const char* from, const char* to);
	int Remove(const char* name);
	int MoveDir(const char* from, const char* to);
	int CopyDir(const char* from, const char* to);
	int RemoveDir(const char* name);
};

#endif //!__FILE_SYS_OPT_H__
