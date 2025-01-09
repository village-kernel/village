//###########################################################################
// terminal_view.cpp
// Definitions of the functions that manage terminal view
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "terminal_view.h"


/// @brief Init Component
/// @param parent 
void TerminalView::InitComponent(VgWedget* parent)
{
	int width = parent->GetWidth();
	int height = parent->GetHeight();

	VgTextBox* textbox = new VgTextBox();
	textbox->AxisMove(0, 20);
	textbox->SetSize(width, height - 20);
	textbox->BindingText(model.ConsoleText);
	parent->AddWedget(textbox);
}
