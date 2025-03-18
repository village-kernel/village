//###########################################################################
// vk_ps2_keyboard.h
// Declarations of the functions that manage ps2 key board
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_PS2_KEY_BOARD_H__
#define __VK_PS2_KEY_BOARD_H__

#include "vk_hardware.h"
#include "vk_driver.h"


/// @brief PS2KeyBoard
class PS2KeyBoard : public InputDriver, public Class
{
public:
    //Structures
    struct Config
    {
        uint32_t irq;
    };
private:
    //Members
    Config config;
    bool isExtended;

    /// @brief Methods
    void InputHandler();
public:
    /// @brief Methods
    PS2KeyBoard();
    ~PS2KeyBoard();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief Fopts Methods
    bool Open();
    void Close();
};


/// @brief PS2KeyBoardDrv
class PS2KeyBoardDrv : public PlatDriver
{
public:
    /// @brief Plat Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_PS2_KEY_BOARD_H__
