//###########################################################################
// vk_base_executor.h
// Declarations of the functions that manage base executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_BASE_EXECUTOR_H__
#define __VK_BASE_EXECUTOR_H__

#include "vk_list.h"
#include "vk_regex.h"
#include "vk_kernel.h"


/// @brief BaseExecutor
class BaseExecutor
{
protected:
    //Members
    char*     path;
    int       argc;
    char**    argv;
    int       tid;

    //Methods
    virtual int Initiate() = 0;
    virtual bool Release() = 0;
public:
    //Methods
    BaseExecutor();
    virtual ~BaseExecutor();
    virtual int Run(const char* path, int argc, char* argv[]);
    virtual bool Wait();
    virtual bool Kill();
};

#endif //!__VK_BASE_EXECUTOR_H__
