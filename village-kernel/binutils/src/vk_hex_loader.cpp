//###########################################################################
// vk_hex_loader.cpp
// Definitions of the functions that manage hex loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_hex_loader.h"
#include "vk_file_stream.h"
#include "vk_kernel.h"
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
	if (!Cleanup())     return false;

	//Output debug info
	kernel->debug.Output(Debug::_Lv2, "load at 0x%08x, %s load done", hex.base, filename);
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
		hex.text = (uint32_t)new char[size]();

		if (hex.text && (file.Read((char*)hex.text, size) == size))
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


/// @brief Checksum
/// @param text 
/// @return 
bool HexLoader::Checksum(char* text)
{
	uint8_t pos = 0, sum = 0, crc = 0;

	//Length of the record
	uint8_t len = HexStrToInt(text, 2) + 4;
	
	//Sum of all decoded byte values
	for (pos = 0; pos < len; pos++)
	{
		sum += HexStrToInt(text + pos * 2, 2);
	}
	
	//Two's complement
	sum = ~sum + 1;

	//Crc of the record
	crc = HexStrToInt(text + pos * 2, 2);

	return (sum == crc);
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
HexLoader::Record* HexLoader::DecodeRecord(char* text)
{
	const int lenPos  = 0, addrPos  = 2, typePos  = 6, dataPos = 8;
	const int lenSize = 2, addrSize = 4, typeSize = 2;

	//Check sum
	if (!Checksum(text)) return NULL;

	//Parser the record
	Record* record  = new Record();
	record->length  = HexStrToInt(text + lenPos,  lenSize);
	record->address = HexStrToInt(text + addrPos, addrSize);
	record->type    = HexStrToInt(text + typePos, typeSize);
	record->data    = text + dataPos;

	return record;
}


/// @brief PreParser
/// @return 
bool HexLoader::PreParser()
{
	const uint32_t segbase  = 16;
	const uint32_t constlen = 10;

	uint32_t segment = 0;
	uint32_t loadSize = 0;
	char*    text = (char*)hex.text;
	
	while (1)
	{
		//Loop until text is ":"
		while (':' != *(text++)) {}

		//Decode record
		Record* record = DecodeRecord(text);
		
		//Break when decode failed
		if (NULL == record) break;
		
		//Add record into list
		records.Add(record);
		
		//Calculate load size
		if (HexLoader::_Data == record->type)
		{
			loadSize = segment + record->address + record->length;
		}
		else if (HexLoader::_ExtSegAddr == record->type)
		{
			segment += HexStrToInt(record->data, 4) * segbase;
		}
		else if (HexLoader::_EndOfFile == record->type)
		{
			hex.offset  = records.Begin()->address;
			loadSize    = loadSize - hex.offset;
			hex.load    = (uint32_t)new char[loadSize]();
			return true;
		}

		//Update text with record length
		text += record->length * 2 + constlen;
	}

	kernel->debug.Error("%s hex file pre parser failed", filename);
	return false;
}


/// @brief LoadProgram
/// @return 
bool HexLoader::LoadProgram()
{
	uint8_t* mapping = (uint8_t*)hex.load;
	uint32_t segment = 0;

	for (records.Begin(); !records.IsEnd(); records.Next())
	{
		Record* record = records.Item();

		if (HexLoader::_Data == record->type)
		{
			for (uint8_t pos = 0; pos < record->length; pos++)
			{
				uint32_t addr  = record->address + segment + pos - hex.offset;
				uint32_t value = HexStrToInt(record->data + pos * 2, 2);
				mapping[addr] = value;
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
	hex.offset  = *(((uint32_t*)hex.load) + 0);
	hex.dynamic = *(((uint32_t*)hex.load) + 1);
	hex.entry   = *(((uint32_t*)hex.load) + 2);
	hex.base    = hex.load - hex.offset;
	hex.exec    = hex.base + hex.entry;
	return true;
}


/// @brief RelEntries
/// @return
bool HexLoader::RelEntries()
{
	uint32_t   relcount = 0;
	uint32_t*  relAddr = NULL;
	DynamicHeader* dynamic = NULL;
	RelocationEntry* relocate = NULL;

	//Calc the dynamic address
	dynamic = (DynamicHeader*)(hex.base + hex.dynamic);

	//Gets the relocate section address and the relcount
	for (int i = 0; dynamic[i].tag != _DT_NULL; i++)
	{
		if (_DT_REL == dynamic[i].tag)
		{
			relocate = (RelocationEntry*)(hex.base + dynamic[i].ptr);
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
			relAddr  = (uint32_t*)(hex.base + relocate[i].offset);
			*relAddr = hex.base + *relAddr;
		}
	}

	return true;
}


/// @brief HexLoader clean up
/// @return 
bool HexLoader::Cleanup()
{
	delete[] (char*)hex.text;
	records.Release();
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
		kernel->debug.Output(Debug::_Lv2, "%s exit", filename);
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
	return true;
}
