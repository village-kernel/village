//###########################################################################
// HexExecutor.cpp
// Definitions of the functions that manage hex executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "HexExecutor.h"


/// @brief HexExecutor Initiate
/// @return tid
int HexExecutor::Initiate()
{
	//Load, parser and execute hex file
	if (!hex.Load(path)) return 0;

	//Create a sandboxed thread to run the app
	return kernel->thread.CreateTask(path, (Method)&HexExecutor::Sandbox, this);
}


/// @brief HexExecutor execute app
void HexExecutor::Sandbox()
{
	hex.Execute(argc, argv);
	hex.Exit();
}


/// @brief HexExecutor release hex
/// @return 
bool HexExecutor::Release()
{
	return hex.Exit();
}


/// @brief HexExecutorFty GetSuffixes
/// @return 
List<char*> HexExecutorFty::GetSuffixes()
{
	List<char*> suffixes;
	suffixes.Add((char*)".hex");
#ifdef ASSOCIATED_EXEC_HEX
	suffixes.Add((char*)".exec");
#endif
	return suffixes;
}


/// @brief HexExecutorFty Create HexExecutor
/// @return 
BaseExecutor* HexExecutorFty::Create()
{
	return new HexExecutor();
}


///Register executor
REGISTER_EXECUTOR(new HexExecutorFty(), hexExecutor);
