//###########################################################################
// vk_lcd_ltdc.h
// Declarations of the functions that manage lcd of ltdc interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_LCD_LTDC_H__
#define __VK_LCD_LTDC_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_drv_gpio.h"
#include "vk_drv_ltdc.h"
#include "vk_drv_dma2d.h"


/// @brief LtdcLcd
class LtdcLcd : public FBDriver
{
public:
    //Structures
    struct Config
    {
        Gpio::Config blGpio;
        Gpio::Config deGpio;
        Gpio::Config vsGpio;
        Gpio::Config hsGpio;
        Gpio::Config clkGpio;
        
        Gpio::Config r3Gpio;
        Gpio::Config r4Gpio;
        Gpio::Config r5Gpio;
        Gpio::Config r6Gpio;
        Gpio::Config r7Gpio;

        Gpio::Config g2Gpio;
        Gpio::Config g3Gpio;
        Gpio::Config g4Gpio;
        Gpio::Config g5Gpio;
        Gpio::Config g6Gpio;
        Gpio::Config g7Gpio;

        Gpio::Config b3Gpio;
        Gpio::Config b4Gpio;
        Gpio::Config b5Gpio;
        Gpio::Config b6Gpio;
        Gpio::Config b7Gpio;

        uint32_t fbaddr;
        uint32_t pixelFormat;
    };
private:
    //Members
    Ltdc         ltdc;
    Dma2D        dma2d;
    Gpio         blGpio;
    Config       config;
    Ltdc::Config ltdcCfg;

    /// @brief Methods
    void PinConfig();
    void LtdcConfig();
    void BackLightOn();
    void BackLightOff();
public:
    /// @brief Methods
    LtdcLcd();
    ~LtdcLcd();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief FB Methods
    bool Setup();
    void DrawPoint(uint32_t x, uint32_t y, uint32_t color);
    uint32_t ReadPoint(uint32_t x, uint32_t y);
    void Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint32_t color);
    void Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint8_t* pxmap);
    void Clear(uint32_t color = 0);
    void Exit();

    /// @brief Fopts Methods
    bool Open();
    int IOCtrl(uint8_t cmd, void* data);
    void Close();
};


/// @brief LtdcLcdDrv
class LtdcLcdDrv : public PlatDriver
{
public:
    /// @brief Plat Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_LCD_LTDC_H__
