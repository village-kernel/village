//###########################################################################
// FileSysOpt.h
// Declarations of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYS_OPT_H__
#define __FILE_SYS_OPT_H__

#include "FileSys.h"


/// @brief FileSysOpt
class FileSysOpt
{
private:
	//Members
	FileSys*    filesys;
	FileVolume* volume;
public:
	//Methods
	FileSysOpt();
	~FileSysOpt();
	bool Move(const char* from, const char* to);
	bool Copy(const char* from, const char* to);
	bool Remove(const char* name);
};

#endif //!__FILE_SYS_OPT_H__
