#ifndef LOGICSIMULATOR_H
#define LOGICSIMULATOR_H

#include "Device.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cmath>
#include <bitset>

using namespace std;

class LogicSimulator{
public:
    LogicSimulator();
    ~LogicSimulator();
    vector<int> getSimulationResult(const vector<int>&);
    vector<vector<int>> getTruthTable();
    int get_iPin_size() const;
    int get_oPin_size() const;
    bool load(const string&);
    

private:
    vector<Device *> circuit;
    vector<Device *> iPins;
    vector<Device *> oPins;
};

#endif