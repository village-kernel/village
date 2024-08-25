//###########################################################################
// Stm32Dma.h
// Works with an underlying DMA channel to create a circular FIFO for
// Asynchronous reception of bytes from a peripheral
// Note that this class is *not* thread safe due to shared resource <length>.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DMA_FIFO_H__
#define __DMA_FIFO_H__

#include "Hardware.h"


/// @brief Stm32Dma
class Stm32Dma
{
public:
	//Structures
	struct Config
	{
		uint8_t group;
		uint8_t stream;
		uint8_t request;
		uint8_t direction;
		void*   periphAddr;
	};
private:
	//Static Constants
	static const uint32_t buffer_size = 512;

	//Members
	Dma dma;
	uint32_t length;
	uint32_t dequeuePtr;
	uint32_t prevDmaDataCtr;
	uint8_t buffer[buffer_size] = { 0 };
private:
	//Methods
	void Update();
	uint8_t Dequeue();
	void Clear();
	void CopyTxData(uint8_t* data, uint16_t length);
public:
	//Methods
	Stm32Dma();
	void Open(Config config);
	int Write(uint8_t* data, uint32_t size, uint32_t offset = 0);
	int Read(uint8_t* data, uint32_t size, uint32_t offset = 0);
	void Close();
};

#endif // !__DMA_FIFO_H__
