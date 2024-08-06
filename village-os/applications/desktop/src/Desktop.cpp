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


/// @brief Setup
void Desktop::Setup(const char* screen)
{
	if (false == SetupWin(screen)) return;

	SetID(DriverID::_character);
	SetName((char*)"desktop");
	kernel->device.RegisterDriver(this);

	kernel->inputEvent.Attach(InputEvent::_OutputText, (Method)&Desktop::UpdateText, this);
	kernel->inputEvent.Attach(InputEvent::_OutputAxis, (Method)&Desktop::UpdateAxis, this);
}


/// @brief SetupWin
bool Desktop::SetupWin(const char* screen)
{
	if (false == graphics.Setup(screen)) return false;

	mainwin = (Window*)graphics.CreateMainWindow();

	tabbar = (Tabbar*)mainwin->CreateWedget(Wedget::_Tabbar);
	tabbar->SetLocation(0, 728, 1024, 40);

	button0 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button0->SetLocation(0, 0, 40, 40);
	button0->SetText((char*)"Start");

	button1 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button1->SetLocation(50, 5, 30, 30);
	button1->SetText((char*)"A");

	button2 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button2->SetLocation(90, 5, 30, 30);
	button2->SetText((char*)"B");

	button3 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button3->SetLocation(130, 5, 30, 30);
	button3->SetText((char*)"C");

	button4 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button4->SetLocation(170, 5, 30, 30);
	button4->SetText((char*)"D");

	frame = (Frame*)mainwin->CreateWedget(Wedget::_Frame);
	frame->SetLocation(40, 40, 944, 650);

	textbox = (TextBox*)frame->CreateWedget(Wedget::_TextBox);
	textbox->SetLocation(1, 21, 942, 628);

	cursor = (Cursor*)mainwin->CreateWedget(Wedget::_Cursor);
	cursor->SetLocation(0, 0, mainwin->GetWidth(), mainwin->GetHeight());

	mainwin->Show();

	return true;
}


/// @brief Update text
void Desktop::UpdateText(InputEvent::OutputText* input)
{
	outText = *input;
}


/// @brief Update location axis
void Desktop::UpdateAxis(InputEvent::OutputAxis* input)
{
	cursor->Update(input->axisX, input->axisY);
}


/// @brief Execute
void Desktop::Execute()
{
	//kernel->process.Run(Process::_Background, "/applications/console.exec desktop");
	
	if (NULL == mainwin) return;

	while (1)
	{
		mainwin->Refresh();
	}
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
	if (0 == outText.size) return 0;

	int brSize = outText.size;

	for (int i = 0; i < brSize; i++)
	{
		data[i] = outText.data[i];
	}

	outText.size = 0;
	
	return brSize;
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
		desktop.Setup(argv[1]);
		desktop.Execute();
		return 0;
	}
}
