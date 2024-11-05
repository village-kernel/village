//###########################################################################
// TerminalAPP.cpp
// Definitions of the functions that manage terminal app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "terminal_app.h"
#include "vk_kernel.h"


/// @brief Constructor
TerminalAPP::TerminalAPP()
{
}


/// @brief Destructor
TerminalAPP::~TerminalAPP()
{
}


/// @brief Setup
void TerminalAPP::Setup()
{
	view.Setup();
}


/// @brief Execute
void TerminalAPP::Execute()
{
	while (1) view.Execute();
}


/// @brief Exit
void TerminalAPP::Exit()
{
	view.Exit();
}


/// @brief main
int main(void)
{
	TerminalAPP terminal;
	terminal.Setup();
	terminal.Execute();
	terminal.Exit();
	return 0;
}
