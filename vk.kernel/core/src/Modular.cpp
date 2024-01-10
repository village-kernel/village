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
	:status(_NoneStates)
{
}


/// @brief Fini constructor
Modular::~Modular()
{
}


/// @brief Singleton Instance
/// @return Modular instance
Modular& Modular::Instance()
{
	static Modular instance;
	return instance;
}
EXPORT_SYMBOL(_ZN7Modular8InstanceEv);


/// @brief Definitions modular
Modular& modular = Modular::Instance();
EXPORT_SYMBOL(modular);


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
		module->SetPid(thread.CreateTask(module->GetName(), (Method)&Modular::ModuleHandler, this, (void*)module));
	}
	status = _EndedExecute;
}


/// @brief Modular execute handler
/// @param module module pointer
void Modular::ModuleHandler(Module* module)
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


/// @brief Register in runtime
/// @param module 
void Modular::RegisterInRuntime(Module* module)
{
	if (status >= _EndedInitialize)
		module->Initialize();
	if (status >= _EndedUpdateParms)
		module->UpdateParams();
	if (status >= _EndedExecute)
		module->SetPid(thread.CreateTask(module->GetName(), (Method)&Modular::ModuleHandler, this, (void*)module));
}


/// @brief Deregister in runtime
/// @param module 
void Modular::DeregisterInRuntime(Module* module)
{
	if (status >= _EndedExecute)
	{
		module->Exit();
		thread.DeleteTask(module->GetPid());
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
