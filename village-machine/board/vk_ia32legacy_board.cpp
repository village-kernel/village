//###########################################################################
// vk_ia32legacy_board.cpp
// Definitions of the functions that manage board config
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_kernel.h"
#include "vk_ata_lba_disk.h"
#include "vk_bochs_vbe.h"
#include "vk_ps2_keyboard.h"
#include "vk_ps2_mouse.h"
#include "vk_pic32_uart.h"
#include "vk_pit32_timer.h"


/// @brief AtaLbaDiskDev
class AtaLbaDiskDev : public PlatDevice
{
private:
    /// @brief Members
    AtaLbaDisk::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .drv = 1,
        };
        driverData = (void*)&config;
        driverName = (char*)"disk0";
    }
};
REGISTER_PLAT_DEVICE(new AtaLbaDiskDev(), ataLbaDisk, ataLbaDiskDev);


/// @brief BochsVBEDev
class BochsVBEDev : public PlatDevice
{
private:
    /// @brief Members
    BochsVBE::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .vmap = (uint16_t*)0xA00000,
        };
        driverData = (void*)&config;
        driverName = (char*)"display0";
    }
};
REGISTER_PLAT_DEVICE(new BochsVBEDev(), bochsVBE, bochsVBEDev);


/// @brief PS2KeyBoardDev
class PS2KeyBoardDev : public PlatDevice
{
private:
    /// @brief Members
    PS2KeyBoard::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .irq = Keyboard_Controller_IRQn,
        };
        driverData = (void*)&config;
        driverName = (char*)"keyboard0";
    }
};
REGISTER_PLAT_DEVICE(new PS2KeyBoardDev(), ps2keyboard, ps2keyboardDev);


/// @brief PS2MouseDev
class PS2MouseDev : public PlatDevice
{
private:
    /// @brief Members
    PS2Mouse::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .irq = Mouse_Controller_IRQn,
        };
        driverData = (void*)&config;
        driverName = (char*)"mouse0";
    }
};
REGISTER_PLAT_DEVICE(new PS2MouseDev(), ps2mouse, ps2mouseDev);


/// @brief Pic32UartDev
class Pic32UartDev : public PlatDevice
{
private:
    /// @brief Members
    Pic32Uart::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .port = 0,
        };
        driverData = (void*)&config;
        driverName = (char*)"serial0";
    }
};
REGISTER_PLAT_DEVICE(new Pic32UartDev(), pic32uart, pic32uartDev);


/// @brief Pit32TimerDev
class Pit32TimerDev : public PlatDevice
{
private:
    /// @brief Members
    Pit32Timer::Config config;
public:
    /// @brief Methods
    void Config()
    {
        config = {
            .timer = 0,
        };
        driverData = (void*)&config;
        driverName = (char*)"timer0";
    }
};
REGISTER_PLAT_DEVICE(new Pit32TimerDev(), pit32timer, pit32timerDev);
