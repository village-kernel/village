//###########################################################################
// VkTicks.cpp
// Definitions of the functions that manage ticks
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_timer_ticks.h"
#include "vk_kernel.h"


/// @brief 
void VkTicks::Setup(GraphicsDevices* devices)
{

}


/// @brief 
void VkTicks::Exit()
{

}


/// @brief 
/// @return 
int VkTicks::GetTicks()
{
	return kernel->system.GetSysClkCounts();
}
