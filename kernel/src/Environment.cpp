//###########################################################################
// Environment.cpp
// Definitions of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Environment.h"
#include "string.h"


///Constructor
Environment::Environment()
{
}


///Singleton instance
Environment& Environment::Instance()
{
	static Environment instance;
	return instance;	
}


//Definitions environment
Environment& environment = Environment::Instance();


///Export symbol
void Environment::ExportSymbol(uint32_t symAddr, const char* name)
{
	symbols.Add(new Symbol(name, symAddr));
}


///Unexport symbol
void Environment::UnexportSymbol(const char* name)
{
	for (symbols.Begin(); !symbols.IsEnd(); symbols.Next())
	{
		if (0 == strcmp(name, symbols.Item()->name))
		{
			symbols.Remove(symbols.Item(), symbols.GetNid()); break;
		}
	}
}


///Search symbol by name and return addr
uint32_t Environment::SearchSymbol(const char* name)
{
	for (symbols.Begin(); !symbols.IsEnd(); symbols.Next())
	{
		if (0 == strcmp(name, symbols.Item()->name))
		{
			return symbols.Item()->addr;
		}
	}
	return 0;
}
