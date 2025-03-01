//###########################################################################
// vk_pit32_timer.h
// Declarations of the functions that manage pit32 timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_PIT32_TIMER_H__
#define __VK_PIT32_TIMER_H__

#include "vk_hardware.h"
#include "vk_driver.h"


/// @brief Pit32Timer
class Pit32Timer : public MiscDriver
{
public:
    /// @brief Config
    struct Config
    {
        uint16_t timer;
    };
private:
    //Members
    Config config;
    uint32_t TIMERX[3] = {TIMER_CH0, TIMER_CH1, TIMER_CH2};
public:
    /// @brief Methods
    Pit32Timer();
    ~Pit32Timer();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief Fopts Methods
    bool Open();
    void Close();
};


/// @brief Pit32TimerDrv
class Pit32TimerDrv : public PlatDriver
{
public:
    /// @brief Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_PIT32_TIMER_H__
