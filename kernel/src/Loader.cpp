//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Loader.h"


///Loader Initialize
void Loader::Initialize()
{
	LoadElf32("1:app-striped.elf");

	ReadELFHeader();

	ReadSectionHeader();
}


void Loader::LoadElf32(const char* path)
{
	file.Open(path);
}


int Loader::ReadELFHeader()
{
	int readSize = file.Read((uint8_t*)&(elf32.elfHeader), elf_header_size);

	return (elf_header_size == readSize) ? _OK : _ERR;
}


int Loader::ReadSectionHeader()
{

	return _OK;
}


int Loader::ReadSymbolTableEntry()
{

	return _OK;
}


int Loader::ReadRelocationEntry()
{
	return _OK;
}


///Register module
REGISTER_MODULE(new Loader(), ModuleID::_loader, loader);
