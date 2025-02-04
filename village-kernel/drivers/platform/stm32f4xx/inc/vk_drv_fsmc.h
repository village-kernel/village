//###########################################################################
// vk_drv_fsmc.h
// Hardware layer class that manages FSMC module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_FSMC_H__
#define __VK_DRV_FSMC_H__

#include "vk_drv_gpio.h"


/// @brief FSMC
class Fsmc
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

#endif //!__VK_DRV_FSMC_H__
