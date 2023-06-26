//###########################################################################
// Launch.cpp
// The overall framework of the launch
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Launch.h"
#include "Kernel.h"
#include "VGA.h"


/// @brief Constructor
Launch::Launch()
{
}


/// @brief Deconstructor
Launch::~Launch()
{
}


/// @brief Initialize
void Launch::Initialize()
{
	Driver* display = device.GetDriver(DriverID::_display);
	gui.Initialize((VGA*)display);
	gui.disp.Printf("hello vk.kernel\r\n");
}


/// @brief Execute
void Launch::Execute()
{

}


/// @brief main
int main(void)
{
	Launch launch;
	launch.Initialize();
	launch.Execute();
	return 0;
}
