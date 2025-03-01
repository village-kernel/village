//###########################################################################
// vk_stm32h743_board.cpp
// Definitions of the functions that manage board config
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_kernel.h"
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
    void Config()
    {
        config = {
            .d0Gpio  = { Gpio::_ChC, Gpio::_Pin8,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .d1Gpio  = { Gpio::_ChC, Gpio::_Pin9,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .d2Gpio  = { Gpio::_ChC, Gpio::_Pin10, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .d3Gpio  = { Gpio::_ChC, Gpio::_Pin11, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .ckGpio  = { Gpio::_ChC, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .cmdGpio = { Gpio::_ChD, Gpio::_Pin2,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
        };
        driverData = (void*)&config;
        driverName = (char*)"disk0";
    }
};
REGISTER_PLAT_DEVICE(new SdioSdCardDev(), sdioSdCard, sdioSdCardDev);


/// @brief Stm32UartDev
class Stm32UartDev : public PlatDevice
{
private:
    /// @brief Members
    Stm32Uart::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .usartCh   = Usart::_Usart1,
            .baudrate  = 115200,
            .enableRTS = false,
            .enableDMA = true,

            .txGpio = { Gpio::_ChA, Gpio::_Pin9,  Gpio::_Altera, Gpio::_AF7, Gpio::_Low },
            .rxGpio = { Gpio::_ChA, Gpio::_Pin10, Gpio::_Altera, Gpio::_AF7, Gpio::_Low },
            .deGpio = { 0, 0, 0, 0, 0 },

            .txDma = { Dma::_Group1, Dma::_Stream2, 42, Dma::_MemoryToPeriph, 0 },
            .rxDma = { Dma::_Group1, Dma::_Stream3, 41, Dma::_PeriphToMemory, 0 },
        };
        driverData = (void*)&config;
        driverName = (char*)"serial0";
    }
};
REGISTER_PLAT_DEVICE(new Stm32UartDev(), stm32uart, stm32uartDev);
