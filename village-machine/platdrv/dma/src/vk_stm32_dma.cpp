//###########################################################################
// vk_stm32_dma.h
// Definitions of the functions that manage stm32 dma
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_stm32_dma.h"
#include "string.h"


/// @brief Constructor
Stm32Dma::Stm32Dma()
    :length(0),
    dequeuePtr(0),
    prevDmaDataCtr(buffer_size)
{
}


/// @brief Open the underlying DMA module
/// @param config 
void Stm32Dma::Open(Config config)
{
    dma.Initialize(config.group, config.stream);
    dma.ConfigPriority(Dma::_VeryHigh);
    dma.ConfigIncMode(true, false);
    dma.ConfigRequest(config.request);
    dma.SetPeriphAddr(config.periphAddr);

    if (Dma::_PeriphToMemory == config.direction)
    {    
        dma.ConfigDirAndDataWidth(Dma::_PeriphToMemory, Dma::_8Bits);
        dma.ConfigCircularMode(true);
        dma.SetDataLen(buffer_size);
        dma.SetMemAddr0(&buffer);
        dma.Enable();
        Clear();
    }
    else
    {
        dma.ConfigDirAndDataWidth(Dma::_MemoryToPeriph, Dma::_8Bits);
    }
}


/// @brief Copy the sent data to the send buffer to avoid accidentally modifying the sent data.
/// @param txData 
/// @param length 
inline void Stm32Dma::CopyTxData(uint8_t* data, uint16_t length)
{
    memcpy((uint8_t*)buffer, (uint8_t*)data, length);
}


/// @brief Dma fifo write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Stm32Dma::Write(uint8_t* data, uint32_t size, uint32_t offset)
{
    if (dma.IsReady())
    {
        CopyTxData(data + offset, size);

        //Reset pipeline, sync bus and memory access
        __asm ("dmb\n" "dsb\n" "isb\n");

        dma.Disable();
        dma.ClearTransferCompleteFlag();
        dma.SetMemAddr0(buffer);
        dma.SetDataLen(size);
        dma.Enable();

        return size;
    }
    return 0;
}


/// @brief Checks DMA counter and updates FIFO to reflect the latest data size
///        Must be executed periodically to ensure FIFO does not become corrupt
///        from multiple over pointer rollovers
void Stm32Dma::Update()
{
    uint32_t dmaDataCtr = dma.GetDataCounter();

    if (dmaDataCtr > prevDmaDataCtr)
        length += buffer_size + prevDmaDataCtr - dmaDataCtr;
    else
        length += prevDmaDataCtr - dmaDataCtr;

    prevDmaDataCtr = dmaDataCtr;
}


/// @brief Dequeues a single byte from the FIFO
///        Caller should check Length() before calling this function
/// @return 
uint8_t Stm32Dma::Dequeue()
{
    uint8_t b = buffer[dequeuePtr];
    if (length)
    {
        if (++dequeuePtr >= buffer_size) dequeuePtr = 0;
        --length;
    }
    return b;
}


/// @brief Clears the FIFO of all existing data, can be called without disabling the DMA
void Stm32Dma::Clear()
{ 
    prevDmaDataCtr = dma.GetDataCounter();
    dequeuePtr = buffer_size - prevDmaDataCtr;
    length = 0;
}


/// @brief Dma fifo read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Stm32Dma::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
    uint32_t readSize = 0;

    Update();

    while (length)
    {
        data[offset + readSize++] = Dequeue();

        if (readSize >= size) break;
    }

    return readSize;
}


/// @brief Close
void Stm32Dma::Close()
{
    dma.Disable();
}
