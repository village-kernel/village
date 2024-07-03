//###########################################################################
// BinExecutor.cpp
// Definitions of the functions that manage bin executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "BinExecutor.h"


/// @brief BinExecutor Execute
/// @return tid
int BinExecutor::Execute()
{
	//Load, parser and execute bin file
	if (!bin.Load(path)) return 0;

	//Create a sandboxed thread to run the app
	return kernel->thread.CreateTask(path, (Method)&BinExecutor::Sandbox, this);
}


/// @brief BinExecutor execute app
void BinExecutor::Sandbox()
{
	bin.Execute(argc, argv);
	bin.Exit();
}


/// @brief BinExecutor release bin
/// @return 
bool BinExecutor::Release()
{
	return bin.Exit();
}
