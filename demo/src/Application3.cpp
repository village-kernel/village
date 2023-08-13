//###########################################################################
// Application3.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application3.h"
#include "DirStream.h"
#if defined(ARCH_ARM)
#include "ILI9488.h"
#elif defined(ARCH_X86)
#include "VGA.h"
#endif

///Constructor
Application3::Application3()
{
}


///Initialize
void Application3::Initialize()
{
	Driver* display = device.GetDriver(DriverID::_display);
#if defined(ARCH_ARM)
	gui.Initialize((ILI9488*)display);
#elif defined(ARCH_X86)
	gui.Initialize((VGA*)display);
#endif
	gui.Printf("hello vk.kernel\r\n");
}


///Execute
void Application3::Execute()
{
	DirStream dir;

	gui.Printf("storage %s\r\n", "libraries");

	if (_OK == dir.Open("libraries"))
	{
		int size = dir.Size();

		FileDir* dirs = new FileDir[size]();

		if (dir.Read(dirs, size) == size)
		{
			for (int i = 0; i < size; i++)
			{
				gui.Printf("%s\r\n", dirs[i].name);
			}
		}

		dir.Close();
	}
}


///Register module
REGISTER_MODULE(new Application3(), (ModuleID::_application + 2), app_3);
