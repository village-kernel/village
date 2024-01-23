//###########################################################################
// Modular.h
// Declarations of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULAR_H__
#define __MODULAR_H__

#include "Module.h"
#include "Templates.h"


/// @brief Modular
class Modular : public Class
{
private:
	//Members
	States        status;
	List<Module*> modules;

	//Methods
	void RegisterInRuntime(Module* module);
	void DeregisterInRuntime(Module* module);
	void ModuleHandler(Module* module);
public:
	//Methods
	Modular();
	~Modular();
	void Initialize();
	void UpdateParams();
	void Execute();
	void FailSafe(int arg);
	void RegisterModule(Module* module, uint32_t id = 0);
	void DeregisterModule(Module* module, uint32_t id = 0);
	Module* GetModule(uint32_t id);
	Module* GetModule(const char* name);
};

#endif // !__MODULAR_H__
