//###########################################################################
// Keyboard.cpp
// The overall framework of the keyboard
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Keyboard.h"


/// @brief Constructor
Keyboard::Keyboard()
{
}


/// @brief Destructor
Keyboard::~Keyboard()
{
}


/// @brief Initialize
void Keyboard::Initialize(const char* keyboard)
{
	keyboarddrv.Open(keyboard, FileMode::_Read);
}


/// @brief Execute
void Keyboard::Execute()
{

}
