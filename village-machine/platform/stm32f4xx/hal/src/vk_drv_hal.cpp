//###########################################################################
// vk_drv_hal.cpp
// Hardware Layer class that manages hal module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_kernel.h"
#include "vk_hardware.h"


/// @brief Delay ms
/// @param Delay 
void DelayMs(uint32_t ms)
{
    kernel->system.DelayMs(ms);
}


/// @brief Get tick
/// @param  
/// @return 
uint32_t GetTick(void)
{
  return kernel->system.GetSysClkCounts();;
}
