//###########################################################################
// ModManager.h
// Declarations of the functions that manage module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MOD_MANAGER_H__
#define __MOD_MANAGER_H__

#include "Defines.h"
#include "Templates.h"
#include "ElfParser.h"

/// @brief ModManager
class ModManager
{
private:
	//Members
	static List<ElfParser> modules;
public:
	//Methods
	ModManager();
	~ModManager();
	bool Install(const char* filename);
	bool Uninstall(const char* filename);
};

#endif //!__MOD_MANAGER_H__
