//###########################################################################
// vk_cmd_kill.cpp
// Definitions of the functions that manage command kill
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"
#include "string.h"
#include "stdlib.h"


/// @brief CmdKill
class CmdKill : public Cmd
{
public:
    /// @brief Cmd kill execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        if (argc >= 2)
        {
            if (0 == strcmp("-p", argv[1]))
            {
                kernel->process.Kill(atoi(argv[2]));
            }
            else if (0 == strcmp("-t", argv[1]))
            {
                kernel->thread.DeleteTask(atoi(argv[2]));
            }
        }
        else
        {
            console->Println("Usage: ");
            console->Println("kill -p <pid>");
            console->Println("kill -t <tid>");
        }
    }


    /// @brief Cmd kill help
    void Help()
    {
        console->Println("cmd kill: kill process");
    }
};


///Register cmd
REGISTER_CMD(new CmdKill(), kill);
