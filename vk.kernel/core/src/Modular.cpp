//###########################################################################
// Modular.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Modular.h"
#include "Kernel.h"
#include "List.h"


/// @brief ConcreteModular
class ConcreteModular : public Modular
{
private:
	//Members
	bool isRuntime;
	List<Module*> modules;
private:
	/// @brief Register in runtime
	/// @param module 
	void RegisterInRuntime(Module* module)
	{
		if (isRuntime) module->Setup();
	}


	/// @brief Deregister in runtime
	/// @param module 
	void DeregisterInRuntime(Module* module)
	{
		if (isRuntime) module->Exit();
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
			modules[i].module->SetID(modules[i].id);
			modules[i].module->SetName(modules[i].name);
			RegisterModule(modules[i].module);
		}
	}
public:
	/// @brief Constructor
	ConcreteModular()
		:isRuntime(false)
	{
	}


	/// @brief Destructor
	~ConcreteModular()
	{
	}


	/// @brief Execute module object->Setup
	void Setup()
	{
		isRuntime = false;

		RegisterModules();
		
		for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
		{
			if (ModuleID::_modular != module->GetID())
			{
				module->Setup();
			}
		}

		isRuntime = true;
	}


	/// @brief Execute module object->Exit
	void Exit()
	{
		for (Module* module = modules.Begin(); !modules.IsEnd(); module = modules.Next())
		{
			if (ModuleID::_modular != module->GetID())
			{
				module->Exit();
			}
		}
	}


	/// @brief Register module object
	/// @param module module pointer
	void RegisterModule(Module* module)
	{
		modules.Insert(module, module->GetID(), module->GetName());
		RegisterInRuntime(module);
	}


	/// @brief Deregister module object
	/// @param module module pointer
	void DeregisterModule(Module* module)
	{
		DeregisterInRuntime(module);
		modules.Remove(module, module->GetID());
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
