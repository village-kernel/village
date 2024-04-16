//###########################################################################
// DmaFifo.h
// Works with an underlying DMA channel to create a circular FIFO for
// Asynchronous reception of bytes from a peripheral
// Note that this class is *not* thread safe due to shared resource <length>.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DMA_FIFO_H__
#define __DMA_FIFO_H__

#include "HalHeaders.h"
#include "Dma.h"

///DmaFifo
class DmaFifo
{
private:
	//Static Constants
	static const uint32_t BufferSize = 512;

	//Members
	Dma dma;
	uint8_t buffer[BufferSize] = { 0 };
	uint32_t prevDmaDataCtr;
	uint32_t dequeuePtr;
	uint32_t length;
public:
	//Methods
	DmaFifo();
	void Initialize(uint8_t dmaGroup, uint8_t dmaChannel, uint8_t dmaRequest, void* periphAddr);
	void Update();
	void Clear();
	uint8_t Dequeue();

	///Gets the amount of data within the buffer
	inline uint32_t Length() { return length; }

	///Enables the underlying DMA, allowing data to be received
	inline void Enable() { dma.Enable(); }

	///Disables the underlying DMA, preventing data to be received
	inline void Disable() { dma.Disable(); }
};

#endif // !__DMA_FIFO_H__
