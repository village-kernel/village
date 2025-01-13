//###########################################################################
// vk_gui_lcddev.cpp
// Definitions of the functions that manage display
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_gui_lcddev.h"
#include "vk_kernel.h"


/// @brief Constructor
/// @param fbname 
VkDisplay::VkDisplay(char* fbname)
	:fbname(fbname),
	fbdev(NULL)
{
}


/// @brief Destructor
VkDisplay::~VkDisplay()
{
}


/// @brief Setup
/// @return 
void VkDisplay::Setup(VgDevices* devices)
{
	//Open the screen by fbname 
	if (screen.Open(fbname, FileMode::_Read))
	{
		//Get the specified lcd driver by ioctrl 
		screen.IOCtrl(0, (void*)&fbdev);
	}
}


/// @brief Exit
void VkDisplay::Exit()
{
	screen.Close();
}


/// @brief GetWidth
/// @return 
int VkDisplay::GetWidth()
{
	return (fbdev) ? fbdev->info.width : 0;
}


/// @brief 
/// @return 
int VkDisplay::GetHeight()
{
	return (fbdev) ? fbdev->info.height : 0;
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
void VkDisplay::Flush(VgDrawArea area, void* pixels)
{
	if (NULL != fbdev)
	{
		uint16_t* pixelsmap = (uint16_t*)pixels;

		for (int y = area.sy; y <= area.ey; y++)
		{
			for (int x = area.sx; x <= area.ex; x++)
			{
				Point(x, y, *pixelsmap++);
			}
		}
	}
}
