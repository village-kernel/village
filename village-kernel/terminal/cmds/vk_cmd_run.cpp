//###########################################################################
// vk_cmd_run.cpp
// Definitions of the functions that manage command Run
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"
#include "string.h"


///CmdRun
class CmdRun : public Cmd
{
public:
    /// @brief Cmd Run execute
    void Execute(int argc, char* argv[])
    {
        if (argc < 2)
        {
            console->Println("Usage: run <program> [arg1] [arg2] [...] [&]");
            return;
        }

        Process::Behavior behavior = Process::_Foreground;

        if (0 == strcmp(argv[argc - 1], "&"))
        {
            behavior = Process::_Background;
        }

        kernel->process.Run(behavior, argv[1], argc - 1, argv + 1);
    }


    /// @brief Cmd run help
    void Help()
    {
        console->Println("cmd run: execute application");
    }
};


///Register cmd
REGISTER_CMD(new CmdRun(), run);
