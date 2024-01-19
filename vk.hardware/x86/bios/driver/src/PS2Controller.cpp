//###########################################################################
// PS2Controller.cpp
// Definitions of the functions that manage ps2 controller
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Hardware.h"


/// @brief PS2Controller
class PS2Controller
{
public:
	/// @brief PS2 write cmd
	/// @param cmd 
	void WriteCmd(uint8_t cmd)
	{
		while (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_INPUT_BUFFER) {}
		PortByteOut(PS2_WRITE_COMMAND, cmd);
	}


	/// @brief PS2 write data
	/// @param data 
	void WriteData(uint8_t data)
	{
		while (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_INPUT_BUFFER) {}
		PortByteOut(PS2_WRITE_DATA, data);
	}


	/// @brief PS2 read data
	/// @return data
	uint8_t ReadData()
	{
		while (!(PortByteIn(PS2_READ_STATUS) & PS2_STATUS_OUTPUT_BUFFER)) {}
		return PortByteIn(PS2_READ_DATA);
	}
};
