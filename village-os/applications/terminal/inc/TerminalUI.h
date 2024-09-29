//###########################################################################
// TerminalUI.h
// Declarations of the terminal ui
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_UI_H__
#define __TERMINAL_UI_H__

#include "Graphics.h"
#include "Kernel.h"


/// @brief TerminalUI
class TerminalUI : public Class
{
private:
	//Members
	Graphics graphics;
	Window*  mainwin;
	Frame*   frame;
	TextBox* textbox;

	//Members
	InputEvent::OutputText outText;

	//Methods
	bool SetupWin();
	void UpdateText(InputEvent::OutputText* input);
public:
	//Methods
	TerminalUI();
	~TerminalUI();
	void Setup();
	void Execute();
	void Exit();

	int Write(uint8_t* data, uint32_t size);
	int Read(uint8_t* data, uint32_t size);
};

#endif //!__TERMINAL_UI_H__
