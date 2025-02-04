//###########################################################################
// vk_observer.cpp
// Definitions of the functions that manage observer model
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_observer.h"


/// @brief Constructor
ObserverModel::ObserverModel()
{
}


/// @brief Desturctor
ObserverModel::~ObserverModel()
{
    observers.Release();
}


/// @brief Attach
/// @param method 
/// @param user 
void ObserverModel::Attach(Method method, Class* user)
{
    Attach(union_cast<Function>(method), (void*)user);
}


/// @brief Attach
/// @param func 
/// @param user 
void ObserverModel::Attach(Function func, void* user)
{
    observers.Add(new Observer(func, user));
}


/// @brief Base detach
/// @param method 
/// @param user 
void ObserverModel::Detach(Method method, Class* user)
{
    Detach(union_cast<Function>(method), (void*)user);
}


/// @brief Detach
/// @param func 
/// @param user 
void ObserverModel::Detach(Function func, void* user)
{
    for (observers.Begin(); !observers.IsEnd(); observers.Next())
    {
        Observer* observer = observers.Item();

        if ((func == observer->func) &&
            (user == observer->user))
        {
            observers.Remove(observer, observers.GetNid());
        }
    }
}


/// @brief Notify
/// @param argv 
void ObserverModel::Notify(void* argv)
{
    for (observers.Begin(); !observers.IsEnd(); observers.Next())
    {
        Observer* observer = observers.Item();
        (observer->func)(observer->user, argv);
    }
}


/// @brief Release
void ObserverModel::Release()
{
    observers.Release();
}
