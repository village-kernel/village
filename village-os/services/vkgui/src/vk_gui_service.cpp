//###########################################################################
// vk_gui_service.cpp
// Definitions of the functions that manage village gui service
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_gui_service.h"
#include "vk_gui_ticks.h"
#include "vk_gui_mouse.h"
#include "vk_gui_keyboard.h"
#include "vk_gui_lcddev.h"
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
	vkgui.timer.SetTicks(new VkTicks());

	//Register mouse
	vkgui.indevs.RegisterIndev(new VkMouse());

	//Register keyboard
	vkgui.indevs.RegisterIndev(new VkKeyBoard());

	//Get all display device fbDevs
	VkList<Base*> fbDevs = kernel->device.GetDevices(DriverID::_framebuffer);

	//Register display
	for (fbDevs.Begin(); !fbDevs.IsEnd(); fbDevs.Next())
	{
		char* fbname = fbDevs.Item()->GetName();
		vkgui.displays.RegisterLcddev(new VkDisplay(fbname));
	}

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
