//###########################################################################
// vk_ps2_controller.h
// Hardware Layer class that manages ps2 controller
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_PS2_CONTROLLER_H__
#define __VK_PS2_CONTROLLER_H__

#include "i386.h"


/// @brief PS2Controller
class PS2Controller
{
public:
	//Methods
	void WriteCmd(uint8_t cmd);
	void WriteData(uint8_t data);
	uint8_t ReadData();
};

#endif //!__VK_PS2_CONTROLLER_H__
