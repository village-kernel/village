//###########################################################################
// Environment.h
// Declarations of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "Templates.h"


///Environment
class Environment
{
private:
	//Structures
	struct Symbol
	{
		const char* name;
		uint32_t    addr;

		Symbol(const char* name, uint32_t addr):
			name(name),
			addr(addr)
		{}
	};

	//Members
	List<Symbol*> symbols;
public:
	//Methods
	Environment();
	~Environment();
	void ExportSymbol(uint32_t symAddr, const char* name);
	void UnexportSymbol(const char* name);
	uint32_t SearchSymbol(const char* name);
};

#endif //!__ENVIRONMENT_H__
