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
    void out_table(const vector<int>&) const;
    void getSimulationResult(const vector<int>&);
    void getTruthTable();
    int get_iPin_size() const;
    bool load(const string&);
    

private:
    vector<Device *> circuit;
    vector<Device *> iPins;
    vector<Device *> oPins;
};

#endif