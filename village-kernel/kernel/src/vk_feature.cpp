//###########################################################################
// vk_feature.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_feature.h"


/// @brief Constructor
ConcreteFeature::ConcreteFeature()
    :isRuntime(false)
{
}


/// @brief Destructor
ConcreteFeature::~ConcreteFeature()
{
}


/// @brief Execute module object->Setup
void ConcreteFeature::Setup()
{
    isRuntime = false;
    
    for (int id = 0; id < _dirverIdSize; id++)
    {
        for (modules.Begin(); !modules.IsEnd(); modules.Next())
        {
            Module* module = modules.Item();

            if (module->GetID() == id) module->Setup();
        }
    }

    isRuntime = true;

    //Output debug info
    kernel->debug.Info("Feature setup done!");
}


/// @brief Execute module object->Exit
void ConcreteFeature::Exit()
{
    isRuntime = false;

    for (int id = _dirverIdSize - 1; id >= 0; id--)
    {
        for (modules.End(); !modules.IsBegin(); modules.Prev())
        {
            Module* module = modules.Item();

            if (module->GetID() == id) module->Exit();
        }
    }

    modules.Release();
}


/// @brief Register module object
/// @param module module pointer
void ConcreteFeature::RegisterModule(Module* module)
{
    modules.Add(module, module->GetName());
    if (isRuntime) module->Setup();
}


/// @brief Unregister module object
/// @param module module pointer
void ConcreteFeature::UnregisterModule(Module* module)
{
    if (isRuntime) module->Exit();
    modules.Remove(module);
}


/// @brief Get the module object by name
/// @param name module name
/// @return module
Module* ConcreteFeature::GetModule(const char* name)
{
    return modules.GetItem(name);
}
