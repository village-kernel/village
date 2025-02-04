//###########################################################################
// vk_rc_parser.h
// Parse run command script
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_RC_PARSER_H__
#define __VK_RC_PARSER_H__

#include "vk_defines.h"
#include "vk_list.h"


///RcParser
class RcParser
{
private:
    //Enumerations
    enum ParserStatus
    {
        _NotRecord = 0,
        _RecordCmd,
        _SaveCmd,
    };

    //Members
    VkList<char*> runcmds;

    //Methods
    void Decode(const char* rcString, int size);
public:
    //Methods
    RcParser(const char* filename = NULL);
    bool Load(const char* filename);
    VkList<char*>& GetRunCmds();
    void Release();
};

#endif //!__VK_RC_PARSER_H__
