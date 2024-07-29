//###########################################################################
// stm32f4xx_drv_dma.cpp
// Hardware Layer class that manages a single DMA module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stm32f4xx_drv_dma.h"


/// @brief Constructor
Dma::Dma()
	:streamReg(NULL),
	commonReg(NULL),
	flagClearReg(NULL),
	statusReg(NULL),
	flagOffset(0)
{
}


/// @brief Selects the DMA channel number
/// @param dmaGroup 
/// @param dmaChannel 
void Dma::Initialize(uint8_t dmaGroup, uint8_t dmaChannel)
{
	if (_DmaGroup1 == dmaGroup)
	{
		//Enable dma1 clock
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

		//Gets the DMA and stream register
		commonReg = DMA1;
		streamReg = DMA1_Stream0 + dmaChannel;
	}
	else if (_DmaGroup2 == dmaGroup)
	{
		//Enable dma2 clock
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
		
		//Gets the DMA and stream register
		commonReg = DMA2;
		streamReg = DMA2_Stream0 + dmaChannel;
	}

	if (dmaChannel <= _DmaStream3)
	{
		//Gets the status and flag clear register
		statusReg = &(commonReg->LISR);
		flagClearReg = &(commonReg->LIFCR);
		
		//Calaculate the flag offset
		if (dmaChannel == _DmaStream0 || dmaChannel == _DmaStream1)
			flagOffset = dmaChannel * 6;
		else
			flagOffset = dmaChannel * 6 + 4;
	}
	else if (dmaChannel >= _DmaStream4)
	{
		//Gets the status and flag clear register
		statusReg = &(commonReg->HISR);
		flagClearReg = &(commonReg->HIFCR);
		
		//Calaculate the flag offset
		if (dmaChannel == _DmaStream4 || dmaChannel == _DmaStream5)
			flagOffset = (dmaChannel - _DmaStream4) * 6;
		else
			flagOffset = (dmaChannel - _DmaStream4) * 6 + 4;
	}

	//Disable dma
	streamReg->CR &= ~DMA_SxCR_EN;
}


/// @brief Sets the DMA burst transfer
/// @param transfer 
void Dma::ConfigBurstTransfer(DmaMemBurstTrans transfer)
{
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_MBURST_Msk) | (transfer << DMA_SxCR_MBURST_Pos);
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_PBURST_Msk) | (transfer << DMA_SxCR_PBURST_Pos);
}


/// @brief Sets the DMA channel priority
/// @param dmaChPriority 
void Dma::ConfigPriority(DmaChPriority dmaChPriority)
{
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_PL_Msk) | (dmaChPriority << DMA_SxCR_PL_Pos);
}


/// @brief Set data transmission direction and data width of the transmission
/// @param dmaDataDir 
/// @param dmaDataSize 
void Dma::ConfigDirAndDataWidth(DmaDatDir dmaDataDir, DmaDataSize dmaDataSize)
{
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_DIR_Msk) | (dmaDataDir << DMA_SxCR_DIR_Pos);
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_MSIZE_Msk) | (dmaDataSize << DMA_SxCR_MSIZE_Pos);
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_PSIZE_Msk) | (dmaDataSize << DMA_SxCR_PSIZE_Pos);
	streamReg->FCR = (streamReg->FCR & ~DMA_SxFCR_FTH_Msk);
}


/// @brief Enables or disables increment mode on memory side and peripheral side
/// @param enaMemInc 
/// @param enaPeriphInc 
void Dma::ConfigIncMode(bool enaMemInc, bool enaPeriphInc)
{
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_MINC_Msk) | (enaMemInc << DMA_SxCR_MINC_Pos);
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_PINC_Msk) | (enaPeriphInc << DMA_SxCR_PINC_Pos);
}


/// @brief Enables or disables circular mode
/// @param isEnableCircularMode 
void Dma::ConfigCircularMode(bool isEnableCircularMode)
{
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_CIRC_Msk) | (isEnableCircularMode << DMA_SxCR_CIRC_Pos);
}


/// @brief Enable or disable DMA related interrupts, including interrupt when:
///        transfer error occurs, transfer half complete, transfer fully complete
/// @param enaXferErr 
/// @param enaHalfXfer 
/// @param enaFullXfer 
void Dma::ConfigInterrupts(bool enaXferErr, bool enaHalfXfer, bool enaFullXfer)
{
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_TEIE_Msk) | (enaXferErr << DMA_SxCR_TEIE_Pos);
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_HTIE_Msk) | (enaHalfXfer << DMA_SxCR_HTIE_Pos);
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_TCIE_Msk) | (enaFullXfer << DMA_SxCR_TCIE_Pos);
}


/// @brief Configure DMA request, must be configured, otherwise you can not use DMA transfer
/// @param request 
void Dma::ConfigRequest(uint8_t request)
{
	streamReg->CR = (streamReg->CR & ~DMA_SxCR_CHSEL_Msk) | (request << DMA_SxCR_CHSEL_Pos);
}


/// @brief Checks if a transfer is ready, this function should not be used in circular mode
/// @return 
bool Dma::IsReady()
{
	if (IsEnable() && !GetTransferCompleteFlag())
	{
		return false;
	}
	return true;
}


/// @brief Attempts to start transfer, if DMA is not currently busy
///        Returns whether transfer was initiated successfully
///        This method should not be used in circular mode, simply call Enable()
/// @return 
bool Dma::StartTransfer()
{
	if (IsReady())
	{
		Disable();
		ClearTransferCompleteFlag();
		Enable();
		return true;
	}
	return false;
}
