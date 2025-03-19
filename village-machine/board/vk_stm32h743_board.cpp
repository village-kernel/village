//###########################################################################
// vk_stm32h743_board.cpp
// Definitions of the functions that manage board config
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_kernel.h"
#include "vk_sdram_w9825g6.h"
#include "vk_sdio_sdcard.h"
#include "vk_stm32_uart.h"
#include "vk_lcd_ltdc.h"


/// @brief W9825G6Dev
class W9825G6Dev : public PlatDevice
{
private:
    /// @brief Members
    W9825G6::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .weGpio   = { Gpio::_ChC, Gpio::_Pin0,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .csGpio   = { Gpio::_ChC, Gpio::_Pin2,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .ckeGpio  = { Gpio::_ChC, Gpio::_Pin3,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .clkGpio  = { Gpio::_ChG, Gpio::_Pin8,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .casGpio  = { Gpio::_ChG, Gpio::_Pin15, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .rasGpio  = { Gpio::_ChF, Gpio::_Pin11, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },

            .ba0Gpio  = { Gpio::_ChG, Gpio::_Pin4,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .ba1Gpio  = { Gpio::_ChG, Gpio::_Pin5,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .bl0Gpio  = { Gpio::_ChE, Gpio::_Pin0,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .bl1Gpio  = { Gpio::_ChE, Gpio::_Pin1,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },

            .a0Gpio   = { Gpio::_ChF, Gpio::_Pin0,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a1Gpio   = { Gpio::_ChF, Gpio::_Pin1,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a2Gpio   = { Gpio::_ChF, Gpio::_Pin2,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a3Gpio   = { Gpio::_ChF, Gpio::_Pin3,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a4Gpio   = { Gpio::_ChF, Gpio::_Pin4,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a5Gpio   = { Gpio::_ChF, Gpio::_Pin5,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a6Gpio   = { Gpio::_ChF, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a7Gpio   = { Gpio::_ChF, Gpio::_Pin13, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a8Gpio   = { Gpio::_ChF, Gpio::_Pin14, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a9Gpio   = { Gpio::_ChF, Gpio::_Pin15, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a10Gpio  = { Gpio::_ChG, Gpio::_Pin0,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a11Gpio  = { Gpio::_ChG, Gpio::_Pin1,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .a12Gpio  = { Gpio::_ChG, Gpio::_Pin2,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },

            .db0Gpio  = { Gpio::_ChD, Gpio::_Pin14, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db1Gpio  = { Gpio::_ChD, Gpio::_Pin15, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db2Gpio  = { Gpio::_ChD, Gpio::_Pin0,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db3Gpio  = { Gpio::_ChD, Gpio::_Pin1,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db4Gpio  = { Gpio::_ChE, Gpio::_Pin7,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db5Gpio  = { Gpio::_ChE, Gpio::_Pin8,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db6Gpio  = { Gpio::_ChE, Gpio::_Pin9,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db7Gpio  = { Gpio::_ChE, Gpio::_Pin10, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db8Gpio  = { Gpio::_ChE, Gpio::_Pin11, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db9Gpio  = { Gpio::_ChE, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db10Gpio = { Gpio::_ChE, Gpio::_Pin13, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db11Gpio = { Gpio::_ChE, Gpio::_Pin14, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db12Gpio = { Gpio::_ChE, Gpio::_Pin15, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db13Gpio = { Gpio::_ChD, Gpio::_Pin8,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db14Gpio = { Gpio::_ChD, Gpio::_Pin9,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
            .db15Gpio = { Gpio::_ChD, Gpio::_Pin10, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
        };
        driverData = (void*)&config;
        driverName = (char*)"sdram0";
    }
};
REGISTER_PLAT_DEVICE(new W9825G6Dev(), w9825g6, w9825g6Dev);


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


/// @brief LtdcLcdDev
class LtdcLcdDev : public PlatDevice
{
private:
    /// @brief Members
    LtdcLcd::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .blGpio  = { Gpio::_ChB, Gpio::_Pin5,  Gpio::_Output, Gpio::_AF0,  Gpio::_Low },
            .deGpio  = { Gpio::_ChF, Gpio::_Pin10, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .vsGpio  = { Gpio::_ChI, Gpio::_Pin9,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .hsGpio  = { Gpio::_ChI, Gpio::_Pin10, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .clkGpio = { Gpio::_ChG, Gpio::_Pin7,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },

            .r3Gpio  = { Gpio::_ChH, Gpio::_Pin9,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .r4Gpio  = { Gpio::_ChH, Gpio::_Pin10, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .r5Gpio  = { Gpio::_ChH, Gpio::_Pin11, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .r6Gpio  = { Gpio::_ChH, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .r7Gpio  = { Gpio::_ChG, Gpio::_Pin6,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },

            .g2Gpio  = { Gpio::_ChH, Gpio::_Pin13, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .g3Gpio  = { Gpio::_ChH, Gpio::_Pin14, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .g4Gpio  = { Gpio::_ChH, Gpio::_Pin15, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .g5Gpio  = { Gpio::_ChI, Gpio::_Pin0,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .g6Gpio  = { Gpio::_ChI, Gpio::_Pin1,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .g7Gpio  = { Gpio::_ChI, Gpio::_Pin2,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },

            .b3Gpio  = { Gpio::_ChG, Gpio::_Pin11, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .b4Gpio  = { Gpio::_ChG, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .b5Gpio  = { Gpio::_ChI, Gpio::_Pin5,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .b6Gpio  = { Gpio::_ChI, Gpio::_Pin6,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },
            .b7Gpio  = { Gpio::_ChI, Gpio::_Pin7,  Gpio::_Altera, Gpio::_AF14, Gpio::_Low },

            .fbaddr  = 0xC0000000,
            .pixelFormat = LTDC_PIXEL_FORMAT_RGB565,
        };
        driverData = (void*)&config;
        driverName = (char*)"display0";
    }
};
REGISTER_PLAT_DEVICE(new LtdcLcdDev(), ltdcLcd, ltdcLcdDev);
