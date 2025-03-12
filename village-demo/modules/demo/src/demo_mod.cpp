//###########################################################################
// demo_mod.cpp
// Definitions of the functions that manage demo mod
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "demo_mod.h"


/// @brief Setup
bool DemoModule::Setup()
{
    kernel->debug.Info("Demo module setup!");
    return true;
}


/// @brief Exit
void DemoModule::Exit()
{
    kernel->debug.Info("Demo module exit!");
}


//Register module
REGISTER_MODULE(new DemoModule(), ModuleID::_feature, demomod);
