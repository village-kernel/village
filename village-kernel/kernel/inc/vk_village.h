//###########################################################################
// vk_village.h
// Declarations of the functions that manage village
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_VILLAGE_H__
#define __VK_VILLAGE_H__

#include "vk_kernel.h"
#include "vk_system.h"
#include "vk_memory.h"
#include "vk_debug.h"
#include "vk_interrupt.h"
#include "vk_scheduler.h"
#include "vk_thread.h"
#include "vk_workqueue.h"
#include "vk_event.h"
#include "vk_symbol.h"
#include "vk_device.h"
#include "vk_feature.h"
#include "vk_filesystem.h"
#include "vk_loader.h"
#include "vk_process.h"
#include "vk_timer.h"
#include "vk_terminal.h"
#include "vk_signal.h"
#include "vk_protocol.h"


/// @brief Village
class Village : public Kernel
{
private:
    /// @brief Members
    ConcreteSystem      concreteSystem;
    ConcreteMemory      concreteMemory;
    ConcreteDebug       concreteDebug;
    ConcreteInterrupt   concreteInterrupt;
    ConcreteScheduler   concreteScheduler;
    ConcreteThread      concreteThread;
    ConcreteWorkQueue   concreteWorkQueue;
    ConcreteEvent       concreteEvent;
    ConcreteSymbol      concreteSymbol;
    ConcreteDevice      concreteDevice;
    ConcreteFeature     concreteFeature;
    ConcreteFileSystem  concreteFilesys;
    ConcreteLoader      concreteLoader;
    ConcreteProcess     concreteProcess;
    ConcreteTimer       concreteTimer;
    ConcreteTerminal    concreteTerminal;
    ConcreteSignal      concreteSignal;
    ConcreteProtocol    concreteProtocol;
private:
    /// @brief Methods
    Village();
    ~Village();
public:
    /// @brief Kernel Methods
    void Setup();
    void Start();
    void Exit();

    /// @brief Power Methods
    void Sleep();
    void Standby();
    void Shutdown();
    void Reboot();

    /// @brief Kernel build info 
    const char* GetBuildDate();
    const char* GetBuildTime();
    const char* GetBuildVersion();
    const char* GetBuildGitCommit();

    /// @brief Static methods
    static Village& Instance();
};

#endif // !__VK_VILLAGE_H__
