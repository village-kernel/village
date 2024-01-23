//###########################################################################
// Kernel.h
// Declarations of the functions that manage Kernel
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "Debug.h"
#include "Memory.h"
#include "Interrupt.h"
#include "Exception.h"
#include "Environment.h"
#include "Thread.h"
#include "Scheduler.h"
#include "Device.h"
#include "Modular.h"

/// @brief Kernel
class Kernel
{
public:
	//Members
	static Debug       debug;
	static Memory      memory;
	static Interrupt   interrupt;
	static Exception   exception;
	static Environment environment;
	static Thread      thread;
	static Scheduler   scheduler;
	static Device      device;
	static Modular     modular;
public:
	//Methods
	Kernel();
	~Kernel();
	static void Initialize();
	static void UpdateParams();
	static void Execute();
	static void FailSafe(int arg);
};

#endif // !__KERNEL_H__
