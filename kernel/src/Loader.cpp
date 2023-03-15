//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Loader.h"
#include "FileStream.h"
#include "string.h"


///Loader Initialize
void Loader::Initialize()
{
	if (LoadElf("1:app-cpp-striped.elf") != _OK) return;

	if (ParserElfHeader() != _OK) return;

	if (ParserElfSection() != _OK) return;

	if (ParserSymbolEntries() != _OK) return;

	if (ParserRelocationEntries() != _OK) return;

	if (RelocationEntries() != _OK) return;

	ExecuteElf();
}


///Loader load elf from path
int Loader::LoadElf(const char* path)
{
	FileStream file;

	if (FR_OK == file.Open(path, FileStream::_Read))
	{
		int size = file.Size();
		elf.map = (uint8_t*)malloc(size);

		if (file.Read(elf.map, size) == size)
		{
			file.Close(); return _OK;
		}

		file.Close();
	}

	return _ERR;
}


///Parser elf header
int Loader::ParserElfHeader()
{
	//Set elf header pointer
	elf.header = (ELFHeader*)(elf.map);

	//Check if it is a valid elf file
	const uint8_t elfmagic[] = {0x7f, 'E', 'L', 'F'};
	if (elf.header->ident[0] !=  elfmagic[0]    ) return _ERR;
	if (elf.header->ident[1] !=  elfmagic[1]    ) return _ERR;
	if (elf.header->ident[2] !=  elfmagic[2]    ) return _ERR;
	if (elf.header->ident[3] !=  elfmagic[3]    ) return _ERR;
	if (elf.header->ident[4] != _ELF_Class_32   ) return _ERR;
	if (elf.header->type     != _ELF_Type_Rel   ) return _ERR;
	if (elf.header->machine  != _ELF_Machine_ARM) return _ERR;
	if (elf.header->version  != _ELF_Ver_Current) return _ERR;

	return _OK;
}


///Parser elf section
int Loader::ParserElfSection()
{
	//Allocate sections memory
	elf.sections = (Section*)malloc(sizeof(Section) * elf.header->sectionHeaderNum);
	if (NULL == elf.sections) return _ERR;

	//Get section headers pointer
	SectionHeader* headers = (SectionHeader*)(elf.map + elf.header->sectionHeaderOffset);
	//Set section header and data
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		//Set header pointer
		elf.sections[i].header = &headers[i];
		
		//Set data pointer
		elf.sections[i].data = (uint8_t*)(elf.map + headers[i].offset);
		
		//Set the next pointer
		if (elf.header->sectionHeaderNum != (i + 1))
			elf.sections[i].next = (Section*)elf.sections + i + 1;
		else
			elf.sections[i].next = NULL;
	}
	
	//Get section names pointer
	uint8_t* name = elf.sections[elf.header->sectionHeaderStringTableIndex].data;
	//Set section name
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		elf.sections[i].name = (uint8_t*)(name + elf.sections[i].header->name);
	}

	return _OK;
}


///Parser ELF symbol entries
int Loader::ParserSymbolEntries()
{
	//Calculate the number of symbol table
	uint32_t symbolTableNum = 0;
	uint32_t strTableIndex = 0;
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		if (_SHT_SYMTAB == elf.sections[i].header->type) symbolTableNum++;

		if (_SHT_STRTAB == elf.sections[i].header->type)
		{
			if (0 == strcmp(".strtab", (const char*)elf.sections[i].name))
			{
				strTableIndex = i;
			}
		}
	}

	//Allocate symbol table memory
	elf.symTabs = (SymbolTable*)malloc(sizeof(SymbolTable) * symbolTableNum);
	if (NULL == elf.symTabs) return _ERR;

	//Set value
	uint32_t symtabIndex = 0;

	//Set symbol tables
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		if (_SHT_SYMTAB == elf.sections[i].header->type)
		{
			//Set the symbol tables section name
			elf.symTabs[symtabIndex].sectionName = elf.sections[i].name;

			//Set the symbol tables section index
			elf.symTabs[symtabIndex].sectionIndex = i;

			//Calculate the number of symbol entries
			uint32_t symbolNum = elf.sections[i].header->size / sizeof(SymbolEntry);

			//Allocate symbols memory
			Symbol* symbols = (Symbol*)malloc(sizeof(Symbol) * symbolNum);
			if (NULL == symbols) return _ERR;
			elf.symTabs[symtabIndex].symbols = symbols;

			//Set symbols
			for (uint32_t n = 0; n < symbolNum; n++)
			{
				//Set symbol entry
				symbols[n].entry = elf.sections[i].symEntries + n;

				//Set symbol name
				if (_STT_SECTION == symbols[n].entry->type)
				{
					uint8_t* name = elf.sections[elf.header->sectionHeaderStringTableIndex].data;
					symbols[n].name = (uint8_t*)(name + elf.sections[symbols[n].entry->index].header->name);
				}
				else
				{
					uint8_t* name = elf.sections[strTableIndex].data;
					symbols[n].name = (uint8_t*)(name + symbols[n].entry->name);
				}

				//Set the next pointer
				if (symbolNum != (n + 1))
					symbols[n].next = (Symbol*)symbols + n + 1;
				else
					symbols[n].next = NULL;
			}

			//Set symbol table next pointer
			if ((symtabIndex + 1) < symbolTableNum)
				elf.symTabs[symtabIndex].next = (SymbolTable*)elf.symTabs + symtabIndex + 1;
			else
				elf.symTabs[symtabIndex].next = NULL;

			//Update index
			symtabIndex++;
		}
	}

	return _OK;
}


///Parser ELF relocation entries
int Loader::ParserRelocationEntries()
{
	//Calculate the number of relocation table
	uint32_t relTableNum = 0;
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		if (_SHT_REL == elf.sections[i].header->type) relTableNum++;
	}

	//Allocate relocation table memory
	elf.relTabs = (RelocationTable*)malloc(sizeof(RelocationTable) * relTableNum);
	if (NULL == elf.relTabs) return _ERR;

	//Set relocation tables
	uint32_t reltabIndex = 0;
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		if (_SHT_REL == elf.sections[i].header->type)
		{
			//Set the relocations tables section name
			elf.relTabs[reltabIndex].sectionName = elf.sections[i].name;

			//Set the relocations tables section index
			elf.relTabs[reltabIndex].sectionIndex = i;

			//Calculate the number of relocation entries
			uint32_t relocationNum = elf.sections[i].header->size / sizeof(RelocationEntry);

			//Allocate relocations memory
			Relocation* relocations = (Relocation*)malloc(sizeof(Relocation) * relocationNum);
			if (NULL == relocations) return _ERR;
			elf.relTabs[reltabIndex].relocations = relocations;

			//Set relocations
			for (uint32_t n = 0; n < relocationNum; n++)
			{
				//Set relocations entry
				relocations[n].entry = elf.sections[i].relEntries + n;

				//Set relocations name
				relocations[n].name = elf.symTabs[0].symbols[relocations[n].entry->symbol].name;
	
				//Set the next pointer
				if (relocationNum != (n + 1))
					relocations[n].next = (Relocation*)relocations + n + 1;
				else
					relocations[n].next = NULL;
			}

			//Set relocations table next pointer
			if ((reltabIndex + 1) < relTableNum)
				elf.relTabs[reltabIndex].next = (RelocationTable*)elf.relTabs + reltabIndex + 1;
			else
				elf.relTabs[reltabIndex].next = NULL;

			//Update index
			reltabIndex++;
		}
	}

	return _OK;
}


///Relocation entries
int Loader::RelocationEntries()
{
	for (RelocationTable* relTab = elf.relTabs; relTab != NULL; relTab = relTab->next)
	{
		for (Relocation* rel = relTab->relocations; rel != NULL; rel = rel->next)
		{
			Symbol symbol = elf.symTabs[0].symbols[rel->entry->symbol];
			
			if (symbol.entry->index)
			{
				Section section = elf.sections[symbol.entry->index];
				uint32_t symAddr = ((uint32_t)section.data) + symbol.entry->value;
				uint32_t relAddr = ((uint32_t)section.data) + rel->entry->offset;
				
				RelocationSymbolCall(relAddr, symAddr, rel->entry->type);
			}
			else
			{
				//return _ERR;
			}
		}
	}
	return _OK;
}


///Relocation symbol call
int Loader::RelocationSymbolCall(uint32_t relAddr, uint32_t symAddr, int type)
{
	switch (type)
	{
		case _R_ARM_ABS32:
			*((uint32_t*)relAddr) = symAddr;
			break;

		case _R_ARM_THM_CALL:
		case _R_ARM_THM_JUMP24:
			RelocationJumpCall(relAddr, symAddr, type);
			break;

		case _R_ARM_TARGET1:
			*((uint32_t*)relAddr) = symAddr;
			break;

		case _R_ARM_THM_JUMP11:
			break;
			
		default: return 0;
	}
	return 0;
}


///Relocation thumb jump call 
int Loader::RelocationJumpCall(uint32_t relAddr, uint32_t symAddr, int type)
{
	uint16_t upper = ((uint16_t *)relAddr)[0];
	uint16_t lower = ((uint16_t *)relAddr)[1];
	uint32_t S  = (upper >> 10) & 1;
	uint32_t J1 = (lower >> 13) & 1;
	uint32_t J2 = (lower >> 11) & 1;

	int32_t offset = (S    << 24) |  /* S     -> offset[24]    */
	((~(J1 ^ S)  & 1     ) << 23) |  /* J1    -> offset[23]    */
	((~(J2 ^ S)  & 1     ) << 22) |  /* J2    -> offset[22]    */
	((  upper    & 0x03ff) << 12) |  /* imm10 -> offset[12:21] */
	((  lower    & 0x07ff) << 1 );   /* imm11 -> offset[1:11]  */
	
	if (offset & 0x01000000) offset -= 0x02000000;

	offset += symAddr - relAddr;

	S  =       (offset >> 24) & 1;
	J1 = S ^ (~(offset >> 23) & 1);
	J2 = S ^ (~(offset >> 22) & 1);

	upper = ((upper & 0xf800) | (S << 10) | ((offset >> 12) & 0x03ff));
	((uint16_t*)relAddr)[0] = upper;

	lower = ((lower & 0xd000) | (J1 << 13) | (J2 << 11) | ((offset >> 1) & 0x07ff));
	((uint16_t*)relAddr)[1] = lower;

	return _OK;
}


///Execute elf
int Loader::ExecuteElf()
{
	if (elf.header->entry)
	{
		void (*exec)() = (void(*)())((uint32_t)elf.map + elf.header->elfHeaderSize + elf.header->entry);
		exec();
		return _OK;
	}
	return _ERR;
}


///Register module
REGISTER_MODULE(new Loader(), ModuleID::_loader, loader);
