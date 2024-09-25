//###########################################################################
// Hal.cpp
// Hardware Layer class that manages hal module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Hardware.h"


/// @brief Override HAL_InitTick()
/// @param TickPriority 
/// @return 
extern "C" HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
	return HAL_OK;
}


/// @brief Override HAL_Delay()
/// @param Delay 
extern "C" void HAL_Delay(uint32_t Delay)
{
	kernel->system.DelayMs(Delay);
}


/// @brief OVerride HAL_GetTick()
/// @param  
/// @return 
extern "C" uint32_t HAL_GetTick(void)
{
  return kernel->system.GetSysClkCounts();;
}
