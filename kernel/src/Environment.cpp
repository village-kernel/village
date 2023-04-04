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
	:list(NULL)
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
	if (0 == symAddr) return;

	SymbolNode** nextNode = &list;

	while (NULL != *nextNode)
	{
		nextNode = &(*nextNode)->next;
	}

	*nextNode = new SymbolNode(new Symbol(name, symAddr));
}


///Unexport symbol
void Environment::UnexportSymbol(uint32_t symAddr, const char* name)
{
	SymbolNode** prevNode = &list;
	SymbolNode** currNode = &list;

	while (NULL != *currNode)
	{
		if ((symAddr == (*currNode)->symbol->addr) &&
			(0 == strcmp(name, (*currNode)->symbol->name)))
		{
			delete *currNode;

			if (*prevNode == *currNode)
				*prevNode = (*currNode)->next;
			else
				(*prevNode)->next = (*currNode)->next;

			break;
		}
		else
		{
			prevNode = currNode;
			currNode = &(*currNode)->next;
		}
	}
}


///Search symbol by name and return addr
uint32_t Environment::SearchSymbol(const char* name)
{
	for (volatile SymbolNode* node = list; NULL != node; node = node->next)
	{
		if (0 == strcmp(name, node->symbol->name))
		{
			return node->symbol->addr;
		}
	}
	return 0;
}
