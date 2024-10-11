//###########################################################################
// VkGuiService.cpp
// Definitions of the functions that manage village gui service
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "VkGuiService.h"
#include "DevStream.h"
#include "Kernel.h"


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

	//Get all display device fbDevs
	List<Base*> fbDevs = kernel->device.GetDevices(DriverID::_framebuffer);

	//Get the universal driver by name
	DevStream screen;

	//Open the first screen 
	if (screen.Open(fbDevs.Begin()->GetName(), FileMode::_Read))
	{
		FBDriver* fbdev = NULL;

		//Get the specified lcd driver by ioctrl 
		screen.IOCtrl(0, (void*)&fbdev);

		//Setup vkgui
		if (false == vkgui.Setup(fbdev)) return false;

		//Enable cursor
		vkgui.EnableCursor();
	}

	//Attach input event
	kernel->event.Attach(Event::_OutputText, (Method)&VkGuiService::TextReceiver, this);
	kernel->event.Attach(Event::_OutputAxis, (Method)&VkGuiService::AxisReceiver, this);

	//Set ready flag
	isReady = true;

	return true;
}


/// @brief Exit
void VkGuiService::Exit()
{
	//Detach input event
	kernel->event.Detach(Event::_OutputText, (Method)&VkGuiService::TextReceiver, this);
	kernel->event.Detach(Event::_OutputAxis, (Method)&VkGuiService::AxisReceiver, this);

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


/// @brief Text input receiver
void VkGuiService::TextReceiver(Event::OutputText* input)
{
	vkgui.InputText(input->data, input->size);
}


/// @brief Axis input receiver
void VkGuiService::AxisReceiver(Event::OutputAxis* input)
{
	vkgui.InputAxis(input->axisX, input->axisY, input->axisZ);
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
