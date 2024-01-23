//###########################################################################
// ModuleTool.h
// Declarations of the functions that manage module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULE_TOOL_H__
#define __MODULE_TOOL_H__

#include "Defines.h"
#include "Templates.h"
#include "ElfLoader.h"


/// @brief ModuleTool
class ModuleTool
{
private:
	//Methods
	List<ElfLoader*>* GetModules();
public:
	//Methods
	ModuleTool();
	~ModuleTool();
	bool Initialize();
	bool Install(const char* filename);
	bool Uninstall(const char* filename);
};

#endif //!__MODULE_TOOL_H__
