//###########################################################################
// vk_library_tool.h
// Declarations of the functions that manage library
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_LIBRARY_TOOL_H__
#define __VK_LIBRARY_TOOL_H__

#include "vk_defines.h"
#include "vk_elf_loader.h"
#include "vk_list.h"


/// @brief LibraryTool
class LibraryTool
{
public:
    //Methods
    LibraryTool();
    ~LibraryTool();
    VkList<ElfLoader*>* GetLibraries();
    bool Install(const char* filename);
    bool Uninstall(const char* filename);
    uint32_t SearchSymbol(const char* symbol);
};

#endif //!__VK_LIBRARY_TOOL_H__
