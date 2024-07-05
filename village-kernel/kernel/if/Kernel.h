//###########################################################################
// Kernel.h
// Declarations of the village interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"
#include "List.h"
#include "Driver.h"
#include "Module.h"


/// @brief System
class System
{
public:
	virtual void SysTickCounter() = 0;
	virtual uint32_t GetSysClkCounts() = 0;
	virtual void DelayMs(uint32_t millis) = 0;
	virtual void EnableIRQ() = 0;
	virtual void DisableIRQ() = 0;
	virtual void Reboot() = 0;
};


/// @brief Memory
class Memory
{
public:
	//Methods
	virtual uint32_t HeapAlloc(uint32_t size) = 0;
	virtual uint32_t StackAlloc(uint32_t size) = 0;
	virtual void Free(uint32_t memory, uint32_t size = 0) = 0;
	virtual uint32_t GetSize() = 0;
	virtual uint32_t GetUsed() = 0;
	virtual uint32_t GetCurrAddr() = 0;
};


/// @brief Debug
class Debug
{
public:
	//Debug level
	enum Level
	{
		_Lv0 = 0,
		_Lv1,
		_Lv2,
		_Lv3,
		_Lv4,
		_Lv5
	};
public:
	//Methods
	virtual void Log(const char* format, ...) = 0;
	virtual void Info(const char* format, ...) = 0;
	virtual void Error(const char* format, ...) = 0;
	virtual void Warn(const char* format, ...) = 0;
	virtual void Output(int level, const char* format, ...) = 0;
	virtual void SetDebugLevel(int level) = 0;
};


/// @brief Interrupt
class Interrupt
{
public:
	//Methods
	virtual int SetISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual int SetISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	virtual int AppendISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual int AppendISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	virtual bool RemoveISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual bool RemoveISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	virtual void ClearISR(int irq) = 0;
	virtual void Handler(int irq) = 0;
};


/// @brief Scheduler
class Scheduler
{
public:
	//Enumerations
	enum Access
	{
		Unprivileged = 0,
		Privileged = 1,
	};
public:
	//Methods
	virtual void Start() = 0;
	virtual void Sched(Access access) = 0;
};


/// @brief Thread
class Thread
{
public:
	//Enumerations
	enum TaskState 
	{
		Pending = 0,
		Running,
		Suspend,
		Blocked,
		Exited,
	};

	//Structures
	struct Task 
	{
		char*            name;
		uint32_t         tid;
		uint32_t         psp;
		uint32_t         ticks;
		uint32_t         stack;
		TaskState        state;
		
		Task(uint32_t stack = 0, char* name = NULL)
			:name(name),
			tid(-1),
			psp(0),
			ticks(0),
			stack(stack),
			state(TaskState::Pending)
		{}
	};
public:
	///Methods
	virtual int CreateTask(const char* name, Function function, void* user = NULL, void* args = NULL) = 0;
	virtual int CreateTask(const char* name, Method method, Class *user, void* args = NULL) = 0;
	virtual bool StartTask(int tid) = 0;
	virtual bool StopTask(int tid) = 0;
	virtual bool WaitForTask(int tid) = 0;
	virtual bool DeleteTask(int tid) = 0;
	virtual bool IsTaskAlive(int tid) = 0;
	virtual List<Task*> GetTasks() = 0;
	virtual void Sleep(uint32_t ticks) = 0;
	virtual void TaskExit() = 0;

	//Scheduler Methods
	virtual void SaveTaskPSP(uint32_t psp) = 0;
	virtual uint32_t GetTaskPSP() = 0;
	virtual void SelectNextTask() = 0;
	virtual void IdleTask() = 0;
};


/// @brief Symbol
class Symbol
{
public:
	//Methods
	virtual void Export(uint32_t symAddr, const char* name) = 0;
	virtual void Unexport(const char* name) = 0;
	virtual uint32_t Search(const char* name) = 0;
};


/// @brief Device
class Device
{
public:
	//Methods
	virtual void RegisterDriver(Driver* driver) = 0;
	virtual void DeregisterDriver(Driver* driver) = 0;
	virtual Driver* GetDriver(const char* name) = 0;
};


/// @brief Feature
class Feature
{
public:
	//Methods
	virtual void RegisterModule(Module* module) = 0;
	virtual void DeregisterModule(Module* module) = 0;
	virtual Module* GetModule(const char* name) = 0;
};


/// @brief FileSys
class FileSys;

/// @brief FileVol
class FileVol;

/// @brief FileSystem
class FileSystem
{
public:
	//Methods
	virtual void RegisterFS(FileSys* fs, const char* name) = 0;
	virtual void DeregisterFS(FileSys* fs, const char* name) = 0;
	virtual int AttachVolume(FileVol* volume) = 0;
	virtual int DetachVolume(FileVol* volume) = 0;
	virtual FileVol* GetVolume(const char* name) = 0;
};


/// @brief WorkQueue
class WorkQueue
{
public:
	//Enumerations
	enum State
	{
		_Suspend = 0,
		_Waked,
		_Running,
		_Finish,
	};

	//Structures
	struct Work
	{
		Function func;
		void*    user;
		void*    args;
		uint32_t ticks;
		State    state;

		Work(Function func, void* user, void* args, uint32_t ticks)
			:func(func),
			user(user),
			args(args),
			ticks(ticks),
			state(_Suspend)
		{}
	};
public:
	//Methods
	virtual Work* Create(Function func, void* user = NULL, void* args = NULL, uint32_t ticks = 0) = 0;
	virtual Work* Create(Method method, Class* user, void* args = NULL, uint32_t ticks = 0) = 0;
	virtual bool Delete(Work* work) = 0;
	virtual bool Sched(Work* work) = 0;
};


/// @brief InputEvent
class InputEvent
{
public:
	//Types
	enum EventType
	{
		_InputKey = 0,
		_InputAxis,
		_OutputText,
		_OutputAxis,
		_AllType,
	};

	//Output format
	enum OutFormat
	{
		_Noraml,
		_Terminal,
	};

	//Input key
	struct InputKey
	{
		int code;
		int status;

		InputKey()
			:code(0),
			status(0)
		{}
	};

	//Input axis
	struct InputAxis
	{
		int axisX;
		int axisY;
		int axisZ;

		InputAxis()
			:axisX(0),
			axisY(0),
			axisZ(0)
		{}
	};

	//Output text
	struct OutputText
	{
		char* data;
		int   size;

		OutputText()
			:data(NULL),
			size(0)
		{}
	};

	//Ouput Axis
	struct OutputAxis
	{
		int axisX;
		int axisY;
		int axisZ;

		OutputAxis()
			:axisX(0),
			axisY(0),
			axisZ(0)
		{}
	};
public:
	//Methods
	virtual void Attach(EventType type, Method method, Class* user) = 0;
	virtual void Attach(EventType type, Function func, void* user = NULL) = 0;
	virtual void Detach(EventType type, Method method, Class* user) = 0;
	virtual void Detach(EventType type, Function func, void* user = NULL) = 0;
	
	//Input Methods
	virtual void ReportKey(int code, int status) = 0;
	virtual void ReportAxis(int axisX, int axisY, int axisZ) = 0;

	//Output Methods
	virtual void PushChar(char chr) = 0;
	virtual void PushString(char* data, int size) = 0;
	virtual void PushAxis(int axisX, int axisY, int axisZ) = 0;
	virtual void SetOutFormat(OutFormat format) = 0;
	virtual OutFormat GetOutFormat() = 0;
};


/// @brief ElfLoader
class ElfLoader;

/// @brief Loader
class Loader
{
public:
	//Enumerations
	enum LoadType
	{
		_Load_Lib = 0,
		_Load_Mod,
	};
public:
	//Methods
	virtual void Loading(int type, const char* filename) = 0;
	virtual List<ElfLoader*>* GetLibraries() = 0;
	virtual List<ElfLoader*>* GetModules() = 0;
};


/// @brief Executor
class Executor;

/// @brief BaseExecutor
class BaseExecutor;

/// @brief Process
class Process
{
public:
	//Enumerations
	enum Behavior
	{
		_Foreground = 0,
		_Background = 1,
	};

	//Structures
	struct Data
	{
		char*         name;
		int           pid;
		int           tid;
		BaseExecutor* exec;

		Data(char* name = NULL)
			:name(name),
			pid(0),
			tid(0),
			exec(NULL)
		{}
	};
public:
	//Methods
	virtual void RegisterExecutor(Executor* executor) = 0;
	virtual void DeregisterExecutor(Executor* executor) = 0;
	virtual int Run(Behavior behavior, const char* args) = 0;
	virtual int Run(Behavior behavior, const char* path, int argc, char* argv[]) = 0;
	virtual bool Kill(const char* path) = 0;
	virtual bool Kill(int pid) = 0;
	virtual List<Data*> GetData() = 0;
};


/// @brief Timer
class Timer
{
public:
	//Enumerations
	enum State
	{
		_Ready = 0,
		_Done,
	};

	//Structures
	struct Job
	{
		Function func;
		void*    user;
		void*    args;
		uint32_t ticks;
		State    state;
		
		Job(uint32_t ticks, Function func, void* user, void* args)
			:func(func),
			user(user),
			args(args),
			ticks(ticks),
			state(_Ready)
		{}
	};
public:
	//Methods
	virtual Job* Create(uint32_t ticks, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual Job* Create(uint32_t ticks, Method method, Class* user, void* args = NULL) = 0;
	virtual void Modify(Job* job, uint32_t ticks) = 0;
	virtual bool Delete(Job* job) = 0;
};


/// @brief Kernel
class Kernel
{
public:
	/// @brief Members
	System&      system;
	Memory&      memory;
	Debug&       debug;
	Interrupt&   interrupt;
	Scheduler&   scheduler;
	Thread&      thread;
	WorkQueue&   workQueue;
	InputEvent&  inputEvent;
	Symbol&      symbol;
	Device&      device;
	Feature&     feature;
	FileSystem&  filesys;
	Loader&      loader;
	Process&     process;
	Timer&       timer;
public:
	/// @brief constructor
	Kernel(
		System&      system,
		Memory&      memory,
		Debug&       debug,
		Interrupt&   interrupt,
		Scheduler&   scheduler,
		Thread&      thread,
		WorkQueue&   workQueue,
		InputEvent&  inputEvent,
		Symbol&      symbol,
		Device&      device,
		Feature&     feature,
		FileSystem&  filesys,
		Loader&      loader,
		Process&     process,
		Timer&       timer
	)
		:system(system),
		memory(memory),
		debug(debug),
		interrupt(interrupt),
		scheduler(scheduler),
		thread(thread),
		workQueue(workQueue),
		inputEvent(inputEvent),
		symbol(symbol),
		device(device),
		feature(feature),
		filesys(filesys),
		loader(loader),
		process(process),
		timer(timer)
	{}

	/// @brief Destructor
	virtual ~Kernel() {}

	/// @brief Kernel Methods
	virtual void Setup() = 0;
	virtual void Start() = 0;
	virtual void Exit() = 0;

	/// @brief Kernel build info 
	virtual const char* GetBuildDate() = 0;
	virtual const char* GetBuildTime() = 0;
	virtual const char* GetBuildVersion() = 0;
	virtual const char* GetBuildGitCommit() = 0;
};

/// @brief Declarations kernel pointer
extern Kernel* kernel;

#endif //!__KERNEL_H__
