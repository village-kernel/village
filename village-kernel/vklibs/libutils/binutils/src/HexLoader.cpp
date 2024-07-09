//###########################################################################
// HexLoader.cpp
// Definitions of the functions that manage hex loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "HexLoader.h"
#include "FileStream.h"
#include "Kernel.h"
#include "string.h"


/// @brief Constructor
/// @param filename 
HexLoader::HexLoader(const char* filename)
{
	if (NULL != filename) Load(filename);
}


/// @brief Destructor
HexLoader::~HexLoader()
{
	Exit();
}


/// @brief HexLoader load file
/// @param filename 
/// @return result
bool HexLoader::Load(const char* filename)
{
	//Save filename in local
	this->filename = new char[strlen(filename) + 1]();
	strcpy(this->filename, filename);

	//Load and mapping
	if (!LoadHex())     return false;
	if (!PreParser())   return false;
	if (!LoadProgram()) return false;
	if (!PostParser())  return false;
	if (!RelEntries())  return false;

	//Output debug info
	kernel->debug.Output(Debug::_Lv2, "%s load done", filename);
	return true;
}


/// @brief HexLoader load hex file
/// @return 
bool HexLoader::LoadHex()
{
	FileStream file;

	if (file.Open(filename, FileMode::_Read))
	{
		int size = file.Size();
		hex.load = (uint32_t)new char[size]();

		if (hex.load && (file.Read((char*)hex.load, size) == size))
		{
			kernel->debug.Output(Debug::_Lv1, "%s hex file load successful", filename);
			file.Close();
			return true;
		}

		file.Close();
	}

	kernel->debug.Error("%s hex file load failed", filename);
	return false;
}


/// @brief HexStrToInt
/// @param str 
/// @param strend
/// @param size 
/// @return 
uint16_t HexLoader::HexStrToInt(char* str, int size)
{
	uint16_t integer = 0;

	for (int i = 0; i < size; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			integer = integer * 16 + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			integer = integer * 16 + 10 + str[i] - 'A';
		else if (str[i] >= 'a' && str[i] <= 'f')
			integer = integer * 16 + 10 + str[i] - 'a';
		else
			return 0;
	}

	return integer;
}


/// @brief RecordParser
///
/// hex format:              |
/// :llaaaatt[dd...]cc       |    type:
/// [:]     : start flag     |    00 - Data
/// [ll]    : length         |    01 - End Of File
/// [aaaa]  : address        |    02 - Extended Segment Address
/// [tt]    : type           |    03 - Start Segment Address
/// [dd...] : data           |    04 - Extended Linear Address
/// [cc]    : check          |    05 - Start Linear Address
///
/// example:
/// :0C00B400B4000000B4020000760200005E
/// [:]   [0C]   [00 B4] [00] [B4 00 00 00 B4 02 00 00 76 02 00 00] [5E]
/// start length address type data                                  check
///
/// @param text 
/// @return 
HexLoader::Record* HexLoader::RecordParser(char** text)
{
	const int lenPos  = 0, addrPos  = 2, typePos  = 6, dataPos = 8;
	const int lenSize = 2, addrSize = 4, typeSize = 2, crcSize = 2;
	      int crcPos     = 0;

	Record* record  = new Record();
	record->length  = HexStrToInt(*text + lenPos,  lenSize);
	record->address = HexStrToInt(*text + addrPos, addrSize);
	record->type    = HexStrToInt(*text + typePos, typeSize);
	record->data    = *text + dataPos;
	crcPos          = dataPos + record->length * 2;
	record->crc     = HexStrToInt(*text + crcPos, crcSize);
	*text           = *text + crcPos + crcSize;

	return record;
}


/// @brief PreParser
/// @return 
bool HexLoader::PreParser()
{
	uint32_t segment = 0;
	uint32_t mapSize = 0;
	char*    text = (char*)hex.load;
	
	while (1)
	{
		while (':' != *(text++)) {}

		Record* record = RecordParser(&text);

		records.Add(record);

		if (HexLoader::_Data == record->type)
		{
			mapSize = segment + record->address + record->length;
		}
		else if (HexLoader::_ExtSegAddr == record->type)
		{
			segment += HexStrToInt(record->data, 4) * 0x10;
		}
		else if (HexLoader::_EndOfFile == record->type)
		{
			hex.offset  = records.Begin()->address;
			mapSize     = mapSize - hex.offset;
			hex.map     = (uint32_t)new char[mapSize]();
			break;
		}
	}

	return true;
}


/// @brief LoadProgram
/// @return 
bool HexLoader::LoadProgram()
{
	uint32_t segment = 0;

	for (records.Begin(); !records.IsEnd(); records.Next())
	{
		Record* record = records.Item();

		if (HexLoader::_Data == record->type)
		{
			for (uint8_t pos = 0; pos < record->length; pos++)
			{
				uint32_t address = record->address - hex.offset + segment + pos;
				((uint8_t*)hex.map)[address] = HexStrToInt(record->data + pos * 2, 2);
			}
		}
		else if (HexLoader::_ExtSegAddr == record->type)
		{
			segment += HexStrToInt(record->data, 4) * 0x10;
		}
	}

	return true;
}


/// @brief PostParser
/// @return 
bool HexLoader::PostParser()
{
	hex.offset  = *(((uint32_t*)hex.map) + 0);
	hex.dynamic = *(((uint32_t*)hex.map) + 1);
	hex.entry   = *(((uint32_t*)hex.map) + 2);
	hex.exec    = hex.map + hex.entry - hex.offset;
	return true;
}


/// @brief RelEntries
/// @return
bool HexLoader::RelEntries()
{
	uint32_t   imagebase = 0;
	uint32_t   relcount = 0;
	uint32_t*  relAddr = NULL;
	DynamicHeader* dynamic = NULL;
	RelocationEntry* relocate = NULL;
	
	//Calc the imagebase value
	imagebase = hex.map - hex.offset;

	//Calc the dynamic address
	dynamic = (DynamicHeader*)(imagebase + hex.dynamic);

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


/// @brief HexLoader execute
/// @param argc 
/// @param argv 
/// @return 
bool HexLoader::Execute(int argc, char* argv[])
{
	if (0 != hex.exec)
	{
		((StartEntry)hex.exec)(kernel, argc, argv);
		return true;
	}
	kernel->debug.Error("%s execute failed!", filename);
	return false;
}


/// @brief HexLoader exit
/// @return result
bool HexLoader::Exit()
{
	delete[] filename;
	delete[] (char*)hex.load;
	delete[] (char*)hex.map;
	records.Release();
	return true;
}
