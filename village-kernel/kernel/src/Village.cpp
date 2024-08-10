//###########################################################################
// Village.cpp
// Definitions of the functions that manage kernel
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Village.h"


/// @brief Constructor
Village::Village() : Kernel
(
	concreteSystem,
	concreteMemory,
	concreteDebug,
	concreteInterrupt,
	concreteScheduler,
	concreteThread,
	concreteWorkQueue,
	concreteInputEvent,
	concreteSymbol,
	concreteDevice,
	concreteFeature,
	concreteFilesys,
	concreteLoader,
	concreteProcess,
	concreteTimer,
	concreteTerminal
)
{
}


/// @brief Destructor
Village::~Village()
{
}


/// @brief Kernel Setup
void Village::Setup()
{
	//Setup interrupt
	concreteInterrupt.Setup();

	//Setup system
	concreteSystem.Setup();

	//Setup memory
	concreteMemory.Setup();

	//Setup device
	concreteDevice.Setup();

	//Setup debug
	concreteDebug.Setup();
	
	//Setup scheduler
	concreteScheduler.Setup();

	//Setup thread
	concreteThread.Setup();

	//Setup work queue
	concreteWorkQueue.Setup();

	//Setup input event
	concreteInputEvent.Setup();
	
	//Setup symbol
	concreteSymbol.Setup();

	//Setup timer
	concreteTimer.Setup();

	//Setup filesys
	concreteFilesys.Setup();

	//Setup terminal
	concreteTerminal.Setup();

	//Setup feature
	concreteFeature.Setup();

	//Setup loader
	concreteLoader.Setup();

	//Setup process
	concreteProcess.Setup();
}


/// @brief Kernel start
void Village::Start()
{
	//Start thread
	concreteThread.Start();

	//Start scheduler
	concreteScheduler.Start();

	//Should not go to here
	while (1) {}
}


/// @brief Kernel exit
void Village::Exit()
{
	//Exit process
	concreteProcess.Exit();

	//Exit loader
	concreteLoader.Exit();

	//Exit feature
	concreteFeature.Exit();

	//Exit terminal
	concreteTerminal.Exit();

	//Exit filesys
	concreteFilesys.Exit();

	//Exit timer
	concreteTimer.Exit();

	//Exit symbol
	concreteSymbol.Exit();

	//Exit input event
	concreteInputEvent.Exit();

	//Exit work queue
	concreteWorkQueue.Exit();

	//Exit thread
	concreteThread.Exit();

	//Exit scheduler
	concreteScheduler.Exit();

	//Exit debug
	concreteDebug.Exit();

	//Exit device
	concreteDevice.Exit();

	//Exit memory
	concreteMemory.Exit();

	//Exit system
	concreteSystem.Exit();

	//Exit interrupt
	concreteInterrupt.Exit();
}


/// @brief Get build date
/// @return date string
const char* Village::GetBuildDate()
{
	return __DATE__;
}


/// @brief Get build time
/// @return 
const char* Village::GetBuildTime()
{
	return __TIME__;
}


/// @brief Get build version
/// @return version string
const char* Village::GetBuildVersion()
{
	return BUILD_VER;
}


/// @brief Get build git commit
/// @return git commit
const char* Village::GetBuildGitCommit()
{
	return GIT_COMMIT;
}


/// @brief Kernel instance
/// @return kernel
Village& Village::Instance()
{
	static Village instance;
	return instance;
}


/// @brief Definition and export kernel
Kernel* kernel = &Village::Instance();
EXPORT_SYMBOL(kernel);


/// @brief Main entry function
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char* argv[])
{
	kernel->Setup();
	kernel->Start();
	kernel->Exit();
	return 0;
}
