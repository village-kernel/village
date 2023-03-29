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
	
	//Members
	static ModuleNode* list;

	//Methods
	void Handler(Module* module);
public:
	//Methods
	Modular();
	static void Initialize();
	static void UpdateParams();
	static void Execute();
	static void FailSafe(int arg);
	static void RegisterModule(Module* module, uint32_t id = 0);
	static void DeregisterModule(Module* module, uint32_t id = 0);
};

#endif // !__MODULAR_H__
