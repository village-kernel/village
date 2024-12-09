//###########################################################################
// vk_elf_executor.h
// Declarations of the functions that manage elf executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_ELF_EXECUTOR_H__
#define __VK_ELF_EXECUTOR_H__

#include "vk_executor.h"
#include "vk_base_executor.h"
#include "vk_elf_loader.h"
#include "vk_class.h"


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
	VkList<char*> GetSuffixes();
	BaseExecutor* Create();
};

#endif //!__VK_ELF_EXECUTOR_H__
