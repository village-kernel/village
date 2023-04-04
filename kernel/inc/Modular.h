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
#define REGISTER_MODULE(mod, id, name) CREATE_MODULE(Modular::Instance().RegisterModule(mod, id), name) MODULE_SECTION

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
	ModuleNode* list;

	//Methods
	Modular();
	static void Handler(Module* module);
public:
	//Methods
	void Initialize();
	void UpdateParams();
	void Execute();
	void FailSafe(int arg);
	void RegisterModule(Module* module, uint32_t id = 0);
	void DeregisterModule(Module* module, uint32_t id = 0);

	//Singleton Instance
	static Modular& Instance();
};

///Declarations modular reference
extern Modular& modular;

#endif // !__MODULAR_H__
