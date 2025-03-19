//###########################################################################
// vk_drv_lcd_8080.h
// Hardware layer class that manages lcd 8080 interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_LCD_8080_H__
#define __VK_DRV_LCD_8080_H__

#include "vk_hardware.h"


/// @brief LCD8080
class LCD8080
{
private:
    //Members
    volatile uint16_t* cmdAddr;
    volatile uint16_t* dataAddr;
public:
    //Methods
    void Initialize();
    void WriteCmd(uint16_t cmd);
    void WriteData(uint16_t data);
    uint16_t ReadData();
};

#endif //!__VK_DRV_LCD_8080_H__
