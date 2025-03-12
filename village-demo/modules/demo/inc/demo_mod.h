//###########################################################################
// demo_mod.h
// Declarations of the demo mod
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEMO_MOD_H__
#define __DEMO_MOD_H__

#include "vk_kernel.h"

/// @brief DemoModule
class DemoModule : public Module
{
public:
    //Methods
    bool Setup();
    void Exit();
};

#endif //!__DEMO_MOD_H__
