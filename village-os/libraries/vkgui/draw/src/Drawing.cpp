//###########################################################################
// Drawing.cpp
// Definitions of the functions that manage drawing
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Drawing.h"
#include "stdarg.h"
#include "stdio.h"


/// @brief Constructor
Drawing::Drawing()
	:fbdev(NULL)
{
}


/// @brief Destrucotr
Drawing::~Drawing()
{
}


/// @brief Display Setup
void Drawing::Setup(FBDriver* fbdev)
{
	//Set fbdev
	this->fbdev = fbdev;

	//Setup point
	point.Setup(this);

	//Setup line
	line.Setup(this);

	//Setup rect
	rect.Setup(this);

	//Setup circle
	circle.Setup(this);

	//Setup area
	area.Setup(this);

	//Setup char
	chr.Setup(this);

	//Setup string
	string.Setup(this);

	//Setup clear
	clear.Setup(this);

	//Clear screen
	clear.Set();
}


/// @brief Display Exit
void Drawing::Exit()
{
	//Exit point
	point.Exit();

	//Exit line
	line.Exit();

	//Exit rect
	rect.Exit();

	//Exit circle
	circle.Exit();

	//Exit area
	area.Exit();

	//Exit char
	chr.Exit();

	//Exit string
	string.Exit();

	//Exit clear
	clear.Exit();
}
