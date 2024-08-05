//###########################################################################
// stm32h7xx_drv_dma.h
// Hardware Layer class that manages a single DMA module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DMA_H__
#define __DMA_H__

#include "stm32h7xx_drv.h"


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

	enum DmaMemBurstTrans
	{
		_Single = 0b00,
		_Incr4  = 0b01,
		_Incr8  = 0b10,
		_Incr16 = 0b11,
	};

	enum DmaChPriority
	{
		_Low = 0b00,
		_Medium = 0b01,
		_High = 0b10,
		_VeryHigh = 0b11,
	};

	enum DmaDataSize
	{
		_8Bits = 0b00,
		_16Bits = 0b01,
		_32Bits = 0b10,
		_Reserved = 0b11,
	};

	enum DmaDatDir
	{
		_PeriphToMemory = 0b00,
		_MemoryToPeriph = 0b01,
		_MemoryToMemory = 0b10,
	};

	enum DmaInterruptType
	{
		_DmaDirectModeError = 1,
		_DmaTransferError,
		_DmaHalfTransfer,
		_DmaTransferComplete,
	};
protected:
	//Menbers
	volatile DMAMUX_ChannelStatus_TypeDef* muxStatusReg;
	volatile DMAMUX_Channel_TypeDef* muxChannelReg;
	volatile DMA_Stream_TypeDef* streamReg;
	volatile DMA_TypeDef* commonReg;
	volatile uint32_t* flagClearReg;
	volatile uint32_t* statusReg;
	volatile uint8_t flagOffset;
public:
	//Methods
	Dma();
	void Initialize(uint8_t group, uint8_t stream);
	void ConfigBurstTransfer(DmaMemBurstTrans transfer);
	void ConfigInterrupts(bool enaXferErr, bool enaHalfXfer, bool enaFullXfer);
	void ConfigDirAndDataWidth(DmaDatDir dmaDataDir, DmaDataSize dmaDataSize);
	void ConfigIncMode(bool enaMemInc, bool enaPeriphInc);
	void ConfigCircularMode(bool isEnableCircularMode);
	void ConfigPriority(DmaChPriority dmaChPriority);
	void ConfigRequest(uint8_t request);
	bool StartTransfer();
	bool IsReady();
	
	///Configure memory address 0
	inline void SetMemAddr0(void* memoryAddr) { streamReg->M0AR = (uint32_t)memoryAddr; };

	///COnfigure memory address 1
	inline void SetMemAddr1(void* memoryAddr) { streamReg->M1AR = (uint32_t)memoryAddr; };

	///Configure the peripheral address
	inline void SetPeriphAddr(void* periphAddr) { streamReg->PAR = (uint32_t)periphAddr; };

	///Configure the length of the data to be transmitted
	inline void SetDataLen(uint16_t len) { streamReg->NDTR = len; };

	///Gets the number of data that have yet to be transmitted
	inline uint32_t GetDataCounter() { return streamReg->NDTR; };

	///Enables DMA, in some cases, data transfer will begin immediately
	inline void Enable() { streamReg->CR |= DMA_SxCR_EN; };

	///Disable DMA
	inline void Disable() { streamReg->CR &= ~DMA_SxCR_EN; };

	///Get enable flag
	inline bool IsEnable() { return streamReg->CR & DMA_SxCR_EN; }

	///Configure dma interrupt
	inline void ConfigDmaInterrupt(DmaInterruptType type) { streamReg->CR |= (1 << type); }

	///Get fifo error flag
	inline bool GetFifoErrorFlag() { return *statusReg & (DMA_LISR_FEIF0 << flagOffset); }

	///Clear fifo error flag
	inline void ClearFifoErrorFlag() { *flagClearReg = (DMA_LIFCR_CFEIF0 << flagOffset); }

	///Get direct mode error flag
	inline bool GetDirectModeErrorFlag() { return *statusReg & (DMA_LISR_DMEIF0 << flagOffset); }

	///Clear direct mode error flag
	inline void ClearDirectModeErrorFlag() { *flagClearReg = (DMA_LIFCR_CDMEIF0 << flagOffset); }

	///Get transfer error flag
	inline bool GetTransferErrorFlag() { return *statusReg & (DMA_LISR_TEIF0 << flagOffset); }

	///Clear transfer error flag
	inline void ClearTransferErrorFlag() { *flagClearReg = (DMA_LIFCR_CTEIF0 << flagOffset); }

	///Get half transfer flag
	inline bool GetHalfTransferFlag() { return *statusReg & (DMA_LISR_HTIF0 << flagOffset); }

	///Clear half transfer flag
	inline void ClearHalfTransferFlag() { *flagClearReg = (DMA_LIFCR_CHTIF0 << flagOffset); }

	///Get transfer complete  flag
	inline bool GetTransferCompleteFlag() { return *statusReg & (DMA_LISR_TCIF0 << flagOffset); }

	///Clear transfer complete flag
	inline void ClearTransferCompleteFlag() { *flagClearReg = (DMA_LIFCR_CTCIF0 << flagOffset); }
};

#endif // !__DMA_H__
