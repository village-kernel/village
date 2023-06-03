//###########################################################################
// ElfParser.cpp
// Definitions of the functions that manage elf parser
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "console.h"
#include "ElfParser.h"
#include "FileStream.h"
#include "string.h"


/// @brief Constructor
/// @param filename 
ElfParser::ElfParser(const char* filename)
{
	if (NULL != filename) Load(filename);
}


/// @brief ElfParser load and parser elf file
/// @param filename 
/// @return result
int ElfParser::Load(const char* filename)
{
	if (LoadElf(filename) != _OK) return _ERR;
	if (ParserElf()       != _OK) return _ERR;
	
	switch (elf.header->type)
	{
	case _ELF_Type_Rel:
		if (RelEntries()  != _OK) return _ERR;
		break;
	case _ELF_Type_Exec:
	case _ELF_Type_Dyn:
		if (CopyToRAM()   != _OK) return _ERR;
		break;
	default: break;
	}
	return _OK;
}


/// @brief ElfParser load elf file
/// @param filename 
/// @return result
int ElfParser::LoadElf(const char* filename)
{
	FileStream file;

	if (FR_OK == file.Open(filename, FileStream::_Read))
	{
		int size = file.Size();
		elf.map = (uint32_t)new uint8_t[size]();

		if (elf.map && (file.Read((uint8_t*)elf.map, size) == size))
		{
			console.info("Load %s successful", filename);
			file.Close();
			return _OK;
		}

		file.Close();
	}

	console.log("Load %s failed", filename);
	return _ERR;
}


/// @brief Get section name
/// @param index 
/// @return name
inline const char* ElfParser::GetSectionName(uint32_t index)
{
	if (elf.header->sectionHeaderNum > index)
	{
		return (const char*)elf.shstrtab + elf.sections[index].name;
	}
	return NULL;
}


/// @brief Get symbol name
/// @param index 
/// @return name
inline const char* ElfParser::GetSymbolName(uint32_t index)
{
	if (elf.symtabNum > index)
	{
		return (const char*)elf.strtab + elf.symtab[index].name;
	}
	return NULL;
}


/// @brief Get symbol addr
/// @param index 
/// @return address
inline uint32_t ElfParser::GetSymbolAddr(uint32_t index)
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


/// @brief Get symbol addr by name
/// @param name 
/// @return address
inline uint32_t ElfParser::GetSymbolAddrByName(const char* name)
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


/// @brief Get section data
/// @param index 
/// @return address
inline ElfParser::SectionData ElfParser::GetSectionData(uint32_t index)
{
	return SectionData(elf.map + elf.sections[index].offset);
}



/// @brief Parser elf
/// @return result
int ElfParser::ParserElf()
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
	if (elf.header->version  != _ELF_Ver_Current) return _ERR;
#if defined(ARCH_X86)
	if (elf.header->machine  != _ELF_Machine_X86) return _ERR;
#elif defined(ARCH_ARM)
	if (elf.header->machine  != _ELF_Machine_ARM) return _ERR;
#endif
	if (elf.header->type     == _ELF_Type_None  ) return _ERR;

	//Set executable load address and entry
	switch (elf.header->type)
	{
		case _ELF_Type_Rel:
			elf.laddr = 0;
			elf.exec = elf.map + elf.header->elfHeaderSize + elf.header->entry;
			break;
		case _ELF_Type_Exec:
			elf.laddr = 0;
			elf.exec = elf.header->entry;
			break;
		case _ELF_Type_Dyn:
			elf.laddr = load_address;
			elf.exec = elf.laddr + elf.header->entry;
			break;
		default: break;
	}

	//Get program headers pointer
	elf.programs = (ProgramHeader*)(elf.map + elf.header->programHeaderOffset);

	//Get section headers pointer
	elf.sections = (SectionHeader*)(elf.map + elf.header->sectionHeaderOffset);

	//Get section string table pointer
	elf.shstrtab = GetSectionData(elf.header->sectionHeaderStringTableIndex).shstrtab;

	//Get some information of elf
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		SectionData data = GetSectionData(i);

		//Set dynsym pointer
		if (_SHT_DYNSYM == elf.sections[i].type)
		{
			elf.dynsym = data.dynsym;
			elf.dynsymNum = elf.sections[i].size / sizeof(SymbolEntry);
		}
		//Set dynamic section pointer
		if (_SHT_DYNAMIC == elf.sections[i].type)
		{
			elf.dynamics = data.dynamic;
		}
		//Set symbol tables pointer
		else if (_SHT_SYMTAB == elf.sections[i].type)
		{
			elf.symtab = data.symtab;
			elf.symtabNum = elf.sections[i].size / sizeof(SymbolEntry);
		}
		//Set section header string table and symbol string talbe pointer
		else if (_SHT_STRTAB == elf.sections[i].type)
		{
			if (0 == strcmp(".dynstr", GetSectionName(i)))
				elf.dynstr = data.dynstr;
			else if (0 == strcmp(".strtab", GetSectionName(i)))
				elf.strtab = data.strtab;
		}
	}

	console.info("Parser elf successful");
	return _OK;
}


/// @brief Relocation symbol entries
/// @return result
int ElfParser::RelEntries()
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
				uint32_t relAddr = GetSectionData(i - 1).addr + relEntry.offset;
				uint32_t symAddr = 0;

				//Calculate new symbol entry addr
				if (symEntry.shndx)
				{
					//Calculate the address of defined symbol entry
					symAddr = GetSectionData(symEntry.shndx).addr + symEntry.value;
				}
				else
				{
					//Get the address of undefined symbol entry
					symAddr = SEARCH_SYMBOL(GetSymbolName(relEntry.symbol));
				}

				//Return when symAddr is 0
				if (0 == symAddr) 
				{
					console.error("Err: count not relocation %s.", GetSymbolName(relEntry.symbol));
					console.error("Relocation elf failed");
					return _ERR;
				}

				//Relocation symbol entry
				RelSymCall(relAddr, symAddr, relEntry.type);

				//Output debug message
				console.log("rel name %s, relAddr 0x%lx, symAddr 0x%lx", 
					GetSymbolName(relEntry.symbol), relAddr, symAddr);
			}
		}
	}

	console.info("Relocation elf successful");
	return _OK;
}

#if defined(ARCH_X86)

/// @brief Relocation symbol call
/// @param relAddr 
/// @param symAddr 
/// @param type 
/// @return result
int ElfParser::RelSymCall(uint32_t relAddr, uint32_t symAddr, int type)
{
	switch (type)
	{
		case _R_386_32:
			*((uint32_t*)relAddr) += symAddr;
			break;

		case _R_386_PC32:
			*((uint32_t*)relAddr) += (symAddr - relAddr);
			break;
			
		case _R_386_GLOB_DAT:
			*((uint32_t*)relAddr) = symAddr;
			break;

		case _R_386_JMP_SLOT:
			*((uint32_t*)relAddr) = symAddr;
			break;

		default: return 0;
	}
	return 0;
}


/// @brief Relocation thumb jump call 
/// @param relAddr 
/// @param symAddr 
/// @param type 
/// @return address
int ElfParser::RelJumpCall(uint32_t relAddr, uint32_t symAddr, int type)
{
	return 0;
}

#elif defined(ARCH_ARM)

/// @brief Relocation symbol call
/// @param relAddr 
/// @param symAddr 
/// @param type 
/// @return address
int ElfParser::RelSymCall(uint32_t relAddr, uint32_t symAddr, int type)
{
	switch (type)
	{
		case _R_ARM_ABS32:
			*((uint32_t*)relAddr) += symAddr;
			break;

		case _R_ARM_THM_CALL:
		case _R_ARM_THM_JUMP24:
			RelJumpCall(relAddr, symAddr, type);
			break;

		case _R_ARM_TARGET1:
			*((uint32_t*)relAddr) += symAddr;
			break;

		case _R_ARM_THM_JUMP11:
			break;
			
		default: return 0;
	}
	return 0;
}


/// @brief Relocation thumb jump call 
/// @param relAddr 
/// @param symAddr 
/// @param type 
/// @return result
int ElfParser::RelJumpCall(uint32_t relAddr, uint32_t symAddr, int type)
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

#endif


/// @brief Load executable to RAM
/// @return result
int ElfParser::CopyToRAM()
{
	if (0 == elf.header->programHeaderNum) return _ERR;

	for (uint32_t i = 0; i < elf.header->programHeaderNum; i++)
	{
		ProgramHeader program = elf.programs[i];

		if (_PT_LOAD == program.type)
		{
			uint8_t* vaddr = (uint8_t*)(elf.laddr + program.vaddr);
			uint8_t* code  = (uint8_t*)(elf.map + program.offset);

			for (uint32_t size = 0; size < program.memSize; size++)
			{
				vaddr[size] = code[size];
			}
		}
	}

	console.info("Load executable successful");

	return _OK;
}


/// @brief ElfParser init array
/// @return result
int ElfParser::InitArray()
{
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		if (0 == strcmp(".init_array", GetSectionName(i)))
		{
			//Get init array
			Function* funcs = GetSectionData(i).funcs;

			//Calculate the size of init array
			uint32_t size = elf.sections[i].size / sizeof(Function);

			//Execute init array
			for (uint32_t i = 0; i < size; i++)
			{
				(funcs[i])();
			}

			break;
		}
	}
	return _OK;
}


/// @brief ElfParser execute symbol
/// @param symbol 
/// @return result
int ElfParser::Execute(const char* symbol)
{
	if (NULL == symbol && 0 != elf.exec)
	{
		((Function)elf.exec)();
		return _OK;
	}
	else
	{
		uint32_t symbolAddr = GetSymbolAddrByName(symbol);
		
		if (symbolAddr)
		{
			((Function)symbolAddr)();
			return _OK;
		}
	}
	return _ERR;
}


/// @brief ElfParser fini array
/// @return result
int ElfParser::FiniArray()
{
	for (uint32_t i = 0; i < elf.header->sectionHeaderNum; i++)
	{
		if (0 == strcmp(".fini_array", GetSectionName(i)))
		{
			//Get fini array
			Function* funcs = GetSectionData(i).funcs;

			//Calculate the size of fini array
			uint32_t size = elf.sections[i].size / sizeof(Function);

			//Execute fini array
			for (uint32_t i = 0; i < size; i++)
			{
				(funcs[i])();
			}

			break;
		}
	}
	return _OK;
}


/// @brief ElfParser exit
/// @return result
int ElfParser::Exit()
{
	delete[] (uint8_t*)elf.map;
	return _OK;
}
