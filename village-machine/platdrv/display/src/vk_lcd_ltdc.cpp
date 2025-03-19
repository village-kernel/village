//###########################################################################
// vk_lcd_ltdc.cpp
// Definitions of the functions that manage lcd of ltdc interface
//
// $Copyright: Copyright (C)
//###########################################################################
#include "vk_lcd_ltdc.h"
#include "vk_kernel.h"
#include "stdlib.h"


/// @brief Constructor
LtdcLcd::LtdcLcd()
{
}


/// @brief Destructor
LtdcLcd::~LtdcLcd()
{
}


/// @brief 
/// @param data 
void LtdcLcd::SetData(void* data)
{
    config = *((Config*)data);
}


/// @brief Pin config
inline void LtdcLcd::PinConfig()
{
    Gpio pin;
    
    pin.Initialize(config.deGpio);
    pin.Initialize(config.vsGpio);
    pin.Initialize(config.hsGpio);
    pin.Initialize(config.clkGpio);

    pin.Initialize(config.r3Gpio);
    pin.Initialize(config.r4Gpio);
    pin.Initialize(config.r5Gpio);
    pin.Initialize(config.r6Gpio);
    pin.Initialize(config.r7Gpio);
    
    pin.Initialize(config.g2Gpio);
    pin.Initialize(config.g3Gpio);
    pin.Initialize(config.g4Gpio);
    pin.Initialize(config.g5Gpio);
    pin.Initialize(config.g6Gpio);
    pin.Initialize(config.g7Gpio);
    
    pin.Initialize(config.b3Gpio);
    pin.Initialize(config.b4Gpio);
    pin.Initialize(config.b5Gpio);
    pin.Initialize(config.b6Gpio);
    pin.Initialize(config.b7Gpio);

    blGpio.Initialize(config.blGpio);
}


/// @brief Config lcd info
void LtdcLcd::LtdcConfig()
{
    ltdcCfg.width = 1024;
    ltdcCfg.height = 600;
    ltdcCfg.hsw = 20;
    ltdcCfg.vsw = 3; 
    ltdcCfg.hbp = 140;
    ltdcCfg.vbp = 20;
    ltdcCfg.hfp = 160;
    ltdcCfg.vfp = 12;
    ltdcCfg.pixsize = 2;

    info.width = ltdcCfg.width;
    info.height = ltdcCfg.height;
    info.bitdepth = 16; // 16 bpp

    ltdc.Initialize(ltdcCfg);
    ltdc.SetClockFreq(300, 25, 6);
    ltdc.LayerParamConfig(0, config.fbaddr, config.pixelFormat, 255, 0, 6, 7, 0x000000);
    ltdc.LayerWindowConfig(0, 0, 0, ltdcCfg.width, ltdcCfg.height);
}


/// @brief LtdcLcd display on
void LtdcLcd::BackLightOn()
{
    blGpio.Set();
}


/// @brief LtdcLcd display off
void LtdcLcd::BackLightOff()
{
    blGpio.Clear();
}


/// @brief LtdcLcd Setup
bool LtdcLcd::Setup()
{
    PinConfig();

    LtdcConfig();
    
    BackLightOn();

    Clear(0x1234);

    return true;
}


/// @brief LtdcLcd draw point
void LtdcLcd::DrawPoint(uint32_t x, uint32_t y, uint32_t color)
{
    *(uint16_t *)(config.fbaddr + ltdcCfg.pixsize * (ltdcCfg.width * y + x)) = color;
}


/// @brief LtdcLcd read point
uint32_t LtdcLcd::ReadPoint(uint32_t x, uint32_t y)
{
    return *(uint16_t *)(config.fbaddr + ltdcCfg.pixsize * (ltdcCfg.width * y + x));
}


/// @brief LtdcLcd fill color
void LtdcLcd::Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint32_t color)
{
    uint32_t offline = ltdcCfg.width - (ex - sx + 1);
    uint32_t outaddr = (config.fbaddr + ltdcCfg.pixsize * (ltdcCfg.width * sy + sx));
    uint32_t outsize = (ey - sy + 1) | ((ex - sx + 1) << 16);

    dma2d.Initialize(config.pixelFormat, offline);
    dma2d.RegToMem(outaddr, color, outsize);
    dma2d.Start();
}


/// @brief LtdcLcd fill pxmap
void LtdcLcd::Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint8_t* pxmap)
{
    uint32_t offline = ltdcCfg.width - (ex - sx + 1);
    uint32_t outaddr = (config.fbaddr + ltdcCfg.pixsize * (ltdcCfg.width * sy + sx));
    uint32_t outsize = (ey - sy + 1) | ((ex - sx + 1) << 16);

    dma2d.Initialize(config.pixelFormat, offline);
    dma2d.MemToMem(outaddr, (uint32_t)pxmap, outsize);
    dma2d.Start();
}


/// @brief LtdcLcd clear
void LtdcLcd::Clear(uint32_t color)
{
    Fill(0, 0, ltdcCfg.width - 1, ltdcCfg.height - 1, color);
}


/// @brief LtdcLcd Exit
void LtdcLcd::Exit()
{

}


/// @brief Open
bool LtdcLcd::Open()
{
    return Setup();
}


/// @brief IOCtrl
/// @param cmd 
/// @param data 
/// @return 
int LtdcLcd::IOCtrl(uint8_t cmd, void* data)
{
    FBDriver** fbdev = (FBDriver**)data;

    *fbdev = this;

    return 0;
}


/// @brief close
void LtdcLcd::Close()
{
    Exit();
}


/// @brief Probe
/// @param device 
/// @return 
bool LtdcLcdDrv::Probe(PlatDevice* device)
{
    device->Attach(new LtdcLcd());
    kernel->device.RegisterFBDevice((FBDriver*)device->GetDriver());
    ((FBDriver*)device->GetDriver())->Open();
    return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool LtdcLcdDrv::Remove(PlatDevice* device)
{
    kernel->device.UnregisterFBDevice((FBDriver*)device->GetDriver());
    delete (LtdcLcd*)device->GetDriver();
    device->Detach();
    return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new LtdcLcdDrv(), ltdcLcd, ltdcLcdDrv);
