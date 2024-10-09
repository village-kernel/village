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
	view.Setup();
	drv.Setup(&view);
}


/// @brief Execute
void TerminalAPP::Execute()
{
	kernel->terminal.CreateConsole(drv.GetName());

	while (1) view.Execute();
}


/// @brief Exit
void TerminalAPP::Exit()
{
	view.Exit();
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
