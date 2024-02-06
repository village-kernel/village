//###########################################################################
// Kernel.h
// Declarations of the functions that manage Kernel
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "System.h"
#include "Debug.h"
#include "Memory.h"
#include "Interrupt.h"
#include "Environment.h"
#include "Thread.h"
#include "Scheduler.h"
#include "Device.h"
#include "Modular.h"


/// @brief Kernel
class Kernel
{
public:
	/// @brief Members
	System*      system;
	Debug*       debug;
	Memory*      memory;
	Interrupt*   interrupt;
	Environment* environment;
	Thread*      thread;
	Scheduler*   scheduler;
	Device*      device;
	Modular*     modular;
public:
	/// @brief constructor
	Kernel()
		:debug(NULL),
		memory(NULL),
		interrupt(NULL),
		environment(NULL),
		thread(NULL),
		scheduler(NULL),
		device(NULL),
		modular(NULL)
	{}

	/// @brief Destructor
	virtual ~Kernel()
	{
	}

	/// @brief Kernel Methods
	virtual void Initialize() = 0;
	virtual void UpdateParams() = 0;
	virtual void Execute() = 0;
	virtual void FailSafe(int arg) = 0;
	virtual void Exit() = 0;

	/// @brief Kernel build info 
	virtual const char* GetBuildDate() = 0;
	virtual const char* GetBuildTime() = 0;
	virtual const char* GetBuildVersion() = 0;
	virtual const char* GetBuildGitCommit() = 0;
};

/// @brief Declarations kernel pointer
extern Kernel* kernel;

#endif // !__KERNEL_H__
