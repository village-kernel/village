//###########################################################################
// vk_gui_lcddev.h
// Declarations of the functions that manage dispaly
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_GUI_LCDDEV_H__
#define __VK_GUI_LCDDEV_H__

#include "vg_lcddev.h"
#include "vk_driver.h"
#include "vk_dev_stream.h"


/// @brief VkDisplay
class VkDisplay : public VgLcddev
{
private:
	//Members
	char*     fbname;
	FBDriver* fbdev;
	DevStream screen;
public:
	//Methods
	VkDisplay(char* fbname = NULL);
	~VkDisplay();

	//Methods
	void Setup(VgDevices* devices);
	void Exit();

	//Draw methods
	int GetWidth();
	int GetHeight();
	void Point(int x, int y, int color);
	void Flush(VgDrawArea area, void* pixels);
};

#endif //!__VK_GUI_LCDDEV_H__
