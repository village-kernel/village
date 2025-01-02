//###########################################################################
// vk_gui_lcddev.cpp
// Definitions of the functions that manage display
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_gui_lcddev.h"
#include "vk_dev_stream.h"
#include "vk_kernel.h"


/// @brief Setup
/// @return 
void VkDisplay::Setup(VgDevices* devices)
{
	//Get all display device fbDevs
	VkList<Base*> fbDevs = kernel->device.GetDevices(DriverID::_framebuffer);

	//Get the universal driver by name
	DevStream screen;

	//Open the first screen 
	if (screen.Open(fbDevs.Begin()->GetName(), FileMode::_Read))
	{
		//Get the specified lcd driver by ioctrl 
		screen.IOCtrl(0, (void*)&fbdev);
	}
}


/// @brief Exit
void VkDisplay::Exit()
{
	
}


/// @brief GetWidth
/// @return 
int VkDisplay::GetWidth()
{
	return fbdev->info.width;
}


/// @brief 
/// @return 
int VkDisplay::GetHeight()
{
	return fbdev->info.height;
}


/// @brief Point
/// @param x 
/// @param y 
/// @param color 
void VkDisplay::Point(int x, int y, int color)
{
	if (NULL != fbdev)
	{
		fbdev->DrawPoint(x, y, color);
	}
}


/// @brief Flush
/// @param area 
/// @param pixels 
void VkDisplay::Flush(DrawArea area, void* pixels)
{
	if (NULL != fbdev)
	{
		uint16_t* pixelsmap = (uint16_t*)pixels;

		for (int y = area.sy; y <= area.ey; y++)
		{
			for (int x = area.sx; x <= area.ex; x++)
			{
				fbdev->DrawPoint(x, y, *pixelsmap++);
			}
		}
	}
}
