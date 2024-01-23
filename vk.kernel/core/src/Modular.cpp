//###########################################################################
// Modular.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Modular.h"
#include "Kernel.h"


/// @brief Constructor
Modular::Modular()
	:status(_NoneStates)
{
}


/// @brief Fini constructor
Modular::~Modular()
{
}


/// @brief Execute module object->Initialize
void Modular::Initialize()
{
	status = _StartInitialize;
	for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
	{
		module->Initialize();
	}
	status = _EndedInitialize;
}


/// @brief Execute module object->UpdateParams
void Modular::UpdateParams()
{
	status = _StartUpdateParams;
	for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
	{
		module->UpdateParams();
	}
	status = _EndedUpdateParms;
}


/// @brief Create task threads for each module
void Modular::Execute()
{
	status = _StartExecute;
	for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
	{
		module->SetPid(Kernel::thread.CreateTask(module->GetName(), (Method)&Modular::ModuleHandler, this, (void*)module));
	}
	status = _EndedExecute;
}


/// @brief Modular execute handler
/// @param module module pointer
void Modular::ModuleHandler(Module* module)
{
	module->Execute();
	DeregisterModule(module);
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


/// @brief Register in runtime
/// @param module 
void Modular::RegisterInRuntime(Module* module)
{
	if (status >= _EndedInitialize)
		module->Initialize();
	if (status >= _EndedUpdateParms)
		module->UpdateParams();
	if (status >= _EndedExecute)
		module->SetPid(Kernel::thread.CreateTask(module->GetName(), (Method)&Modular::ModuleHandler, this, (void*)module));
}


/// @brief Deregister in runtime
/// @param module 
void Modular::DeregisterInRuntime(Module* module)
{
	if (status >= _EndedExecute)
	{
		module->Exit();
		Kernel::thread.DeleteTask(module->GetPid());
	}
}


/// @brief Register module object
/// @param module module pointer
/// @param id module id
void Modular::RegisterModule(Module* module, uint32_t id)
{
	modules.Insert(module, id, module->GetName());
	RegisterInRuntime(module);
}
EXPORT_SYMBOL(_ZN7Modular14RegisterModuleEP6Modulem);


/// @brief Deregister module object
/// @param module module pointer
/// @param id module id
void Modular::DeregisterModule(Module* module, uint32_t id)
{
	DeregisterInRuntime(module);
	modules.Remove(module, id);
}
EXPORT_SYMBOL(_ZN7Modular16DeregisterModuleEP6Modulem);


/// @brief Get the module object
/// @param id module id
/// @return module
Module* Modular::GetModule(uint32_t id)
{
	return modules.GetItem(id);
}
EXPORT_SYMBOL(_ZN7Modular9GetModuleEm);


/// @brief Get the module object by name
/// @param name module name
/// @return driver
Module* Modular::GetModuleByName(const char* name)
{
	return modules.GetItemByName(name);
}
EXPORT_SYMBOL(_ZN7Modular15GetModuleByNameEPKc);
