//###########################################################################
// Kernel.h
// Declarations of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "Thread.h"
#include "Scheduler.h"
#include "Modular.h"
#include "Device.h"
#include "IOStream.h"

///Kernel
class Kernel
{
private:
	//Members
	static volatile bool isReady;
public:
	//Methods
	Kernel();
	static void Initialize();
	static void UpdateParams();
	static void Execute();
	static void FailSafe(int arg);
};

#endif // !__KERNEL_H__
