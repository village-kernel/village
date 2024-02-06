//###########################################################################
// Environment.h
// Declarations of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "Module.h"


/// @brief Environment
class Environment : public Module
{
public:
	//Methods
	virtual void ExportSymbol(uint32_t symAddr, const char* name) = 0;
	virtual void UnexportSymbol(const char* name) = 0;
	virtual uint32_t SearchSymbol(const char* name) = 0;
};

#endif //!__ENVIRONMENT_H__
