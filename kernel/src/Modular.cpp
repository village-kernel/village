//###########################################################################
// Modular.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Modular.h"
#include "Thread.h"
#include "Environment.h"


///Constructor
Modular::Modular()
{
}


///Singleton instance
Modular& Modular::Instance()
{
	static Modular instance;
	return instance;
}
EXPORT_SYMBOL(Modular::Instance, _ZN7Modular8InstanceEv);


//Definitions modular
Modular& modular = Modular::Instance();


///Execute module object->Initialize
void Modular::Initialize()
{
	for (modules.Begin(); !modules.End(); modules.Next())
	{
		modules.Item()->Initialize();
	}
}


///Execute module object->UpdateParams
void Modular::UpdateParams()
{
	for (modules.Begin(); !modules.End(); modules.Next())
	{
		modules.Item()->UpdateParams();
	}
}


///Create task threads for each module
void Modular::Execute()
{
	for (modules.Begin(); !modules.End(); modules.Next())
	{
		thread.CreateTask((Function)&Modular::Handler, (char*)(modules.Item()));
	}
}


///Modular execute handler
void Modular::Handler(Module* module)
{
	module->Execute();
	modular.DeregisterModule(module);
}


///Execute module object->FailSafe
void Modular::FailSafe(int arg)
{
	for (modules.Begin(); !modules.End(); modules.Next())
	{
		modules.Item()->FailSafe(arg);
	}
}


///Register module object
void Modular::RegisterModule(Module* module, uint32_t id)
{
	modules.Add(module, id);
}
EXPORT_SYMBOL(Modular::RegisterModule, _ZN7Modular14RegisterModuleEP6Modulem);


///Deregister module object
void Modular::DeregisterModule(Module* module, uint32_t id)
{
	modules.Remove(module, id);
}
EXPORT_SYMBOL(Modular::DeregisterModule, _ZN7Modular16DeregisterModuleEP6Modulem);
