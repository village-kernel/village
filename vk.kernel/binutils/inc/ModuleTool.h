//###########################################################################
// ModuleTool.h
// Declarations of the functions that manage module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULE_TOOL_H__
#define __MODULE_TOOL_H__

#include "Defines.h"
#include "ElfLoader.h"
#include "List.h"


/// @brief ModuleTool
class ModuleTool
{
public:
	//Methods
	ModuleTool();
	~ModuleTool();
	List<ElfLoader*>* GetModules();
	bool Install(const char* filename);
	bool Uninstall(const char* filename);
};

#endif //!__MODULE_TOOL_H__
