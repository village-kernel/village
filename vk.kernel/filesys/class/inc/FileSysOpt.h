//###########################################################################
// FileSysOpt.h
// Declarations of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYS_OPT_H__
#define __FILE_SYS_OPT_H__

#include "FileSystem.h"


/// @brief FileSysOpt
class FileSysOpt
{
private:
	//Members
	FileOpts*   opts;
	FileSystem* filesys;
public:
	//Methods
	FileSysOpt();
	~FileSysOpt();
	int Move(const char* from, const char* to);
	int Copy(const char* from, const char* to);
	int Remove(const char* name);
};

#endif //!__FILE_SYS_OPT_H__
