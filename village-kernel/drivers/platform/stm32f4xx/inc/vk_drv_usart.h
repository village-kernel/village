//###########################################################################
// vk_drv_ssart.h
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_USART_H__
#define __VK_DRV_USART_H__

#include "stm32f4xx.h"
#include "vk_drv_gpio.h"


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
    };

    //Enumerations
    enum DataBits
    {
        _8Bits = 0,
        _9Bits = 1,
    };

    enum Parity
    {
        _NoParity = 0,
        _Parity = 1,
    };

    enum StopBits
    {
        _1Stop = 0b00,
        _HalfStop = 0b01,
        _2Stop = 0b10,
        _1AndHalfStop = 0b11,
    };

    //Structures
    struct PinConfig
    {
        Gpio::GpioChannel ch;
        uint16_t pin;
        uint16_t alt;
    };    
private:
    //Members
    volatile USART_TypeDef* base;
    volatile Channel channel;
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
    inline void Enable() { base->CR1 |= USART_CR1_UE; }

    ///Disables operation of the USART peripheral
    inline void Disable() { base->CR1 &= ~USART_CR1_UE; }

    ///Gets the address of the transmit data register
    inline uint32_t* GetTxAddr() { return (uint32_t*)&(base->DR); }

    ///Gets the address of the receive data register
    inline uint32_t* GetRxAddr() { return (uint32_t*)&(base->DR); }

    ///Checks for Framing Errors
    inline bool CheckFramingError() { return (base->SR & USART_SR_FE_Msk); }

    ///Clears the Framing Error flag
    inline void ClearFramingError() { base->SR |= USART_SR_FE_Msk; }

    ///Clears the receiver timeout flag, not support
    inline void ClearReceiverTimeoutFlag() {  }

    ///Check if the send register is empty
    inline bool IsTxRegisterEmpty() { return bool(base->SR & USART_SR_TXE_Msk); }

    ///Check if the read date register not empty
    inline bool IsReadDataRegNotEmpty() { return bool(base->SR & USART_SR_RXNE_Msk); }

    ///Check if receiver timeout, not support
    inline bool IsReceiverTimeout() { return false; }
};

#endif //!__VK_DRV_USART_H__
