//###########################################################################
// BaseExecutor.h
// Declarations of the functions that manage base executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __BASE_EXECUTOR_H__
#define __BASE_EXECUTOR_H__

#include "List.h"
#include "Regex.h"
#include "Kernel.h"


/// @brief BaseExecutor
class BaseExecutor
{
protected:
	//Members
	char*     path;
	int       argc;
	char**    argv;
	int       tid;

	//Methods
	virtual int Execute() = 0;
	virtual bool Release() = 0;
public:
	//Methods
	BaseExecutor();
	virtual ~BaseExecutor();
	virtual int Run(const char* path, int argc, char* argv[]);
	virtual bool Wait();
	virtual bool Kill();
};

#endif //!__BASE_EXECUTOR_H__
