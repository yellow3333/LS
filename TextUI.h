#ifndef TEXTUI_H
#define TEXTUI_H

#include "LogicSimulator.h"
#include <vector>
#include <iostream>
#include <cstdlib>

class TextUI{
public:
    bool displayMenu();
    bool processCommand();
private:
    bool loadCompleted = false;
    LogicSimulator *ls = new LogicSimulator;
};

#endif