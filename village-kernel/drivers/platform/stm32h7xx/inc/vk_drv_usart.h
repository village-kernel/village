//###########################################################################
// vk_drv_usart.h
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_USART_H__
#define __VK_DRV_USART_H__

#include "stm32h7xx_ll_usart.h"
#include "stm32h7xx_ll_bus.h"

/// @brief Usart
class Usart
{
public:
    //Enumerations
    enum Channel
    {
        _Usart1 = 1,
        _Usart2 = 2,
        _Usart3 = 3,
        _Usart4 = 4,
        _Usart5 = 5,
    };

    enum DataBits
    {
        _8Bits = LL_USART_DATAWIDTH_8B,
        _9Bits = LL_USART_DATAWIDTH_9B,
    };

    enum Parity
    {
        _NoParity = LL_USART_PARITY_NONE,
        _Parity = LL_USART_PARITY_EVEN,
    };

    enum StopBits
    {
        _1Stop = LL_USART_STOPBITS_1,
        _HalfStop = LL_USART_STOPBITS_0_5,
        _2Stop = LL_USART_STOPBITS_2,
        _1AndHalfStop = LL_USART_STOPBITS_1_5,
    };
private:
    //Members
    USART_TypeDef* UARTx;
public:
    //Methods
    Usart();
    void Initialize(Channel channel);
    void ConfigPortSettings(DataBits dataBits, Parity parity, StopBits stopBits);
    void ConfigDriverEnableMode(bool usingDEM = true, bool polarity = false);
    void ConfigReceiverTimeout(bool enable, uint32_t rto = 0, uint8_t blen = 0);
    void ConfigDma(bool dmaTxEnable = true, bool dmaRxEnable = true);
    void SetBaudRate(uint32_t baudRate, bool over8 = false);
    void CheckError();
    int Write(uint8_t* data, uint32_t size, uint32_t offset);
    int Read(uint8_t* data, uint32_t size, uint32_t offset);

    ///Enables operation of the USART peripheral
    inline void Enable() { LL_USART_Enable(UARTx); }

    ///Disables operation of the USART peripheral
    inline void Disable() { LL_USART_Disable(UARTx); }

    ///Gets the address of the transmit data register
    inline uint32_t* GetTxAddr() { return (uint32_t*)&(UARTx->TDR); }

    ///Gets the address of the receive data register
    inline uint32_t* GetRxAddr() { return (uint32_t*)&(UARTx->RDR); }

    ///Checks for Framing Errors
    inline bool CheckFramingError() { return LL_USART_IsActiveFlag_FE(UARTx); }

    ///Clears the Framing Error flag
    inline void ClearFramingError() { LL_USART_ClearFlag_FE(UARTx); }

    ///Clears the receiver timeout flag
    inline void ClearReceiverTimeoutFlag() { LL_USART_ClearFlag_RTO(UARTx); }

    ///Check if the send register is empty
    inline bool IsTxRegisterEmpty() { return LL_USART_IsActiveFlag_TXE(UARTx); }

    ///Check if the read date register not empty
    inline bool IsReadDataRegNotEmpty() { return LL_USART_IsActiveFlag_RXNE(UARTx); }

    ///Check if receiver timeout
    inline bool IsReceiverTimeout() { return LL_USART_IsActiveFlag_RTO(UARTx); }
};

#endif // !__VK_DRV_USART_H__
