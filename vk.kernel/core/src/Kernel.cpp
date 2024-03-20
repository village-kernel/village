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
public:
	/// @brief Constructor
	ConcreteKernel()
	{
		extern System    psystem;
		extern Debug     pdebug;
		extern Memory    pmemory;
		extern Interrupt pinterrupt;
		extern Thread    pthread;
		extern Scheduler pscheduler;
		extern Symbol    psymbol;
		extern Device    pdevice;
		extern Feature   pfeature;

		this->system    = &psystem;
		this->debug     = &pdebug;
		this->memory    = &pmemory;
		this->interrupt = &pinterrupt;
		this->thread    = &pthread;
		this->scheduler = &pscheduler;
		this->symbol    = &psymbol;
		this->device    = &pdevice;
		this->feature   = &pfeature;
	}


	/// @brief Destructor
	~ConcreteKernel()
	{
	}
public:
	/// @brief Kernel instance
	/// @return kernel
	static ConcreteKernel& Instance()
	{
		static ConcreteKernel instance;
		return instance;
	}


	/// @brief Kernel Setup
	void Setup()
	{
		feature->Setup();
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
Kernel* kernel = &ConcreteKernel::Instance();
EXPORT_SYMBOL(kernel);
