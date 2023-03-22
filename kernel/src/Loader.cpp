//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Loader.h"
#include "FileStream.h"
#include "rcParser.h"
#include "string.h"


///Loader Initialize
void Loader::Initialize()
{
	LoadLibraries();
	LoadModules();
}


///Loader load libraries
void Loader::LoadLibraries()
{
	
}


///Loader load modules
void Loader::LoadModules()
{
	RcParser rc;
	rc.Load("1:init.rc");
	std::list<std::string> resources = rc.GetResources();
	std::list<std::string>::iterator it = resources.begin();
	std::string path("1:");
	path += (*it).c_str();

	if (LoadElf(path.c_str()) != _OK) return;
	if (ParserElf() != _OK) return;
	if (RelEntries() != _OK) return;
	
	ExecuteElf("Entry");
}


///Loader load elf from path
int Loader::LoadElf(const char* path)
{
	FileStream file;

	if (FR_OK == file.Open(path, FileStream::_Read))
	{
		int size = file.Size();
		elf.map = (uint32_t)malloc(size);

		if (file.Read((uint8_t*)elf.map, size) == size)
		{
			file.Close(); return _OK;
		}

		file.Close();
	}

	return _ERR;
}


///Get section name
inline const char* Loader::GetSectionName(uint32_t index)
{
	if (elf.sectionNum > index)
	{
		return (const char*)elf.shstrtab + elf.sections[index].name;
	}
	return NULL;
}


///Get symbol name
inline const char* Loader::GetSymbolName(uint32_t index)
{
	if (elf.symtabNum > index)
	{
		return (const char*)elf.strtab + elf.symtab[index].name;
	}
	return NULL;
}


///Get symbol addr
inline uint32_t Loader::GetSymbolAddr(uint32_t index)
{
	if (elf.symtabNum > index)
	{
		SymbolEntry symbol = elf.symtab[index];

		if (symbol.shndx)
		{
			return GetSectionData(symbol.shndx).addr + symbol.value;
		}
	}
	return 0;
}


///Get symbol addr by name
inline uint32_t Loader::GetSymbolAddrByName(const char* name)
{
	for (uint32_t i = 0; i < elf.symtabNum; i++)
	{
		if(0 == strcmp(name, GetSymbolName(i)))
		{
			return GetSymbolAddr(i);
		}
	}
	return 0;
}


///Get section data
inline Loader::SectionData Loader::GetSectionData(uint32_t index)
{
	return SectionData(elf.map + elf.sections[index].offset);
}


///Parser elf
int Loader::ParserElf()
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
	
	//Set elf exec entry
	elf.exec = elf.map + elf.header->elfHeaderSize + elf.header->entry;

	//Get section headers pointer
	elf.sections = (SectionHeader*)(elf.map + elf.header->sectionHeaderOffset);
	elf.sectionNum = elf.header->sectionHeaderNum;

	//Get some information of elf
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		SectionData data = GetSectionData(i);

		//Set symbol tables pointer
		if (_SHT_SYMTAB == elf.sections[i].type)
		{
			elf.symtab = data.symtab;
			elf.symtabNum = elf.sections[i].size / sizeof(SymbolEntry);
		}
		//Set section header string table and symbol string talbe pointer
		else if (_SHT_STRTAB == elf.sections[i].type)
		{
			if (i == elf.header->sectionHeaderStringTableIndex)
				elf.shstrtab = data.shstrtab;
			else
				elf.strtab = data.strtab;
		}
	}

	return _OK;
}


///Relocation symbol entries
int Loader::RelEntries()
{
	//Set relocation tables
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		if (_SHT_REL == elf.sections[i].type)
		{
			//Calculate the number of relocation entries
			uint32_t relEntryNum = elf.sections[i].size / sizeof(RelocationEntry);

			//Get relocation entries table
			RelocationEntry* reltab = GetSectionData(i).reltab;

			//Relocation symbol entry
			for (uint32_t n = 0; n < relEntryNum; n++)
			{
				//Get relocation entry
				RelocationEntry relEntry = reltab[n];

				//Get symbol entry
				SymbolEntry symEntry = elf.symtab[relEntry.symbol];

				//Get relocation section addr
				uint32_t secAddr = GetSectionData(i - 1).addr;
				uint32_t relAddr = secAddr + relEntry.offset;
				uint32_t symAddr = 0;

				//Calculate new symbol entry addr
				if (symEntry.shndx)
				{
					//Calculate defined symbol entry symAddr
					symAddr = secAddr + symEntry.value;
				}
				else
				{
					//Get undefined symbol entry symAddr
					symAddr = SEARCH_SYMBOL(GetSymbolName(relEntry.symbol));
				}

				//Relocation symbol entry
				if (0 == symAddr) return _ERR;
				RelSymCall(relAddr, symAddr, relEntry.type);
			}
		}
	}

	return _OK;
}


///Relocation symbol call
int Loader::RelSymCall(uint32_t relAddr, uint32_t symAddr, int type)
{
	switch (type)
	{
		case _R_ARM_ABS32:
			*((uint32_t*)relAddr) = symAddr;
			break;

		case _R_ARM_THM_CALL:
		case _R_ARM_THM_JUMP24:
			RelJumpCall(relAddr, symAddr, type);
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
int Loader::RelJumpCall(uint32_t relAddr, uint32_t symAddr, int type)
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
int Loader::ExecuteElf(const char* symbol)
{
	if (NULL == symbol && 0 != elf.exec)
	{
		Thread::CreateTask((ThreadHandlerC)elf.exec);
		return _OK;
	}
	else
	{
		uint32_t symbolAddr = GetSymbolAddrByName("Entry");
		
		if (symbolAddr)
		{
			Thread::CreateTask((ThreadHandlerC)symbolAddr);
			return _OK;
		}
	}
	return _ERR;
}


///Register module
REGISTER_MODULE(new Loader(), ModuleID::_loader, loader);
