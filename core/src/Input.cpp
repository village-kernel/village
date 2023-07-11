//###########################################################################
// Input.cpp
// Definitions of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Input.h"
#include "Debug.h"
#include "Environment.h"


/// @brief Constructor
Input::Input()
{
}


/// @brief Deconstructor
Input::~Input()
{
}


/// @brief Singleton Instance
/// @return Input instance
Input& Input::Instance()
{
	static Input instance;
	return instance;
}
EXPORT_SYMBOL(_ZN5Input8InstanceEv);


/// @brief Definitions input
Input& input = Input::Instance();
EXPORT_SYMBOL(input);


/// @brief Input initialize
void Input::Initialize()
{

}


/// @brief Input execute
void Input::Execute()
{

}


/// @brief Report key
/// @param keycode 
/// @param status 
void Input::ReportKey(uint8_t keycode, int status)
{
	debug.Output(Debug::_Lv2, "keycode %d, keystatuts %d", keycode, status);
}


///Register module
REGISTER_MODULE(&Input::Instance(), ModuleID::_input, input);
