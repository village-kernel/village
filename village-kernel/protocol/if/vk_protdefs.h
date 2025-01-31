//###########################################################################
// vk_protdefs.h
// Declarations of the interface protocol
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_PROTOCOL_DEFINES_H__
#define __VK_PROTOCOL_DEFINES_H__

#include "stddef.h"
#include "stdint.h"


///Protocol stack register macro
#define REGISTER_PROTOCOL_STACK(stack, name)                     \
static struct _Stack_##name {                                    \
    Stack* _stack = stack;                                       \
    _Stack_##name() {                                            \
        _stack->SetName((char*)#name);                           \
        kernel->protocol.RegisterStack(_stack);                  \
    }                                                            \
    ~_Stack_##name() {                                           \
        kernel->protocol.UnregisterStack(_stack);                \
    }                                                            \
} const _stack_##name __attribute__((used,__section__(".stack")))


#endif //!__VK_PROTOCOL_DEFINES_H__
