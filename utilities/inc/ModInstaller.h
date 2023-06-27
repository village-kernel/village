//###########################################################################
// ModInstaller.h
// Declarations of the functions that manage module installer
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MOD_INSTALLER_H__
#define __MOD_INSTALLER_H__

#include "Defines.h"
#include "Templates.h"
#include "ElfParser.h"

/// @brief ModInstaller
class ModInstaller
{
private:
	//Members
	static List<ElfParser> modules;
public:
	//Methods
	ModInstaller();
	~ModInstaller();
	bool Install(const char* module);
	bool Uninstall(const char* module);
};

#endif //!__MOD_INSTALLER_H__
