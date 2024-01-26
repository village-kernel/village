//###########################################################################
// BinLoader.cpp
// Definitions of the functions that manage bin loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "BinLoader.h"
#include "FileStream.h"
#include "Kernel.h"
#include "string.h"


/// @brief Constructor
/// @param filename 
BinLoader::BinLoader(const char* filename)
{
	if (NULL != filename) Load(filename);
}


/// @brief Deconstructor
BinLoader::~BinLoader()
{
	Exit();
}


/// @brief BinLoader load file
/// @param filename 
/// @return result
int BinLoader::Load(const char* filename)
{
	//Save filename in local
	this->filename = new char[strlen(filename) + 1]();
	strcpy(this->filename, filename);

	//Load and mapping
	if (LoadBin() != _OK) return _ERR;

	//Output debug info
	Kernel::debug.Output(Debug::_Lv2, "%s load done", filename);
	return _OK;
}


/// @brief BinLoader load bin file
/// @return 
int BinLoader::LoadBin()
{
	FileStream file;

	if (_OK == file.Open(filename, FileMode::_Read))
	{
		int size = file.Size();
		bin.load = (uint32_t)new char[size]();

		if (bin.load && (file.Read((char*)bin.load, size) == size))
		{
			bin.exec = bin.load + *((uint32_t*)bin.load);
			Kernel::debug.Output(Debug::_Lv1, "%s bin file load successful", filename);
			file.Close();
			return _OK;
		}

		file.Close();
	}

	Kernel::debug.Error("%s bin file load failed", filename);
	return _ERR;
}


/// @brief BinLoader execute
/// @param argc 
/// @param argv 
/// @return 
int BinLoader::Execute(int argc, char* argv[])
{
	if (0 != bin.exec)
	{
		((Entry)bin.exec)(argc, argv);
		return _OK;
	}
	Kernel::debug.Error("%s execute failed!", filename);
	return _ERR;
}


/// @brief BinLoader exit
/// @return result
int BinLoader::Exit()
{
	delete[] filename;
	delete[] (char*)bin.load;
	return _OK;
}
