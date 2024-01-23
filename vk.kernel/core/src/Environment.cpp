//###########################################################################
// Environment.cpp
// Definitions of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Environment.h"
#include "Kernel.h"
#include "string.h"


/// @brief Constructor
Environment::Environment()
{
}


/// @brief Fini constructor
Environment::~Environment()
{
}


/// @brief Export symbol
/// @param symAddr symbol address
/// @param name symbol name
void Environment::ExportSymbol(uint32_t symAddr, const char* name)
{
	symbols.Add(new Symbol(name, symAddr));
}
EXPORT_SYMBOL(_ZN11Environment12ExportSymbolEmPKc);


/// @brief Unexport symbol
/// @param name symbol name
void Environment::UnexportSymbol(const char* name)
{
	for (Symbol* symbol = symbols.Begin(); !symbols.IsEnd(); symbol = symbols.Next())
	{
		if (0 == strcmp(name, symbol->name))
		{
			symbols.Remove(symbol, symbols.GetNid()); break;
		}
	}
}
EXPORT_SYMBOL(_ZN11Environment14UnexportSymbolEPKc);


/// @brief Search symbol by name and return addr
/// @param name symbol name
/// @return symbol address
uint32_t Environment::SearchSymbol(const char* name)
{
	for (Symbol* symbol = symbols.Begin(); !symbols.IsEnd(); symbol = symbols.Next())
	{
		if (0 == strcmp(name, symbol->name))
		{
			return symbol->addr;
		}
	}
	return 0;
}
EXPORT_SYMBOL(_ZN11Environment12SearchSymbolEPKc);
