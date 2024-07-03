//###########################################################################
// ElfExecutor.h
// Declarations of the functions that manage elf executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ELF_EXECUTOR_H__
#define __ELF_EXECUTOR_H__

#include "BaseExecutor.h"
#include "ElfLoader.h"
#include "Class.h"


/// @brief ElfExecutor
class ElfExecutor : public BaseExecutor, public Class
{
private:
	//Members
	ElfLoader elf;
private:
	//Methods
	int Execute();
	void Sandbox();
	bool Release();
};

#endif //!__ELF_EXECUTOR_H__
