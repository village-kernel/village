//###########################################################################
// Environment.cpp
// Definitions of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Environment.h"
#include "string.h"


///Singleton instance
Environment& Environment::Instance()
{
	static Environment instance;
	return instance;	
}


///Constructor
Environment::Environment()
	:list(NULL)
{
}


///Export symbol
void Environment::ExportSymbol(Symbol* symbol)
{
	if (NULL == symbol) return;

	SymbolNode** nextNode = &list;

	while (NULL != *nextNode)
	{
		nextNode = &(*nextNode)->next;
	}

	*nextNode = new SymbolNode(symbol);
}


///Unexport symbol
void Environment::UnexportSymbol(Symbol* symbol)
{
	SymbolNode** prevNode = &list;
	SymbolNode** currNode = &list;

	while (NULL != *currNode)
	{
		if (symbol == (*currNode)->symbol)
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
