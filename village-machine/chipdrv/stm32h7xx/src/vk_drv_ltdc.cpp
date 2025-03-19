//###########################################################################
// vk_drv_ltdc.cpp
// Hardware Layer class that manages a single hltdc module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_ltdc.h"


/// @brief Initialize
void Ltdc::Initialize(Config config)
{
    this->config = config;

    __HAL_RCC_LTDC_CLK_ENABLE();

    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.State = HAL_LTDC_STATE_RESET;

    hltdc.Init.HorizontalSync = config.hsw - 1;
    hltdc.Init.VerticalSync   = config.vsw - 1;
    hltdc.Init.AccumulatedHBP = config.hsw + config.hbp - 1;
    hltdc.Init.AccumulatedVBP = config.vsw + config.vbp - 1;
    hltdc.Init.AccumulatedActiveW = config.hsw + config.hbp + config.width - 1;
    hltdc.Init.AccumulatedActiveH = config.vsw + config.vbp + config.height - 1;
    hltdc.Init.TotalWidth = config.hsw + config.hbp + config.width + config.hfp - 1;
    hltdc.Init.TotalHeigh = config.vsw + config.vbp + config.height + config.vfp - 1;
    hltdc.Init.Backcolor.Red = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Blue = 0;
    HAL_LTDC_Init(&hltdc);
}


/// @brief Set clock freq
/// @param pll3n 
/// @param pll3m 
/// @param pll3r 
void Ltdc::SetClockFreq(uint32_t pll3n, uint32_t pll3m, uint32_t pll3r)
{
    RCC_PeriphCLKInitTypeDef periphclk_initure;
    periphclk_initure.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    periphclk_initure.PLL3.PLL3M = pll3m;
    periphclk_initure.PLL3.PLL3N = pll3n;
    periphclk_initure.PLL3.PLL3P = 2;
    periphclk_initure.PLL3.PLL3Q = 2;
    periphclk_initure.PLL3.PLL3R = pll3r;
    HAL_RCCEx_PeriphCLKConfig(&periphclk_initure);
}


/// @brief Layer param config
/// @param layerx 
/// @param bufaddr 
/// @param pixformat 
/// @param alpha 
/// @param alpha0 
/// @param bfac1 
/// @param bfac2 
/// @param bkcolor 
void Ltdc::LayerParamConfig(uint8_t layerIdx, uint32_t fbaddr, uint8_t pixformat, uint8_t alpha, uint8_t alpha0, uint8_t bfac1, uint8_t bfac2, uint32_t bkcolor)
{
    LTDC_LayerCfgTypeDef playercfg;
    playercfg.WindowX0 = 0;
    playercfg.WindowY0 = 0;
    playercfg.WindowX1 = config.width;
    playercfg.WindowY1 = config.height;
    playercfg.PixelFormat = pixformat;
    playercfg.Alpha  = alpha;
    playercfg.Alpha0 = alpha0;
    playercfg.BlendingFactor1 = (uint32_t)bfac1 << 8;
    playercfg.BlendingFactor2 = (uint32_t)bfac2 << 8;
    playercfg.FBStartAdress = fbaddr;
    playercfg.ImageWidth  = config.width;
    playercfg.ImageHeight = config.height;
    playercfg.Backcolor.Red   = (uint8_t)(bkcolor & 0X00FF0000) >> 16;
    playercfg.Backcolor.Green = (uint8_t)(bkcolor & 0X0000FF00) >> 8;
    playercfg.Backcolor.Blue  = (uint8_t)(bkcolor & 0X000000FF);
    HAL_LTDC_ConfigLayer(&hltdc, &playercfg, layerIdx);
}  


/// @brief Layer window config
/// @param layerIdx 
/// @param sx 
/// @param sy 
/// @param width 
/// @param height 
void Ltdc::LayerWindowConfig(uint8_t layerIdx, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
    HAL_LTDC_SetWindowPosition(&hltdc, sx, sy, layerIdx);
    HAL_LTDC_SetWindowSize(&hltdc, width, height, layerIdx);
}
