//###########################################################################
// Bridge.cpp
// Definitions of the functions that manage bridge
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Bridge.h"


/// @brief Constructor
Bridge::Bridge()
{
}


/// @brief Deconstructor
Bridge::~Bridge()
{
}


/// @brief Get driver
/// @param id 
/// @return driver
Driver* Bridge::GetDriver(uint32_t id)
{
	return device.GetDriver(id);
}


/// @brief Get driver by name
/// @param name 
/// @return drvier
Driver* Bridge::GetDriverByName(const char* name)
{
	return device.GetDriverByName(name);
}
