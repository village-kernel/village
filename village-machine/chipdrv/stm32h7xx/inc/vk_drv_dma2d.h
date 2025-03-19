//###########################################################################
// vk_drv_dma2d.h
// Hardware Layer class that manages a single dma2d module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_DMA2D_H__
#define __VK_DRV_DMA2D_H__

#include "vk_hardware.h"


/// @brief Dma2D
class Dma2D
{
public:
    //Methods
    void Initialize(uint32_t pixformat, uint32_t offline);
    void RegToMem(uint32_t outAddr, uint32_t color, uint32_t size);
    void MemToMem(uint32_t outAddr, uint32_t fgAddr, uint32_t size);
    void Start();
    void Stop();
};

#endif //!__VK_DRV_DMA2D_H__
