//###########################################################################
// SettingsApp.cpp
// Definitions of the functions that manage settings app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "settings_app.h"


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
	view.Setup();
}


/// @brief Execute
void SettingsApp::Execute()
{
	while(1) view.Execute();
}


/// @brief Exit
void SettingsApp::Exit()
{
	view.Exit();
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
