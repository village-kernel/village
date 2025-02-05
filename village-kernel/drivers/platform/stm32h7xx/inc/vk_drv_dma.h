//###########################################################################
// vk_drv_dma.h
// Hardware Layer class that manages a single DMA module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_DMA_H__
#define __VK_DRV_DMA_H__

#include "stm32h7xx_ll_dma.h"
#include "stm32h7xx_ll_bus.h"

/// @brief Dma
class Dma
{
public:
    //Enumerations
    enum DmaGroup
    {
        _Group1 = 1,
        _Group2,
    };

    enum DmaStream
    {
        _Stream0 = 0,
        _Stream1,
        _Stream2,
        _Stream3,
        _Stream4,
        _Stream5,
        _Stream6,
        _Stream7,
    };

    enum DmaChPriority
    {
        _Low = LL_DMA_PRIORITY_LOW,
        _Medium = LL_DMA_PRIORITY_MEDIUM,
        _High = LL_DMA_PRIORITY_HIGH,
        _VeryHigh = LL_DMA_PRIORITY_VERYHIGH,
    };

    enum DmaDataSize
    {
        _8Bits = LL_DMA_MDATAALIGN_BYTE,
        _16Bits = LL_DMA_PDATAALIGN_HALFWORD,
        _32Bits = LL_DMA_MDATAALIGN_WORD,
    };

    enum DmaDatDir
    {
        _PeriphToMemory = LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
        _MemoryToPeriph = LL_DMA_DIRECTION_MEMORY_TO_PERIPH,
        _MemoryToMemory = LL_DMA_DIRECTION_MEMORY_TO_MEMORY,
    };
protected:
    //Members
    DMA_TypeDef* DMAx;
    uint32_t stream;
public:
    //Methods
    Dma();
    void Initialize(uint8_t group, uint8_t stream);
    void ConfigDirAndDataWidth(DmaDatDir dmaDataDir, DmaDataSize dmaDataSize);
    void ConfigIncMode(bool enaMemInc, bool enaPeriphInc);
    void ConfigCircularMode(bool isEnableCircularMode);
    void ConfigPriority(DmaChPriority dmaChPriority);
    void ConfigRequest(uint8_t request);
    bool GetTransferCompleteFlag();
    void ClearTransferCompleteFlag();
    bool IsReady();

    ///Configure memory address 0
    inline void SetMemAddr0(void* memoryAddr) { LL_DMA_SetMemoryAddress(DMAx, stream, (uint32_t)memoryAddr); }

    ///Configure memory address 1
    inline void SetMemAddr1(void* memoryAddr) { LL_DMA_SetMemoryAddress(DMAx, stream, (uint32_t)memoryAddr); }

    ///Configure the peripheral address
    inline void SetPeriphAddr(void* periphAddr) { LL_DMA_SetPeriphAddress(DMAx, stream, (uint32_t)periphAddr); }

    ///Configure the length of the data to be transmitted
    inline void SetDataLen(uint16_t len) { LL_DMA_SetDataLength(DMAx, stream, len); }

    ///Gets the number of data that have yet to be transmitted
    inline uint32_t GetDataCounter() { return LL_DMA_GetDataLength(DMAx, stream); }

    ///Enables DMA, in some cases, data transfer will begin immediately
    inline void Enable() { LL_DMA_EnableStream(DMAx, stream); }

    ///Disable DMA
    inline void Disable() { LL_DMA_DisableStream(DMAx, stream); }

    ///Get enable flag
    inline bool IsEnable() { return LL_DMA_IsEnabledStream(DMAx, stream); }
};

#endif // !__DMA_H__
