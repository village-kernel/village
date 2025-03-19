//###########################################################################
// vk_drv_dma2d.cpp
// Hardware Layer class that manages a single DMA2D module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_dma2d.h"


/// @brief Initialize
/// @param pixformat 
/// @param offline 
void Dma2D::Initialize(uint32_t pixformat, uint32_t offline)
{
    __HAL_RCC_DMA2D_CLK_ENABLE();

    DMA2D->CR &= ~(DMA2D_CR_START);
    DMA2D->OPFCCR = pixformat;
    DMA2D->OOR = offline;
}


/// @brief Register to memory
/// @param addr 
/// @param size 
/// @param color 
void Dma2D::RegToMem(uint32_t outAddr, uint32_t color, uint32_t size)
{
    DMA2D->CR    = DMA2D_R2M;
    DMA2D->OMAR  = outAddr;
    DMA2D->NLR   = size;
    DMA2D->OCOLR = color;
}


/// @brief Memory to Memory
/// @param addr 
/// @param size 
/// @param fbaddr 
void Dma2D::MemToMem(uint32_t outAddr, uint32_t fgAddr, uint32_t size)
{
    DMA2D->CR    = DMA2D_M2M;
    DMA2D->FGMAR = fgAddr;
    DMA2D->OMAR  = outAddr;
    DMA2D->NLR   = size;
}


/// @brief Start
void Dma2D::Start()
{
    uint32_t timeout = 0;

    DMA2D->CR |= DMA2D_CR_START;

    while ((DMA2D->ISR & (DMA2D_FLAG_TC)) == 0)
    {
        if (timeout++ > 0X1FFFFF) break;
    }

    DMA2D->IFCR |= DMA2D_FLAG_TC;
}


/// @brief Stop
void Dma2D::Stop()
{
    DMA2D->CR &= ~(DMA2D_CR_START);
}
