//###########################################################################
// TerminalDrv.cpp
// Definitions of the functions that manage terminal drv
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "TerminalDrv.h"
#include "Kernel.h"


/// @brief Constructor
TerminalDrv::TerminalDrv()
{
}


/// @brief Destructor
TerminalDrv::~TerminalDrv()
{
	Exit();
}


/// @brief Setup
void TerminalDrv::Setup(TerminalView* view)
{
	this->view = view;
	this->SetID(DriverID::_character);
	this->SetName((char*)"terminal");
	kernel->device.RegisterCharDevice(this);
}


/// @brief Exit
void TerminalDrv::Exit()
{
	kernel->device.UnregisterCharDevice(this);
}


/// @brief Open
bool TerminalDrv::Open()
{
	return true;
}


/// @brief Write data
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int TerminalDrv::Write(uint8_t* data, uint32_t size, uint32_t offset)
{
	return view->Input(data, size);
}


/// @brief Read data
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int TerminalDrv::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
	return view->Output(data, size);
}


/// @brief Close
void TerminalDrv::Close()
{

}
