//###########################################################################
// Application1.h
// The overall framework of the program
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __APPLICATION1_H__
#define __APPLICATION1_H__

#include "Module.h"
#include "Gpo.h"


///Application
class Application1 : public Module
{
private:
    Gpo led;
public:
    //Methods
    Application1();
    void Initialize();
    void Execute();
};

#endif //!__APPLICATION1_H__
