//###########################################################################
// rcParser.cpp
// Parse resource script
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "rcParser.h"
#include "FileStream.h"


///Constructor
RcParser::RcParser(const char* filename)
{
	if (NULL != filename) Load(filename);
}


///Load file
int RcParser::Load(const char* filename)
{
	FileStream file;
	Result res = _ERR;

	if (_OK == file.Open(filename, FileMode::_Read))
	{
		int size = file.Size();

		const char* text = new const char[size]();

		if (file.Read((char*)text, size) == size)
		{
			Decode(text);
			res = _OK;
		}
		
		file.Close();
		
		delete[] text;
	}

	return res;
}


///Decode the rc data
void RcParser::Decode(const char* rcString)
{
	const int32_t start_delimiter= -1;

	ParserStatus status = _RecordCmd;
	int32_t startIndex  = start_delimiter;
	int32_t recordBytes = 0;
	
	for (int32_t i = 0; ; i++)
	{
		char byte = rcString[i];

		switch (byte)
		{
			case '#':
				status = _NotRecord;
				break;
			
			case ' ':
				if (_RecordCmd == status)
					status = _SaveCmd;
				break;

			case '\r':
				continue;

			case '\n':
				if (_RecordCmd == status)
					status = _SaveCmd;
				else if (_NotRecord == status)
					status = _RecordCmd;
				break;

			default:
				if (_RecordCmd == status)
				{
					if (byte > ' ' && byte <= '~')
					{
						if (start_delimiter == startIndex)
						{
							startIndex = i;
						}
						recordBytes++;
					}
				}
				break;
		}

		//Save cmd
		if ((_SaveCmd == status) && (start_delimiter != startIndex))
		{
			char* cmd = new char[recordBytes + 1]();

			if (NULL != cmd)
			{
				//Copy cmd
				for (int32_t j = 0; j < recordBytes; j++)
				{
					cmd[j] = rcString[startIndex + j];
				}
				cmd[recordBytes] = '\0';

				//Add cmd to run cmd list
				status      = _RecordCmd;
				startIndex  = start_delimiter;
				recordBytes = 0;
				runcmds.Add(cmd);
			}
			else
			{
				break;
			}
		}

		//Ended decode
		if ('\0' == byte) break;
	}
}


///Get run commands
List<char*>& RcParser::GetRunCmds()
{
	return runcmds;
}


///Release
void RcParser::Release()
{
	runcmds.Release();
}
