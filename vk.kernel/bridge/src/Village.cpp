//###########################################################################
// Village.cpp
// Definitions of the functions that manage Village
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "System.h"
#include "Village.h"


/// @brief Constructor
Village::Village()
{
}


/// @brief Destructor
Village::~Village()
{
}


/// @brief Reboot
void Village::Reboot()
{
	System::Reboot();
}


/// @brief Sleep
/// @param ticks 
void Village::Sleep(uint32_t ticks)
{
	Kernel::thread.Sleep(ticks);
}


/// @brief Get tasks
/// @return tasks
List<Thread::Task*> Village::GetTasks()
{
	return Kernel::thread.GetTasks();
}


/// @brief Get memory size
/// @return size
uint32_t Village::GetMemSize()
{
	return Kernel::memory.GetSize();
}


/// @brief Get memory used
/// @return used
uint32_t Village::GetMemUsed()
{
	return Kernel::memory.GetUsed();
}


/// @brief Get driver
/// @param id 
/// @return driver
Driver* Village::GetDriver(uint32_t id)
{
	return Kernel::device.GetDriver(id);
}


/// @brief Get driver by name
/// @param name 
/// @return drvier
Driver* Village::GetDriver(const char* name)
{
	return Kernel::device.GetDriver(name);
}


/// @brief Get module
/// @param id 
/// @return module
Module* Village::GetModule(uint32_t id)
{
	return Kernel::modular.GetModule(id);
}


/// @brief Get module by name
/// @param name 
/// @return module
Module* Village::GetModule(const char* name)
{
	return Kernel::modular.GetModule(name);
}


/// @brief 
/// @param observer 
void Village::AttachInput(InputObserver* observer)
{
	Input* input = (Input*)Kernel::modular.GetModule("input");
	if (NULL == input)
	{
		Kernel::debug.Error("loader feature not support");
		return;
	}
	input->Attach(observer);
}


/// @brief 
/// @param keycode 
/// @param status 
void Village::ReadInputEvent(uint8_t& keycode, int& status)
{
	Input* input = (Input*)Kernel::modular.GetModule("input");
	if (NULL == input)
	{
		Kernel::debug.Error("loader feature not support");
		return;
	}
	input->ReadEvent(keycode, status);
}


/// @brief 
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void Village::ReadInputMovement(int& axisX, int& axisY, int& axisZ)
{
	Input* input = (Input*)Kernel::modular.GetModule("input");
	if (NULL == input)
	{
		Kernel::debug.Error("loader feature not support");
		return;
	}
	input->ReadMovement(axisX, axisY, axisZ);
}


/// @brief Set debug level
/// @param level 
void Village::SetDebugLevel(int level)
{
	Kernel::debug.SetDebugLevel(level);
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
	return  __TIME__;
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
