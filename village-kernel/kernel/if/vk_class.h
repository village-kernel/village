//###########################################################################
// vk_class.h
// Declarations of the class
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_CLASS_H__
#define __VK_CLASS_H__

#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"


/// @brief Base
class Base
{
private:
    //Members
    int   id;
    char* name;
    void* data;
public:
    //Constructor
    Base(): id(-1), name((char*)"Unknown"), data(NULL) {}

    //Destructor
    virtual ~Base() {}

    //Methods
    virtual void SetID(int id)         { this->id = id;     }
    virtual int  GetID()               { return this->id;   }
    virtual void SetName(char* name)   { this->name = name; }
    virtual char* GetName()            { return this->name; }
    virtual void SetData(void* data)   { this->data = data; }
    virtual void* GetData()            { return this->data; }
};


/// @brief Class
class Class {};
typedef void (Class::*Method)(void*);
typedef void (*Function)(void*, void*);

#endif //!__VK_CLASS_H__
