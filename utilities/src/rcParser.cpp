//###########################################################################
// rcParser.cpp
// Parse resource script
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "rcParser.h"
#include "FileStream.h"


///Load file
int RcParser::Load(std::string filePath)
{
	FileStream file;
	Result res = _ERR;

	if (FR_OK == file.Open(filePath, FileStream::_Read))
	{
		int size = file.Size();

		std::string str; str.resize(size);

		if (file.Read((uint8_t*)str.c_str(), size) == size)
		{
			Decode(str);
			res = _OK;
		}
		
		file.Close();
		std::string().swap(str);
	}

	return res;
}


///Decode the rc data
void RcParser::Decode(std::string rcString)
{
	std::string resource = "";
	std::string::iterator it;
	ParserStatus status = _RecordResource;

	for (it = rcString.begin(); it != rcString.end(); it++)
	{
		char byte = *it;

		switch (byte)
		{
			case '#':
				status = _NullRecord;
				break;
			
			case ' ':
			case '\n':
				status = _SaveResource;
				break;

			default:
				if (byte > ' ' && byte <= '~')
				{
					if (_RecordResource == status)
						resource += byte;
				}
				break;
		}

		//Save rerourece path
		if (_SaveResource == status)
		{
			if (resource != "")
			{
				resources.push_front(resource);
				resource = "";
			}
			status = _RecordResource;
		}
	}
}


///Get resources
std::list<std::string> RcParser::GetResources()
{
	return resources;
}


///Release
void RcParser::Release()
{
	resources.clear();
	std::list<std::string>().swap(resources);
}
