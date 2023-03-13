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

	ReadSectionHeaders();

	ReadSymbolTableEntries();

	ReadRelocationEntries();
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


int Loader::ReadSectionHeaders()
{
	uint32_t sectionHeaderByteSizes = elf32.elfHeader.sectionHeaderNum * elf32.elfHeader.sectionHeaderSize;
	uint32_t sectionHeaderOffset = elf32.elfHeader.sectionHeaderOffset;
	
	elf32.sectionHeaders = (SectionHeader*)malloc(sectionHeaderByteSizes);

	int readSize = file.Read((uint8_t*)elf32.sectionHeaders, sectionHeaderByteSizes, sectionHeaderOffset);

	return (sectionHeaderByteSizes == readSize) ? _OK : _ERR;
}


int Loader::ReadSymbolTableEntries()
{
	return _OK;
}


int Loader::ReadRelocationEntries()
{
	return _OK;
}


///Register module
REGISTER_MODULE(new Loader(), ModuleID::_loader, loader);
