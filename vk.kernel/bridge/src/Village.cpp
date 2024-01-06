//###########################################################################
// Village.cpp
// Definitions of the functions that manage Village
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Debug.h"
#include "System.h"
#include "Kernel.h"
#include "Village.h"


/// @brief Constructor
Village::Village()
{
}


/// @brief Deconstructor
Village::~Village()
{
}


/// @brief Singleton Instance
/// @return Village instance
Village& Village::Instance()
{
	static Village instance;
	return instance;
}


/// @brief Definitions Village
Village& village = Village::Instance();


/// @brief Reboot
void Village::Reboot()
{
	System::Reboot();
}


/// @brief Sleep
/// @param ticks 
void Village::Sleep(uint32_t ticks)
{
	thread.Sleep(ticks);
}


/// @brief Get memory size
/// @return size
uint32_t Village::GetMemSize()
{
	return memory.GetSize();
}


/// @brief Get memory used
/// @return used
uint32_t Village::GetMemUsed()
{
	return memory.GetUsed();
}


/// @brief Get driver
/// @param id 
/// @return driver
Driver* Village::GetDriver(uint32_t id)
{
	return device.GetDriver(id);
}


/// @brief Get driver by name
/// @param name 
/// @return drvier
Driver* Village::GetDriverByName(const char* name)
{
	return device.GetDriverByName(name);
}


/// @brief Set debug level
/// @param level 
void Village::SetDebugLevel(int level)
{
	debug.SetDebugLevel(level);
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
