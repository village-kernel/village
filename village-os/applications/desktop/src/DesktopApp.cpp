//###########################################################################
// DesktopApp.cpp
// Definitions of the functions that manage desktop app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DesktopApp.h"


/// @brief Constructor
DesktopApp::DesktopApp()
{
}


/// @brief Destructor
DesktopApp::~DesktopApp()
{
	Exit();
}


/// @brief Setup
void DesktopApp::Setup()
{
	view.Setup();
}


/// @brief Execute
void DesktopApp::Execute()
{
	while (1) view.Execute();
}


/// @brief Exit
void DesktopApp::Exit()
{
	view.Exit();
}


/// @brief main
int main(int argc, char* argv[])
{
	DesktopApp desktop;
	desktop.Setup();
	desktop.Execute();
	desktop.Exit();
	return 0;
}
