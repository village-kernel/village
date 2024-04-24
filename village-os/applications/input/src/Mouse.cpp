//###########################################################################
// Mouse.cpp
// The overall framework of the mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Mouse.h"


/// @brief Constructor
Mouse::Mouse()
{
}


/// @brief Destructor
Mouse::~Mouse()
{
}


/// @brief Initialize
void Mouse::Initialize(const char* mouse)
{
	mousedrv.Open(mouse, FileMode::_Read);
}


/// @brief Execute
void Mouse::Execute()
{

}
