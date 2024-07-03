//###########################################################################
// ElfExecutor.cpp
// Definitions of the functions that manage elf executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "ElfExecutor.h"


/// @brief ElfExecutor Execute
/// @return tid
int ElfExecutor::Execute()
{
	//Load, parser and execute bin file
	if (!elf.Load(path)) return 0;

	//Create a sandboxed thread to run the app
	return kernel->thread.CreateTask(path, (Method)&ElfExecutor::Sandbox, this);
}


/// @brief ElfExecutor execute app
void ElfExecutor::Sandbox()
{
	elf.Execute(NULL, argc, argv);
	elf.Exit();
}


/// @brief ElfExecutor release elf
/// @return 
bool ElfExecutor::Release()
{
	return elf.Exit();
}
