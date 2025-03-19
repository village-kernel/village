//###########################################################################
// vk_drv_ltdc.h
// Hardware Layer class that manages a single ltdc module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_LTDC_H__
#define __VK_DRV_LTDC_H__

#include "vk_hardware.h"


/// @brief Ltdc
class Ltdc
{
public:
    //Config
    struct Config
    {
        uint16_t  width;
        uint16_t  height;
        uint16_t  hsw;
        uint16_t  vsw;
        uint16_t  hbp;
        uint16_t  vbp;
        uint16_t  hfp;
        uint16_t  vfp;
        uint16_t  pixsize;
    };
private:
    //Members
    Config config;
    LTDC_HandleTypeDef  hltdc;
public:
    //Methods
    void Initialize(Config config);
    void SetClockFreq(uint32_t pll3n, uint32_t pll3m, uint32_t pll3r);
    void LayerParamConfig(uint8_t layerIdx, uint32_t fbaddr, uint8_t pixformat, uint8_t alpha, uint8_t alpha0, uint8_t bfac1, uint8_t bfac2, uint32_t bkcolor);
    void LayerWindowConfig(uint8_t layerIdx, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);
};

#endif // !__VK_DRV_LTDC_H__
