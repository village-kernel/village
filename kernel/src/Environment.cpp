//###########################################################################
// Environment.cpp
// Definitions of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Environment.h"
#include "string.h"


/// @brief Constructor
Environment::Environment()
{
}


/// @brief Singleton Instance
/// @return Environment instance
Environment& Environment::Instance()
{
	static Environment instance;
	return instance;	
}


/// @brief Definitions environment
Environment& environment = Environment::Instance();


/// @brief Export symbol
/// @param symAddr symbol address
/// @param name symbol name
void Environment::ExportSymbol(uint32_t symAddr, const char* name)
{
	symbols.Add(new Symbol(name, symAddr));
}


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
