//###########################################################################
// vk_cmd_power.cpp
// Definitions of the functions that manage command reboot
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"


/// @brief CmdSleep
class CmdSleep : public Cmd
{
public:
    /// @brief Cmd sleep execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        kernel->Sleep();
    }


    /// @brief Cmd sleep help
    void Help()
    {
        console->Println("cmd sleep: enter sleep mode");
    }
};


/// @brief CmdStandby
class CmdStandby : public Cmd
{
public:
    /// @brief Cmd standby execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        kernel->Standby();
    }


    /// @brief Cmd standby help
    void Help()
    {
        console->Println("cmd standby: enter standby mode");
    }
};


/// @brief CmdShutdown
class CmdShutdown : public Cmd
{
public:
    /// @brief Cmd shutdown execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        kernel->Shutdown();
    }


    /// @brief Cmd shutdown help
    void Help()
    {
        console->Println("cmd shutdown: shutdown device");
    }
};


/// @brief CmdReboot
class CmdReboot : public Cmd
{
public:
    /// @brief Cmd reboot execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        kernel->Reboot();
    }


    /// @brief Cmd reboot help
    void Help()
    {
        console->Println("cmd reboot: reboot device");
    }
};


///Register cmd
REGISTER_CMD(new CmdSleep(),    sleep   );
REGISTER_CMD(new CmdStandby(),  standby );
REGISTER_CMD(new CmdShutdown(), shutdown);
REGISTER_CMD(new CmdReboot(),   reboot  );
