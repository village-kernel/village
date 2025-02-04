//###########################################################################
// vk_event.h
// Declarations of the functions that manage event
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_EVENT_H__
#define __VK_EVENT_H__

#include "vk_observer.h"
#include "vk_dev_stream.h"
#include "vk_kernel.h"
#include "vk_list.h"
#include "vk_cast.h"


/// @brief ConcreteEvent
class ConcreteEvent : public Event
{
private:
    /// @brief Input members
    InputKey     inputKey;
    InputAxis    inputAxis;
    
    /// @brief Output members
    OutputText   outputText;
    OutputAxis   outputAxis;
    OutFormat    outFormat;

    /// @brief Model members
    VkList<DevStream*> inDevs;
    ObserverModel observers[_AllType];
public:
    /// @brief Methods
    ConcreteEvent();
    ~ConcreteEvent();
    void Setup();
    void Exit();

    /// @brief Device Methods
    void InitInputDevice(const char* input);
    void ExitInputDevice(const char* input);

    /// @brief Attach Methods
    void Attach(EventType type, Method method, Class* user);
    void Attach(EventType type, Function func, void* user = NULL);
    void Detach(EventType type, Method method, Class* user);
    void Detach(EventType type, Function func, void* user = NULL);
    
    /// @brief Input Methods
    void ReportKey(int code, int status);
    void ReportAxis(int axisX, int axisY, int axisZ);

    /// @brief Output Methods
    void PushChar(char chr);
    void PushString(char* data, int size);
    void PushAxis(int axisX, int axisY, int axisZ);
    void SetOutFormat(OutFormat format);
    OutFormat GetOutFormat();
};

#endif //!__VK_EVENT_H__
