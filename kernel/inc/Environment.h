//###########################################################################
// Environment.h
// Declarations of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "Templates.h"

#ifdef KBUILD_NO_ENVIRONNEMNT
	///Export symbol marco
	#define EXPORT_SYMBOL(symbol, name)    /*export symbol*/

	///Search symbol marco
	#define SEARCH_SYMBOL(name)            (0)
#else
	///Symbol section, avoid being optimized by the compiler
	#define SYMBOL_SECTION                 __attribute__((used,__section__(".symbols")))

	///Symbol create macro
	#define CREATE_SYMBOL(symbol, name)    static struct _Sym_##name{_Sym_##name(){symbol;}} const _sym_##name

	///Export symbol marco
	#define EXPORT_SYMBOL(symbol, name)    CREATE_SYMBOL(Environment::Instance().ExportSymbol(union_cast<uint32_t>(&symbol), #name), name) SYMBOL_SECTION

	///Search symbol marco
	#define SEARCH_SYMBOL(name)            Environment::Instance().SearchSymbol(name)
#endif

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
	SymbolNode* list;

	//Methods
	Environment();
public:
	//Methods
	void ExportSymbol(uint32_t symAddr, const char* name);
	void UnexportSymbol(uint32_t symAddr, const char* name);
	uint32_t SearchSymbol(const char* name);

	//Singleton Instance
	static Environment& Instance();
};

#endif //!__ENVIRONMENT_H__
