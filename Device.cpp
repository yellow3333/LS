#include "Device.h"

using namespace std;

Device::Device(){}

Device::~Device(){
    iPins.clear();
}


void Device::addinputPins(int value) {
    this->value = value; // 設置值
}

void Device::addinputPins(Device * gate){
    iPins.push_back(gate);
    return ;
}


