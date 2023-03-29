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

		char* text = (char*)malloc(size); 

		if (file.Read((uint8_t*)text, size) == size)
		{
			Decode(text);
			res = _OK;
		}
		
		file.Close();
		
		free(text);
	}

	return res;
}


///Decode the rc data
void RcParser::Decode(char* rcString)
{
	std::string  cmd = "";
	RunCmdNode** nextNode = &runcmds;
	ParserStatus status   = _RecordCmd;
	
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
					if (byte > ' ' && byte <= '~') cmd += byte;
				}
				break;
		}

		//Save cmd
		if (_SaveCmd == status)
		{
			if (cmd != "")
			{
				*nextNode = new RunCmdNode(cmd);
				nextNode  = &(*nextNode)->next;
				cmd = "";
			}
			status = _RecordCmd;
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
		delete node;
	}
}
