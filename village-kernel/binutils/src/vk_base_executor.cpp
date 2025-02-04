//###########################################################################
// vk_base_executor.cpp
// Definitions of the functions that manage base executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_base_executor.h"
#include "vk_kernel.h"


/// @brief Constructor
BaseExecutor::BaseExecutor()
    :path(NULL),
    argc(0),
    argv(NULL),
    tid(0)
{
}


/// @brief Destructor
BaseExecutor::~BaseExecutor()
{
}


/// @brief BaseExecutor Run
/// @param path file path
/// @param argc running argc
/// @param argv running argv
/// @return tid
int BaseExecutor::Run(const char* path, int argc, char* argv[])
{
    //Set argc and argv
    this->path = (char*)path;
    this->argc = argc;
    this->argv = argv;
    
    //Load, parser file and create task
    this->tid = Initiate();

    //Start task
    kernel->thread.StartTask(tid);

    return tid;
}


/// @brief BaseExecutor wait
/// @return result
bool BaseExecutor::Wait()
{
    return kernel->thread.WaitForTask(tid);
}


/// @brief BaseExecutor kill
/// @return result
bool BaseExecutor::Kill()
{
    return (kernel->thread.StopTask(tid) && Release());
}
