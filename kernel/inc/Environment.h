//###########################################################################
// Environment.h
// Declarations of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "stdint.h"
#include "stddef.h"

///Symbol section, avoid being optimized by the compiler
#define SYMBOL_SECTION                 __attribute__((used,__section__(".symbols")))

///Symbol create macro
#define CREATE_SYMBOL(symbol, name)    static struct _Sym_##name{_Sym_##name(){symbol;}} const _sym_##name

///Symbol class macro
#define SYMBOL_CLASS(symbol, name)     new Environment::Symbol(#name, (uint32_t)&symbol)

///Export symbol marco
#define EXPORT_SYMBOL(symbol, name)    CREATE_SYMBOL(Environment::ExportSymbol(SYMBOL_CLASS(symbol, name)), name) SYMBOL_SECTION

///Search symbol marco
#define SEARCH_SYMBOL(name)            Environment::SearchSymbol(name)

///Environment
class Environment
{
public:
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
private:
	//Structures
	struct SymbolNode
	{
		Symbol*     symbol;
		SymbolNode* next;

		SymbolNode(Symbol* symbol = NULL) :
			symbol(symbol),
			next(NULL)
		{}
	};

	//Members
	static SymbolNode* list;
public:
	//Methods
	static void ExportSymbol(Symbol* symbol);
	static void UnexportSymbol(Symbol* symbol);
	static uint32_t SearchSymbol(const char* name);
};

#endif //!__ENVIRONMENT_H__
