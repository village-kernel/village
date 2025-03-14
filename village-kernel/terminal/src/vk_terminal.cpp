//###########################################################################
// vk_terminal.cpp
// Definitions of the functions that manage terminal
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_terminal.h"
#include "string.h"


/// @brief Terminal Constructor
ConcreteTerminal::ConcreteTerminal()
{
}


/// @brief Terminal Destructor
ConcreteTerminal::~ConcreteTerminal()
{
}


/// @brief Terminal Setup
void ConcreteTerminal::Setup()
{
    //Create terminal execute
    kernel->thread.CreateTask("Terminal::Execute", (Method)&ConcreteTerminal::Execute, this);

    //Output debug info
    kernel->debug.Info("Terminal setup done!");
}


/// @brief Terminal Execute
void ConcreteTerminal::Execute()
{
    DevStream serial;
    
    //Open serial
    if (serial.Open("serial0", FileMode::_ReadWrite))
    {
        const char* msg = "\r\nPlease press Enter to activate this console.\r\n";
        const int   msglen = strlen(msg);

        //Output msg
        while (msglen != serial.Write((char*)msg, msglen)) {}

        //Wait for Enter
        char key = 0; do { serial.Read((char*)&key, 1); } while (0x0d != key);

        //Close serial
        serial.Close();

        //Create the default console
        CreateConsole("serial0");
    }
}


/// @brief Terminal Exit
void ConcreteTerminal::Exit()
{
    cmds.Release();
    sandboxes.Release();
}


/// @brief Register cmd object
/// @param cmd console command pointer
/// @param name console command name
void ConcreteTerminal::RegisterCmd(Cmd* cmd, char* name)
{
    cmds.Insert(cmd, name);
}


/// @brief Unregister cmd object
/// @param cmd console command pointer
/// @param name console command name 
void ConcreteTerminal::UnregisterCmd(Cmd* cmd, char* name)
{
    cmds.Remove(cmd, name);
}


/// @brief Terminal get cmds
/// @return 
VkList<Cmd*> ConcreteTerminal::GetCmds()
{
    return cmds;
}


/// @brief Terminal thread name
/// @param driver 
/// @return 
char* ConcreteTerminal::ThreadName(const char* driver)
{
    const char* prefix = "Console::";
    char* name = new char[strlen(prefix) + strlen(driver) + 1]();
    strcpy(name, prefix);
    strcat(name, driver);
    return name;
}


/// @brief Terminal CreateConsole
/// @param driver 
/// @return 
int ConcreteTerminal::CreateConsole(const char* driver)
{
    Sandbox* sandbox = NULL;

    //Create sandbox object
    if ((sandbox = new Sandbox((char*)driver)) == NULL)
    {
        return -1;
    }

    //Create console object
    if ((sandbox->console = new Console()) == NULL)
    {
        delete sandbox;
        return -1;
    }

    //Add to sandboxes list
    if ((sandbox->cid = sandboxes.Add(sandbox, (char*)driver)) < 0)
    {
        delete sandbox;
        return -1;
    }

    //Create thread task
    sandbox->tid = kernel->thread.CreateTask
    (
        ThreadName(driver), (Method)&ConcreteTerminal::ConsoleSandbox, this, sandbox
    );

    //Start console task
    kernel->thread.StartTask(sandbox->tid);

    return sandbox->cid;
}


/// @brief Terminal DestroyConsole
/// @param driver 
bool ConcreteTerminal::DestroyConsole(const char* driver)
{
    Sandbox* sandbox = sandboxes.GetItem(driver);

    if (NULL != sandbox)
    {
        kernel->thread.StopTask(sandbox->tid);
        kernel->thread.DeleteTask(sandbox->tid);
        return sandboxes.Remove(sandbox);
    }

    return true;
}


/// @brief Terminal console sandbox
void ConcreteTerminal::ConsoleSandbox(Sandbox* sandbox)
{
    if (NULL != sandbox)
    {
        sandbox->console->Setup(sandbox->driver);
        sandbox->console->Execute();
        sandbox->console->Exit();
        sandboxes.Remove(sandbox);
    }
}


/// @brief Terminal get sandboxes
/// @return 
VkList<Terminal::Sandbox*> ConcreteTerminal::GetSandboxes()
{
    return sandboxes;
}
