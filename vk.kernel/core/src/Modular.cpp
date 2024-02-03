//###########################################################################
// Modular.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Modular.h"
#include "Kernel.h"
#include "Templates.h"


/// @brief ConcreteModular
class ConcreteModular : public Modular
{
private:
	//Members
	States        status;
	List<Module*> modules;
private:
	/// @brief Register in runtime
	/// @param module 
	void RegisterInRuntime(Module* module)
	{
		if (status >= _EndedInitialize)
			module->Initialize();
		if (status >= _EndedUpdateParms)
			module->UpdateParams();
		if (status >= _EndedExecute)
			module->SetPid(kernel->thread->CreateTask(module->GetName(), (Method)&ConcreteModular::ModuleHandler, this, (void*)module));
	}


	/// @brief Deregister in runtime
	/// @param module 
	void DeregisterInRuntime(Module* module)
	{
		if (status >= _EndedExecute)
		{
			module->Exit();
			kernel->thread->DeleteTask(module->GetPid());
		}
	}

	
	/// @brief Modular execute handler
	/// @param module module pointer
	void ModuleHandler(Module* module)
	{
		module->Execute();
	}

	
	/// @brief Register modules
	void RegisterModules()
	{
		extern ModuleInfo __modules_start;
		extern ModuleInfo __modules_end;

		uint32_t count = &__modules_end - &__modules_start;
		ModuleInfo* modules = &__modules_start;

		for (uint32_t i = 0; i < count; i++)
		{
			if (ModuleID::_modular != modules[i].id)
			{
				modules[i].module->SetName(modules[i].name);
				RegisterModule(modules[i].module, modules[i].id);
			}
		}
	}
public:
	/// @brief Constructor
	ConcreteModular()
		:status(_NoneStates)
	{
	}


	/// @brief Destructor
	~ConcreteModular()
	{
	}


	/// @brief Execute module object->Initialize
	void Initialize()
	{
		RegisterModules();
		
		status = _StartInitialize;
		for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
		{
			module->Initialize();
		}
		status = _EndedInitialize;
	}


	/// @brief Execute module object->UpdateParams
	void UpdateParams()
	{
		status = _StartUpdateParams;
		for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
		{
			module->UpdateParams();
		}
		status = _EndedUpdateParms;
	}


	/// @brief Create task threads for each module
	void Execute()
	{
		status = _StartExecute;
		for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
		{
			module->SetPid(kernel->thread->CreateTask(module->GetName(), (Method)&ConcreteModular::ModuleHandler, this, (void*)module));
		}
		status = _EndedExecute;
	}


	/// @brief Execute module object->FailSafe
	/// @param arg fail arg
	void FailSafe(int arg)
	{
		for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
		{
			module->FailSafe(arg);
		}
	}


	/// @brief Execute module object->Exit
	void Exit()
	{
		for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
		{
			module->Exit();
		}
	}


	/// @brief Register module object
	/// @param module module pointer
	/// @param id module id
	void RegisterModule(Module* module, uint32_t id)
	{
		modules.Insert(module, id, module->GetName());
		RegisterInRuntime(module);
	}


	/// @brief Deregister module object
	/// @param module module pointer
	/// @param id module id
	void DeregisterModule(Module* module, uint32_t id)
	{
		DeregisterInRuntime(module);
		modules.Remove(module, id);
	}


	/// @brief Get the module object
	/// @param id module id
	/// @return module
	Module* GetModule(uint32_t id)
	{
		return modules.GetItem(id);
	}


	/// @brief Get the module object by name
	/// @param name module name
	/// @return driver
	Module* GetModule(const char* name)
	{
		return modules.GetItemByName(name);
	}
}; 


///Register module
REGISTER_MODULE(ConcreteModular, ModuleID::_modular, modular);
