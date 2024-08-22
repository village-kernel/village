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
	Exit();
}


/// @brief Setup
void Desktop::Setup()
{
	if (false == SetupWin()) return;

	SetID(DriverID::_character);
	SetName((char*)"desktop");
	kernel->device.RegisterCharDevice(this);

	kernel->inputEvent.Attach(InputEvent::_OutputText, (Method)&Desktop::UpdateText, this);
	kernel->inputEvent.Attach(InputEvent::_OutputAxis, (Method)&Desktop::UpdateAxis, this);
}


/// @brief Exit
void Desktop::Exit()
{
	kernel->inputEvent.Detach(InputEvent::_OutputAxis, (Method)&Desktop::UpdateAxis, this);
	kernel->inputEvent.Detach(InputEvent::_OutputText, (Method)&Desktop::UpdateText, this);

	kernel->device.DeregisterCharDevice(this);

	graphics.Exit();
}


/// @brief SetupWin
bool Desktop::SetupWin()
{
	if (false == graphics.Setup()) return false;

	mainwin = (Window*)graphics.CreateMainWindow();

	tabbar = (Tabbar*)mainwin->CreateWedget(Wedget::_Tabbar);
	tabbar->SetLocation(0, mainwin->GetHeight() - 40, mainwin->GetWidth(), 40);

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
	frame->SetLocation(20, 20, mainwin->GetWidth() - 40, mainwin->GetHeight() - 78);

	textbox = (TextBox*)frame->CreateWedget(Wedget::_TextBox);
	textbox->SetLocation(1, 21, mainwin->GetWidth() - 42, mainwin->GetHeight() - 100);

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
	if (NULL == mainwin) return;

	kernel->terminal.CreateConsole("desktop");

	while (1) mainwin->Refresh();
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
	Desktop desktop;
	desktop.Setup();
	desktop.Execute();
	desktop.Exit();
	return 0;
}
