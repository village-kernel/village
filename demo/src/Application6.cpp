//###########################################################################
// Application6.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application6.h"
#include "Console.h"


///Constructor
Application6::Application6()
{
}


///Application6 initialize
void Application6::Initialize()
{
	char data[] = "hello module init";

	console.Output(data);
}


///Application6 execute
void Application6::Execute()
{
	char data[] = "hello module execute";

	for (int i = 0; i < 5; i++)
	{
		console.Output(data);
		thread.Sleep(1000);
	}
}


//Register module
REGISTER_MODULE(new Application6(), (ModuleID::_application + 6), app_6);
