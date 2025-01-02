//###########################################################################
// VkGuiService.cpp
// Definitions of the functions that manage village gui service
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_gui_service.h"
#include "vk_timer_ticks.h"
#include "vk_mouse_indev.h"
#include "vk_keyboard_indev.h"
#include "vk_disp_lcddev.h"
#include "vk_kernel.h"


/// @brief Constructor
VkGuiService::VkGuiService()
	:isReady(false)
{
} 


/// @brief Destructor
VkGuiService::~VkGuiService()
{
}


/// @brief Setup
bool VkGuiService::Setup()
{
	//Clear ready flag
	isReady = false;

	//Register tick
	vkgui.timer.RegisterTick(new VkTicks());

	//Register mouse
	vkgui.indevs.RegisterIndev(new VkMouse());

	//Register keyboard
	vkgui.indevs.RegisterIndev(new VkKeyBoard());

	//Register display
	vkgui.displays.RegisterLcddev(new VkDisplay());

	//Setup vkgui
	vkgui.Setup();

	//Set ready flag
	isReady = true;

	return true;
}


/// @brief Exit
void VkGuiService::Exit()
{
	//Exit vkgui
	vkgui.Exit();
}


/// @brief GetData
/// @return 
void* VkGuiService::GetData()
{
	while (!isReady) {}
	return (void*)(&vkgui);
}


/// @brief vkgui execute
void VkGuiService::Execute()
{
	while (1)
	{
		vkgui.Execute();
		kernel->thread.Sleep(1);
	}
}


/// @brief main
int main(int argc, char* argv[])
{
	VkGuiService vkgui;
	vkgui.SetID(ModuleID::_serivce);
	vkgui.SetName((char*)"vkgui");
	kernel->feature.RegisterModule(&vkgui);
	vkgui.Execute();
	kernel->feature.UnregisterModule(&vkgui);
	return 0;
}
