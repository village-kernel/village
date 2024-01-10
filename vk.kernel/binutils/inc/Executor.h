//###########################################################################
// Executor.h
// Declarations of the functions that manage executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "Templates.h"
#include "ElfLoader.h"
#include "Regex.h"


///Executor
class Executor : public Class
{
public:
	//Enumerations
	enum Behavior
	{
		_Foreground = 0,
		_Background = 1,
	};
private:
	//Members
	int       argc;
	char**    argv;
	Regex     regex;
	ElfLoader elf;

	//Methods
	void Sandbox();
public:
	//Methods
	Executor();
	~Executor();
	int Run(Behavior behavior, const char* args);
	int Run(Behavior behavior, const char* path, int argc, char* argv[]);
};

#endif //!__EXECUTOR_H__
