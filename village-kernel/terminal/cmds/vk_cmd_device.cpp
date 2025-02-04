//###########################################################################
// vk_cmd_device.cpp
// Definitions of the functions that manage command device
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"


/// @brief CmdDevice
class CmdDevice : public Cmd
{
public:
    /// @brief Cmd device execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        for (int id = 0; id <= DriverID::_miscellaneous; id++)
        {
            VkList<Base*> list = kernel->device.GetDevices((DriverID)id);

            for (list.Begin(); !list.IsEnd(); list.Next())
            {
                console->Println("%s ", list.GetName());
            }
        }
    }


    /// @brief Cmd device help
    void Help()
    {
        console->Println("cmd device: display device list");
    }
};


///Register cmd
REGISTER_CMD(new CmdDevice(), device);
