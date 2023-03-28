//###########################################################################
// Executor.h
// Declarations of the functions that manage executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "Module.h"
#include "ElfParser.h"


///Executor
class Executor : public Module
{
private:
	//Members
	ElfParser elf;

	//Methods
	void Sandbox();
public:
	//Methods
	int Run(const char* path, char* argv[]);
};

#endif //!__EXECUTOR_H__
