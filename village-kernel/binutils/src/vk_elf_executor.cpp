//###########################################################################
// vk_elf_executor.cpp
// Definitions of the functions that manage elf executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_elf_executor.h"
#include "vk_kernel.h"


/// @brief ElfExecutor Initiate
/// @return tid
int ElfExecutor::Initiate()
{
    //Load, parser and execute elf file
    if (!elf.Load(path)) return -1;

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
VkList<char*> ElfExecutorFty::GetSuffixes()
{
    VkList<char*> suffixes;
    suffixes.Add((char*)".elf");
#ifdef ASSOCIATED_EXEC_ELF
    suffixes.Add((char*)".exec");
#endif
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
