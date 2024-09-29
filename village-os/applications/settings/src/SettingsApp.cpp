//###########################################################################
// SettingsApp.cpp
// Definitions of the functions that manage settings app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "SettingsApp.h"


/// @brief Constructor
SettingsApp::SettingsApp()
{
}


/// @brief Destructor
SettingsApp::~SettingsApp()
{
}


/// @brief Setup
void SettingsApp::Setup()
{
	ui.Setup();
}


/// @brief Execute
void SettingsApp::Execute()
{
	while(1) ui.Execute();
}


/// @brief Exit
void SettingsApp::Exit()
{
	ui.Exit();
}


/// @brief main
int main(void)
{
	SettingsApp settings;
	settings.Setup();
	settings.Execute();
	settings.Exit();
	return 0;
}
