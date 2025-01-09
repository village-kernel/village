//###########################################################################
// terminal_model.cpp
// Definitions of the functions that manage terminal view model
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "terminal_model.h"


/// @brief Constructor
TerminalModel::TerminalModel()
{
	ConsoleText = new RelayData<char*>((char*)"shabi");
}


/// @brief Destructor
TerminalModel::~TerminalModel()
{
	delete ConsoleText;
}
