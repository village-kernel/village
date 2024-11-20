//###########################################################################
// vk_disp_lcddev.cpp
// Definitions of the functions that manage display
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_disp_lcddev.h"
#include "vk_dev_stream.h"
#include "vk_kernel.h"


/// @brief Setup
/// @return 
void VkDisplay::Setup()
{
	//Get all display device fbDevs
	List<Base*> fbDevs = kernel->device.GetDevices(DriverID::_framebuffer);

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


/// @brief Flush
/// @param area 
/// @param pixels 
void VkDisplay::Flush(DrawArea area, uint8_t* pixels)
{
	if (NULL != fbdev)
	{
		uint16_t* pixelsmap = (uint16_t*)pixels;

		for (int y = area.y0; y < area.y1; y++)
		{
			for (int x = area.x0; x < area.x1; x++)
			{
				fbdev->DrawPoint(x, y, *pixelsmap++);
			}
		}
	}
}
