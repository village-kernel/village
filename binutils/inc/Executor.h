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


///Executor
class Executor : public Class
{
private:
	//Members
	int argc;
	char** argv;
	ElfLoader elf;

	//Methods
	void Sandbox();
public:
	//Methods
	Executor();
	~Executor();
	int Run(const char* path, int argc = 0, char* argv[] = NULL);
};

#endif //!__EXECUTOR_H__
