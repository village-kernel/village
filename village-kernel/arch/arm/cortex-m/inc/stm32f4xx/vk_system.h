//###########################################################################
// vk_system.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SYSTEM_H__
#define __VK_SYSTEM_H__

#include "vk_kernel.h"


/// @brief System
class ConcreteSystem : public System, public Class
{
private:
    /// @brief Static constants
    static const uint32_t microsInSec = 1000000;
    static const uint32_t microsInMilli = 1000;

    /// @brief Members
    uint32_t sysTicks;
    uint32_t cyclesInMicro;

    /// @brief Methods
    void SysTickHandler();
    void ConfigurePower();
    void ConfigCoreDebug();
    void ConfigSysTick();
    void ConfigureForHsi();
    void ConfigureForXtal();
public:
    /// @brief Methods
    ConcreteSystem();
    ~ConcreteSystem();
    void Setup();
    void Exit();

    /// @brief Ticks Methods
    void SysTickCounter();
    uint32_t GetSysClkCounts();
    void DelayUs(uint32_t micros);
    void DelayMs(uint32_t millis);

    /// @brief IRQ Methods
    void EnableIRQ();
    void DisableIRQ();

    /// @brief Power Methods
    void Sleep();
    void Standby();
    void Shutdown();
    void Reboot();
};

#endif //!__VK_SYSTEM_H__
