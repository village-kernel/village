//###########################################################################
// DmaFifo.h
// Works with an underlying DMA channel to create a circular FIFO for
// Asynchronous reception of bytes from a peripheral.
// Note that this class is *not* thread safe due to shared resource <length>.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DmaFifo.h"


///Default Constructor
DmaFifo::DmaFifo()
	:prevDmaDataCtr(BufferSize),
	dequeuePtr(0),
	length(0)
{
}


///Initializes the underlying DMA module
void DmaFifo::Initialize(uint8_t dmaGroup, uint8_t dmaChannel, uint8_t dmaRequest, void* periphAddr)
{
	dma.Initialize(dmaGroup, dmaChannel);
	dma.ConfigDirAndDataWidth(Dma::_PeriphToMemory, Dma::_8Bits);
	dma.ConfigIncMode(true, false);
	dma.ConfigCircularMode(true);
	dma.ConfigRequest(dmaRequest);
	
	dma.SetDataLen(BufferSize);
	dma.SetMemAddr0(&buffer);
	dma.SetPeriphAddr(periphAddr);
}


///Checks DMA counter and updates FIFO to reflect the latest data size
///Must be executed periodically to ensure FIFO does not become corrupt
///from multiple over pointer rollovers
void DmaFifo::Update()
{
	uint32_t dmaDataCtr = dma.GetDataCounter();

	if (dmaDataCtr > prevDmaDataCtr)
		length += BufferSize + prevDmaDataCtr - dmaDataCtr;
	else
		length += prevDmaDataCtr - dmaDataCtr;

	prevDmaDataCtr = dmaDataCtr;
}


///Dequeues a single byte from the FIFO
///Caller should check Length() before calling this function
uint8_t DmaFifo::Dequeue()
{
	uint8_t b = buffer[dequeuePtr];
	if (length)
	{
		if (++dequeuePtr >= BufferSize) dequeuePtr = 0;
		--length;
	}
	return b;
}


///Clears the FIFO of all existing data, can be called without disabling the DMA
void DmaFifo::Clear()
{ 
	prevDmaDataCtr = dma.GetDataCounter();
	dequeuePtr = BufferSize - prevDmaDataCtr;
	length = 0;
}
