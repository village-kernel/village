//###########################################################################
// vk_stm32h743_devices.h
// Declarations of the functions that manage stm32h743 devices
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_STM32H743_DEVICES_H__
#define __VK_STM32H743_DEVICES_H__

#include "vk_sdio_sdcard.h"
#include "vk_stm32_uart.h"


/// @brief SpiSdCardDev
class SdioSdCardDev : public PlatDevice
{
private:
    /// @brief Members
    SdioSdCard::Config config;
public:
    /// @brief Methods
    void Config();
};


/// @brief Stm32UartDev
class Stm32UartDev : public PlatDevice
{
private:
    /// @brief Members
    Stm32Uart::Config config;
public:
    /// @brief Methods
    void Config();
};

#endif //!__VK_STM32H743_DEVICES_H__
