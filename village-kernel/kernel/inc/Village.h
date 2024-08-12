//###########################################################################
// Village.h
// Declarations of the functions that manage village
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VILLAGE_H__
#define __VILLAGE_H__

#include "Kernel.h"
#include "System.h"
#include "Memory.h"
#include "Debug.h"
#include "Interrupt.h"
#include "Scheduler.h"
#include "Thread.h"
#include "WorkQueue.h"
#include "InputEvent.h"
#include "Symbol.h"
#include "Device.h"
#include "Feature.h"
#include "FileSystem.h"
#include "Loader.h"
#include "Process.h"
#include "Timer.h"
#include "Terminal.h"
#include "Signal.h"


/// @brief Village
class Village : public Kernel
{
private:
	/// @brief Members
	ConcreteSystem      concreteSystem;
	ConcreteMemory      concreteMemory;
	ConcreteDebug       concreteDebug;
	ConcreteInterrupt   concreteInterrupt;
	ConcreteScheduler   concreteScheduler;
	ConcreteThread      concreteThread;
	ConcreteWorkQueue   concreteWorkQueue;
	ConcreteInputEvent  concreteInputEvent;
	ConcreteSymbol      concreteSymbol;
	ConcreteDevice      concreteDevice;
	ConcreteFeature     concreteFeature;
	ConcreteFileSystem  concreteFilesys;
	ConcreteLoader      concreteLoader;
	ConcreteProcess     concreteProcess;
	ConcreteTimer       concreteTimer;
	ConcreteTerminal    concreteTerminal;
	ConcreteSignal      concreteSignal;
private:
	/// @brief Methods
	Village();
	~Village();
public:
	/// @brief Kernel Methods
	void Setup();
	void Start();
	void Exit();

	/// @brief Power Methods
	void Sleep();
	void Standby();
	void Shutdown();
	void Reboot();

	/// @brief Kernel build info 
	const char* GetBuildDate();
	const char* GetBuildTime();
	const char* GetBuildVersion();
	const char* GetBuildGitCommit();

	/// @brief Static methods
	static Village& Instance();
};

#endif // !__VILLAGE_H__
