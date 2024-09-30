//###########################################################################
// TerminalUI.cpp
// Definitions of the functions that manage terminal ui
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "TerminalUI.h"


/// @brief Constructor
TerminalUI::TerminalUI()
{
}


/// @brief Destructor
TerminalUI::~TerminalUI()
{
}


/// @brief Setup
void TerminalUI::Setup()
{
	if (false == SetupWin()) return;

	kernel->inputEvent.Attach(InputEvent::_OutputText, (Method)&TerminalUI::UpdateText, this);
}


/// @brief Execute
void TerminalUI::Execute()
{
	if (NULL != mainwin)
	{
		mainwin->Refresh();
	}
}


/// @brief Exit
void TerminalUI::Exit()
{
	kernel->inputEvent.Detach(InputEvent::_OutputText, (Method)&TerminalUI::UpdateText, this);
}


/// @brief SetupWin
bool TerminalUI::SetupWin()
{
	VkGUI* vkgui = (VkGUI*)kernel->feature.GetModule("vkgui");

	if (NULL != vkgui)
	{
		mainwin = (Window*)vkgui->CreateMainWindow();

		frame = (Frame*)mainwin->CreateWedget(Wedget::_Frame);
		frame->SetLocation(20, 20, mainwin->GetWidth(), mainwin->GetHeight());

		textbox = (TextBox*)frame->CreateWedget(Wedget::_TextBox);
		textbox->SetLocation(1, 21, frame->GetWidth() - 2, frame->GetHeight() - 22);

		mainwin->Show();

		return true;
	}
	return false;
}


/// @brief Update text
void TerminalUI::UpdateText(InputEvent::OutputText* input)
{
	outText = *input;
}


/// @brief 
/// @param data 
/// @param size 
/// @return 
int TerminalUI::Write(uint8_t* data, uint32_t size)
{
	data[size] = '\0';
	textbox->AppendText((char*)data);
	return size;
}


/// @brief 
/// @param data 
/// @param size 
/// @return 
int TerminalUI::Read(uint8_t* data, uint32_t size)
{
	if (0 == outText.size) return 0;

	int brSize = ((int)size > outText.size) ? outText.size : size;

	for (int i = 0; i < brSize; i++)
	{
		data[i] = outText.data[i];
	}

	outText.size -= brSize;
	
	return brSize;
}
