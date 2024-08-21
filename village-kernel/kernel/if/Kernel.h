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
	/// @brief Ticks Methods
	virtual void SysTickCounter() = 0;
	virtual uint32_t GetSysClkCounts() = 0;
	virtual void DelayMs(uint32_t millis) = 0;
	
	/// @brief IRQ Methods
	virtual void EnableIRQ() = 0;
	virtual void DisableIRQ() = 0;

	/// @brief Power Methods
	virtual void Sleep() = 0;
	virtual void Standby() = 0;
	virtual void Shutdown() = 0;
	virtual void Reboot() = 0;
};


/// @brief Memory
class Memory
{
public:
	/// @brief Alloc Methods
	virtual uint32_t HeapAlloc(uint32_t size) = 0;
	virtual uint32_t StackAlloc(uint32_t size) = 0;
	virtual void Free(uint32_t memory, uint32_t size = 0) = 0;
	
	/// @brief Info Methods
	virtual uint32_t GetSize() = 0;
	virtual uint32_t GetUsed() = 0;
	virtual uint32_t GetCurrAddr() = 0;
};


/// @brief Debug
class Debug
{
public:
	/// @brief Debug level
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
	/// @brief Methods
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
	/// @brief Set Methods
	virtual int SetISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual int SetISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	
	/// @brief Append Methods
	virtual int AppendISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual int AppendISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	
	/// @brief Remove Methods
	virtual bool RemoveISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual bool RemoveISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	
	/// @brief Clear Methods
	virtual void ClearISR(int irq) = 0;

	/// @brief Replace Methods
	virtual void Replace(int irq, uint32_t handler) = 0;

	/// @brief Feature Methods
	virtual void Handler(int irq) = 0;
};


/// @brief Scheduler
class Scheduler
{
public:
	/// @brief Methods
	virtual void Start() = 0;
	virtual void Sched() = 0;
};


/// @brief Thread
class Thread
{
public:
	/// @brief Enumerations
	enum TaskState 
	{
		_Pending = 0,
		_Running,
		_Suspend,
		_Blocked,
		_Exited,
	};

	/// @brief Structures
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
			state(TaskState::_Pending)
		{}
	};
public:
	/// @brief Create Methods
	virtual int CreateTask(const char* name, Function function, void* user = NULL, void* args = NULL) = 0;
	virtual int CreateTask(const char* name, Method method, Class *user, void* args = NULL) = 0;
	
	/// @brief Task Methods
	virtual bool StartTask(int tid) = 0;
	virtual bool StopTask(int tid) = 0;
	virtual bool WaitForTask(int tid) = 0;
	virtual bool DeleteTask(int tid) = 0;
	virtual bool IsTaskAlive(int tid) = 0;
	virtual List<Task*> GetTasks() = 0;
	
	/// @brief State Methods
	virtual void ChangeState(TaskState state) = 0;
	virtual void Sleep(uint32_t ticks) = 0;
	virtual void TaskExit() = 0;

	/// @brief Scheduler Methods
	virtual void SaveTaskPSP(uint32_t psp) = 0;
	virtual uint32_t GetTaskPSP() = 0;
	virtual void SelectNextTask() = 0;
	virtual void IdleTask() = 0;
};


/// @brief Symbol
class Symbol
{
public:
	/// @brief Methods
	virtual void Export(uint32_t symAddr, const char* name) = 0;
	virtual void Unexport(const char* name) = 0;
	virtual uint32_t Search(const char* name) = 0;
};


/// @brief Device
class Device
{
public:
	/// @brief Block device methods
	virtual void RegisterBlockDevice(BlockDevice* device) = 0;
	virtual void DeregisterBlockDevice(BlockDevice* device) = 0;

	/// @brief Char device methods
	virtual void RegisterCharDevice(CharDevice* device) = 0;
	virtual void DeregisterCharDevice(CharDevice* device) = 0;

	/// @brief Framebuffer device methods
	virtual void RegisterFBDevice(FBDevice* device) = 0;
	virtual void DeregisterFBDevice(FBDevice* device) = 0;

	/// @brief Netwrok device methods
	virtual void RegisterNetworkDevice(NetworkDevice* device) = 0;
	virtual void DeregisterNetworkDevice(NetworkDevice* device) = 0;

	/// @brief Misc device methods
	virtual void RegisterMiscDevice(MiscDevice* device) = 0;
	virtual void DeregisterMiscDevice(MiscDevice* device) = 0;

	/// @brief Platform device methods
	virtual void RegisterPlatDevice(PlatDevice* device) = 0;
	virtual void DeregisterPlatDevice(PlatDevice* device) = 0;

	/// @brief Platform driver methods
	virtual void RegisterPlatDriver(PlatDriver* driver) = 0;
	virtual void DeregisterPlatDriver(PlatDriver* driver) = 0;

	/// @brief Data methods
	virtual FBDevice* GetDeviceFB(const char* name) = 0;
	virtual Fopts* GetDeviceFopts(const char* name) = 0;
	virtual List<Base*> GetDevices(DriverID id) = 0;
};


/// @brief Feature
class Feature
{
public:
	/// @brief Register Methods
	virtual void RegisterModule(Module* module) = 0;
	virtual void DeregisterModule(Module* module) = 0;
	
	/// @brief Data Methods
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
	/// @brief Register Methods
	virtual void RegisterFS(FileSys* fs, const char* name) = 0;
	virtual void DeregisterFS(FileSys* fs, const char* name) = 0;
	
	/// @brief Volume Methods
	virtual int AttachVolume(FileVol* volume) = 0;
	virtual int DetachVolume(FileVol* volume) = 0;
	virtual FileVol* GetVolume(const char* name) = 0;
};


/// @brief WorkQueue
class WorkQueue
{
public:
	/// @brief Enumerations
	enum State
	{
		_Suspend = 0,
		_Waked,
		_Running,
		_Finish,
	};

	/// @brief Structures
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
	/// @brief Create Methods
	virtual Work* Create(Function func, void* user = NULL, void* args = NULL, uint32_t ticks = 0) = 0;
	virtual Work* Create(Method method, Class* user, void* args = NULL, uint32_t ticks = 0) = 0;
	
	/// @brief Feature Methods
	virtual bool Delete(Work* work) = 0;
	virtual bool Sched(Work* work) = 0;
};


/// @brief InputEvent
class InputEvent
{
public:
	/// @brief Types
	enum EventType
	{
		_InputKey = 0,
		_InputAxis,
		_OutputText,
		_OutputAxis,
		_AllType,
	};

	/// @brief Output format
	enum OutFormat
	{
		_Noraml,
		_Terminal,
	};

	/// @brief Input key
	struct InputKey
	{
		int code;
		int status;

		InputKey()
			:code(0),
			status(0)
		{}
	};

	/// @brief Input axis
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

	/// @brief Output text
	struct OutputText
	{
		char* data;
		int   size;

		OutputText()
			:data(NULL),
			size(0)
		{}
	};

	/// @brief Ouput Axis
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
	/// @brief Attach Methods
	virtual void Attach(EventType type, Method method, Class* user) = 0;
	virtual void Attach(EventType type, Function func, void* user = NULL) = 0;
	virtual void Detach(EventType type, Method method, Class* user) = 0;
	virtual void Detach(EventType type, Function func, void* user = NULL) = 0;
	
	/// @brief Input Methods
	virtual void ReportKey(int code, int status) = 0;
	virtual void ReportAxis(int axisX, int axisY, int axisZ) = 0;

	/// @brief Output Methods
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
	/// @brief Enumerations
	enum LoadType
	{
		_Lib = 0,
		_Mod,
	};
public:
	/// @brief Load Methods
	virtual void Load(int type, const char* filename) = 0;
	virtual void Unload(int type, const char* filename) = 0;
	
	/// @brief Install Methods
	virtual bool Install(int type, const char* filename) = 0;
	virtual bool Uninstall(int type, const char* filename) = 0;
	
	/// @brief Data Methods
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
	/// @brief Enumerations
	enum Behavior
	{
		_Foreground = 0,
		_Background = 1,
	};

	/// @brief Structures
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
	/// @brief Register Methods
	virtual void RegisterExecutor(Executor* executor) = 0;
	virtual void DeregisterExecutor(Executor* executor) = 0;
	
	/// @brief Run Methods
	virtual int Run(Behavior behavior, const char* args) = 0;
	virtual int Run(Behavior behavior, const char* path, int argc, char* argv[]) = 0;
	
	/// @brief Kill Methods
	virtual bool Kill(const char* path) = 0;
	virtual bool Kill(int pid) = 0;
	
	/// @brief Data Methods
	virtual List<Data*> GetData() = 0;
};


/// @brief Timer
class Timer
{
public:
	/// @brief Enumerations
	enum State
	{
		_Ready = 0,
		_Done,
	};

	/// @brief Structures
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
	/// @brief Create Methods
	virtual Job* Create(uint32_t ticks, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual Job* Create(uint32_t ticks, Method method, Class* user, void* args = NULL) = 0;
	
	/// @brief Feature Methods
	virtual void Modify(Job* job, uint32_t ticks) = 0;
	virtual bool Delete(Job* job) = 0;
};


/// @brief Cmd
class Cmd;

/// @brief Console
class Console;

/// @brief Terminal
class Terminal
{
public:
	/// @brief Structures
	struct Sandbox
	{
		int           cid;
		int           tid;
		char*         driver;
		Console*      console;

		Sandbox(char* driver = NULL)
			:cid(0),
			tid(0),
			driver(driver),
			console(NULL)
		{}
	};
public:
	/// @brief Cmd Methods
	virtual void RegisterCmd(Cmd* cmd, char* name) = 0;
	virtual void DeregisterCmd(Cmd* cmd, char* name) = 0;
	virtual List<Cmd*> GetCmds() = 0;

	/// @brief Console Methods
	virtual int CreateConsole(const char* driver) = 0;
	virtual bool DestroyConsole(const char* driver) = 0;
	virtual List<Sandbox*> GetSandboxes() = 0;
};


/// @brief Signal
class Signal
{
public:
	/// @brief Feature Methods
	virtual void Raising(int signal) = 0;
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
	Terminal&    terminal;
	Signal&      signal;
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
		Timer&       timer,
		Terminal&    terminal,
		Signal&      signal
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
		timer(timer),
		terminal(terminal),
		signal(signal)
	{}

	/// @brief Destructor
	virtual ~Kernel() {}

	/// @brief Kernel Methods
	virtual void Setup() = 0;
	virtual void Start() = 0;
	virtual void Exit() = 0;

	/// @brief Power Methods
	virtual void Sleep() = 0;
	virtual void Standby() = 0;
	virtual void Shutdown() = 0;
	virtual void Reboot() = 0;
	
	/// @brief Kernel build info 
	virtual const char* GetBuildDate() = 0;
	virtual const char* GetBuildTime() = 0;
	virtual const char* GetBuildVersion() = 0;
	virtual const char* GetBuildGitCommit() = 0;
};

/// @brief Declarations kernel pointer
extern Kernel* kernel;

#endif //!__KERNEL_H__
