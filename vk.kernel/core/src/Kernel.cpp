//###########################################################################
// Kernel.cpp
// Definitions of the functions that manage kernel
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"


/// @brief ConcreteKernel
class ConcreteKernel : public Kernel, public Class
{
private:
	/// @brief Get module
	/// @param id 
	/// @return 
	Module* GetModule(uint32_t id)
	{
		extern ModuleInfo __modules_start;
		extern ModuleInfo __modules_end;

		uint32_t count = &__modules_end - &__modules_start;
		ModuleInfo* modules = &__modules_start;

		for (uint32_t i = 0; i < count; i++)
		{
			if (id == modules[i].id)
			{
				return modules[i].module;
			}
		}
		return NULL;
	}


	/// @brief 
	/// @return 
	bool GetModules()
	{
		//Gets the debug pointer
		debug = (Debug*)GetModule(ModuleID::_debug);
		if (NULL == debug) return false;

		//Gets the memory pointer
		memory = (Memory*)GetModule(ModuleID::_memory);
		if (NULL == memory) { debug->Error("Gets the memory module failed!"); return false;} 

		//Gets the system pointer
		system = (System*)GetModule(ModuleID::_system);
		if (NULL == system) { debug->Error("Gets the system module failed!"); return false;} 

		//Gets the interrupt pointer
		interrupt = (Interrupt*)GetModule(ModuleID::_interrupt);
		if (NULL == interrupt) { debug->Error("Gets the interrupt module failed!"); return false;} 

		//Gets the environment pointer
		environment = (Environment*)GetModule(ModuleID::_environment);
		if (NULL == environment) { debug->Error("Gets the environment module failed!"); return false;} 

		//Gets the thread pointer
		thread = (Thread*)GetModule(ModuleID::_thread);
		if (NULL == thread) { debug->Error("Gets the thread module failed!"); return false;} 
		
		//Gets the scheduler pointer
		scheduler = (Scheduler*)GetModule(ModuleID::_scheduler);
		if (NULL == scheduler) { debug->Error("Gets the scheduler module failed!"); return false; }

		//Gets the device pointer
		device = (Device*)GetModule(ModuleID::_device);
		if (NULL == device) { debug->Error("Gets the device module failed!"); return false; }

		//Gets the modular pointer
		modular = (Modular*)GetModule(ModuleID::_modular);
		if (NULL == modular) { debug->Error("Gets the modular module failed!"); return false; }

		return true;
	}
public:
	/// @brief Constructor
	ConcreteKernel()
	{
	}


	/// @brief Destructor
	~ConcreteKernel()
	{
	}


	/// @brief Kernel Setup
	void Setup()
	{
		if (GetModules())
		{
			modular->Setup();
		}
	}


	/// @brief Kernel execute
	void Execute()
	{
		//Start scheduler
		scheduler->StartScheduler();

		//Should not go to here
		while (1) {}
	}


	/// @brief Kernel exit
	void Exit()
	{
		modular->Exit();
	}


	/// @brief Get build date
	/// @return date string
	const char* GetBuildDate()
	{
		return __DATE__;
	}


	/// @brief Get build time
	/// @return 
	const char* GetBuildTime()
	{
		return  __TIME__;
	}


	/// @brief Get build version
	/// @return version string
	const char* GetBuildVersion()
	{
		return BUILD_VER;
	}


	/// @brief Get build git commit
	/// @return git commit
	const char* GetBuildGitCommit()
	{
		return GIT_COMMIT;
	}
}; 


/// @brief Definition and export kernel
static ConcreteKernel concreteKernel;
Kernel* kernel = &concreteKernel;
EXPORT_SYMBOL(kernel);
