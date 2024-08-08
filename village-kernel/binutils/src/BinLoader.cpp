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


/// @brief Destructor
BinLoader::~BinLoader()
{
	Exit();
}


/// @brief BinLoader load file
/// @param filename 
/// @return result
bool BinLoader::Load(const char* filename)
{
	//Save filename in local
	this->filename = new char[strlen(filename) + 1]();
	strcpy(this->filename, filename);

	//Load and mapping
	if (!LoadBin())     return false;
	if (!PostParser())  return false;
	if (!RelEntries())  return false;

	//Output debug info
	kernel->debug.Output(Debug::_Lv2, "load at 0x%08x, %s load done", bin.load, filename);
	return true;
}


/// @brief BinLoader load bin file
/// @return 
bool BinLoader::LoadBin()
{
	FileStream file;

	if (file.Open(filename, FileMode::_Read))
	{
		int size = file.Size();
		bin.load = (uint32_t)new char[size]();

		if (bin.load && (file.Read((char*)bin.load, size) == size))
		{
			kernel->debug.Output(Debug::_Lv1, "%s bin file load successful", filename);
			file.Close();
			return true;
		}

		file.Close();
	}

	kernel->debug.Error("%s bin file load failed", filename);
	return false;
}


/// @brief PostParser
/// @return 
bool BinLoader::PostParser()
{
	bin.offset  = *(((uint32_t*)bin.load) + 0);
	bin.dynamic = *(((uint32_t*)bin.load) + 1);
	bin.entry   = *(((uint32_t*)bin.load) + 2);
	bin.exec    = bin.load + bin.entry - bin.offset;
	return true;
}


/// @brief RelEntries
/// @return
bool BinLoader::RelEntries()
{
	uint32_t   imagebase = 0;
	uint32_t   relcount = 0;
	uint32_t*  relAddr = NULL;
	DynamicHeader* dynamic = NULL;
	RelocationEntry* relocate = NULL;
	
	//Calc the imagebase value
	imagebase = bin.load - bin.offset;

	//Calc the dynamic address
	dynamic = (DynamicHeader*)(imagebase + bin.dynamic);

	//Gets the relocate section address and the relcount
	for (int i = 0; dynamic[i].tag != _DT_NULL; i++)
	{
		if (_DT_REL == dynamic[i].tag)
		{
			relocate = (RelocationEntry*)(imagebase + dynamic[i].ptr);
		}
		else if (_DT_RELCOUNT == dynamic[i].tag)
		{
			relcount = dynamic[i].val;
		}
	}

	//Check if relocation is needed
    if (!relocate && relcount == 0) return true;
	if (!relocate || relcount == 0) return false;

	//Relocate the value of relative type
	for (uint32_t i = 0; i < relcount; i++)
	{
		if (_R_TYPE_RELATIVE == relocate[i].type)
		{
			relAddr  = (uint32_t*)(imagebase + relocate[i].offset);
			*relAddr = imagebase + *relAddr;
		}
	}

	return true;
}


/// @brief BinLoader execute
/// @param argc 
/// @param argv 
/// @return 
bool BinLoader::Execute(int argc, char* argv[])
{
	if (0 != bin.exec)
	{
		((StartEntry)bin.exec)(kernel, argc, argv);
		return true;
	}
	kernel->debug.Error("%s execute failed!", filename);
	return false;
}


/// @brief BinLoader exit
/// @return result
bool BinLoader::Exit()
{
	delete[] filename;
	delete[] (char*)bin.load;
	return true;
}
