//###########################################################################
// Modular.h
// Declarations of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULAR_H__
#define __MODULAR_H__

#include "Module.h"

///Module section, avoid being optimized by the compiler
#define MODULE_SECTION                 __attribute__((used,__section__(".modules")))

///Module create macro
#define CREATE_MODULE(mod, name)       static struct _Mod_##name{_Mod_##name(){mod;}} const _mod_##name

///Module register macro
#define REGISTER_MODULE(mod, id, name) CREATE_MODULE(Modular::RegisterModule(mod, id), name) MODULE_SECTION

///Modular
class Modular
{
private:
	//Structures
	struct ModuleNode
	{
		Module* module;
		ModuleNode* next;

		ModuleNode(Module* module = NULL) :
			module(module),
			next(NULL)
		{}
	};
	
	//Static constants
	static const uint8_t initialize = 0;
	static const uint8_t updateparams = 1;
	static const uint8_t execute = 2;
	static const uint8_t failsafe = 3;
	
	//Members
	static ModuleNode* list;
public:
	//Methods
	Modular();
	static void Initialize();
	static void UpdateParams();
	static void Execute();
	static void FailSafe(int arg);
	static void RegisterModule(Module* module, uint32_t id);
	static void DeregisterModule(Module* module, uint32_t id);
};

#endif // !__MODULAR_H__
