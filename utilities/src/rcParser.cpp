//###########################################################################
// rcParser.cpp
// Parse resource script
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "rcParser.h"
#include "Memory.h"
#include "FileStream.h"


///Constructor
RcParser::RcParser(const char* filename)
	: runcmds(NULL)
{
	if (NULL != filename) Load(filename);
}


///Load file
int RcParser::Load(const char* filename)
{
	FileStream file;
	Result res = _ERR;

	if (FR_OK == file.Open(filename, FileStream::_Read))
	{
		int size = file.Size();

		const char* text = (const char*)Memory::HeapAlloc(size); 

		if (file.Read((uint8_t*)text, size) == size)
		{
			Decode(text);
			res = _OK;
		}
		
		file.Close();
		
		Memory::Free((uint32_t)text);
	}

	return res;
}


///Decode the rc data
void RcParser::Decode(const char* rcString)
{
	RunCmdNode** nextNode = &runcmds;
	ParserStatus status = _RecordCmd;
	int32_t startIndex = 0;
	int32_t recordBytes = 0;
	
	for (int32_t i = 0; rcString[i] != '\0'; i++)
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
					if (0 == startIndex) startIndex = i;
					if (byte > ' ' && byte <= '~') recordBytes++;
				}
				break;
		}

		//Save cmd
		if (_SaveCmd == status)
		{
			char* cmd = (char*)Memory::HeapAlloc(recordBytes + 1);

			if (NULL != cmd)
			{
				//Copy cmd
				for (int32_t j = 0; j < recordBytes; j++)
				{
					cmd[j] = rcString[startIndex + j];
				}
				cmd[recordBytes] = '\0';

				//Add cmd to run cmd list
				*nextNode  = new RunCmdNode(cmd);
				nextNode   = &(*nextNode)->next;
				status     = _RecordCmd;
				startIndex = 0;
			}
			else
			{
				break;
			}
		}
	}
}


///Get run commands
RcParser::RunCmdNode* RcParser::GetRunCmds()
{
	return runcmds;
}


///Release
void RcParser::Release()
{
	for (RunCmdNode* node = runcmds; NULL != node; node = node->next)
	{
		Memory::Free((uint32_t)node->cmd);
		delete node;
	}
}
