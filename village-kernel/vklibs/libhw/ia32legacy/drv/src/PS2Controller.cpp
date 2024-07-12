//###########################################################################
// PS2Controller.cpp
// Definitions of the functions that manage ps2 controller
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "PS2Controller.h"


/// @brief PS2 write cmd
/// @param cmd 
void PS2Controller::WriteCmd(uint8_t cmd)
{
	while (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_INPUT_BUFFER) {}
	PortByteOut(PS2_WRITE_COMMAND, cmd);
}


/// @brief PS2 write data
/// @param data 
void PS2Controller::WriteData(uint8_t data)
{
	while (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_INPUT_BUFFER) {}
	PortByteOut(PS2_WRITE_DATA, data);
}


/// @brief PS2 read data
/// @return data
uint8_t PS2Controller::ReadData()
{
	while (!(PortByteIn(PS2_READ_STATUS) & PS2_STATUS_OUTPUT_BUFFER)) {}
	return PortByteIn(PS2_READ_DATA);
}
