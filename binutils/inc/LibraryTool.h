//###########################################################################
// LibraryTool.h
// Declarations of the functions that manage library
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LIBRARY_TOOL_H__
#define __LIBRARY_TOOL_H__

#include "Defines.h"


/// @brief LibraryTool
class LibraryTool
{
public:
	//Methods
	LibraryTool();
	~LibraryTool();
	bool Install(const char* filename);
	bool Uninstall(const char* filename);
	uint32_t SearchSymbol(const char* symbol);
};

#endif //!__LIBRARY_TOOL_H__
