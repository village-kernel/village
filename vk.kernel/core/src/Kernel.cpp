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
	Component* GetComponent(uint32_t id)
	{
		extern ComponentInfo __components_start;
		extern ComponentInfo __components_end;

		uint32_t count = &__components_end - &__components_start;
		ComponentInfo* components = &__components_start;

		for (uint32_t i = 0; i < count; i++)
		{
			if (id == components[i].id)
			{
				return components[i].body;
			}
		}
		return NULL;
	}


	/// @brief Init Component
	/// @return 
	uint32_t InitComponents()
	{
		//Gets the debug pointer
		debug = (Debug*)GetComponent(ComponentID::_debug);
		if (NULL == debug) return ComponentID::_debug;

		//Gets the memory pointer
		memory = (Memory*)GetComponent(ComponentID::_memory);
		if (NULL == memory) return ComponentID::_memory;

		//Gets the system pointer
		system = (System*)GetComponent(ComponentID::_system);
		if (NULL == system) return ComponentID::_system;

		//Gets the interrupt pointer
		interrupt = (Interrupt*)GetComponent(ComponentID::_interrupt);
		if (NULL == interrupt) return ComponentID::_interrupt;

		//Gets the thread pointer
		thread = (Thread*)GetComponent(ComponentID::_thread);
		if (NULL == thread) return ComponentID::_thread;
		
		//Gets the scheduler pointer
		scheduler = (Scheduler*)GetComponent(ComponentID::_scheduler);
		if (NULL == scheduler) return ComponentID::_scheduler;

		//Gets the symbol pointer
		symbol = (Symbol*)GetComponent(ComponentID::_symbol);
		if (NULL == symbol) return ComponentID::_symbol;

		//Gets the device pointer
		device = (Device*)GetComponent(ComponentID::_device);
		if (NULL == device) return ComponentID::_device;

		//Gets the feature pointer
		feature = (Feature*)GetComponent(ComponentID::_feature);
		if (NULL == feature) return ComponentID::_feature;

		return 0;
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
		if (0 == InitComponents())
		{
			feature->Setup();
		}
	}


	/// @brief Kernel start
	void Start()
	{
		//Start scheduler
		scheduler->Start();

		//Should not go to here
		while (1) {}
	}


	/// @brief Kernel exit
	void Exit()
	{
		feature->Exit();
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
