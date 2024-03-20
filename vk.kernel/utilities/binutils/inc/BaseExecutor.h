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


/// @brief BaseExecutor
class BaseExecutor
{
public:
	//Enumerations
	enum Behavior
	{
		_Foreground = 0,
		_Background = 1,
	};
protected:
	//Members
	int       pid;
	int       argc;
	char**    argv;
	Regex     regex;

	//Methods
	virtual int Execute(const char* path) = 0;
public:
	//Methods
	BaseExecutor();
	virtual ~BaseExecutor();
	virtual int Run(Behavior behavior, const char* args);
	virtual int Run(Behavior behavior, const char* path, int argc, char* argv[]);
	virtual bool Wait();
};

#endif //!__BASE_EXECUTOR_H__
