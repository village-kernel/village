//###########################################################################
// vk_sdram_w9825g6.h
// Declarations of the functions that manage sdram 29825g6
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SDRAM_W9825G6_H__
#define __VK_SDRAM_W9825G6_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_kernel.h"
#include "vk_drv_gpio.h"
#include "vk_drv_sdram.h"


/// @brief W9825G6
class W9825G6 : public CharDriver
{
public:
    //Structures
    struct Config
    {
        Gpio::Config weGpio;
        Gpio::Config csGpio;
        Gpio::Config ckeGpio;
        Gpio::Config clkGpio;
        Gpio::Config casGpio;
        Gpio::Config rasGpio;
        
        Gpio::Config ba0Gpio;
        Gpio::Config ba1Gpio;
        Gpio::Config bl0Gpio;
        Gpio::Config bl1Gpio;

        Gpio::Config a0Gpio;
        Gpio::Config a1Gpio;
        Gpio::Config a2Gpio;
        Gpio::Config a3Gpio;
        Gpio::Config a4Gpio;
        Gpio::Config a5Gpio;
        Gpio::Config a6Gpio;
        Gpio::Config a7Gpio;
        Gpio::Config a8Gpio;
        Gpio::Config a9Gpio;
        Gpio::Config a10Gpio;
        Gpio::Config a11Gpio;
        Gpio::Config a12Gpio;

        Gpio::Config db0Gpio;
        Gpio::Config db1Gpio;
        Gpio::Config db2Gpio;
        Gpio::Config db3Gpio;
        Gpio::Config db4Gpio;
        Gpio::Config db5Gpio;
        Gpio::Config db6Gpio;
        Gpio::Config db7Gpio;
        Gpio::Config db8Gpio;
        Gpio::Config db9Gpio;
        Gpio::Config db10Gpio;
        Gpio::Config db11Gpio;
        Gpio::Config db12Gpio;
        Gpio::Config db13Gpio;
        Gpio::Config db14Gpio;
        Gpio::Config db15Gpio;

        uint32_t refreshRate;
        uint32_t bankAddress;
    };
private:
    //Members
    Config config;
    SDRAM  sdram;

    //Methods
    void PinConfig();
    void SendCmd();
    void InitSequence();
public:
    /// @brief Methods
    W9825G6();
    ~W9825G6();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief Fopts Methods
    bool Open();
    void Close();
};


/// @brief W9825G6Drv
class W9825G6Drv : public PlatDriver
{
public:
    /// @brief Plat Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_SDRAM_W9825G6_H__
