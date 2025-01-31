//###########################################################################
// vk_signals.h
// Declarations of the interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SIGNALS_H__
#define __VK_SIGNALS_H__

enum Signals
{
    _None = 0,
    
    _Sleep,
    _Standby,
    _Shutdown,
    _Reboot,

    _Kill,
};

#endif //!__VK_SIGNALS_H__
