//###########################################################################
// Application.h
// The overall framework of the program
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Module.h"
#include "Gpo.h"

///Application
class Application : public Module
{
private:
    Gpo led;
public:
    //Methods
    Application();
    void Initialize();
    void Execute();
};

#endif //!__APPLICATION_H__
