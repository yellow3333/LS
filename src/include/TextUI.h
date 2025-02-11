#ifndef TEXTUI_H
#define TEXTUI_H

#include "LogicSimulator.h"
#include <vector>
#include <iostream>
#include <cstdlib>

class TextUI{
public:
    int inputDigit()const;
    int inputServe(int serve, int iPinID = 0)const;
    void displayMenu()const;
    bool processCommand();
private:
    bool loadCompleted = false;
    LogicSimulator *ls = new LogicSimulator;
};

#endif