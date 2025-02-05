//###########################################################################
// vk_stm32f407_devices.cpp
// Definitions of the functions that manage devices config
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_stm32f407_devices.h"
#include "vk_kernel.h"


/// @brief SpiSdCardDev
void SpiSdCardDev::Config()
{
    config = {
        .spiCh    = Spi::_Spi3,
        .sckGpio  = { Gpio::_ChC, Gpio::_Pin10, Gpio::_Altera, Gpio::_AF6, Gpio::_Low  },
        .misoGpio = { Gpio::_ChC, Gpio::_Pin11, Gpio::_Altera, Gpio::_AF6, Gpio::_Low  },
        .mosiGpio = { Gpio::_ChC, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF6, Gpio::_Low  },
        .csGpio   = { Gpio::_ChB, Gpio::_Pin5,  Gpio::_Output, Gpio::_AF0, Gpio::_High },
        .dtGpio   = { Gpio::_ChB, Gpio::_Pin6,  Gpio::_Output, Gpio::_AF0, Gpio::_Low  },
    };
    driverData = (void*)&config;
    driverName = (char*)"disk0";
}
REGISTER_PLAT_DEVICE(new SpiSdCardDev(), spiSdCard, spiSdCardDev);


/// @brief SpiW25Q64Dev
void SpiW25Q64Dev::Config()
{
    config = {
        .spiCh    = Spi::_Spi2,
        .sckGpio  = { Gpio::_ChB, Gpio::_Pin13, Gpio::_Altera, Gpio::_AF5, Gpio::_Low  },
        .misoGpio = { Gpio::_ChB, Gpio::_Pin14, Gpio::_Altera, Gpio::_AF5, Gpio::_Low  },
        .mosiGpio = { Gpio::_ChB, Gpio::_Pin15, Gpio::_Altera, Gpio::_AF5, Gpio::_Low  },
        .csGpio   = { Gpio::_ChB, Gpio::_Pin12, Gpio::_Output, Gpio::_AF0, Gpio::_High },
        .wpGpio   = { Gpio::_ChF, Gpio::_Pin15, Gpio::_Output, Gpio::_AF0, Gpio::_High },
        .deviceID = 0xEF16,
    };
    driverData = (void*)&config;
    driverName = (char*)"disk1";
}
REGISTER_PLAT_DEVICE(new SpiW25Q64Dev(), spiW25qxx, spiW25Q64Dev);


/// @brief ILI9488Dev
void ILI9488Dev::Config()
{
    config = {
        .blGpio   = { Gpio::_ChG, Gpio::_Pin8,  Gpio::_Output, Gpio::_AF0,  Gpio::_Low },
        .csGpio   = { Gpio::_ChG, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
        .rsGpio   = { Gpio::_ChF, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
        .wrGpio   = { Gpio::_ChD, Gpio::_Pin5,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
        .rdGpio   = { Gpio::_ChD, Gpio::_Pin4,  Gpio::_Altera, Gpio::_AF12, Gpio::_Low },
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
    driverName = (char*)"display0";
}
REGISTER_PLAT_DEVICE(new ILI9488Dev(), ili9488, ili9488Dev);


/// @brief Stm32UartDev
void Stm32UartDev::Config()
{
    config = {
        .usartCh   = Usart::_Usart1,
        .baudrate  = 115200,
        .enableRTS = false,
        .enableDMA = true,

        .txGpio = { Gpio::_ChA, Gpio::_Pin9, Gpio::_Altera, Gpio::_AF7, Gpio::_Low },
        .rxGpio = { Gpio::_ChB, Gpio::_Pin7, Gpio::_Altera, Gpio::_AF7, Gpio::_Low },
        .deGpio = { 0, 0, 0, 0, 0 },

        .txDma = { Dma::_Group2, Dma::_Stream7, 4, Dma::_MemoryToPeriph, 0 },
        .rxDma = { Dma::_Group2, Dma::_Stream2, 4, Dma::_PeriphToMemory, 0 },
    };
    driverData = (void*)&config;
    driverName = (char*)"serial0";
}
REGISTER_PLAT_DEVICE(new Stm32UartDev(), stm32uart, stm32uartDev);


/// @brief Stm32UsbDev
void Stm32UsbDev::Config()
{
    config = {
        .irq = OTG_FS_IRQn,
        
        .dmGpio = { Gpio::_ChA, Gpio::_Pin11, Gpio::_Altera, Gpio::_AF10, Gpio::_Low },
        .dpGpio = { Gpio::_ChA, Gpio::_Pin12, Gpio::_Altera, Gpio::_AF10, Gpio::_Low },
    };
    driverData = (void*)&config;
    driverName = (char*)"usb0";
}
REGISTER_PLAT_DEVICE(new Stm32UsbDev(), stm32Usb, stm32UsbDev);
