//###########################################################################
// Launch.cpp
// The overall framework of the launch
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Launch.h"
#include "Village.h"


/// @brief Constructor
Launch::Launch()
	:mainwin(NULL)
{
}


/// @brief Deconstructor
Launch::~Launch()
{
}


/// @brief Initialize
void Launch::Initialize(const char* drvname)
{
	gui.Initialize(drvname);

	mainwin = (Window*)gui.CreateMainWindow();

	Toolbar* toolbar = (Toolbar*)mainwin->CreateWedget(Wedget::_Toolbar);
	toolbar->SetLocation(0, 0, 320, 20);

	Label* label = (Label*)toolbar->CreateWedget(Wedget::_Label);
	label->SetLocation(0, 0, 80, 20);
	label->SetLabel((char*)"menu");

	Tabbar* tabbar = (Tabbar*)mainwin->CreateWedget(Wedget::_Tabbar);
	tabbar->SetLocation(90, 160, 130, 40);

	Button* button1 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button1->SetLocation(10, 10, 20, 20);
	button1->SetText((char*)"A");

	Button* button2 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button2->SetLocation(40, 10, 20, 20);
	button2->SetText((char*)"B");

	Button* button3 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button3->SetLocation(70, 10, 20, 20);
	button3->SetText((char*)"C");

	Button* button4 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button4->SetLocation(100, 10, 20, 20);
	button4->SetText((char*)"D");

	mainwin->Show();

	village.AttachInputMovement(union_cast<Function>(&Launch::Movement), (void*)this);
}


/// @brief Movement
/// @param inputMove 
void Launch::Movement(Input::InputMove* inputMove)
{
	mainwin->Update(inputMove->axisX, inputMove->axisY, inputMove->axisZ);
	mainwin->Show();
}


/// @brief Execute
void Launch::Execute()
{
	while (1) {}
}


/// @brief main
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return _ERR;
	}
	else
	{
		Launch launch;
		launch.Initialize(argv[1]);
		launch.Execute();
		return _OK;
	}
}
