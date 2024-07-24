#include "Kernel.h"
#include "Hardware.h"

///Override HAL_InitTick()
extern "C" HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
	return HAL_OK;
}


///Override HAL_Delay()
extern "C" void HAL_Delay(uint32_t Delay)
{
	kernel->system.DelayMs(Delay);
}


///OVerride HAL_GetTick
extern "C" uint32_t HAL_GetTick(void)
{
  return kernel->system.GetSysClkCounts();;
}
