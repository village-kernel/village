//###########################################################################
// vk_drv_dma.cpp
// Hardware Layer class that manages a single DMA module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_dma.h"


/// @brief Constructor
Dma::Dma()
    : DMAx(NULL),
      stream(0)
{
}


/// @brief Selects the DMA channel number
/// @param group 
/// @param stream 
void Dma::Initialize(uint8_t group, uint8_t stream)
{
    if (_Group1 == group)
    {
        // Enable DMA1 clock
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
        DMAx = DMA1;
    }
    else if (_Group2 == group)
    {
        // Enable DMA2 clock
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
        DMAx = DMA2;
    }

    // Set stream index
    this->stream = stream;

    // Disable DMA stream
    LL_DMA_DisableStream(DMAx, stream);
}


/// @brief Sets the DMA channel priority
/// @param dmaChPriority 
void Dma::ConfigPriority(DmaChPriority dmaChPriority)
{
    LL_DMA_SetStreamPriorityLevel(DMAx, stream, dmaChPriority);
}


/// @brief Set data transmission direction and data width of the transmission
/// @param dmaDataDir 
/// @param dmaDataSize 
void Dma::ConfigDirAndDataWidth(DmaDatDir dmaDataDir, DmaDataSize dmaDataSize)
{
    LL_DMA_SetDataTransferDirection(DMAx, stream, dmaDataDir);
    LL_DMA_SetMemorySize(DMAx, stream, dmaDataSize);
    LL_DMA_SetPeriphSize(DMAx, stream, dmaDataSize);
}


/// @brief Enables or disables increment mode on memory side and peripheral side
/// @param enaMemInc 
/// @param enaPeriphInc 
void Dma::ConfigIncMode(bool enaMemInc, bool enaPeriphInc)
{
    LL_DMA_SetMemoryIncMode(DMAx, stream, enaMemInc ? LL_DMA_MEMORY_INCREMENT : LL_DMA_MEMORY_NOINCREMENT);
    LL_DMA_SetPeriphIncMode(DMAx, stream, enaPeriphInc ? LL_DMA_PERIPH_INCREMENT : LL_DMA_PERIPH_NOINCREMENT);
}


/// @brief Enables or disables circular mode
/// @param isEnableCircularMode 
void Dma::ConfigCircularMode(bool isEnableCircularMode)
{
    LL_DMA_SetMode(DMAx, stream, isEnableCircularMode ? LL_DMA_MODE_CIRCULAR : LL_DMA_MODE_NORMAL);
}


/// @brief Configure DMA request
/// @param request 
void Dma::ConfigRequest(uint8_t request)
{
    LL_DMA_SetChannelSelection(DMAx, stream, request << DMA_SxCR_CHSEL_Pos);
}


/// @brief Get transfer complete flag
/// @return 
bool Dma::GetTransferCompleteFlag()
{
    if (_Stream0 == stream)
        return LL_DMA_IsActiveFlag_TC0(DMAx);
    else if (_Stream1 == stream)
        return LL_DMA_IsActiveFlag_TC1(DMAx);
    else if (_Stream2 == stream)
        return LL_DMA_IsActiveFlag_TC2(DMAx);
    else if (_Stream3 == stream)
        return LL_DMA_IsActiveFlag_TC3(DMAx);
    else if (_Stream4 == stream)
        return LL_DMA_IsActiveFlag_TC4(DMAx);
    else if (_Stream5 == stream)
        return LL_DMA_IsActiveFlag_TC5(DMAx);
    else if (_Stream6 == stream)
        return LL_DMA_IsActiveFlag_TC6(DMAx);
    else if (_Stream7 == stream)
        return LL_DMA_IsActiveFlag_TC7(DMAx);
    return false;
}


/// @brief Clear transfer complete flag
void Dma::ClearTransferCompleteFlag()
{
    if (_Stream0 == stream)
        LL_DMA_ClearFlag_TC0(DMAx);
    else if (_Stream1 == stream)
        LL_DMA_ClearFlag_TC1(DMAx);
    else if (_Stream2 == stream)
        LL_DMA_ClearFlag_TC2(DMAx);
    else if (_Stream3 == stream)
        LL_DMA_ClearFlag_TC3(DMAx);
    else if (_Stream4 == stream)
        LL_DMA_ClearFlag_TC4(DMAx);
    else if (_Stream5 == stream)
        LL_DMA_ClearFlag_TC5(DMAx);
    else if (_Stream6 == stream)
        LL_DMA_ClearFlag_TC6(DMAx);
    else if (_Stream7 == stream)
        LL_DMA_ClearFlag_TC7(DMAx);
}


/// @brief Checks if a transfer is ready
/// @return 
bool Dma::IsReady()
{
    return !(IsEnable() && !GetTransferCompleteFlag());
}
