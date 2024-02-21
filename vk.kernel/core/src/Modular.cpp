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
			module->Setup();
		}

		isRuntime = true;
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
