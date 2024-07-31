//###########################################################################
// ElfExecutor.h
// Declarations of the functions that manage elf executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ELF_EXECUTOR_H__
#define __ELF_EXECUTOR_H__

#include "BaseExecutor.h"
#include "Executor.h"
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
	int Initiate();
	void Sandbox();
	bool Release();
};


/// @brief ElfExecutorFty
class ElfExecutorFty : public Executor
{
public:
	List<char*> GetSuffixes();
	BaseExecutor* Create();
};

#endif //!__ELF_EXECUTOR_H__
