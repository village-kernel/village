//###########################################################################
// stm32h743_config.h
//
// Contains hardware configuration such as pin and peripheral assignments
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __HW_STM32H743_CONFIG_H__
#define __HW_STM32H743_CONFIG_H__


//*********************************Serial**********************************//
#define UART_SERIAL_CHANNEL                  1
#define UART_SERIAL_BAUD_RATE                115200
#define UART_SERIAL_RX_DMA_GROUP             1
#define UART_SERIAL_TX_DMA_GROUP             1
#define UART_SERIAL_RX_DMA_CHANNEL           2
#define UART_SERIAL_TX_DMA_CHANNEL           3
#define UART_SERIAL_RX_DMA_REQUEST           41
#define UART_SERIAL_TX_DMA_REQUEST           42
#define UART_SERIAL_ENABLEDMA                false

#define UART_SERIAL_RX_CH                    Gpio::_ChA
#define UART_SERIAL_RX_PIN                   10
#define UART_SERIAL_RX_AF_NUM                7

#define UART_SERIAL_TX_CH                    Gpio::_ChA
#define UART_SERIAL_TX_PIN                   9
#define UART_SERIAL_TX_AF_NUM                7


//*********************************lcd Pin*********************************//
#define LCD_BACK_LIGHT_CH                    Gpio::_ChG
#define LCD_BACK_LIGHT_PIN                   8

#define LCD_CS_CH                            Gpio::_ChG
#define LCD_CS_PIN                           12

#define LCD_RS_CH                            Gpio::_ChF
#define LCD_RS_PIN                           12

#define LCD_WR_CH                            Gpio::_ChD
#define LCD_WR_PIN                           5

#define LCD_RD_CH                            Gpio::_ChD
#define LCD_RD_PIN                           4

#define LCD_DB0_CH                           Gpio::_ChD
#define LCD_DB0_PIN                          14

#define LCD_DB1_CH                           Gpio::_ChD
#define LCD_DB1_PIN                          15

#define LCD_DB2_CH                           Gpio::_ChD
#define LCD_DB2_PIN                          0

#define LCD_DB3_CH                           Gpio::_ChD
#define LCD_DB3_PIN                          1

#define LCD_DB4_CH                           Gpio::_ChE
#define LCD_DB4_PIN                          7

#define LCD_DB5_CH                           Gpio::_ChE
#define LCD_DB5_PIN                          8

#define LCD_DB6_CH                           Gpio::_ChE
#define LCD_DB6_PIN                          9

#define LCD_DB7_CH                           Gpio::_ChE
#define LCD_DB7_PIN                          10

#define LCD_DB8_CH                           Gpio::_ChE
#define LCD_DB8_PIN                          11

#define LCD_DB9_CH                           Gpio::_ChE
#define LCD_DB9_PIN                          12

#define LCD_DB10_CH                          Gpio::_ChE
#define LCD_DB10_PIN                         13

#define LCD_DB11_CH                          Gpio::_ChE
#define LCD_DB11_PIN                         14

#define LCD_DB12_CH                          Gpio::_ChE
#define LCD_DB12_PIN                         15

#define LCD_DB13_CH                          Gpio::_ChD
#define LCD_DB13_PIN                         8

#define LCD_DB14_CH                          Gpio::_ChD
#define LCD_DB14_PIN                         9

#define LCD_DB15_CH                          Gpio::_ChD
#define LCD_DB15_PIN                         10


//********************************SpiFlash*********************************//
#define SPI_FLASH_SCK_CH                     Gpio::_ChF
#define SPI_FLASH_SCK_PIN                    7
#define SPI_FLASH_SCK_AF_NUM                 5

#define SPI_FLASH_MISO_CH                    Gpio::_ChF
#define SPI_FLASH_MISO_PIN                   8
#define SPI_FLAHS_MISO_AF_NUM                5

#define SPI_FLASH_MOSI_CH                    Gpio::_ChF
#define SPI_FLASH_MOSI_PIN                   9
#define SPI_FLASH_MOSI_AF_NUM                5

#define SPI_FLASH_CS_CH                      Gpio::_ChF
#define SPI_FLASH_CS_PIN                     6

#define SPI_FLASH_WP_CH                      Gpio::_ChF
#define SPI_FLASH_WP_PIN                     15

#define SPI_FLASH_CHANNEL                    Spi::_Spi5


//********************************SD Card*********************************//
#define SPI_SD_SCK_CH                        Gpio::_ChC
#define SPI_SD_SCK_PIN                       10
#define SPI_SD_SCK_AF_NUM                    6

#define SPI_SD_MISO_CH                       Gpio::_ChC
#define SPI_SD_MISO_PIN                      11
#define SPI_SD_MISO_AF_NUM                   6

#define SPI_SD_MOSI_CH                       Gpio::_ChC
#define SPI_SD_MOSI_PIN                      11
#define SPI_SD_MOSI_AF_NUM                   6

#define SPI_SD_CS_CH                         Gpio::_ChD
#define SPI_SD_CS_PIN                        2

#define SPI_SD_DETECT_CH                     Gpio::GpioChannel(NULL)
#define SPI_SD_DETECT_PIN                    uint8_t(NULL)

#define SPI_SD_CHANNEL                       Spi::_Spi3


#endif // !__HW_STM32H743_CONFIG_H__
