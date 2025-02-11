#ifndef DEVICE_H
#define DEVICE_H

#include "Device.h"
#include <iostream>
#include <vector>

using namespace std;

class Device{
public:
    Device();
    ~Device();
    void addinputPins(int value);
    void addinputPins(Device *);
    virtual int getOutput() const = 0;
protected :
   vector<Device *> iPins;
   int value;
};

#endif