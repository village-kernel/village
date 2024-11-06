//###########################################################################
// Taichi.cpp
// Definitions of the functions that manage taichi service
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "taichi_service.h"
#include "vk_rc_parser.h"
#include "vk_kernel.h"


/// @brief Constructor
TaichiService::TaichiService()
{
}


/// @brief Destructor
TaichiService::~TaichiService()
{
}


/// @brief Loader load
/// @param filename rc file path
void TaichiService::Load(const char* filename)
{
	RcParser* parser = new RcParser(filename);

	List<char*>& runcmds = parser->GetRunCmds();

	for (runcmds.Begin(); !runcmds.IsEnd(); runcmds.Next())
	{
		kernel->process.Run(Process::_Background, runcmds.Item());
	}

	parser->Release();
	delete parser;
}


/// @brief Loader unload
/// @param filename rc file path
void TaichiService::Unload(const char* filename)
{
	RcParser* parser = new RcParser(filename);

	List<char*>& runcmds = parser->GetRunCmds();

	for (runcmds.End(); !runcmds.IsBegin(); runcmds.Prev())
	{
		kernel->process.Kill(runcmds.Item());
	}

	parser->Release();
	delete parser;
}


/// @brief Setup
void TaichiService::Setup()
{
	//Load services
	Load("/services/_load_.rc");

	//Load programs
	Load("/programs/_load_.rc");
}


/// @brief Execute
void TaichiService::Execute()
{
	kernel->thread.Blocked();
}


/// @brief Exit
void TaichiService::Exit()
{
	//Unload programs
	Unload("programs/_load_.rc");

	//Unload services
	Unload("services/_load_.rc");
}


/// @brief main
int main(void)
{
	TaichiService taichi;
	taichi.Setup();
	taichi.Execute();
	taichi.Exit();
	return 0;
}
