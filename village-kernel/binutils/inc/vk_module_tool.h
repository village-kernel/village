//###########################################################################
// vk_module_tool.h
// Declarations of the functions that manage module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_MODULE_TOOL_H__
#define __VK_MODULE_TOOL_H__

#include "vk_defines.h"
#include "vk_elf_loader.h"
#include "vk_list.h"


/// @brief ModuleTool
class ModuleTool
{
public:
	//Methods
	ModuleTool();
	~ModuleTool();
	VkList<ElfLoader*>* GetModules();
	bool Install(const char* filename);
	bool Uninstall(const char* filename);
};

#endif //!__VK_MODULE_TOOL_H__
