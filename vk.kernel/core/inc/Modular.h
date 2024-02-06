//###########################################################################
// Modular.h
// Declarations of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULAR_H__
#define __MODULAR_H__

#include "Module.h"


/// @brief Modular
class Modular : public Module
{
public:
	//Methods
	virtual void RegisterModule(Module* module, uint32_t id = 0) = 0;
	virtual void DeregisterModule(Module* module, uint32_t id = 0) = 0;
	virtual Module* GetModule(uint32_t id) = 0;
	virtual Module* GetModule(const char* name) = 0;
};

#endif // !__MODULAR_H__
