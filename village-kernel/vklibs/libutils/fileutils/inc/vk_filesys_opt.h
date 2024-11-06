//###########################################################################
// vk_filesys_opt.h
// Declarations of the functions that manage filesys opts
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FILE_SYS_OPT_H__
#define __VK_FILE_SYS_OPT_H__

#include "vk_filesystem.h"


/// @brief FileSysOpt
class FileSysOpt
{
public:
	//Methods
	FileSysOpt();
	~FileSysOpt();
	bool Move(const char* source, const char* target);
	bool Copy(const char* source, const char* target);
	bool Remove(const char* source);
};

#endif //!__VK_FILE_SYS_OPT_H__
