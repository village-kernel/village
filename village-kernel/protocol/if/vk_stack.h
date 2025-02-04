//###########################################################################
// vk_stack.h
// Specifies the interface for all classes that contain stack logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_STACK_INTERFACE_H__
#define __VK_STACK_INTERFACE_H__

#include "vk_defines.h"
#include "vk_class.h"
#include "vk_protdefs.h"


/// @brief Stack
class Stack : public Base, public Class
{
public:
    //Constructor
    Stack() { }

    //Destructor
    virtual ~Stack() { }

    //Methods
    virtual void Setup() = 0;
    virtual void Exit()  = 0;
};

#endif // !__VK_STACK_INTERFACE_H__
