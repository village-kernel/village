//###########################################################################
// TerminalAPP.cpp
// Definitions of the functions that manage terminal app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "TerminalAPP.h"
#include "Kernel.h"


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
	ui.Setup();
	drv.Setup(&ui);
}


/// @brief Execute
void TerminalAPP::Execute()
{
	kernel->terminal.CreateConsole(drv.GetName());

	while (1) ui.Execute();
}


/// @brief Exit
void TerminalAPP::Exit()
{
	ui.Exit();
	drv.Exit();
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
