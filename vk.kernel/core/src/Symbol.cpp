//###########################################################################
// Symbol.cpp
// Definitions of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Symbol.h"
#include "Kernel.h"
#include "string.h"
#include "List.h"


/// @brief ConcreteSymbol
class ConcreteSymbol : public Symbol
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
private:
	/// @brief Export symbols
	void ExportSymbols()
	{
		extern SymbolInfo __symbols_start;
		extern SymbolInfo __symbols_end;

		uint32_t count = &__symbols_end - &__symbols_start;
		SymbolInfo* symbols = &__symbols_start;

		for (uint32_t i = 0; i < count; i++)
		{
			Export(symbols[i].addr, symbols[i].name);
		}
	}
public:
	/// @brief Constructor
	ConcreteSymbol()
	{
	}


	/// @brief Destructor
	~ConcreteSymbol()
	{
	}


	/// @brief Setup
	void Setup()
	{
		ExportSymbols();
	}


	/// @brief Exit
	void Exit()
	{
		symbols.Release();
	}


	/// @brief Export symbol
	/// @param symAddr symbol address
	/// @param name symbol name
	void Export(uint32_t symAddr, const char* name)
	{
		symbols.Add(new Symbol(name, symAddr));
	}


	/// @brief Unexport symbol
	/// @param name symbol name
	void Unexport(const char* name)
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
	uint32_t Search(const char* name)
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
};


///Register module
REGISTER_MODULE(ConcreteSymbol, ModuleID::_symbol, symbol);
