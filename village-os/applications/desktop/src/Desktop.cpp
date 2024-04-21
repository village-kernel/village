//###########################################################################
// Desktop.cpp
// The overall framework of the desktop
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Desktop.h"
#include "Kernel.h"


/// @brief Constructor
Desktop::Desktop()
	:mainwin(NULL)
{
}


/// @brief Deconstructor
Desktop::~Desktop()
{
}


/// @brief Initialize
void Desktop::Initialize(const char* screen, const char* keyboard, const char* mouse)
{
	graphics.Initialize(screen, keyboard, mouse);

	mainwin = (Window*)graphics.CreateMainWindow();

	Toolbar* toolbar = (Toolbar*)mainwin->CreateWedget(Wedget::_Toolbar);
	toolbar->SetLocation(0, 0, 1024, 20);

	Label* label = (Label*)toolbar->CreateWedget(Wedget::_Label);
	label->SetLocation(0, 0, 80, 20);
	label->SetLabel((char*)"menu");

	Tabbar* tabbar = (Tabbar*)mainwin->CreateWedget(Wedget::_Tabbar);
	tabbar->SetLocation(412, 728, 130, 40);

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

	kernel->inputevent.Attach(InputEvent::_Key, (Method)&Desktop::UpdateKey, this);
	kernel->inputevent.Attach(InputEvent::_Loc, (Method)&Desktop::UpdateLoc, this);
}


/// @brief Update key
void Desktop::UpdateKey(InputEvent::Key* input)
{
	mainwin->UpdateKey(input->code, input->status);
}


/// @brief Update location
void Desktop::UpdateLoc(InputEvent::Loc* input)
{
	mainwin->UpdateCursor(input->axisX, input->axisY, input->axisZ);
}


/// @brief Execute
void Desktop::Execute()
{
	while (1) {}
}


/// @brief main
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return -1;
	}
	else
	{
		Desktop desktop;
		desktop.Initialize(argv[1], argv[2], argv[3]);
		desktop.Execute();
		return 0;
	}
}
