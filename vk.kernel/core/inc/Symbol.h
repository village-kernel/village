//###########################################################################
// Symbol.h
// Declarations of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include "Module.h"


/// @brief Symbol
class Symbol : public Module
{
public:
	//Methods
	virtual void Export(uint32_t symAddr, const char* name) = 0;
	virtual void Unexport(const char* name) = 0;
	virtual uint32_t Search(const char* name) = 0;
};

#endif //!__SYMBOL_H__
