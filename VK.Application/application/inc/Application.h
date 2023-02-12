//###########################################################################
// Application.h
// The overall framework of the program
//
// $Copyright: Copyright (C) jingwei
//###########################################################################
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Module.h"

///Application
class Application : public Module
{
private:

public:
    //Methods
    Application();
    void Initialize();
    void Execute();
};

#endif //!__APPLICATION_H__
