//###########################################################################
// BinExecutor.cpp
// Definitions of the functions that manage bin executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "BinExecutor.h"


/// @brief BinExecutor Initiate
/// @return tid
int BinExecutor::Initiate()
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


/// @brief BinExecutorFty GetSuffixes
/// @return 
List<char*> BinExecutorFty::GetSuffixes()
{
	List<char*> suffixes;
	suffixes.Add((char*)".bin");
	return suffixes;
}


/// @brief BinExecutorFty Create BinExecutor
/// @return 
BaseExecutor* BinExecutorFty::Create()
{
	return new BinExecutor();
}


///Register executor
REGISTER_EXECUTOR(new BinExecutorFty(), binExecutor);
