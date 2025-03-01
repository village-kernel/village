//###########################################################################
// vk_stm32_uart.h
// Declarations of the functions that manage stm32 uart
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_STM32_UART_H__
#define __VK_STM32_UART_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_drv_gpio.h"
#include "vk_drv_usart.h"
#include "vk_stm32_dma.h"


/// @brief Stm32Uart
class Stm32Uart : public CharDriver
{
public:
    //Structures
    struct Config
    {
        Usart::Channel  usartCh;
        uint32_t        baudrate;
        bool            enableRTS;
        bool            enableDMA;

        Gpio::Config    txGpio;
        Gpio::Config    rxGpio;
        Gpio::Config    deGpio;

        Stm32Dma::Config txDma;
        Stm32Dma::Config rxDma;
    };
private:
    //Members
    Usart    usart;
    Stm32Dma txFifo;
    Stm32Dma rxFifo;
    Config   config;
    bool     isUsed;

    /// @brief Methods
    void PinConfig();
public:
    /// @brief Methods
    Stm32Uart();
    ~Stm32Uart();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief Fopts Methods
    bool Open();
    int Write(uint8_t* data, uint32_t size, uint32_t offset = 0);
    int Read(uint8_t* data, uint32_t size, uint32_t offset = 0);
    void Close();
};


/// @brief Stm32UartDrv
class Stm32UartDrv : public PlatDriver
{
public:
    /// @brief Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_STM32_UART_H__
