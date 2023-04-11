//###########################################################################
// Modular.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Modular.h"
#include "Thread.h"
#include "Environment.h"


/// @brief Constructor
Modular::Modular()
{
}


/// @brief Singleton Instance
/// @return Modular instance
Modular& Modular::Instance()
{
	static Modular instance;
	return instance;
}
EXPORT_SYMBOL(Modular::Instance, _ZN7Modular8InstanceEv);


/// @brief Definitions modular
Modular& modular = Modular::Instance();


/// @brief Execute module object->Initialize
void Modular::Initialize()
{
	for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
	{
		module->Initialize();
	}
}


/// @brief Execute module object->UpdateParams
void Modular::UpdateParams()
{
	for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
	{
		module->UpdateParams();
	}
}


/// @brief Create task threads for each module
void Modular::Execute()
{
	for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
	{
		thread.CreateTask((Function)&Modular::Handler, (char*)(module));
	}
}


/// @brief Modular execute handler
/// @param module module pointer
void Modular::Handler(Module* module)
{
	module->Execute();
	modular.DeregisterModule(module);
}


/// @brief Execute module object->FailSafe
/// @param arg fail arg
void Modular::FailSafe(int arg)
{
	for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
	{
		module->FailSafe(arg);
	}
}


/// @brief Register module object
/// @param module module pointer
/// @param id module id
void Modular::RegisterModule(Module* module, uint32_t id)
{
	modules.Insert(module, id);
}
EXPORT_SYMBOL(Modular::RegisterModule, _ZN7Modular14RegisterModuleEP6Modulem);


/// @brief Deregister module object
/// @param module module pointer
/// @param id module id
void Modular::DeregisterModule(Module* module, uint32_t id)
{
	modules.Remove(module, id);
}
EXPORT_SYMBOL(Modular::DeregisterModule, _ZN7Modular16DeregisterModuleEP6Modulem);
