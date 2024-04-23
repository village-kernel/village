//###########################################################################
// Desktop.cpp
// The overall framework of the desktop
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Desktop.h"
#include "Kernel.h"
#include "ElfExecutor.h"


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
	SetupWin(screen, keyboard, mouse);

	kernel->inputevent.Attach(InputEvent::_Key, (Method)&Desktop::UpdateKey, this);
	kernel->inputevent.Attach(InputEvent::_Loc, (Method)&Desktop::UpdateLoc, this);

	SetID(DriverID::_character);
	SetName((char*)"desktop");
	kernel->device.RegisterDriver(this);
}


/// @brief SetupWin
void Desktop::SetupWin(const char* screen, const char* keyboard, const char* mouse)
{
	graphics.Initialize(screen, keyboard, mouse);

	mainwin = (Window*)graphics.CreateMainWindow();

	toolbar = (Toolbar*)mainwin->CreateWedget(Wedget::_Toolbar);
	toolbar->SetLocation(0, 0, 1024, 20);

	label = (Label*)toolbar->CreateWedget(Wedget::_Label);
	label->SetLocation(0, 0, 80, 20);
	label->SetLabel((char*)"menu");

	tabbar = (Tabbar*)mainwin->CreateWedget(Wedget::_Tabbar);
	tabbar->SetLocation(412, 728, 130, 40);

	button1 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button1->SetLocation(10, 10, 20, 20);
	button1->SetText((char*)"A");

	button2 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button2->SetLocation(40, 10, 20, 20);
	button2->SetText((char*)"B");

	button3 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button3->SetLocation(70, 10, 20, 20);
	button3->SetText((char*)"C");

	button4 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button4->SetLocation(100, 10, 20, 20);
	button4->SetText((char*)"D");

	textbox = (TextBox*)mainwin->CreateWedget(Wedget::_TextBox);
	textbox->SetLocation(40, 40, 944, 650);

	cursor = (Cursor*)mainwin->CreateWedget(Wedget::_Cursor);
	cursor->SetLocation(0, 0, mainwin->GetWidth(), mainwin->GetHeight());

	mainwin->Show();
}

const char codes[] = {
	' ', 
	' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '+', 0x7f,
	' ', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x0d,
	' ', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', ' ',
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
};

char keycode;


/// @brief Update key
void Desktop::UpdateKey(InputEvent::Key* input)
{
	if (input->code >= 0 && input->code <= 0x39)
	{
		keycode = codes[input->code];
	}
}


/// @brief Update location
void Desktop::UpdateLoc(InputEvent::Loc* input)
{
	cursor->Update(input->axisX,input->axisY);
}


/// @brief Execute
void Desktop::Execute()
{
	ElfExecutor* console = new ElfExecutor();
	console->Run(ElfExecutor::_Background, "/applications/console.exec desktop");
	while (1) {}
}


/// @brief Open
bool Desktop::Open()
{
	return true;
}


/// @brief Write data
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Desktop::Write(uint8_t* data, uint32_t size, uint32_t offset)
{
	data[size] = '\0';
	textbox->AppendText((char*)data);
	return size;
}


/// @brief Read data from rx buffer
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Desktop::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
	if (keycode)
	{
		data[0] = keycode;
		keycode = 0;
		return 1;
	}
	return 0;
}


/// @brief Close
void Desktop::Close()
{

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
