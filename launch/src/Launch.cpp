//###########################################################################
// Launch.cpp
// The overall framework of the launch
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Launch.h"
#include "Village.h"
#if defined(ARCH_ARM)
#include "ILI9488.h"
#elif defined(ARCH_X86)
#include "VGA.h"
#endif


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
	Driver* display = village.GetDriver(DriverID::_display);
#if defined(ARCH_ARM)
	gui.Initialize((ILI9488*)display);
#elif defined(ARCH_X86)
	gui.Initialize((VGA*)display);
#endif
	gui.Printf("hello vk.kernel\r\n");
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
