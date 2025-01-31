//###########################################################################
// vk_ps2_mouse.h
// Declarations of the functions that manage ps2 mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_PS2_MOUSE_H__
#define __VK_PS2_MOUSE_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_kernel.h"
#include "vk_ps2_controller.h"


/// @brief PS2Mouse
class PS2Mouse : public CharDriver, public Class
{
public:
    //Structures
    struct Config
    {
        uint32_t irq;
    };
private:
    //Packet union
    union Packet
    {
        uint8_t byte[4];
        struct
        {
            //Byte 0
            uint8_t leftBtn:1;
            uint8_t rightBtn:1;
            uint8_t middleBtn:1;
            uint8_t always1:1;
            uint8_t xSignBit:1;
            uint8_t ySignBit:1;
            uint8_t xOverflow:1;
            uint8_t yOverflow:1;
            //Byte 1
            uint8_t x;
            //Byte 2
            uint8_t y;
            //Byte 3
            uint8_t z;
        } __attribute__((packed));
    };

    //Members
    Config  config;
    uint8_t ack;
    uint8_t setting;
    uint8_t mouseid;
    uint8_t count;
    Packet  packet;

    //Status members
    bool isLeftBtnPressed;
    bool isRightBtnPressed;
    bool isMiddleBtnPressed;
    
    //Controller members
    PS2Controller ps2;
    
    //Work
    WorkQueue::Work* work;

    /// @brief Methods
    uint8_t MouseWriteData(uint8_t data);
    uint8_t MouseReadData();
    bool ConfigureMouse();
    void InputHandler();
    void  ReportHandler();
public:
    /// @brief Methods
    PS2Mouse();
    ~PS2Mouse();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief Fopts Methods
    bool Open();
    void Close();
};


/// @brief PS2MouseDrv
class PS2MouseDrv : public PlatDriver
{
public:
    /// @brief Plat Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_PS2_MOUSE_H__
