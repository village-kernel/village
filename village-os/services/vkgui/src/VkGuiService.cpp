//###########################################################################
// VkGuiService.cpp
// Definitions of the functions that manage village gui service
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "VkGuiService.h"


/// @brief Constructor
VkGuiService::VkGuiService()
{
} 


/// @brief Destructor
VkGuiService::~VkGuiService()
{
}


/// @brief Setup
bool VkGuiService::Setup()
{
	if (false == vkgui.Setup()) return false;
	kernel->inputEvent.Attach(InputEvent::_OutputText, (Method)&VkGuiService::TextReceiver, this);
	kernel->inputEvent.Attach(InputEvent::_OutputAxis, (Method)&VkGuiService::AxisReceiver, this);
	return true;
}


/// @brief Exit
void VkGuiService::Exit()
{
	kernel->inputEvent.Detach(InputEvent::_OutputText, (Method)&VkGuiService::TextReceiver, this);
	kernel->inputEvent.Detach(InputEvent::_OutputAxis, (Method)&VkGuiService::AxisReceiver, this);
	vkgui.Exit();
}


/// @brief GetData
/// @return 
void* VkGuiService::GetData()
{
	return (void*)(&vkgui);
}


/// @brief Text input receiver
void VkGuiService::TextReceiver(InputEvent::OutputText* input)
{
	vkgui.InputText(input->data, input->size);
}


/// @brief Axis input receiver
void VkGuiService::AxisReceiver(InputEvent::OutputAxis* input)
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
	kernel->thread.Blocked();
	kernel->feature.UnregisterModule(&vkgui);
	return 0;
}
