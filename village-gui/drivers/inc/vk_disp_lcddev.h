//###########################################################################
// vk_disp_lcddev.h
// Declarations of the functions that manage dispaly
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DISPLAY_LCDDEV_H__
#define __VK_DISPLAY_LCDDEV_H__

#include "vg_lcddev.h"
#include "vk_driver.h"


/// @brief VkDisplay
class VkDisplay : public Lcddev
{
private:
	//Members
	FBDriver* fbdev;
public:
	//Methods
	void Setup(VgDevices* devices);
	void Exit();

	//Draw methods
	int GetWidth();
	int GetHeight();
	void Point(int x, int y, int color);
	void Flush(DrawArea area, void* pixels);
};

#endif //!__VK_DISPLAY_LCDDEV_H__
