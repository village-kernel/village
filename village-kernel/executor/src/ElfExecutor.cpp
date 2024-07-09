//###########################################################################
// ElfExecutor.cpp
// Definitions of the functions that manage elf executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "ElfExecutor.h"


/// @brief ElfExecutor Initiate
/// @return tid
int ElfExecutor::Initiate()
{
	//Load, parser and execute elf file
	if (!elf.Load(path)) return 0;

	//Create a sandboxed thread to run the app
	return kernel->thread.CreateTask(path, (Method)&ElfExecutor::Sandbox, this);
}


/// @brief ElfExecutor execute app
void ElfExecutor::Sandbox()
{
	elf.Execute(argc, argv);
	elf.Exit();
}


/// @brief ElfExecutor release elf
/// @return 
bool ElfExecutor::Release()
{
	return elf.Exit();
}


/// @brief ElfExecutorFty GetSuffixes
/// @return 
List<char*> ElfExecutorFty::GetSuffixes()
{
	List<char*> suffixes;
	suffixes.Add((char*)".elf");
	return suffixes;
}


/// @brief ElfExecutorFty Create
/// @return 
BaseExecutor* ElfExecutorFty::Create()
{
	return new ElfExecutor();
}


///Register executor
REGISTER_EXECUTOR(new ElfExecutorFty(), elfExecutor);
