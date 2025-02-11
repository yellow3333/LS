#ifndef LOGICSIMULATOR_H
#define LOGICSIMULATOR_H

#include "Device.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cmath>
#include <bitset>

class LogicSimulator{
public:
    LogicSimulator();
    ~LogicSimulator();
    void outTalbeHead()const;
    void outTableItem(const vector<int>&) const;
    void getSimulationResult(const vector<int>&);
    void getTruthTable();
    int getInPinSize();
    bool load(const string&);
    void clearLogic();
    

private:
    vector<Device *> circuit;
    vector<Device *> iPins;
    vector<Device *> oPins;
    int numOfIn, numOfGate, numOfOut;
};

#endif